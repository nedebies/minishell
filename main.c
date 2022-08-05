/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:27:18 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/05 12:48:51 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_parse_builtins(char *str)
{
    if(ft_cd(str))
        return(0);
    if(ft_echo(str))
        return(0);
    if(ft_env(str))
        return(0);
    if(ft_exit(str))
        return(1);
    if(ft_export(str))
        return(0);
    if(ft_pwd(str))
        return(0);
    if(ft_unset(str))
        return(0);
    return (0);
}

int main(int ac, char **av, char **envp)
{
    char *str;
    (void)av;
    (void)envp; // a virer
    while (ac > 0)
    {
        str = readline(GRN"nedebies@student.s19.be minishell &> "GRN);
        if (!str || ft_parse_builtins(str)) // AUCUNE GESTION DES CTRL+X atm
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