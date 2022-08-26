/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:27:18 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/26 15:14:59 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_shell *data)
{
	int	nbr;

	nbr = ft_atoi(ft_getenv(data->head_env, "?"));
	if (data->head_env)
		ft_free_env(&data->head_env);
	if (data->cmd && data->count_cmd > 0)
		free_shell(data);
	exit(nbr);
}

static void	ft_main_exit(char *str, t_shell *data)
{
	ft_putstr_fd("exit\n", 1);
	free(str);
	ft_exit(data);
}

void	ft_run_prompt(t_shell *data)
{
	char	*str;

	while (1)
	{
		set_input_signals();
		str = readline("not-bash> ");
		signal(SIGINT, &signal_handler2);
		if (!str)
			ft_main_exit(str, data);
		if (ft_strlen(str))
		{
			add_history(str);
			if (!parser(str, data))
			{
				executor(data);
				free_shell(data);
			}
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell		data;

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
