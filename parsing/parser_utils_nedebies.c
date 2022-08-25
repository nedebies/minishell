/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_nedebies.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 14:20:59 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/25 16:55:38 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int     count_args(t_list *lst)
{
    int i;

    i = 0;
    while (lst)
    {
        if (lst->content == "|" || lst->content == "<" || lst->content == ">")
            break ;
        else
        {
            i++;
            lst = lst->next;
        }
    }
    return (i);
}

/** Create a tab with the arguments only **/
char    **init_args(t_list *lst, t_cmnd cmds)
{
    char    **av;
    int     i;
    int     cnt;

    cnt = count_args(lst);
    i = 0;
    av = malloc(sizeof(char *) * cnt + 1);
    if (!av)
        return (NULL);
    while (i < cnt)
    {
            av[i] = parsing_line();
            i++;
    }
    av[i] = 0;
    return (av);
}

/** Create a file for the redir **/
void   set_file(lst)
{
    return ;
}

/** Create a t_cmnd struct according to its tokens **/
void init_cmds(t_list *lst, t_cmnd *cmds)
{
    int i;

    i = 0;
    if (!lst)
        return ;
    while (lst)
    {
        if (lst->content == ">" || lst->content == "<")
        {
            set_file(lst);
            lst = lst->next->next;
        }
        else if (lst->content == "|")
        {
            i++;
            lst = lst->next;
        }
        else
        {
            cmds[i].executable = ft_strdup(lst->content); // to set ! only the cmd
            cmds[i].argv = init_args(lst, cmds[i]);
        }
    }
}