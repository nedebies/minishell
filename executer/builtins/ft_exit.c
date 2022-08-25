/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:41:01 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/24 10:08:08 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int      only_digits(char *s)
{
        int i;

        i = -1;
        if (check_option(s) == EXIT_FAILURE)
                i = 0;
        while(s[++i])
        {
                if(!ft_isdigit(s[i]))
                        return(0);
        }
        return (1);
}

int ft_exit(char **av)
{
        int     arg;
        arg = 0;
        while (av[arg])
                arg++;
        ft_putstr_fd("exit\n", 1);
	if (av[0] && !only_digits(av[0]))
		return (throw_error("exit", *av, "numeric argument required"));
        if (arg > 2)
		return (throw_error("exit", 0, "too many arguments"));
        free_env();
        ft_free_split(av);
        exit(EXIT_SUCCESS);
}