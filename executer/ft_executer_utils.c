/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executer_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 17:52:21 by nedebies          #+#    #+#             */
/*   Updated: 2022/09/02 14:27:38 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_exit_status(int exit_status)
{
	if (WIFEXITED(exit_status))
		exit_status = WEXITSTATUS(exit_status);
	else if (WIFSIGNALED(exit_status))
	{
		if (WTERMSIG(exit_status) == SIGQUIT)
			write(1, "Quit: 3\n", 8);
		exit_status = 128 + WTERMSIG(exit_status);
	}
	return (exit_status);
}

void	ft_free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static char	*error_path(t_shell *dt, char *command, char *tmp, char *cmd)
{
	dt->exit_code = 127;
	ft_putstr_fd("not-bash: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": command not found\n", 2);
	free(command);
	free(tmp);
	free(cmd);
	return (NULL);
}

char	*join_path(char *cmd, char **path, t_shell *dt)
{
	int		i;
	char	*tmp;
	char	*command;

	i = 0;
	if (!cmd)
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (cmd);
	if (access(cmd, F_OK) != 0 && ft_strchr(cmd, '/'))
	{
		ft_no_file_dir(-1, cmd);
		return (NULL);
	}
	if (access(cmd, X_OK) != 0 && access(cmd, F_OK) == 0 && ft_strchr(cmd, '/'))
		return (permission_error(cmd, dt));
	command = ft_strdup(cmd);
	tmp = ft_strjoin("/", cmd);
	free(cmd);
	cmd = ft_strjoin(path[i], tmp);
	while (path[i] && access(cmd, X_OK) != 0)
	{
		free(cmd);
		cmd = ft_strjoin(path[i++], tmp);
	}
	if (path[i] == NULL)
		return (error_path(dt, command, tmp, cmd));
	free(command);
	free(tmp);
	return (cmd);
}

void	ft_close_fd(int *fd[2], t_shell *data)
{
	int	i;

	i = 0;
	while (i < data->count_cmd - 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
	i = 0;
	while (i < data->count_cmd - 1)
		free(fd[i++]);
	free(fd);
}
