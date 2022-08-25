/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_stringcount.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdony <hdony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:00:15 by hdony             #+#    #+#             */
/*   Updated: 2022/08/11 16:35:13 by hdony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_onlymeta(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (ft_strchr(METACHAR, str[i]) == NULL)
            return (0);
        i++;
    }
    return (1);
}

int is_onlytext(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (ft_strchr(METACHAR, str[i]) != NULL)
            return (0);
        i++;
    }
    return (1);
}

/* string_count to count the # of char* that will be pointed by tab2*/
int ft_string_count(char **tab)
{
    int i;
    int sc;

    i = 0;
    sc = 0;
    while (tab[i] != 0)
    {
        if (is_onlytext(tab[i]))
            sc++;
        else if (is_onlymeta(tab[i]))
            sc++;
        else
            sc += 2;
        i++;
    }
    return (sc);
}