/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:36:57 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/08 13:52:16 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_pwd(char **split, char **envp)
{
    int i;

    i = 0;
    if(!ft_strncmp(split[0], "pwd", 3) || !ft_strncmp(split[0], "PWD", 3))
    {
        while (ft_strnstr(envp[i], "PWD", 4) == 0)
            i++;
        if (envp[i])
        {
            ft_putstr_fd(envp[i] + 4, 1);
            write(1, "\n", 1);
        }
        return (1);
    }
    return (0);
}