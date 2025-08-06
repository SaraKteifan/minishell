/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 14:30:22 by skteifan          #+#    #+#             */
/*   Updated: 2025/08/05 11:33:35 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **args)
{
	if (args[1] == NULL)
	{
		perror("cd: expected argument");
		return (1);
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("cd");
			return (1);
		}
	}
	return (0);
}
