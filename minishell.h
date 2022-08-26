/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:30:29 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/26 12:51:10 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <curses.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <limits.h>
# include <errno.h>
# include <termios.h>

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
}						t_manager;

typedef struct s_redir{
	char	*name;
	char	mode;
}				t_redir;

typedef struct    s_cmd
{
    char            *cmd;
    char            **arguments;
	int             in_file;
	int             out_file;
    t_list			*redir;
}                t_cmd;

typedef struct s_mshl{
	t_cmd	*cmd;
	int		count_cmd;
}				t_mshl;

extern t_manager		g_manager;
t_manager		g_manager;

/* ERRORS (by nedebies)*/
int	check_option(char *argv);
int	throw_error(char *cmd, char *argv, char *err);
int	throw_error_exit(char *cmd, char *err, int exit_code);
int	throw_error_usage(char *cmd, char *argv);
int	throw_error_env(char *cmd, char *argv);
int	ft_print_error(const char *str, int nbr);
void	ft_print_err_export(char *str);

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

/** EXEC (by nedebies) **/
int	ft_executer(t_mshl *data);
int exec_builtins(t_mshl *cmnd, int i);

/** PARSER (by hdony & odan) **/
/**
void        ft_parser(char **cmd);
int         check_content(char *str);
int         check_smpl_cmd_content(char **cmd);
int         check_left_ofpipe(char **cmd);
t_cmnd      *ft_parse_smpl_cmd(char **cmd);
int         args_count(char **cmd, int j);**/

void	ft_dup_fd(int i, int **fd, t_mshl *data);
char	**list2mass_env(t_list *lst);
int	set_exit_status(int exit_status);
void	ft_free_arr(char **arr);
char	*join_path(char *cmd, char **path);
int	ft_check_open(int fd, char *name);
int	read_heredoc(const char *end, int *fd);
int	heredoc(t_cmd *cmd, const char *end_file);
int	ft_redir(t_cmd *cmd, t_list *lst);
void	ft_init_file(t_list *lst, t_cmd *cmd);
int	put_in_mid_line(char **line, char *str, int start, int end);
char	*parse_line(char *line);
int	init_cmd(t_list *lst, t_mshl *mini);
int	len_quotes(char *line, int i);
t_list	*get_tokens(char *line, t_list *token);
int	ft_insnewlst(t_list **is_head, char *name, char *val);
int	pre_parse(char *line);
int	parser(char *line, t_mshl *mini);

/** ENV (by nedebies & hdony) **/
void	free_env(void);
int	valid_env_name(char *identifier);
void	remove_env(t_env *target);
t_env	*get_env(char *identifier);
char	*get_env_value(char *argv);
char	*get_env_name(char *argv);
void	add_env(char *name, char *value);
int	count_var_nbr(void);
char	**new_envp(void);

/** SIGNAL HANDLING (by nedebies) **/
void	init_signal(void);
void	handle_sigint(int signo);
void	handle_sigint2(int signo);

/**   BUILTINS (by nedebies) **/
int	is_builtin(t_mshl *data, int num_cmd);
int ft_echo(char **split);
int ft_cd(char **split);
int ft_pwd(char **envp);
int ft_export(char **split);
int ft_unset(char **split);
int ft_env(char **envp);
int ft_exit();

/** PROCESS (by nedebies) **/
void	process(t_mshl *data, char **envp, int i, int **fd);
int	ft_create_pipe(int **fd, t_mshl *data);
void	ft_close_fd(int *fd[2], t_mshl *data);
int	ft_processing(pid_t	*id, t_mshl *data, char **envp);

#endif