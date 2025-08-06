/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cleanup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 10:06:59 by skteifan          #+#    #+#             */
/*   Updated: 2025/08/05 14:27:21 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_fds(int **fds, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(fds[i]);
		i++;
	}
	free(fds);
}

void	close_fds(int *fds)
{
	close(fds[0]);
	close(fds[1]);
}
