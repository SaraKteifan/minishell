/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 11:14:40 by skteifan          #+#    #+#             */
/*   Updated: 2025/08/04 17:40:03 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_stdin_stdout_fds(int fds[])
{
	fds[0] = dup(STDIN_FILENO);
	if (fds[0] < 0)
	{
		perror("dup");
		return (2);
	}
	fds[1] = dup(STDOUT_FILENO);
	if (fds[1] < 0)
	{
		perror("dup");
		close(fds[0]);
		return (2);
	}
	return (0);
}

int	restore_and_close_stdin_stdout_fds(int fds[])
{
	if (dup2(fds[0], STDIN_FILENO) == -1 || dup2(fds[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return (2);
	}
	close(fds[0]);
	close(fds[1]);
	return (0);
}

int	execute_cmd_in_parent(t_cmd *cmd, t_minishell *minishell)
{
	int	res;
	int	red;
	int	saved_fds[2];

	res = check_file_error_or_no_cmd(cmd, minishell);
	if (res != 0)
		return (res);
	red = save_stdin_stdout_fds(saved_fds);
	if (red != 0)
		return (red);
	red = handle_redirections(cmd);
	if (red != 0)
	{
		restore_and_close_stdin_stdout_fds(saved_fds);
		return (red);
	}
	res = find_and_launch_special_builtin(cmd, minishell);
	red = restore_and_close_stdin_stdout_fds(saved_fds);
	if (red != 0)
		return (red);
	return (res);
}
