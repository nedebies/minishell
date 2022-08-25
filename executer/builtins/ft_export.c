/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:38:03 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/24 10:09:27 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int find_equal(char *str)
{
    int i;

    i = 0;
    if(!str)
        return (0);
    while (str[i] && str[i] != '=')
        i++;
    if (!str[i])
        return (0);
    return (i);
}

int ft_export(char **split)
{
    t_env   *ptr;

    ptr = g_manager.env;
    if(!split[0] || check_option(split[0]) || !find_equal(split[0]))
        return (throw_error_usage("export", split[0]));
    if (valid_env_name(split[0]) == EXIT_FAILURE)
			return(throw_error_env("unset", *split));
    while (ptr->next)
    {
        if (get_env_name(split[0]) == get_env_name(ptr->name))
        {
            ptr->name = get_env_name(split[0]);
            return(EXIT_SUCCESS);
        }
        ptr = ptr->next;
    }
    add_env(get_env_name(split[0]), get_env_value(split[0]));
    return (EXIT_SUCCESS);
}