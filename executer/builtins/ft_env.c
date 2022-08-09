/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:40:31 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/08 13:51:44 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_env(char **split, char **envp)
{
    int i;

    i = 0;
    if (!ft_strncmp(split[0], "env", 3) || !ft_strncmp(split[0], "ENV", 3))
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