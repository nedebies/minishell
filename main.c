/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:27:18 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/02 13:40:19 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_exit(char *str)
{
    int     i;
    int     j;
    char    *exit;

    i = 0;
    j = 0;
    exit = "exit";
    while (str[j] == 32)
		j++;
    while(exit[i])
    {
        if (str[i + j] != exit[i])
            return (0);
        i++;
    }
    return (1);
}

int main(int ac, char **av, char **envp)
{
    char *str;
    (void)av;
    (void)envp; // a virer
    while (ac > 0)
    {
        str = readline(GRN"nedebies@minishell-&> "GRN);
        if (ft_exit(str))
            break ;
        //else
        //    ft_minishell(str, envp);
    }
    return (0);
}