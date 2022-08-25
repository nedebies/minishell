/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_nedebies.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 14:20:59 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/25 15:30:24 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void init_cmd(t_list *lst, t_cmnd *cmds)
{
    if (!lst)
        return ;
    while (lst)
    {
        if (lst->content == '>' || lst->content == '<')
        {
            // REDIR > <
        lst = lst->next->next;
        }
        else if (lst->content == '|')
            lst = lst->next;
        else
        {
            // REDIR >> <<
        }
    }
}