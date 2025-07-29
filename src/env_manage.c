/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 20:27:44 by skteifan          #+#    #+#             */
/*   Updated: 2025/07/05 20:27:44 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_get(t_env **env_list, char *key)
{
	t_env	*ptr;

	ptr = *env_list;
	while (ptr)
	{
		if (ft_strncmp(key, ptr->key, ft_strlen(key) + 1) == 0)
			return (ptr->value);
		ptr = ptr->next;
	}
	return (NULL);
}

int	env_set(t_env **env_list, char *key, char *value)
{
	t_env	*env_var;

	env_var = create_env_var(key, value);
	if (!env_var)
		return (1);
	add_env_var_at_end(env_var, env_list);
	return (0);
}

int	env_unset(t_env **env_list, char *key)
{
	t_env	*temp;
	t_env	*current;

	while (*env_list && ft_strncmp(key, (*env_list)->key,
			ft_strlen(key) + 1) == 0)
	{
		temp = *env_list;
		*env_list = (*env_list)->next;
		free_env_var(temp);
	}
	current = *env_list;
	while (current && current->next)
	{
		if (ft_strncmp(key, current->next->key, ft_strlen(key) + 1) == 0)
		{
			temp = current->next;
			current->next = current->next->next;
			free_env_var(temp);
		}
		else
			current = current->next;
	}
	return (0);
}
