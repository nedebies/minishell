/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:30:29 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/25 22:43:49 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <sys/wait.h>

# define READ 0
# define WRITE 1
# define ERROR 2
# define BACKUP_FD 255

# define METACHAR "<>|"
# define QUOTES         "\'\""
# define SPACES         "\f\r\v\t\n' '"

# define ERROR_FLAG -1
# define SUCCESS_FLAG 0
# define EXIT_EACCES 126
# define EXIT_ENOENT 127
# define EXIT_MAX 255
# define EXIT_SYNTAXERR 258

# define MODE_APPEND 1
# define MODE_READ 2
# define MODE_WRITE 3
# define MODE_HEREDOC 4

typedef struct  s_redir{
	char	*name;
	char	mode;
}				t_redir;

typedef struct  s_env
{
    char            *name;
    char            *value;
    struct s_env    *next;
}               t_env;

typedef struct  s_manager
{
	t_env				*env;
	int					exit_code;
    int                 count_cmd;
}						t_manager;

typedef struct    s_cmnd
{
    char            *executable;
    char            **argv;
    t_list			*redir;
    struct s_cmnd   *next;
}                t_cmnd;

typedef enum	s_redir_type
{
	GREAT,
	DGREAT,
	LESS,
	DLESS,
}				t_redir_type;

extern t_manager		g_manager;
t_manager		g_manager;

/* ERRORS (by nedebies)*/
int	check_option(char *argv);
int	throw_error(char *cmd, char *argv, char *err);
int	throw_error_exit(char *cmd, char *err, int exit_code);
int	throw_error_usage(char *cmd, char *argv);
int	throw_error_env(char *cmd, char *argv);

int ft_expander(void);

/** LEXER (by hdony) **/
char    **lexer(char *str);
int     ft_string_count(char **tab);
int     get_text_len(char *str);
int     get_metachar_len(char *str, char **metachar_mark);
void	check_token(char **tab, int sc);
int 	ft_find_text(char *str, int metachar_len);
void 	handle_text_metachar_1(char **tab2, char *str, char *metachar_mark, int *text_len, int *j);
void    ft_print_tab(char **tab2);

/** PARSER (by hdony & odan) **/
/**
void        ft_parser(char **cmd);
int         check_content(char *str);
int         check_smpl_cmd_content(char **cmd);
int         check_left_ofpipe(char **cmd);
t_cmnd      *ft_parse_smpl_cmd(char **cmd);
int         args_count(char **cmd, int j);**/

int	put_in_mid_line(char **line, char *str, int start, int end);
char	*parse_line(char *line);
int     ft_count_args(t_list *lst);
char    **init_args(t_list *lst);
void	ft_init_file(t_list *lst, t_cmnd cmd);
void init_cmds(t_list *lst, t_cmnd *cmds);

int	len_quotes(char *line, int i);
t_list	*get_tokens(char *line, t_list *token);
int	pre_parse(char *line);
int	parser(char *line, t_cmnd *cmds);

void    ft_init_env(char **envp);
char    **ft_free_split(char **split);
void	ft_free_llist(t_cmnd *data);

/** ENV (by nedebies) **/
void	free_env(void);
int	valid_env_name(char *identifier);
void	remove_env(t_env *target);
t_env	*get_env(char *identifier);
char	*get_env_value(char *argv);
char	*get_env_name(char *argv);
void	add_env(char *name, char *value);


/** EXEC (by nedebies) **/
int	ft_executer(t_cmnd *cmnd, char **envp);
int exec_builtins(t_cmnd *cmnd);

/** SIGNAL HANDLING (by nedebies) **/
void	init_signal(void);
void	handle_sigint(int signo);
void	handle_sigint2(int signo);

/**   BUILTINS (by nedebies) **/
// int exec_builtins(t_btree *btree);
int	is_builtin(char *cmd);
int ft_echo(char **split);
int ft_cd(char **split);
int ft_pwd(char **envp);
int ft_export(char **split);
int ft_unset(char **split);
int ft_env(char **envp);
int ft_exit();

/** PROCESS (by nedebies) **/
int	ft_processing(pid_t	*id, t_cmnd *data, char **envp, int cnt_cmd);

#endif