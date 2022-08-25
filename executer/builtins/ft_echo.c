/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:33:56 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/24 10:06:24 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_echo(char **split)
{
    int i;
    int nl;

    i = 0;
    nl = 1;

        if (!split[0])
        {
            write(1, "\n", 1);
            return (0);
        }
        if (!ft_strncmp(split[0], "-n", 2))
        {
            nl = 0;
            while(split[0][++i])
            {
                if (split[1][i] != 'n')
                    throw_error_usage(split[0], split[1]);
            }
            if (!split[1])
                throw_error_usage(split[0], split[2]);
        }
        i = 0;
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
            while(split[i])
            {
                ft_putstr_fd(split[i], 1);
                if (split[i + 1])
                    write(1, " ", 1);
                i++;
            }
        }
    return (0);
}