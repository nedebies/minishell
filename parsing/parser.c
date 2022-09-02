/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:27:03 by nedebies          #+#    #+#             */
/*   Updated: 2022/09/02 10:35:18 by nedebies         ###   ########.fr       */
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

/** Lex the line in tokens til line 21 then init the command line (parsing) **/
int	parser(char *line, t_shell *mini)
{
	t_list	*tokens;

	tokens = NULL;
	mini->count_cmd = pre_parse(line, mini);
	if (mini->count_cmd == -1)
		return (1);
	tokens = get_tokens(line, tokens);
	mini->cmd = malloc(sizeof(t_cmnd) * mini->count_cmd);
	if (!mini->count_cmd)
		return (1);
	ft_memset(mini->cmd, '\0', sizeof(t_cmnd) * mini->count_cmd);
	init_cmd(tokens, mini);
	free(line);
	ft_lstclear(&tokens, free);
	return (0);
}
