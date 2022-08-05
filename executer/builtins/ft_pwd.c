/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:36:57 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/05 15:52:25 by nedebies         ###   ########.fr       */
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
    while (ft_strnstr(envp[i], "PWD", 4) == 0) //segfault atm
		i++;
    ft_putstr_fd(ft_strchr(split[i], 61), 1);
    return (0);
}