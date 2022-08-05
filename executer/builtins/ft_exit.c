/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:41:01 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/05 15:36:20 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_exit(char **split)
{
    int     i;
    char    *exit;

    i = 0;
    exit = "exit";
    if (split[0])
    {
        while(exit[i])
        {
            if (split[0][i] != exit[i])
                return (0);
            i++;
        }
    }
    return (1);
}