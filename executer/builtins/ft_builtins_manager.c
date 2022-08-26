/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_manager.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 11:29:03 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/26 02:29:18 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_builtin(t_mshl *data, int num_cmd)
{
	char	*cmd;

	cmd = data->cmd[i].cmd;
	if (!ft_strncmp(cmd, "cd", 2))
		return (1);
	if (!ft_strncmp(cmd, "echo", 4))
		return (1);
	if (!ft_strncmp(cmd, "env", 3))
		return (1);
	if (!ft_strncmp(cmd, "export", 6))
		return (1);
	if (!ft_strncmp(cmd, "unset", 5))
		return (1);
	if (!ft_strncmp(cmd, "pwd", 3))
		return (1);
	if (!ft_strncmp(cmd, "exit", 4))
		return (1);
	return (0);
}

int exec_builtins(t_mshl cmnd, int i)
{
	char	*cmd;
	char	**av;

	cmd = cmnd.cmd[i].cmd;
	av = cmnd.cmd[i].arguments;
	if (!ft_strncmp(cmd, "cd", 2))
		return (ft_cd(av));
	if (!ft_strncmp(cmd, "echo", 4))
		return (ft_echo(av));
	if (!ft_strncmp(cmd, "env", 3))
		return (ft_env(av));
	if (!ft_strncmp(cmd, "export", 6))
	 	return (ft_export(av));
	if (!ft_strncmp(cmd, "exit", 4))
		return (ft_exit(av));
	if (!ft_strncmp(cmd, "pwd", 3))
		return (ft_pwd(av));
	if (!ft_strncmp(cmd, "unset", 5))
		return (ft_unset(av));
	return (EXIT_FAILURE);
}