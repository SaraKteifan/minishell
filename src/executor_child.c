/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 11:39:29 by skteifan          #+#    #+#             */
/*   Updated: 2025/08/06 09:07:16 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_cmd_in_child(t_cmd *cmd, t_minishell *minishell)
{
	int	res;
	int	red;
	int	pid;
	int	status;

	res = 0;
	pid = fork();
	if (pid == 0)
	{
		red = handle_redirections(cmd);
		if (red != 0)
			exit (red);
		if (is_builtin(cmd->cmd_name))
			res = find_and_launch_builtin(cmd, minishell);
		else
			res = ft_execve(cmd, minishell);
		exit(res);
	}
	wait(&status);
	minishell->exit_status = WEXITSTATUS(status);
	return (res);
}

int	execute_one_command(t_cmd *cmd, t_minishell *minishell)
{
	int	res;

	res = check_file_error_or_no_cmd(cmd, minishell);
	if (res != 0)
		return (res);
	res = execute_cmd_in_child(cmd, minishell);
	if (res != 0)
		return (res);
	return (res);
}
