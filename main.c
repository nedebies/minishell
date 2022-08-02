/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:27:18 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/02 15:14:44 by nedebies         ###   ########.fr       */
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
    if (str)
    {
        while (str[j] == 32)
		    j++;
        while(exit[i])
        {
            if (str[i + j] != exit[i])
                return (0);
            i++;
        }
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
        str = readline(GRN"nedebies@student.s19.be minishell &> "GRN);
        if (!str || ft_exit(str)) // AUCUNE GESTION DES CTRL+X atm
            break ;
        else
            write(1, "rien atm\n", 9); //a virer ofc
        //    ft_minishell(str, envp);
        ft_parser();
        ft_executer();
        ft_expander();
        ft_lexer();
    }
    return (0);
}