/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:27:18 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/26 03:03:18 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	t_mshl	*cmds;

//	t_cmnd	*cmnd_tab;
// 		cmnd_tab = parse_nopipes(cmd);
	cmds = NULL;
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
			if (parser(str, cmds))
				free(str);
			else
			{
				ft_executer(cmds);
				//free_mshl(cmnd);
			}
		}
	}
	return (EXIT_SUCCESS);
}
