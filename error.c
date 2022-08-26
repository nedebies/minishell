/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:09:45 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/26 14:14:42 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_print_error(t_list **is_head, const char *str, int nbr)
{
	char	*name;

	if (str)
		perror(str);
	if (nbr < 0)
		nbr = EXIT_FAILURE;
	name = ft_itoa(nbr);
	ft_putenv(is_head, "?", name);
	free(name);
	return (nbr);
}

void	ft_print_err_export(char *str)
{
	ft_putstr_fd("export: \'", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
}
