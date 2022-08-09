/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:27:18 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/09 22:46:35 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

 static	int	ft_free_split(char **split)
 {
     size_t i;
     i = 0;
     while (split[i])
         i++;
 	while (i != 0)
 		free(split[--i]);
 	free(split);
 	return (0);
 }

 static int ft_parse_builtins(char **split, char **envp)
 {
     if(ft_cd(split))
         return(0);
     if(ft_echo(split))
         return(0);
     if(ft_env(split, envp))
         return(0);
     if(ft_exit(split))
         return(1);
     if(ft_export(split))
         return(0);
     if(ft_pwd(split, envp))
         return(0);
     if(ft_unset(split))
         return(0);
     return (0);
 }

int main(int ac, char **av, char **envp)
{
    char *str; // readline()
    char **cmd; // readline() splitted and TOKENIZED
    (void)av;

    str = NULL;
    cmd = NULL;
    while (ac > 0)
    {
        str = readline(GRN"not-bash&> "GRN);
        add_history(str); //simplier to create an history than a list
        cmd = lexer(str);
        if (!cmd)
        {
            if (ft_parse_builtins(cmd, envp))
                ft_free_split(cmd);
            break ;
        }  // NO CTRL+C CTRL+D CTRL+(backslash) atm
// MUST ADD FREES LATER
    //     ft_minishell(str, envp);
    //     ft_parser(); // TO DO
    //     ft_executer(); // TO DO
    //     ft_expander(); // TO DO
    //     ft_free_split(split);
    }
    free(str);
    return (0);
}