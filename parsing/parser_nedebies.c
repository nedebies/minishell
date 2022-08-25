/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_nedebies.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:00:37 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/25 18:56:50 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/** Return the quotes tokens' lenghts **/
int	len_quotes(char *line, int i)
{
	char	quotes;
	int		len;

	len = 0;
	quotes = line[i];
	len++;
	while (line[i + len] != quotes)
		len++;
	return (len + 1);
}

/** Return the lenght of a token **/
static int	len_token(char *line, int i)
{
	int	len;

	len = 0;
	if (line[i] == '<' || line[i] == '>')
	{
		i++;
		if (line[i] == '<' || line[i] == '>')
			return (2);
		return (1);
	}
	if (line[i] == '|')
		return (1);
	if (line[i] == '\"' || line[i] == '\'')
		return (len_quotes(line, i));
	while (line[i + len])
	{
		if (line[i + len] == ' ' || line[i + len] == '\t')
			return (len);
		if (line[i + len] == '<' || line[i + len] == '>')
			return (len);
		if (line[i + len] == '|')
			return (len);
		len++;
	}
	return (len);
}

/** Create a tokens' t_list **/
t_list	*get_tokens(char *line, t_list *token)
{
	int		len;
	int		i;
	char	*tmp;

	len = 0;
	i = 0;
	while (line[i])
	{
		while ((line[i] == ' ' || line[i] == '\t') && line[i])
			i++;
		len = len_token(line, i);
		tmp = ft_substr(line, i, len);
		ft_lstadd_back(&token, ft_lstnew(tmp));
		i += len;
	}
	return (token);
}

/** Check if the line's empty or if it's full of whitespaces **/
static	int	check_empty_line(char *line)
{
	if (!*line)
	{
		free(line);
		return (1);
	}
	while ((*line == ' ' || *line == '\t') && *line)
		line++;
	if (!*line)
		return (1);
	return (0);
}

/** Throw the error in case of unclosed quotes**/
static char	*print_quotes_er(char quotes)
{
	if (quotes == '\'')
		ft_putstr_fd("minishell: unclosed single quote error\n", 2);
	else
		ft_putstr_fd("minishell: unclosed double quote error\n", 2);
	return (NULL);
}

/** Print generic errors about tokens **/
static char	*print_er(char *error)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	return (NULL);
}

/** Check if quotes are closed and if pipes aren't doubled **/
static char	*ft_check_sign(char *line, char quotes, int *count_cmd)
{
	if (*line == '\'' || *line == '\"')
	{
		quotes = *line;
		line++;
		while (*line != quotes && *line)
			line++;
		if (*line != quotes)
			return (print_quotes_er(quotes));
	}
	if (*line == '|')
	{
		(*count_cmd)++;
		line++;
		if (*line == '|')
			return (print_er("`|'"));
	}
	else
		line++;
	return (line);
}

/** Check at first it the line is empty or check if the line doesn't end with a special char **/
int	pre_parse(char *line)
{
	char	quotes;
	int		count_cmd;

	count_cmd = 1;
	if (check_empty_line(line))
		return (-1);
	while (*line)
	{
		quotes = '0';
		line = ft_check_sign(line, quotes, &count_cmd);
		if (!line)
			return (-1);
	}
	if (*(line - 1) == '|' || *(line - 1) == '<' || *(line - 1) == '>')
	{
		print_er("`newline'");
		return (-1);
	}
	return (count_cmd);
}

int	parser(char *line, t_cmnd *cmds)
{
	t_list	*tokens;

	tokens = NULL;
	g_manager.count_cmd = pre_parse(line);
	if (g_manager.count_cmd == -1)
	{
		//throw error
		return (1);
	}
	tokens = get_tokens(line, tokens);
	cmds = malloc(sizeof(t_cmnd) * g_manager.count_cmd);
	if (!g_manager.count_cmd)
		return (1);
	ft_memset(cmds, '\0', sizeof(t_cmnd) * g_manager.count_cmd);
	init_cmds(tokens, cmds); // TO FINISH
	free(line);
	ft_lstclear(&tokens, free);
	return (0);
}
