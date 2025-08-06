/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 09:40:04 by skteifan          #+#    #+#             */
/*   Updated: 2025/08/06 11:56:45 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**init_fds(int count)
{
	int	i;
	int	**fds;

	i = 0;
	fds = malloc((count - 1) * sizeof(int *));
	if (!fds)
		return (NULL);
	while (i < count - 1)
	{
		fds[i] = malloc(2 * sizeof(int));
		if (!fds[i])
		{
			free_fds(fds, i);
			return (NULL);
		}
		i++;
	}
	return (fds);
}

int	ft_pipes(t_cmd *cmd_list, t_minishell *minishell)
{
	int	i;
	int	res;
	int	count;
	int	**fds;

	i = 0;
	res = 0;
	count = count_cmd(cmd_list);
	fds = init_fds(count);
	if (!fds)
		return (-1);
	while (cmd_list)
	{
		if (cmd_list->next)
		{
			if (pipe(fds[i]) == -1)
			{
				close_fds(cmd_list->p_fds);
				free_fds(fds, count - 1);
				perror("pipe");
				return (2);
			}
			cmd_list->fds = fds[i];
			cmd_list->next->p_fds = fds[i];
		}
		res = execute_one_command(cmd_list, minishell);
		if (cmd_list->p_fds)
			close_fds(cmd_list->p_fds);
		// if (cmd_list->fds)
		// 	close_fds(cmd_list->fds);
		//if (cmd_list->p_fds)
		//	close(cmd_list->p_fds[0]);
		//if (cmd_list->fds)
		//	close(cmd_list->fds[1]);
		i++;
		cmd_list = cmd_list->next;
	}
	free_fds(fds, count - 1);
	return (res);
}
