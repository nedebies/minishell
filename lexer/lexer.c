/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:21:47 by hdony             #+#    #+#             */
/*   Updated: 2022/08/09 23:01:40 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/**
void	ft_lstadd_back_bis(t_split **alst, t_split *new)
{
	t_split	*tmp;

	tmp = *alst;
	if (*alst == NULL && new != NULL)
	{
		new->next = tmp;
		*alst = new;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}


t_split *create_node(char **split)
{
    t_split *new;

    new = malloc(sizeof(*new));
    new->split = split;
    new->next = NULL;
    return (new);
}

void    create_list(t_split **head, char **split)
{
    t_split *new;

    new = create_node(split);
    ft_lstadd_back_bis(head, new);
}

void    lexer(char *cmd, t_split **head)
{
    //my struct will point to the second command entered by the user, it will work like an historic 
    char    **split;
    int     i;

    i = 0;
    split = ft_split(cmd, 32);    
    create_list(head, split);
   // printf("%s\n", (*head)->split[0]);
}
**/

static char *ft_set_split(char *str, char *token)
{
    free(str);
    if (!ft_strncmp(token, "less", 4))
        str = strdup("LESS");
    else if (!ft_strncmp(token, "lessless", 8))
        str = strdup("LESSLESS");
    else if (!ft_strncmp(token, "great", 5))
        str = strdup("GREAT");
    else if (!ft_strncmp(token, "greatgreat", 10))
        str = strdup("GREATGREAT");
    else if (!ft_strncmp(token, "pipe", 4))
        str = strdup("PIPE");
    return(str); 
}

static char **check_token(char **tab)
{
    int  i;

    i = -1;
    while(tab[++i])
    {
        if (!ft_strncmp(tab[i], "<", 1))
            tab[i] = ft_set_split(tab[i], "less");
        else if (!ft_strncmp(tab[i], "<<", 2))
            tab[i] = ft_set_split(tab[i], "lessless");
        else if (!ft_strncmp(tab[i], ">", 1))
            tab[i] = ft_set_split(tab[i], "great");
        else if (!ft_strncmp(tab[i], ">>", 2))
            tab[i] = ft_set_split(tab[i], "greatgreat");
        else if (!ft_strncmp(tab[i], "|", 1))
            tab[i] = ft_set_split(tab[i], "pipe");
    }
    return (tab);
}

char    **lexer(char *cmd)
{
    char    **tab;

    tab = NULL;
    if (ft_strlen(cmd) > 0)
    {
        tab = ft_split(cmd, 32);
        if (!tab)
            return (NULL);  
        tab = check_token(tab);
    }
    return (tab);
}