/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 09:45:02 by skteifan          #+#    #+#             */
/*   Updated: 2025/08/06 09:09:05 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmd(t_cmd *cmd_list)
{
	int		i;
	t_cmd	*ptr;

	i = 0;
	ptr = cmd_list;
	while (ptr)
	{
		i++;
		ptr = ptr->next;
	}
	return (i);
}

int	check_file_error_or_no_cmd(t_cmd *cmd, t_minishell *minishell)
{
	if (cmd->file_error)
	{
		close_fds(cmd->fds);
		close_fds(cmd->p_fds);
		minishell->exit_status = 1;
		return (1);
	}
	if (!cmd->cmd_name)
	{
		close_fds(cmd->fds);
		close_fds(cmd->p_fds);
		return (1);
	}
	return (0);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}
