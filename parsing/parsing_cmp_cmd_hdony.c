/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmp_cmd_hdony.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:27:32 by hdony             #+#    #+#             */
/*   Updated: 2022/08/24 09:34:39 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int parsing_check_metachar(char *str)
{
    if (!ft_strncmp(str, "LESS", 4))
        return (1);
    else if (!ft_strncmp(str, "LESSLESS", 8))
        return (1);
    else if (!ft_strncmp(str, "GREAT", 5))
        return (1);
    else if (!ft_strncmp(str, "GREATGREAT", 10))
        return (1);
    return (0);
}

/*if no METACHAR & no redirections, returns 0*/
int check_left_ofpipe(char **cmd)
{
    int i;

    i = 0;
    while (ft_strncmp(cmd[i], "PIPE", 4) && cmd[i] != 0)
    {
        if (parsing_check_metachar(cmd[i]) || check_option(cmd[i]))
            return(1);
        i++;
    }
    return (0);
}
