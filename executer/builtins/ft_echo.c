/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:33:56 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/10 09:38:14 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int ft_echo(char **split)
{
    int i;
    int nl;

    i = 0;
    nl = 1;
    if (split && !ft_strncmp(split[0], "echo", 4))
    {
        if (!ft_strncmp(split[1], "-n", 2))
        {
            nl = 0;
            while(split[1][++i])
            {
                if (split[1][i] != 'n')
                    return(0); // throw error instead
            }
        }
        i = 1;
        if (nl == 1)
        {
            while(split[i])
            {
                ft_putstr_fd(split[i++], 1);
                write(1, " ", 1);
            }
            write(1, "\n", 1);
        }
        else
        {
            while(split[i + 1])
            {
                ft_putstr_fd(split[i + 1], 1);
                if (split[i + 2])
                    write(1, " ", 1);
                i++;
            }
        }
    }
    return (0);
}