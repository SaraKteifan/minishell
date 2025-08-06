/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 09:03:22 by skteifan          #+#    #+#             */
/*   Updated: 2025/08/06 08:50:38 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_cmd_list(t_cmd *cmd_list, t_minishell *minishell)
{
	int	res;
	int	cmd_count;

	cmd_count = count_cmd(cmd_list);
	if (cmd_count == 1)
	{
		if (is_special_builtin(cmd_list->cmd_name))
			res = execute_cmd_in_parent(cmd_list, minishell);
		else
			res = execute_one_command(cmd_list, minishell);
	}
	else if (cmd_count > 1)
		res = ft_pipes(cmd_list, minishell);
	else
		return (0);
	if (res == 2)
	{
		minishell->exit_status = 1;
		return (1);
	}
	if (res == -1)
		return (-1);
	return (0);
}
