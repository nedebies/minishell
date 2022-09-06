/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:28:29 by nedebies          #+#    #+#             */
/*   Updated: 2022/09/06 12:55:53 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_dup_fd(int i, int **fd, t_shell *data)
{
	if (data->cmd[i].out_file)
	{
		dup2(data->cmd[i].out_file, STDOUT_FILENO);
		close(data->cmd[i].out_file);
	}
	else if (i < data->count_cmd - 1)
		dup2(fd[i][1], STDOUT_FILENO);
	if (data->cmd[i].in_file)
	{
		dup2(data->cmd[i].in_file, STDIN_FILENO);
		close(data->cmd[i].in_file);
	}
	else if (i != 0)
		dup2(fd[i - 1][0], STDIN_FILENO);

	ft_close_fd(fd, data, i);
}

static char	**ft_get_path(t_shell *data)
{
	char	*tmp;
	char	**path;

	tmp = ft_getenv(data->envp_list, "PATH");
	path = ft_split(tmp, ':');
	return (path);
}

static int	cmd_with_path(t_shell *dt, char **path)
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
		}
		i++;
	}
	return (0);
}

int	ft_executer(t_shell *data)
{
	pid_t	*id;
	char	**path;
	char	**envp;

	envp = get_envp(data->envp_list);
	path = ft_get_path(data);
	cmd_with_path(data, path);
	id = malloc(sizeof(pid_t) * data->count_cmd);
	if (!id)
		return (-1);
	ft_process_manager(id, data, envp, -1);
	free(id);
	if (path)
		ft_free_arr(path);
	ft_free_arr(envp);
	return (0);
}
