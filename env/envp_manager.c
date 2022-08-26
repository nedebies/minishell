/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 10:29:34 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/26 02:46:06 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_var_nbr(void)
{
	t_env	*tmp;
	int		vc;

	tmp = g_manager.env;
	vc = 0;
	while (tmp->next != NULL)
	{
		vc++;
		tmp = tmp->next;
	}
	return (vc);
}

char	**new_envp(void)
{
	char	**new;
	t_env	*tmp;
	char	*new_str;
	int		i;

	tmp = g_manager.env;
	new = malloc(sizeof(char*) * (count_var_nbr() + 1));
	i = -1;
	if (!new)
		return (NULL);
	while (tmp->next != NULL)
	{
		new_str = ft_strjoin(tmp->name, "=");
		new[++i] = ft_strjoin(new_str, tmp->value);
		free(new_str);
		tmp = tmp->next;
	}
	new[i] = 0;
	return (new);
}

void	*minishell_calloc(size_t count, size_t size)
{
	size_t	i;
	void	*res;

	res = (void *)malloc(size * count);
	if (!(res))
		exit(EXIT_FAILURE);
	i = 0;
	while (i < size * count)
	{
		*((char *)res + i) = '\0';
		i++;
	}
	return (res);
}

void	free_env(void)
{
	t_env	*tmp;

	while (g_manager.env)
	{
		tmp = g_manager.env;
		g_manager.env = g_manager.env->next;
		if (tmp->name)
			free(tmp->name);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

int	valid_env_name(char *identifier)
{
	char	*ptr;

	ptr = identifier;
	if (((*identifier < 'a' || *identifier > 'z') && (*identifier < 'A'
				|| *identifier > 'Z')) && *identifier != '_')
		return (EXIT_FAILURE);
	while (*ptr && *ptr != '=')
	{
		if (!ft_isalnum(*ptr) && (*ptr != '_'))
			return (EXIT_FAILURE);
		ptr++;
	}
	return (EXIT_SUCCESS);
}

void	remove_env(t_env *target)
{
	t_env	*tmp;

	tmp = g_manager.env;
	if (tmp == target)
		g_manager.env = tmp->next;
	else
	{
		while (tmp->next != target)
			tmp = tmp->next;
		tmp->next = target->next;
	}
	free(target->name);
	free(target->value);
	free(target);
}

t_env	*get_env(char *identifier)
{
	t_env			*ptr;
	unsigned int	len;

	ptr = g_manager.env;
	len = ft_strlen(identifier);
	while (ptr)
	{
		if (ft_strlen(ptr->name) == len && ft_strncmp(identifier, ptr->name,
				len) == 0)
			return (ptr);
		ptr = ptr->next;
	}
	return (0);
}

char	*get_env_value(char *argv)
{
	char	*value;
	char	*ptr;
	int		len;

	ptr = ft_strchr(argv, '=');
	if (!ptr)
		return (0);
	ptr++;
	len = ft_strlen(ptr) + 1;
	value = (char *)minishell_calloc(len, sizeof(char));
	if (!value)
		exit(EXIT_FAILURE);
	ft_strlcpy(value, ptr, len);
	return (value);
}

char	*get_env_name(char *argv)
{
	char	*name;
	size_t	len;

	if (!ft_strchr(argv, '='))
		len = ft_strlen(argv) + 1;
	else
		len = ft_strchr(argv, '=') - argv + 1;
	name = (char *)minishell_calloc(len, sizeof(char));
	if (!name)
		exit(EXIT_FAILURE);
	ft_strlcpy(name, argv, len);
	return (name);
}

void	add_env(char *name, char *value)
{
	t_env	*ptr;
	t_env	*new;

	ptr = g_manager.env;
	new = (t_env *)minishell_calloc(1, sizeof(t_env));
	if (!new)
		exit(EXIT_FAILURE);
	new->name = name;
	new->value = value;
	new->next = 0;
	if (!g_manager.env)
	{
		g_manager.env = new;
		return ;
	}
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}
