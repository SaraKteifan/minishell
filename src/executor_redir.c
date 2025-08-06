/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 09:56:01 by skteifan          #+#    #+#             */
/*   Updated: 2025/08/06 11:56:15 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_infile_and_redir(t_cmd *cmd)
{
	int	infile_fd;

	if (cmd->p_fds)
		close_fds(cmd->p_fds);
	infile_fd = open(cmd->infile, O_RDONLY);
	if (infile_fd < 0)
	{
		perror(cmd->infile);
		return (2);
	}
	if (dup2(infile_fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(infile_fd);
		return (2);
	}
	close(infile_fd);
	return (0);
}

int	open_outfile_and_redir(t_cmd *cmd)
{
	int	outfile_fd;
	int	flags;

	if (cmd->fds)
		close_fds(cmd->fds);
	flags = O_WRONLY;
	if (cmd->append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	outfile_fd = open(cmd->outfile, flags);
	if (outfile_fd < 0)
	{
		perror(cmd->outfile);
		return (2);
	}
	if (dup2(outfile_fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(outfile_fd);
		return (2);
	}
	close(outfile_fd);
	return (0);
}

int	read_from_pipe(int *fd)
{
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd[0]);
		return (2);
	}
	close(fd[0]);
	return (0);
}

int	write_to_pipe(int *fd)
{
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd[1]);
		return (2);
	}
	close(fd[1]);
	return (0);
}

int	handle_redirections(t_cmd *cmd)
{
	int	red;

	red = 0;
	if (cmd->infile)
		red = open_infile_and_redir(cmd);
	else if (cmd->p_fds)
		red = read_from_pipe(cmd->p_fds);
	if (red != 0)
		return (red);
	if (cmd->outfile)
		red = open_outfile_and_redir(cmd);
	else if (cmd->fds)
		red = write_to_pipe(cmd->fds);
	return (red);
}
