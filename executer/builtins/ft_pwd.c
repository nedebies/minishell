/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:36:57 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/24 10:10:42 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(char **av)
{
	char	*cwd;
	if (*av && check_option(*av) == EXIT_FAILURE)
		return (throw_error_usage("pwd", *av));
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (throw_error("pwd", NULL, strerror(errno)));
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(cwd);
	return (EXIT_SUCCESS);
}