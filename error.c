/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:09:45 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/26 02:41:33 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
static int	ft_len_nbr(long d)
{
	int	len;

	len = 1;
	if (d < 0)
	{
		d = -d;
		len += 1;
	}
	while (d >= 10)
	{
		len++;
		d /= 10;
	}
	return (len);
}

static char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		i;
	long	nbr;

	nbr = n;
	i = 0;
	len = ft_len_nbr(nbr);
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	if (nbr < 0)
	{
		nbr = -nbr;
		str[i] = '-';
	}
	str[len - i++] = '\0';
	while (nbr >= 10)
	{
		str[len - i++] = (nbr % 10) + '0';
		nbr /= 10;
	}
	str[len - i] = (nbr % 10) + '0';
	return (str);
}

int	ft_print_error(const char *str, int nbr)
{
	char	*name;

	if (str)
		perror(str);
	if (nbr < 0)
		nbr = EXIT_FAILURE;
	name = ft_itoa(nbr);
	add_env("?", name);
	free(name);
	return (nbr);
}

void	ft_print_err_export(char *str)
{
	ft_putstr_fd("export: \'", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
}


int	check_option(char *argv)
{
	int	exit_code;

	exit_code = EXIT_SUCCESS;
	if (*argv == '-')
		exit_code = EXIT_FAILURE;
	return (exit_code);
}

int	throw_error(char *cmd, char *argv, char *err)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (argv)
	{
		ft_putstr_fd(argv, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(err, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	throw_error_usage(char *cmd, char *argv)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	write(STDERR_FILENO, argv, 2);
	ft_putstr_fd(": invalid option\n", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": usage: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	throw_error_synthax(char *cmd, char *argv)
{
	ft_putstr_fd("not-bash: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	write(STDERR_FILENO, argv, 2);
	ft_putstr_fd(": invalid option\n", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": usage: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	throw_error_env(char *cmd, char *argv)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("`", STDERR_FILENO);
	ft_putstr_fd(argv, STDERR_FILENO);
	ft_putstr_fd("\': not a valid identifier\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	throw_error_exit(char *cmd, char *err, int exit_code)
{
	g_manager.exit_code = exit_code;
	throw_error(cmd, 0, err);
	exit(g_manager.exit_code);
	return (EXIT_FAILURE);
}