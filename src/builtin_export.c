/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 13:22:04 by skteifan          #+#    #+#             */
/*   Updated: 2025/08/05 11:51:13 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_env_variable(t_minishell *minishell, char *key, char *value)
{
	t_env	*env;
	t_env	*new_env;

	env = minishell->env_list;
	while (env)
	{
		if (ft_strncmp(env->key, key, -1) == 0)
		{
			free(env->value);
			env->value = ft_strdup(value);
			return (0);
		}
		env = env->next;
	}
	new_env = malloc(sizeof(t_env));
	new_env->key = ft_strdup(key);
	new_env->value = ft_strdup(value);
	new_env->next = minishell->env_list;
	minishell->env_list = new_env;
	return (0);
}

int	handle_export(t_minishell *minishell, char *key, char *value)
{
	if (key && value)
	{
		return (update_env_variable(minishell, key, value));
	}
	else
	{
		printf("export: invalid syntax. Expected format: KEY=VALUE\n");
		return (1);
	}
}

int	ft_export(t_minishell *minishell, char **args)
{
	char	*key;
	char	*value;
	t_env	*env;

	if (args[1] != NULL)
	{
		key = args[1];
		value = ft_strchr(key, '=');
		if (value)
		{
			*value = '\0';
			value++;
			return (handle_export(minishell, key, value));
		}
		else
		{
			printf("export: invalid syntax. Expected format: KEY=VALUE\n");
			return (1);
		}
	}
	else
	{
		env = minishell->env_list;
		while (env)
		{
			printf("declare -x ");
			printf("%s=%s\n", env->key, env->value);
			env = env->next;
		}
		return (0);
	}
}
