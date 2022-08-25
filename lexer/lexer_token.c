/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdony <hdony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:54:46 by hdony             #+#    #+#             */
/*   Updated: 2022/08/19 12:07:30 by hdony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* replace str with the written expression of the metacharacter, | will be "pipe"*/
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
    // else if (!ft_strncmp(token, "squote", 6))
    //     str = strdup("SQUOTE");
    // else if (!ft_strncmp(token, "dquote", 6))
    //     str = strdup("DQUOTE");
    return(str); 
}

/* metacharacters like "<< > |" will always be the very first characters of the split[i]*/

void    check_token(char **tab, int string_count)
{
    int  i;

    i = 0;
    if (!*tab)
        return ;
    while(tab[i] && i < string_count)
    {
        if (!ft_strncmp(tab[i], "<", 1)) /*check the 1st character to the split[i] and compare it to "<" */
            tab[i] = ft_set_split(tab[i], "less");
        else if (!ft_strncmp(tab[i], "<<", 2))
            tab[i] = ft_set_split(tab[i], "lessless");
        else if (!ft_strncmp(tab[i], ">", 1))
            tab[i] = ft_set_split(tab[i], "great");
        else if (!ft_strncmp(tab[i], ">>", 2))
            tab[i] = ft_set_split(tab[i], "greatgreat");
        else if (!ft_strncmp(tab[i], "|", 1))
            tab[i] = ft_set_split(tab[i], "pipe");
        // write(1, "20\n", 3);
        i++;
    }
}
