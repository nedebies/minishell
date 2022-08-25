/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_hdony.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdony <hdony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:27:03 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/24 18:56:10 by hdony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_for_add_pipes(char **cmd, int *i)
{
    printf("cmd[i]: %s\n", cmd[*i]);
    *i += 1;
    while (cmd[*i])
    {
        if (!ft_strncmp(cmd[*i], "PIPE", 4))
            return (1);
        *i += 1;
    }
    return (0);
}

/*static void print_list(t_cmnd *cmnd)
{
    t_cmnd *index;
    int     i;

    index = cmnd;
    i = 0;
    while (index->next != NULL)
    {
        printf("node %d: %p\n", i, index);
        printf("node %d: %s\n", i, index->executable);
        index = index->next;
        i++;
    }
}*/

t_cmnd *last_node(t_cmnd *cmnd)
{
	t_cmnd    *tmp;

	tmp = cmnd;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	return (tmp);
}

t_cmnd  *create_node(void)
{
    t_cmnd *node;
    
    node = malloc(sizeof(*node));
    if (!node)
        return (NULL);
    return (node);
}

static void    create_add_node(t_cmnd *cmnd)
{
    t_cmnd *node;
    t_cmnd *tmp;

    node = create_node();
    if (cmnd->next == NULL)
    {
        cmnd->next = node;
    }
    else
    {
        tmp = last_node(cmnd);
        tmp->next = node;
    }
}

int args_count(char **cmd, int j)
{
    int i;

    i = j;
    // printf("cmd[j]: %s\n", cmd[j]);
    while (cmd[j] != 0 && ft_strncmp(cmd[j], "PIPE", 4))
        j++;
    if (j == i)
        return (0);
    else
        return (j);
}

/*check if there are pipes in the cmd*/
static int check_lexer_content(char **cmd)
{
    int pc;
    int i;

    pc = 0;
    i = 0;
    while (cmd[i] != 0)
    {
        if (!ft_strncmp(cmd[i], "PIPE", 4))
            pc ++;
        i++;
    }
    return (pc);
}

void    init_cmnd(t_cmnd *cmnd)
{
    cmnd->executable = NULL;
    cmnd->argv = NULL;
    cmnd->next = NULL;
}

int len_cmd(char **cmd)
{
    int i;

    i = 0;
    while (cmd[i])
    {
        printf("%s\n", cmd[i]);
        i++;
    }
    return (i);
}

void    ft_parser(char **cmd)
{
    int i;
    int j;
    int k;
    int pc;
    int ac;
    int len;
    t_cmnd  *cmnd;

    i = 0;
    j = 0;
    k = 0;
    ac = 0;
    len = len_cmd(cmd);
    pc = check_lexer_content(cmd);
    // printf("pc: %d\n", pc);
    printf("len: %d\n", len);
    cmnd = malloc(sizeof(*cmnd));
    if (!cmnd)
        return ;  //free
    init_cmnd(cmnd);
    while (i <= pc)
    {
        write(1, "4\n", 2);
        while(ft_strncmp(cmd[j], "PIPE", 4) && cmd[j] != 0)
        {
            printf("cmd[j]: %s\n", cmd[j]);
            if (j == 0 || ((cmd[j - 1]) && !ft_strncmp(cmd[j - 1], "PIPE", 4)))
            {
                cmnd->executable = ft_strdup(cmd[j++]);
                printf("exec: %s\n", cmnd->executable);
            }
            ac = args_count(cmd, j);
            printf("ac: %d\n", ac);
            printf("j: %d\n", j);
            if (ac)
            {
                printf("ac\n");
                cmnd->argv = malloc(sizeof(char *) * ac + 1);
                while (ac > 0)
                {
                    cmnd->argv[k++] = ft_strdup(cmd[j++]);
                    ac--;
                }
                cmnd->argv[k] = 0;
                k = 0;
                j += ac;
            }
            write(1, "1\n", 2);
            printf("cmd[j]: %s\n", cmd[j]);
            if (cmd[j])
            {
                write(1, "2\n", 2);
                j++;
                create_add_node(cmnd);
            }
            write(1, "3\n", 2);
        }
        write(1, "5\n", 2);
        i++;
    }
}