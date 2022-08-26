/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:41:01 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/26 14:57:48 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	ft_return_error_isnum(t_shell *data, int num_cmd, int i)
{
	printf("exit: %s : numeric positive argument required\n", \
			data->cmd[num_cmd].arguments[i]);
	ft_print_error(&data->head_env, NULL, 1);
}

static void	ft_return_error_args(t_shell *data)
{
	printf("exit: too many arguments\n");
	ft_print_error(&data->head_env, NULL, 1);
}

static void	ft_set_retcode(t_shell *data, int num_cmd)
{
	if (ft_atoi(data->cmd[num_cmd].arguments[1]) > 255)
		ft_print_error(&data->head_env, NULL, 255);
	else
		ft_print_error(&data->head_env, NULL, \
						ft_atoi(data->cmd[num_cmd].arguments[1]));
}

void	ft_builtin_exit(t_shell *data, int num_cmd)
{
	int	i;
	int	num_flags;

	i = 1;
	num_flags = 0;
	while (data->cmd[num_cmd].arguments[i])
	{
		if (!ft_isnumber(data->cmd[num_cmd].arguments[i]))
		{
			ft_return_error_isnum(data, num_cmd, i);
			return ;
		}
		num_flags++;
		i++;
	}
	if (num_flags > 1)
	{
		ft_return_error_args(data);
		return ;
	}
	if (i > 1)
		ft_set_retcode(data, num_cmd);
        ft_putstr_fd("exit\n", 1);
	ft_exit(data);
}
