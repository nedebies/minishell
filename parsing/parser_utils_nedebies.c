/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_nedebies.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 16:58:45 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/25 22:42:19 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
static int	is_end(int c)
{
	if (c == '_')
		return (0);
	if (ft_isalpha(c))
		return (0);
	if (ft_isdigit(c))
		return (0);
	if (c == '?')
		return (0);
	return (1);
}

int	put_in_mid_line(char **line, char *str, int start, int end)
{
	char	*head;
	char	*tail;
	char	*tmp;

	head = ft_substr(*line, 0, start);
	tail = ft_substr(*line, end + 1, ft_strlen(*line) - end - 1);
	free(*line);
	*line = ft_strjoin(head, str);
	tmp = ft_strdup(*line);
	free(*line);
	*line = ft_strjoin(tmp, tail);
	free(tmp);
	free(head);
	free(tail);
	return (0);
}

static int	dollar(char **line, int start)
{
	int		i;
	char	*str;
	char	*tmp;

	i = 0;
	while ((*line)[start + i + 1] && !(is_end((*line)[start + i + 1])))
		i++;
	tmp = ft_substr(*line, start + 1, i);
	str = g_manager.env->value;
	if (!str)
	{
		free(tmp);
		return (-1);
	}
	free(tmp);
	put_in_mid_line(line, str, start, start + i);
	return (1);
}

static	int	del_quotes(char **line, int start)
{
	char	quotes;
	char	*mid;
	int		end;

	end = start + 1;
	quotes = (*line)[start];
	while ((*line)[end])
	{
		if ((*line)[end] == '$' && quotes == '\"')
		{
			if (dollar(line, end) == -1)
				end++;
		}
		else if ((*line)[end] == quotes)
			break ;
		else
			end++;
	}
	mid = ft_substr(*line, start + 1, end - start - 1);
	put_in_mid_line(line, mid, start, end);
	free(mid);
	return (end - 2);
}

char	*parse_line(char *line)
{
	int	i;

	i = 0;
	if (!*line)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			i = del_quotes(&line, i);
			if (i == -1)
				break ;
		}
		else if (line[i] == '$')
		{
			i = dollar(&line, i);
			if (i == -1)
				break ;
		}
		i++;
	}
	return (line);
}
int     ft_count_args(t_list *lst)
{
    int     i;
    char    *token;

    i = 0;
    token = lst->content;
    while (lst)
    {
        if (*token == '|' || *token == '<' || *token == '>')
            break ;
        else
        {
            i++;
            lst = lst->next;
        }
    }
    return (i);
}

/** Create a tab with the arguments only **/
char    **init_args(t_list *lst)
{
	int		count_args;
	char	**args;
	int		i;

	i = 0;
	count_args = ft_count_args(lst);
	args = malloc((sizeof(char *) * count_args) + 1);
	if (!args)
		return (NULL);
	memset(args, '\0', sizeof(char *) * count_args + 1);
	while (i < count_args)
	{
		lst->content = parse_line(lst->content);
		args[i] = ft_strdup(lst->content);
		lst = lst->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

void	ft_init_file(t_list *lst, t_cmnd cmd)
{
	char	*file;
	t_redir	*redir;

	if (!lst)
		return ;
	redir = malloc(sizeof(t_redir));
	lst->next->content = parse_line(lst->next->content);
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
	ft_lstadd_back(&cmd.redir, ft_lstnew(redir));
}

/** Create a t_cmnd struct according to its tokens **/
void init_cmds(t_list *lst, t_cmnd *cmds)
{
    int i;
    char *token;

    token = lst->content;
    i = 0;
    if (!lst)
        return ;
    while (lst)
    {
        if (*token == '>' || *token == '<')
        {
            ft_init_file(lst, cmds[i]);
            lst = lst->next->next;
        }
        else if (*token == '|')
        {
            i++;
            lst = lst->next;
        }
        else
        {
            cmds[i].executable = ft_strdup(token);
            cmds[i].executable = parse_line(cmds[i].executable);
            cmds[i].argv = init_args(lst);
        }
    }
}