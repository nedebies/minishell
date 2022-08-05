/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:40:31 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/05 13:22:53 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int isenv(char *str)
{
    int     i;
    int     j;
    char    *env;

    i = 0;
    j = 0;
    env = "env";
    if (str)
    {
        while (str[j] == 32)
		    j++;
        while(env[i])
        {
            if (str[i + j] != env[i])
                return (0);
            i++;
        }
    }
    return (1);
}

int ft_env(char *str, char **envp)
{
    int i;

    i = 0;
    if (isenv(str))
    {
        while(envp[i])
        {
            ft_putstr_fd(envp[i], 1);
            write(1, "\n", 1);
            i++;
        }
        return (1);
    }
    return (0);
}