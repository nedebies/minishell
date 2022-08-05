/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:27:18 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/05 14:27:00 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_parse_builtins(char *str, char **envp)
{
    if(ft_cd(str))
        return(0);
    if(ft_echo(str))
        return(0);
    if(ft_env(str, envp))
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

    while (ac > 0)
    {
        str = readline(GRN"not-bash&> "GRN);
        if (!str || ft_parse_builtins(str, envp)) // NO CTRL+C CTRL+D CTRL+(backslash) atm
            break ; // MUST ADD FREES LATER
        //    ft_minishell(str, envp);
        ft_parser(); // TO DO
        ft_executer(); // TO DO
        ft_expander(); // TO DO
        ft_lexer(); // TO DO
    }
    return (0);
}