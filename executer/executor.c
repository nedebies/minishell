/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:28:29 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/26 15:16:02 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_dup_fd(int i, int **fd, t_shell *data)
{
	if (i != 0)
		dup2(fd[i - 1][0], STDIN_FILENO);
	if (i != data->count_cmd -1)
		dup2(fd[i][1], STDOUT_FILENO);
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
	ft_close_fd(fd, data);
}

static char	**ft_get_path(t_shell *data)
{
	char	*tmp;
	char	**path;

	tmp = ft_getenv(data->head_env, "PATH");
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
			dt->cmd[i].cmd = join_path(dt->cmd[i].cmd, path, dt->head_env);
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

int	executor(t_shell *data)
{
	pid_t	*id;
	char	**path;
	int		ret;
	char	**envp;

	envp = list2mass_env(data->head_env);
	path = ft_get_path(data);
	if (!data->cmd[0].cmd)
	{
		ret = ft_redir(&data->cmd[0], data->cmd[0].redir);
		ft_print_error(&data->head_env, NULL, ret);
	}
	else
	{
		if (cmd_with_path(data, envp, path) == -1)
			return (-1);
		id = malloc(sizeof(pid_t) * data->count_cmd);
		ft_processing(id, data, envp);
		free(id);
	}
	ft_free_arr(path);
	ft_free_arr(envp);
	return (0);
}