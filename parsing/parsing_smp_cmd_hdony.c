/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_smp_cmd_hdony.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdony <hdony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:55:09 by hdony             #+#    #+#             */
/*   Updated: 2022/08/24 18:09:38 by hdony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*return 0 if there is no METACHAR and no options in the cmd*/
int check_content(char *str)
{
    if((!get_metachar_len(str, NULL)) && !(check_option(str)))
        return (0);
    return (1);
}

/*check if options and redicrections in smpl cmd*/
int check_smpl_cmd_content(char **cmd)
{
    int i;

    i = 0;
    while (cmd[i] != 0)
    {
        if (check_content(cmd[i]))
            return(1);
        i++;
    }
    return (0);
}

void    initialize_cmnd(t_cmnd *cmnd)
{
    cmnd->executable = NULL;
    cmnd->argv = NULL;
}

void    populate_exec(char *str, t_cmnd *cmnd)
{
    cmnd->executable = str;
}

void    populate_args(char *str, char **argv)
{
    static int  i = 0;

    argv[i] = str;
    printf("argv: %s\n", argv[i]);
    i++;
}

void    allocate_args(char **cmd, t_cmnd *cmnd, int ac)
{
    int i;
    int j;

    i = 0;
    j = -1;

    cmnd->argv = malloc(sizeof(char *) * (ac + 1));
    cmnd->argv[ac] = 0;
    while (cmd[++i])
    {
        cmnd->argv[++j] = cmd[i];
    }
}
 
t_cmnd   *ft_parse_smpl_cmd(char **cmd)
{
    t_cmnd  *cmnd;
    int     ac;

    ac = args_count(cmd, 0);
    cmnd = malloc(sizeof(*cmnd));
    if (!cmnd)
        return (NULL);
    initialize_cmnd(cmnd);
    populate_exec(cmd[0], cmnd);
    allocate_args(cmd, cmnd, ac);
    return (cmnd);
}