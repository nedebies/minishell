/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:27:18 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/25 12:00:48 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_manager		g_manager; //variable globale pas convaincu atm !

void	ft_free_llist(t_cmnd *data)
{
	t_cmnd	*tmp;

	tmp = data;
	while (tmp->next != NULL)
	{
		free(tmp);
	}
	free(data);
}

char	**ft_free_split(char **split)
{
	size_t i;
	i = 0;

	if (*split)
	{
		while (split[i] != 0)
			i++;
		while (i != 0)
			free(split[--i]);
		free(split);
	}
	return (0);
}

static void	init_manager(char *command_line)
{
	g_manager.command_line = command_line;
	g_manager.rc = 0;
	g_manager.quote_error = 0;
}

static void exit_main(char *str)
{
	if (!str)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		free(str);
		exit(EXIT_SUCCESS);
	}
}

static void	init_env(int ac, char **av, char **envp)
{
	if (ac > 1)
		throw_error_exit(av[1], strerror(ENOENT), EXIT_ENOENT);
	while (*envp)
	{
		add_env(get_env_name(*envp), get_env_value(*envp));
		envp++;
	}
}

int main(int ac, char **av, char **envp)
{
	char 	*str;
	char	**cmd;
	t_cmnd	*cmnd;

//	t_cmnd	*cmnd_tab;
// 		cmnd_tab = parse_nopipes(cmd);

	init_env(ac, av, envp);
	while (ac > 0)
	{
		init_signal();
		str = readline("\001\033[1;92m\002not-bash> \001\033[0m\002");
		signal(SIGINT, &handle_sigint2);
		if (!str)
			exit_main(str);
		if (!ft_strlen(str))
			free(str);
		else
		{
			add_history(str);
			init_manager(str);
			if (parser(str, cmnd))
				free(str);
			else
			{
				ft_executor(cmnd);
				free_mshl(cmnd);
			}
		}
	}
	return (EXIT_SUCCESS);
}
