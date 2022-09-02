/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:38:03 by nedebies          #+#    #+#             */
/*   Updated: 2022/09/01 11:12:55 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_print_env(t_list **is_envp_list)
{
	t_env	**env_lst;
	int		i;

	i = 0;
	env_lst = ft_sortenv(is_envp_list);
	while (env_lst && env_lst[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env_lst[i]->name, 1);
		ft_putstr_fd("=\"", 1);
		if (ft_getenv(*is_envp_list, env_lst[i]->name))
		{
			ft_putstr_fd(ft_getenv(*is_envp_list, env_lst[i]->name), 1);
			ft_putstr_fd("\"\n", 1);
		}
		else
			ft_putstr_fd("\"\n", 1);
		i++;
	}
	free(env_lst);
}

char	*get_name(char *s)
{
	int		i;
	char	*temp;

	i = 0;
	while (s[i] != '=' && s[i] != '\0')
		i++;
	temp = ft_substr(s, 0, i);
	return (temp);
}

int	ft_check_name(char *name)
{
	if (ft_isalpha(name[0]) || name[0] == '_')
		return (1);
	ft_print_err_export(name);
	return (0);
}

int	add_value(char *name, t_shell *d, int num_cmd, int i)
{
	char	*value;

	if (ft_check_name(name))
	{
		if (ft_isset('=', d->cmd[num_cmd].args[i]))
			value = get_value_env(d->cmd[num_cmd].args[i]);
		else
			value = get_value_env(d->cmd[num_cmd].args[++i]);
		if (ft_strlen(value))
			ft_putenv(&d->envp_list, name, value);
		else
		{
			free(value);
			return (-1);
		}
		free(value);
	}
	else
		return (-1);
	return (i);
}

void	ft_export(t_shell *data, int num_cmd)
{
	int		i;
	char	*name;

	if (!data->cmd[num_cmd].args[1])
		return (ft_print_env(&data->envp_list));
	i = 1;
	while (ft_strlen(data->cmd[num_cmd].args[i]))
	{
		name = get_name_env(data->cmd[num_cmd].args[i]);
		i = add_value(name, data, num_cmd, i);
		free(name);
		if (i == -1)
			return ;
		i++;
	}
	ft_print_error(data, NULL, 0);
}
