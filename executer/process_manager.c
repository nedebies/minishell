/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 23:47:01 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/25 16:23:34 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/** Close and free the processes **/
static void	ft_close_fd(int *fd[2], int cnt_cmd)
{
	int	i;

	i = 0;
	while (i < cnt_cmd - 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
	i = 0;
	while (i < cnt_cmd - 1)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}

/** Wait the end of a process if necessary **/
static void	ft_wait_process(pid_t *id, int cnt_cmd)
{
	int		i;
	int		ret;

	i = 0;
	while (i < cnt_cmd)
	{
		waitpid(id[i], &ret, 0);
		i++;
	}
}

/** Execute the command in a single process **/
static void	process(t_cmnd *data, char **envp)
{
	signal(SIGQUIT, SIG_DFL);
	// MUST CHECK REDIR HERE
	//ft_dup_fd(i, fd, data); NOT INPUT YET
	if (is_builtin(data->executable))
		exec_builtins(data);
	else if (execve(data->executable, data->argv, envp) < 0)
		throw_error_exit(data->executable, "invalid option", EXIT_EACCES);
	exit(EXIT_SUCCESS);
}

/** Generate the right amount of processes **/
static int	ft_create_pipe(int **fd, int cnt_cmd)
{
	int	i;

	i = 0;
	while (i < cnt_cmd - 1)
	{
		if (pipe(fd[i]) < 0)
		{
			ft_putstr_fd("error in pipe\n", 2);
			return(1);
		}
		i++;
	}
	return (0);
}

/** Check if theres x pipes to create x + 1 processes
	If x = 0 check if its a builtin to execute it **/
int	ft_processing(pid_t	*id, t_cmnd *data, char **envp, int cnt_cmd)
{
	int		i;
	int		**fd;

	i = -1;
	if (is_builtin(data->executable) && !data->next) // Not certain if necessary
		return(exec_builtins(data));
	fd = malloc(sizeof(int *) * (cnt_cmd - 1));
	while (++i < cnt_cmd - 1)
		fd[i] = malloc(sizeof(int) * 2);
	if (!fd || ft_create_pipe(fd, cnt_cmd))
		return (1);
	i = 0;
	while (i < cnt_cmd)
	{
		id[i] = fork();
		if (id[i] == -1)
			exit(EXIT_FAILURE);
		else if (id[i] == 0)
			process(data, envp);
		i++;
	}
	ft_close_fd(fd, cnt_cmd);
	ft_wait_process(id, cnt_cmd);
	return (0);
}
