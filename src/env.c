/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:33:09 by skteifan          #+#    #+#             */
/*   Updated: 2025/07/01 21:33:09 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key(char *s)
{
	int		i;
	int		j;
	char	*key;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	key = malloc(i + 1);
	if (!key)
		return (NULL);
	j = 0;
	while (j < i)
	{
		key[j] = s[j];
		j++;
	}
	key[j] = '\0';
	return (key);
}

char	*get_value(char *s)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	i++;
	value = malloc(ft_strlen(s) - i + 1);
	if (!value)
		return (NULL);
	j = 0;
	while (s[i] != '\0')
		value[j++] = s[i++];
	value[j] = '\0';
	return (value);
}

t_env	*create_env_var(char *key, char *value)
{
	t_env	*env_var;

	env_var = malloc(sizeof(t_env));
	if (!env_var)
		return (NULL);
	env_var->key = key;
	env_var->value = value;
	env_var->next = NULL;
	return (env_var);
}

void	add_env_var_at_end(t_env *env_var, t_env **env_list)
{
	t_env	*ptr;

	if (env_var == NULL)
		return ;
	if (*env_list == NULL)
	{
		*env_list = env_var;
		return ;
	}
	ptr = *env_list;
	while (ptr)
	{
		if (ptr->next == NULL)
		{
			ptr->next = env_var;
			return ;
		}
		ptr = ptr->next;
	}
}

int	build_env_list(char **envp, t_env **env_list)
{
	int		i;
	char	*key;
	char	*value;
	t_env	*env_var;

	i = 0;
	while (envp[i] != NULL)
	{
		key = get_key(envp[i]);
		value = get_value(envp[i]);
		if (!key || !value)
		{
			if (key)
				free(key);
			if (value)
				free(value);
			return (1);
		}
		env_var = create_env_var(key, value);
		if (!env_var)
			return (1);
		add_env_var_at_end(env_var, env_list);
		i++;
	}
	return (0);
}
