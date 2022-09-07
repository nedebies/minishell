/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 17:55:36 by nedebies          #+#    #+#             */
/*   Updated: 2022/09/06 16:51:55 by nedebies         ###   ########.fr       */
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

static char	**set_args(int count_args)
{
	char	**args;

	args = NULL;
	args = malloc((sizeof(char *) * count_args) + 1);
	if (!args)
		return (NULL);
	ft_memset(args, '\0', sizeof(char *) * count_args + 1);
	args[count_args] = NULL;
	return (args);
}

static char	**init_cmd_args(t_list **lst, t_shell *data, int idx, int j)
{
	int		count_args;
	char	**args;
	char	*token;

	count_args = args_counter(*lst);
	args = set_args(count_args);
	if (!args)
		return (NULL);
	while (count_args-- > 0)
	{
		token = (*lst)->content;
		if (*token == '<' || *token == '>')
		{
			ft_init_file(*lst, data->cmd, data, idx);
			(*lst) = (*lst)->next->next;
		}
		else
		{
			(*lst)->content = parse_line((*lst)->content, data, -1);
			args[j++] = ft_strdup((*lst)->content);
			(*lst) = (*lst)->next;
		}
	}
	return (args);
}

static char	*set_wrong_cmd(char *s)
{
	free(s);
	return (ft_strdup(""));
}

void	init_each_command(t_list **lst, t_shell *data, int i)
{
	data->cmd[i].cmd = ft_strdup((*lst)->content);
	data->cmd[i].cmd = parse_line(data->cmd[i].cmd, data, -1);
	if (!ft_strncmp(data->cmd[i].cmd, ">>", 2))
		data->cmd[i].cmd = set_wrong_cmd(data->cmd[i].cmd);
	else if (!ft_strncmp(data->cmd[i].cmd, "<<", 2))
		data->cmd[i].cmd = set_wrong_cmd(data->cmd[i].cmd);
	else if (!ft_strncmp(data->cmd[i].cmd, ">", 1))
		data->cmd[i].cmd = set_wrong_cmd(data->cmd[i].cmd);
	else if (!ft_strncmp(data->cmd[i].cmd, "<", 1))
		data->cmd[i].cmd = set_wrong_cmd(data->cmd[i].cmd);
	data->cmd[i].args = init_cmd_args(lst, data, i, 0);
}
