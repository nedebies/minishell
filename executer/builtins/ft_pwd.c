/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:36:57 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/05 16:06:30 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_pwd(char **split, char **envp)
{
    int i;
    char   *pwd;

    pwd = "pwd";
    i = -1;
    while(pwd[++i])
    {
        if (split[0][i] != pwd[i])
            return (1);
    }
    i = 0;
    while (ft_strnstr(envp[i], "PWD", 4) == 0)
        i++;
    if (envp[i])
    {
        ft_putstr_fd(envp[i] + 4, 1);
        write(1, "\n", 1);
    }
    return (0);
}