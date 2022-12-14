/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odan <odan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 17:55:53 by nedebies          #+#    #+#             */
/*   Updated: 2022/09/07 18:36:16 by odan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	read_heredoc(const char *end, int *fd)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	close(fd[0]);
	while (1)
	{
		line = readline("> ");
		if (strncmp(line, end, ft_strlen(line)) == 0 && *line)
			break ;
		rl_redisplay();
		ft_putstr_fd(line, fd[1]);
		ft_putchar_fd('\n', fd[1]);
		free(line);
	}
	free(line);
	close(fd[1]);
	exit(EXIT_SUCCESS);
}

static int	heredoc(t_cmnd *cmd, const char *end_file)
{
	int				fd[2];
	pid_t			id;
	struct termios	*attr_out;
	struct termios	*attr_in;

	attr_out = (struct termios *)malloc(sizeof(struct termios));
	attr_in = (struct termios *)malloc(sizeof(struct termios));
	if (!attr_out || !attr_in)
		return (0);
	pipe(fd);
	tcgetattr(STDOUT_FILENO, attr_out);
	tcgetattr(STDIN_FILENO, attr_in);
	id = fork();
	signal(SIGINT, SIG_IGN);
	if (id == 0)
		read_heredoc(end_file, fd);
	close(fd[1]);
	waitpid(id, NULL, 0);
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, attr_out);
	tcsetattr(STDIN_FILENO, TCSANOW, attr_in);
	free(attr_out);
	free(attr_in);
	dup2(fd[0], cmd->in_file);
	close(fd[0]);
	return (0);
}

static void	ft_check_fd(t_cmnd *cmd, t_redir **rd, t_list *lst)
{
	*rd = lst->content;
	if ((*rd)->mode == MODE_READ || (*rd)->mode == MODE_HEREDOC)
	{
		if (cmd->in_file)
			close(cmd->in_file);
	}
	else if ((*rd)->mode == MODE_APPEND || (*rd)->mode == MODE_WRITE)
	{
		if (cmd->out_file)
			close(cmd->out_file);
	}
}

int	ft_redir(t_cmnd *cmd, t_list *lst, int i)
{
	t_redir	*rd;

	while (lst)
	{
		ft_check_fd(cmd, &rd, lst);
		if (rd->mode == MODE_READ && i == rd->idx)
			cmd->in_file = open(rd->name, O_RDONLY);
		else if (rd->mode == MODE_WRITE && i == rd->idx)
			cmd->out_file = open(rd->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (rd->mode == MODE_APPEND && i == rd->idx)
			cmd->out_file = open(rd->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (rd->mode == MODE_HEREDOC && i == rd->idx)
			heredoc(cmd, rd->name);
		lst = lst->next;
		if (ft_no_file_dir(cmd->in_file, rd->name))
			return (1);
		else if (ft_no_file_dir(cmd->out_file, rd->name))
			return (1);
	}
	return (0);
}

void	ft_init_file(t_list *lst, t_cmnd *cmd, t_shell *data, int idx)
{
	char	*file;
	t_redir	*redir;

	if (!lst)
		return ;
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return ;
	lst->next->content = parse_line(lst->next->content, data, -1);
	file = lst->next->content;
	if (!ft_strncmp(lst->content, "<<", 3))
		redir->mode = MODE_HEREDOC;
	else if (!ft_strncmp(lst->content, ">>", 3))
		redir->mode = MODE_APPEND;
	else if (!ft_strncmp(lst->content, ">", 2))
		redir->mode = MODE_WRITE;
	else if (!ft_strncmp(lst->content, "<", 2))
		redir->mode = MODE_READ;
	redir->name = ft_strdup(file);
	if (redir->mode > 0)
		redir->idx = idx;
	else
		redir->idx = -1;
	ft_lstadd_back(&cmd->redir, ft_lstnew(redir));
}
