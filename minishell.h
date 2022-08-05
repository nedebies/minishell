/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:30:29 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/05 13:19:43 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define GRN "\e[1;32m"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"

int ft_parser(void);
int ft_executer(void);
int ft_expander(void);
int ft_lexer(void);

/**   BUILTINS  **/
int ft_echo(char *str);
int ft_cd(char *str);
int ft_pwd(char *str);
int ft_export(char *str);
int ft_unset(char *str);
int ft_env(char *str, char **envp);
int ft_exit(char *str);
#endif