/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:28:29 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/25 11:17:52 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/** Check if the non builtin command actually exist **/
static int	is_valid_cmd2(t_cmnd *cmnd, char **paths)
{
	char	*part_path;
	char	*path;
	int		i;

	i = -1;
	while (paths[++i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmnd->executable);
		free(part_path);
		if (access(path, F_OK) == 0)
		{
			free(path);
			return(1);
		}
		free(path);
	}
	return (0);
}

/** Return TRUE if every commands are valid (builtins or not) **/
static int	is_valid_cmd(t_cmnd *cmnd, char **paths, int *cnt)
{
	int		i;
	t_cmnd	*tmp;


	tmp = cmnd;
	i = -1;
	while(tmp->next)
	{
		tmp = tmp->next;
		cnt++;
	}
	while (++i < *cnt)
	{
		if(!is_builtin(cmnd->executable))
			if (!is_valid_cmd2(cmnd, paths))
				return (0);
		cmnd = cmnd->next;
	}
	return (1);
}

/** Split the envps PATH **/
static char	**get_paths(char **envp)
{
	char	**paths;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

/** Check if the commands are valid before processing anything **/
int	ft_executer(t_cmnd *cmnd, char **envp)
{
	pid_t	*id;
	char	**paths;
	int		i;
	char	*cmd;

	i = 1;
	cmd = cmnd->executable;
	if (!cmd)
	{
		ft_free_llist(cmnd);
		exit(EXIT_FAILURE);
	}
	paths = get_paths(envp);
	if (!paths)
	{
		ft_free_split(paths);
		ft_free_llist(cmnd);
		exit(EXIT_FAILURE);
	}
	if (!is_valid_cmd(cmnd, paths, &i))
	{
		ft_free_split(paths);
		ft_free_llist(cmnd);
		exit(EXIT_FAILURE);
	}
	id = malloc(sizeof(pid_t) * i);
	ft_processing(id, cmnd, envp, i);
	free(id);
	ft_free_split(paths);
	return (EXIT_SUCCESS);
}