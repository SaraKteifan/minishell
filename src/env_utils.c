/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:37:42 by skteifan          #+#    #+#             */
/*   Updated: 2025/07/01 21:37:42 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_env(t_env **env)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = *env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**env_list_to_array(t_env **env_list)
{
	int		i;
	int		j;
	char	*tmp;
	char	**array;

	i = count_env(env_list);
	array = malloc((i + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	j = 0;
	while (j < i)
	{
		tmp = ft_strjoin((*env_list)->key, "=");
		array[j] = ft_strjoin(tmp, (*env_list)->value);
		free(tmp);
		j++;
		(*env_list) = (*env_list)->next;
	}
	array[j] = NULL;
	return (array);
}
