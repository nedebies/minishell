/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:28:29 by nedebies          #+#    #+#             */
/*   Updated: 2022/09/02 16:36:13 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_dup_fd(int i, int **fd, t_shell *data)
{
	if (i != 0)
		dup2(fd[i - 1][0], STDIN_FILENO);
	if (data->cmd[i].in_file)
	{
		dup2(data->cmd[i].in_file, STDIN_FILENO);
		close(data->cmd[i].in_file);
	}
	if (data->cmd[i].out_file)
	{
		dup2(data->cmd[i].out_file, STDOUT_FILENO);
		close(data->cmd[i].out_file);
	}
	if (i != data->count_cmd -1)
		dup2(fd[i][1], STDOUT_FILENO);
	ft_close_fd(fd, data);
}

static char	**ft_get_path(t_shell *data)
{
	char	*tmp;
	char	**path;

	tmp = ft_getenv(data->envp_list, "PATH");
	path = ft_split(tmp, ':');
	return (path);
}

static int	cmd_with_path(t_shell *dt, char **envp, char **path)
{
	int		i;

	i = 0;
	while (i < dt->count_cmd)
	{
		if (!is_builtin(dt, i))
		{
			if (!ft_getenv(dt->envp_list, "PATH"))
			{
				if (access(dt->cmd[i].cmd, X_OK) == 0)
					return (0);
				ft_no_file_dir(-1, dt->cmd[i].cmd);
				dt->exit_code = 127;
				return (-1);
			}
			dt->cmd[i].cmd = join_path(dt->cmd[i].cmd, path, dt);
			if (!dt->cmd[i].cmd)
			{
				ft_free_arr(path);
				ft_free_arr(envp);
				return (-1);
			}
		}
		i++;
	}
	return (0);
}

int	ft_executer(t_shell *data, int ret)
{
	char	**path;
	char	**envp;

	envp = get_envp(data->envp_list);
	path = ft_get_path(data);
	if (!data->cmd[0].cmd)
	{
		ret = ft_redir(&data->cmd[0], data->cmd[0].redir);
		ft_print_error(data, NULL, ret);
	}
	else
	{
		if (cmd_with_path(data, envp, path) == -1)
			return (-1);
		ft_process_manager(data, -1);
	}
	if (path)
		ft_free_arr(path);
	ft_free_arr(envp);
	return (0);
}
