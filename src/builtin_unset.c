/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 14:31:10 by skteifan          #+#    #+#             */
/*   Updated: 2025/08/05 11:52:22 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **args, t_env **env_list)
{
	t_env	*env;
	t_env	*prev;

	env = *env_list;
	prev = NULL;
	if (args[1] == NULL)
	{
		printf("unset: Too few arguments\n");
		return (1);
	}
	while (env)
	{
		if (ft_strncmp(env->key, args[1], -1) == 0)
		{
			if (prev)
			{
				prev->next = env->next;
			}
			else
			{
				*env_list = env->next;
			}
			free(env->key);
			free(env->value);
			free(env);
			return (0);
		}
		prev = env;
		env = env->next;
	}
	printf("unset: %s: variable not found\n", args[1]);
	return (1);
}
