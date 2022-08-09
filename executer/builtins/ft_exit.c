/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:41:01 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/09 23:26:17 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_exit(char **split)
{
    if (!ft_strncmp(split[0], "exit", 4)) //erreur si split[2] existe
    {
        ft_putstr_fd("exit\n", 1);
        return (1);
    }
    return (0);
}