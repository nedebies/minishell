/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:27:18 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/05 15:32:37 by nedebies         ###   ########.fr       */
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
    if(ft_pwd(split))
        return(0);
    if(ft_unset(split))
        return(0);
    return (0);
}

int main(int ac, char **av, char **envp)
{
    char *str;
    (void)av;
    char **split;

    split = NULL;
    while (ac > 0)
    {
        str = readline(GRN"not-bash&> "GRN);
        split = ft_split(str, 32);
        if (!str || ft_parse_builtins(split, envp)) // NO CTRL+C CTRL+D CTRL+(backslash) atm
            break ; // MUST ADD FREES LATER
        //    ft_minishell(str, envp);
        ft_parser(); // TO DO
        ft_executer(); // TO DO
        ft_expander(); // TO DO
        ft_lexer(); // TO DO
        ft_free_split(split);
    }
    return (0);
}