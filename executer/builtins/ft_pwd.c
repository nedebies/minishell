/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:36:57 by nedebies          #+#    #+#             */
/*   Updated: 2022/08/26 14:12:18 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_builtin_pwd(t_list **is_head_env)
{
	char	*str;

	str = ft_getenv(*is_head_env, "PWD");
	if (str)
		printf("%s\n", str);
	ft_print_error(is_head_env, NULL, 0);
}