/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 23:47:01 by nedebies          #+#    #+#             */
/*   Updated: 2022/09/02 17:01:37 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	process2(t_shell *data, int i, int **fd)
{
	int	ret;
	char **envp;

	envp = get_envp(data->envp_list);
	ret = 0;
	signal(SIGQUIT, SIG_DFL);
	ret = ft_redir(data->cmd + i, data->cmd[i].redir);
	if (ret)
		exit(EXIT_FAILURE);
	ft_dup_fd(i, fd, data);
	if (is_builtin(data, i))
		execute_builtin(data, i);
	else if (execve(data->cmd[i].cmd, data->cmd[i].args, envp) == -1)
	{
		perror(data->cmd[i].cmd);
		data->exit_code = 126;
		exit (data->exit_code);
	}
	//exit(EXIT_SUCCESS);
}

static void	process(t_shell *data, int i, int **fd)
{
	int	ret;
	char **envp;

	envp = get_envp(data->envp_list);
	ret = 0;
	signal(SIGQUIT, SIG_DFL);
	ret = ft_redir(data->cmd + i, data->cmd[i].redir);
	if (ret)
		exit(EXIT_FAILURE);
	ft_dup_fd(i, fd, data);
	if (is_builtin(data, i))
		execute_builtin(data, i);
	else if (execve(data->cmd[i].cmd, data->cmd[i].args, envp) == -1)
	{
		perror(data->cmd[i].cmd);
		data->exit_code = 126;
		exit (data->exit_code);
	}
	exit(EXIT_SUCCESS);
}

int	ft_create_pipe(int **fd, t_shell *data)
{
	int	i;

	i = 0;
	while (i < data->count_cmd - 1)
	{
		if (pipe(fd[i]) == -1)
		{
			ft_putstr_fd("error in pipe\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	ft_wait_process(pid_t	id, t_shell *data)
{
	int		i;
	int		ret;

	i = 0;
	while (i < data->count_cmd)
	{
		waitpid(id, &ret, 0);
		ret = set_exit_status(ret);
		ft_print_error(data, NULL, ret);
		i++;
	}
}

static int	**ft_malloc_fd(t_shell *data, int i)
{
	int	**fd;

	fd = malloc(sizeof(int *) * (data->count_cmd - 1));
	if (!fd)
		return (0);
	while (++i < data->count_cmd - 1)
	{
		fd[i] = malloc(sizeof(int ) * 2);
		if (!fd[i])
			return (0);
	}
	if ((ft_create_pipe(fd, data)) || !fd)
		return (0);
	return (fd);
}

int	ft_process_manager(t_shell *data, int i)
{
	pid_t	id;
	int		**fd;

	if (is_builtin(data, 0) == 1 && data->count_cmd == 1)
	{
		execute_builtin(data, 0);
		return (0);
	}
	fd = ft_malloc_fd(data, i);
	if (!fd)
		return (1);
	i = 0;
	while (++i < data->count_cmd)
	{
		id = fork();
		if (id == -1)
			exit(EXIT_FAILURE);
		else if (id == 0)
			process(data, i, fd);
	}
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
	if  (id)
		process2(data, 0, fd); // no 
	if (data->count_cmd > 1)
		ft_close_fd(fd, data);
	ft_wait_process(id, data);
	return (0);
}
