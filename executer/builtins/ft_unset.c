/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:38:59 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/24 10:10:01 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_unset(char **av)
{
	t_env	*to_del;
	int		exit_code;

	exit_code = EXIT_SUCCESS;
	if (!*(av + 1))
		return (exit_code);
	av++;
	while (*av)
	{
		if (check_option(*av) == EXIT_FAILURE)
			exit_code = throw_error_usage("unset", *av) + 1;
		else if (ft_strchr(*av, '='))
			exit_code = throw_error_env("unset", *av);
		else if (valid_env_name(*av) == EXIT_FAILURE)
			exit_code = throw_error_env("unset", *av);
		else
		{
			to_del = get_env(*av);
			if (to_del)
				remove_env(to_del);
		}
		av++;
	}
	return (exit_code);
}