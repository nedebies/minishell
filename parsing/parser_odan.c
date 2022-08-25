/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_odan.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orandan <orandan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 23:16:40 by orandan           #+#    #+#             */
/*   Updated: 2022/08/24 23:23:04 by orandan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int	add_str(t_cmnd *cmnd, char *new_str)
{
	char	**new_argv;
	int		i;
	
	i = 0;
	while (cmnd->argv && cmnd->argv[i])
		i++;
	new_argv = malloc(sizeof(char *) * (i + 2));
	if (!new_argv)
		return (-1); // ERROR
	new_argv[i + 1] = NULL;
	new_argv[i] = ft_strdup(new_str); //malloc so needs a free as well
	while (i--)
		new_argv[i] = ft_strdup(cmnd->argv[i]);
	if (cmnd->argv)
	{
		i = 0;
		while (cmnd->argv[i])
			free (cmnd->argv[i++]);
		free (cmnd->argv);
	}
	cmnd->argv = new_argv;
	return (0);
}

int	add_t_redir(t_redir **redir, int type, char *arg)
{
	t_redir	*new;
	t_redir *last;

	new = malloc(sizeof(t_redir) * 1);
	if (!new)
		return (0); // ERROR
	new->type = type;
	new->arg = arg;
	new->next = NULL;
	if (!*redir)
		*redir = new;
	else
	{
		last = *redir;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	return (0);
}

int	parse_redir(t_cmnd **cmnd, char *metachar, char *arg)
{
	if (!ft_strncmp(metachar, ">", 2))
		add_t_redir(&((*cmnd)->out), GREAT, arg);
	else if (!ft_strncmp(metachar, ">>", 3))
		add_t_redir(&((*cmnd)->out), DGREAT, arg);
	else if (!ft_strncmp(metachar, "<", 2))
		add_t_redir(&((*cmnd)->in), LESS, arg);
	else if (!ft_strncmp(metachar, "<<", 3))
		add_t_redir(&((*cmnd)->in), DLESS, arg);
	return (0);	
}

t_cmnd	*parse_nopipes(char **lex)
{
	t_cmnd	*cmnd;
	int		i;

	i = 0;
	cmnd = (t_cmnd *)malloc(sizeof(t_cmnd));
	if (!cmnd)
		return (NULL); // ERROR
	cmnd->executable = lex[i];
	cmnd->argv = NULL;
	cmnd->in = NULL;
	cmnd->out = NULL;
	while (lex[++i] && ft_strncmp(lex[i], "|", 1))
	{
		if (!ft_strchr(METACHAR, lex[i][0]))
			add_str(cmnd, lex[i]);
		else
		{
			if (!lex[i + 1] || ft_strchr(METACHAR, lex[i + 1][0]))
				break ; //ERROR
			parse_redir(&cmnd, lex[i], lex[i + 1]);
			i++;
		}
	}
	return (cmnd);
}
