/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:30:29 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/09 22:53:14 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define GRN "\e[1;32m"
# include "./libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# define METACHARACTERS "()<>|&"
# define QUOTES         "\'\""
# define SPACES         "\t\n"
/**
typedef struct  s_token
{
    int     type;
    char    *string;
}               t_token;

typedef struct  s_split
{
    char            **split;
    struct s_split  *next;
}               t_split;**/

int ft_parser(void);

int ft_executer(void);

int ft_expander(void);

char    **lexer(char *str);

/**   BUILTINS  **/
int ft_echo(char **split);
int ft_cd(char **split);
int ft_pwd(char **split, char **envp);
int ft_export(char **split);
int ft_unset(char **split);
int ft_env(char **split, char **envp);
int ft_exit(char **split);
#endif