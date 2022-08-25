/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:40:31 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/24 10:07:04 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_env(char **av)
{
	t_env	*ptr;
	ptr = g_manager.env;
	if (*av)
		return (throw_error("env", *av, "No such file or directory"));
	while (ptr)
	{
		if (ptr->value)
		{
			ft_putstr_fd(ptr->name, STDOUT_FILENO);
			write(STDOUT_FILENO, "=", 1);
			ft_putstr_fd(ptr->value, STDOUT_FILENO);
			write(STDOUT_FILENO, "\n", 1);
		}
		ptr = ptr->next;
	}
	return (EXIT_SUCCESS);
}
