/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 17:55:08 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/31 14:03:07 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	put_in_mid_line(char **line, char *str, int start, int end)
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

static int	dollar(char **line, int start, t_shell *data)
{
	int		i;
	char	*str;
	char	*tmp;

	i = 0;
	while ((*line)[start + i + 1] && !(is_end((*line)[start + i + 1])))
		i++;
	tmp = ft_substr(*line, start + 1, i);
	str = ft_getenv(data->envp_list, tmp);
	if (!str)
	{
		free(tmp);
		return (-1);
	}
	free(tmp);
	put_in_mid_line(line, str, start, start + i);
	return (1);
}

static	int	del_quotes(char **line, int start, t_shell *data, int flag)
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
			if (dollar(line, end, data) == -1)
				end++;
		}
		else if ((*line)[end] == quotes)
			break ;
		else
			end++;
	}
	mid = ft_substr(*line, start + 1, end - start - 1);
	if (flag)
		*line -= 1;
	put_in_mid_line(line, mid, start, end);
	free(mid);
	return (end - 2);
}

static int	dollar_quotes(char **line, int start, t_shell *data)
{
	int	i;

	i = 0;
	*line += 1;
	i = del_quotes(line, start, data, 1);
	return (i);
}

/** Deal with metachar (quotes and $) in the line **/
char	*parse_line(char *line, t_shell *data, int i)
{
	if (!*line)
		return (NULL);
	while (line[++i])
	{
		if (line[i] == '$' && (line[i + 1] == '\'' || line[i + 1] == '\"'))
		{
			i = dollar_quotes(&line, i, data);
			if (i == -1)
				break ;
		}
		else if (line[i] == '\'' || line[i] == '\"')
		{
			i = del_quotes(&line, i, data, 0);
			if (i == -1)
				break ;
		}
		else if (line[i] == '$')
		{
			i = dollar(&line, i, data);
			if (i == -1)
				break ;
		}
	}
	return (line);
}
