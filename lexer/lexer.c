/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:21:47 by hdony             #+#    #+#             */
/*   Updated: 2022/08/21 00:48:14 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_print_tab(char **tab2)
{
    int i;

    i = 0;
    while (tab2[i] != 0)
    {
        printf("string: %s\n", tab2[i]);
        i++;
    }
}

/* 
** check if the METACHAR is at the beginning or the end of the array
** of TEXT + METACHAR
*/
static void handle_text_metachar_2(char **tab2, char *str, char *metachar_mark,
     int *text_len, int *j)
{
    tab2[*j] = ft_substr(metachar_mark, 0, 2);
    *j += 1;
    if (str == metachar_mark)
    {
        *text_len = get_text_len(&str[2]);
        tab2[*j] = ft_substr(metachar_mark, 2, *text_len);
    }
    else
    {
        *text_len = get_text_len(str);
        tab2[*j] = ft_substr(str, 0, *text_len);
    }
    *j += 1;
}

/*
** check if there is TEXT + METACHAR in the array
** split the TEXT and the METACHAR in separate arrays
** else populate tab2 with the METACHAR
*/
static void handle_text_metachar(char **tab2, char *str, int metachar_len,
    char *metachar_mark, int *text_len, int *j)
{
    int     find_text;
    
    find_text = ft_find_text(metachar_mark, metachar_len);
    // write(1, "15\n", 3);
    if (find_text == 1 && metachar_len == 1)
        handle_text_metachar_1(tab2, str, metachar_mark, text_len, j);
    else if (find_text == 1 && metachar_len == 2)
        handle_text_metachar_2(tab2, str, metachar_mark, text_len, j);
    else if (!find_text)
    {
        tab2[*j] = ft_substr(metachar_mark, 0, metachar_len);
        *j += 1;
    }
}

static void handle_text(char **tab2, char *str, int metachar_len,
     int *text_len, int *j)
{
    *text_len = get_text_len(str);
    if (*text_len > 0)
    {
        tab2[*j] = ft_substr(str, metachar_len, *text_len);
        *j += 1;
    }
}

/*
** get the length of the METACHAR if any
** else handle TEXT ONLY
 */
static void check_for_text_metachar(char **tab2, char *str, int *j)
{
    int     text_len;
    char    *metachar_mark;
    int     metachar_len;

    text_len = 0;    
    metachar_mark = NULL;
    metachar_len = get_metachar_len(str, &metachar_mark);
    if (metachar_len > 0)
        handle_text_metachar(tab2, str, metachar_len, metachar_mark, &text_len, j);
    else
        handle_text(tab2, str, metachar_len, &text_len, j);
}

/*
** allocate memory for the newly created arrays
** check if there are TEXT + METACHAR in the splitted arrays
 */
static char    **second_split(char **split, int string_count)
{
    int     i;
    int     j;
    char    **tab2;

    i = -1;
    j = 0;
    // printf("sc: %d\n", string_count);
    tab2 = malloc(sizeof(char *) * (string_count + 1));
    if (!tab2)
        return (NULL);
    tab2[string_count] = 0;
    while (split[++i] != 0)
    {
        check_for_text_metachar(tab2, split[i], &j);
    }
    return (tab2);
}

/*
** the lexer takes the user command as input and returns a 2d array
** it does a 1st split on the spaces of the cmd, then it breaks each
** splitted arrays into new arrays containing either :
** TEXT ONLY || METACHARS ONLY
** >cat ==> > + cat
 */
 
char    **lexer(char *str)
{
    char    **tab;
    char    **tab2;
    char    *metachar_mark;
    int     string_count;
    
    tab = NULL;
    tab2 = NULL;
    metachar_mark = NULL;
    if (!str)
        return (NULL);
    while (*str == 32)
        str++;
    tab = ft_split(str, 32);
   if (!tab[0])
       return (NULL);
    if (!get_metachar_len(str, &metachar_mark))
        return tab;
    else
    {
        string_count = ft_string_count(tab);
        tab2 = second_split(tab, string_count);
        if (!tab2)
            return (NULL);
        if (ft_strlen(*tab) > 0)
		{
            ft_free_split(tab);
        }
        check_token(tab2, string_count);
        // ft_print_tab(tab2);
        return (tab2);
    }
}