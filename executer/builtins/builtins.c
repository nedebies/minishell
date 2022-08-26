/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 11:29:03 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/26 15:04:07 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_builtin(t_shell *data, int num_cmd)
{
	if (data->cmd[num_cmd].cmd == NULL)
		return (0);
	if (ft_strncmp(data->cmd[num_cmd].cmd, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(data->cmd[num_cmd].cmd, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(data->cmd[num_cmd].cmd, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(data->cmd[num_cmd].cmd, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(data->cmd[num_cmd].cmd, "exit", 5) == 0)
		return (1);
	else if (ft_strncmp(data->cmd[num_cmd].cmd, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(data->cmd[num_cmd].cmd, "export", 7) == 0)
		return (1);
	return (0);
}

int	execute_builtin(t_shell *data, int num_cmd)
{
	if (!ft_strncmp(data->cmd[num_cmd].arguments[0], "pwd", 3))
		ft_builtin_pwd(&data->head_env);
	else if (!ft_strncmp(data->cmd[num_cmd].arguments[0], "echo", 4))
		ft_builtin_echo(data, num_cmd);
	else if (!ft_strncmp(data->cmd[num_cmd].arguments[0], "cd", 2))
		ft_builtin_cd(data, num_cmd);
	else if (!ft_strncmp(data->cmd[num_cmd].arguments[0], "env", 3))
		ft_builtin_env(&data->head_env);
	else if (!ft_strncmp(data->cmd[num_cmd].arguments[0], "export", 6))
		ft_builtin_export(data, num_cmd);
	else if (!ft_strncmp(data->cmd[num_cmd].arguments[0], "unset", 5))
		ft_builtin_unset(data, num_cmd);
	else if (!ft_strncmp(data->cmd[num_cmd].arguments[0], "exit", 4))
		ft_builtin_exit(data, num_cmd);
	return (EXIT_SUCCESS);
}

static char	*ft_join_env(t_env *env)
{
	char	*str_env;
	char	*tmp;

	tmp = ft_strjoin(env->name, "=");
	str_env = ft_strjoin(tmp, env->value);
	free(tmp);
	return (str_env);
}

char	**list2mass_env(t_list *lst)
{
	int		i;
	int		size;
	char	**mass;
	t_env	*env;

	size = ft_lstsize(lst) + 1;
	mass = malloc(size * sizeof(char *));
	i = 0;
	while (lst && i < size)
	{
		env = (t_env *)lst->content;
		mass[i++] = ft_join_env(env);
		lst = lst->next;
	}
	mass[i] = NULL;
	return (mass);
}
