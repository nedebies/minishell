/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:30:29 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/08 13:11:45 by nedebies         ###   ########.fr       */
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

int ft_parser(void);

int ft_executer(void);

int ft_expander(void);

int ft_lexer(void);

/**   BUILTINS  **/
int ft_echo(char **split);
int ft_cd(char **split);
int ft_pwd(char **split, char **envp);
int ft_export(char **split);
int ft_unset(char **split);
int ft_env(char **split, char **envp);
int ft_exit(char **split);
#endif