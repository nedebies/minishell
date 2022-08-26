/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:16:03 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/26 14:16:16 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_comp(char *one, char *two)
{
	int	i;

	i = 0;
	while (one && two)
	{
		if (one[i] > two[i])
			return (1);
		else if (one[i] < two[i])
			return (0);
		else if (one[i] == two[i])
			i++;
	}
	return (0);
}

static void	ft_bubble_sort(t_env **is_head_env, int nbr)
{
	t_env	*ls_tmp;
	int		swapped;
	int		i;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (i < nbr - 1)
		{
			if (ft_comp(is_head_env[i]->name, is_head_env[i + 1]->name))
			{
				ls_tmp = is_head_env[i];
				is_head_env[i] = is_head_env[i + 1];
				is_head_env[i + 1] = ls_tmp;
				swapped = 1;
			}
			i++;
		}
	}
}

t_env	**ft_sortenv(t_list **is_head_env)
{
	t_env	**ls_head_env;
	t_list	*ls_cur_env;
	int		i;

	i = 0;
	ls_head_env = calloc(ft_lstsize(*is_head_env) + 1, sizeof(t_env *));
	if (!ls_head_env)
		return (NULL);
	ls_cur_env = *is_head_env;
	while (ls_cur_env)
	{
		ls_head_env[i] = (t_env *)(ls_cur_env->content);
		i++;
		ls_cur_env = ls_cur_env->next;
	}
	ls_head_env[i] = NULL;
	ft_bubble_sort(ls_head_env, ft_lstsize(*is_head_env));
	return (ls_head_env);
}
