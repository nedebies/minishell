/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:27:03 by nedebies          #+#    #+#             */
/*   Updated: 2022/09/06 16:51:55 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_end(int c)
{
	if (c == '_')
		return (0);
	if (ft_isalpha(c))
		return (0);
	if (ft_isdigit(c))
		return (0);
	if (c == '?')
		return (0);
	return (1);
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
			init_each_command(&lst, mini, i);
	}
	return (0);
}

/** Lex the line in tokens til line 21 then init the command line (parsing) **/
int	parser(char *line, t_shell *shell)
{
	t_list	*tokens;

	tokens = NULL;
	shell->count_cmd = pre_parse(line, shell);
	if (shell->count_cmd == -1)
		return (1);
	tokens = get_tokens(line, tokens);
	shell->cmd = malloc(sizeof(t_cmnd) * shell->count_cmd);
	if (!shell->count_cmd)
		return (1);
	ft_memset(shell->cmd, '\0', sizeof(t_cmnd) * shell->count_cmd);
	init_cmd(tokens, shell);
	free(line);
	ft_lstclear(&tokens, free);
	return (0);
}
