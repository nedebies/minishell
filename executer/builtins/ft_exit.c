/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:41:01 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/05 12:48:39 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_exit(char *str)
{
    int     i;
    int     j;
    char    *exit;

    i = 0;
    j = 0;
    exit = "exit";
    if (str)
    {
        while (str[j] == 32)
		    j++;
        while(exit[i])
        {
            if (str[i + j] != exit[i])
                return (0);
            i++;
        }
    }
    return (1);
}