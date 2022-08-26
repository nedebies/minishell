/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:00:37 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/26 14:57:08 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parser(char *line, t_shell *mini)
{
	t_list	*tokens;

	tokens = NULL;
	mini->count_cmd = pre_parse(line);
	if (mini->count_cmd == -1)
	{
		ft_putenv(&mini->head_env, "?", "1");
		return (1);
	}
	tokens = get_tokens(line, tokens);
	mini->cmd = malloc(sizeof(t_cmd) * mini->count_cmd);
	if (!mini->count_cmd)
		return (1);
	ft_memset(mini->cmd, '\0', sizeof(t_cmd) * mini->count_cmd);
	init_cmd(tokens, mini);
	free(line);
	ft_lstclear(&tokens, free);
	return (0);
}