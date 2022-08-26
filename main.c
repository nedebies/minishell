/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:27:18 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/26 14:28:58 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_main_exit(char *line_read, t_mshl *data)
{
	ft_putstr_fd("exit\n", 1);
	free(line_read);
	ft_exit(data);
}

void	ft_run_prompt(t_mshl *data)
{
	char	*line_read;

	while (1)
	{
		set_input_signals();
		line_read = readline("\001\033[1;92m\002minishell> \001\033[0m\002");
		signal(SIGINT, &signal_handler2);
		if (!line_read)
			ft_main_exit(line_read, data);
		if (!ft_strlen(line_read))
		{
			free(line_read);
			continue ;
		}
		add_history(line_read);
		if (parser(line_read, data))
		{
			free(line_read);
			continue ;
		}
		executor(data);
		free_mshl(data);
	}
}

void	ft_exit(t_mshl *data)
{
	int	nbr;

	nbr = ft_atoi(ft_getenv(data->head_env, "?"));
	if (data->head_env)
		ft_free_env(&data->head_env);
	if (data->cmd && data->count_cmd > 0)
		free_mshl(data);
	exit(nbr);
}

int	main(int ac, char **av, char **envp)
{
	t_mshl		data;

	(void)ac;
	(void)av;
	data.head_env = ft_init_env(envp);
	if (!data.head_env)
		return (0);
	rl_catch_signals = 0;
	ft_putenv(&data.head_env, "?", "0");
	ft_run_prompt(&data);
	return (0);
}
