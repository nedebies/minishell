/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdony <hdony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 13:38:52 by hdony             #+#    #+#             */
/*   Updated: 2022/08/22 16:10:24 by hdony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int  find_metachar_len(char *str)
{
    int i;

    i = 0;
    if (str[i] == '>' || str[i] == '<')
    {
        if (str[i + 1] == str[i])
            return (2);
    }
    return (1);
}

int   get_metachar_len(char *str, char **metachar_mark)
{
    int i;
    int metachar_len;
    
    i = -1;
    metachar_len = 0;
    while (str[++i])
    {
        if (ft_strchr(METACHAR, str[i]) != NULL)
        {
            *metachar_mark = &str[i];
            metachar_len = find_metachar_len(&str[i]);
            break; 
        }
    }
    return (metachar_len);
}

int  get_text_len(char *str)
{
    int i;

    i = -1;
    while (str[++i])
    {
        if (ft_strchr(SPACES, str[i]) != NULL)
            break;
        else if (ft_strchr(METACHAR, str[i]) != NULL)
            break;
        else if (ft_strchr(QUOTES, str[i]) != NULL)
            break;
    }
    return (i);
}

int ft_find_text(char *str, int metachar_len)
{
    int i;

    i = 0;
    if (metachar_len == 2)
    {
        if (ft_isalpha(str[i + 2]))
            return (1);
        else if (ft_isalpha(str[i - 1]))
            return (1);
    }
    else if (metachar_len == 1)
    {
        if (ft_isalpha(str[i + 1]) || ft_isalpha(str[i - 1]))
            return (1);
    }
    return (0);
}

/* 
** check if the METACHAR is at the beginning or the end of the array
** of TEXT + METACHAR
*/
void handle_text_metachar_1(char **tab2, char *str, char *metachar_mark,
     int *text_len, int *j)
{
    tab2[*j] = ft_substr(metachar_mark, 0, 1);
    // write(1, "16\n", 3);
    *j += 1;
    if (str == metachar_mark)
    {
        *text_len = get_text_len(&str[1]);
        tab2[*j] = ft_substr(metachar_mark, 1, *text_len);
    }
    else
    {
        *text_len = get_text_len(str);
        tab2[*j] = ft_substr(str, 0, *text_len);
    }
    // write(1, "17\n", 3);
    *j += 1;
}