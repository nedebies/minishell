/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 17:55:36 by nedebies          #+#    #+#             */
/*   Updated: 2022/09/06 11:59:52 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	args_counter(t_list *lst)
{
	int		count;
	char	*token;

	count = 0;
	while (lst)
	{
		token = lst->content;
		if (*token == '<' || *token == '>')
			count = count - 1;
		if (*token == '|')
			break ;
		lst = lst->next;
		count++;
	}
	return (count);
}

static char	**init_cmd_args(t_list **lst, t_shell *data, int idx)
{
	int		count_args;
	char	**args;
	int		i;
	int		j;
	char 	*token;

	i = 0;
	j = 0;
	count_args = args_counter(*lst);
	args = malloc((sizeof(char *) * count_args) + 1);
	if (!args)
		return (NULL);
	ft_memset(args, '\0', sizeof(char *) * count_args + 1);
	while (i < count_args)
	{
		token = (*lst)->content;
		if (*token == '<' || *token == '>')
		{
			ft_init_file(*lst, data->cmd, data, idx);
			(*lst) = (*lst)->next->next;
			i++;
		}
		else
		{
			(*lst)->content = parse_line((*lst)->content, data, -1);
			args[j] = ft_strdup((*lst)->content);
			(*lst) = (*lst)->next;
			i++;
			j++;
		}
	}
	args[i] = NULL;
	return (args);
}

static void	init_command(t_list **lst, t_shell *data, int i)
{
	data->cmd[i].cmd = ft_strdup((*lst)->content);
	data->cmd[i].cmd = parse_line(data->cmd[i].cmd, data, -1);
	data->cmd[i].args = init_cmd_args(lst, data, i);
}

/** Fill the cmnd structures with the token content **/
int	init_cmd(t_list *lst, t_shell *mini)
{
	int		i;
	char	*token;

	i = 0;
	while (lst)
	{
		token = lst->content;
		if (!token)
			return (1);
		if (*token == '|')
		{
			i++;
			lst = lst->next;
		}
		else
			init_command(&lst, mini, i);
	}
	return (0);
}
