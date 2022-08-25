/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 22:22:35 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/25 14:10:00 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		//rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		g_manager.exit_code = 1;
	}
}

void	handle_sigint2(int signo)
{
	if (signo == SIGINT)
		ft_putendl_fd("", 1);
}

void	init_signal(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

