/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 14:31:30 by skteifan          #+#    #+#             */
/*   Updated: 2025/08/03 09:25:11 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **args, t_env *env_list)
{
	(void)args;
	(void)env_list;
	ft_putstr_fd("This is exit\n", STDOUT_FILENO);
	return (0);
}
