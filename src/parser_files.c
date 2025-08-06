/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 09:26:44 by skteifan          #+#    #+#             */
/*   Updated: 2025/08/06 09:05:55 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	try_to_open_infile(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->infile, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(cmd->infile);
		cmd->file_error = 1;
		return (1);
	}
	close(fd);
	return (0);
}

int	try_to_open_outfile(t_cmd *cmd)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (cmd->append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(cmd->outfile, flags, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(cmd->outfile);
		cmd->file_error = 1;
		return (1);
	}
	close(fd);
	return (0);
}

char	*expand_input(char *input, t_minishell *minishell)
{
	char	*tmp;

	tmp = expand_variable_in_string(input, minishell);
	if (!tmp)
		return (NULL);
	free(input);
	input = tmp;
	return (input);
}

int	heredoc_loop(int fd, t_cmd *cmd, t_token_type deli_type,
	t_minishell *minishell)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (ft_strncmp(input, cmd->heredoc_limiter, -1) == 0 || input == NULL)
		{
			free(input);
			break ;
		}
		if (deli_type == T_WORD)
		{
			input = expand_input(input, minishell);
			if (!input)
				return (-1);
		}
		if (write(fd, input, ft_strlen(input)) == -1
			|| write(fd, "\n", 1) == -1)
			return (1);
		free(input);
	}
	return (0);
}

int	handle_heredoc(t_cmd *cmd, t_token_type deli_type, t_minishell *minishell)
{
	int		fd;
	int		res;

	fd = open(cmd->infile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: internal error:\
			 failed to create heredoc temp file\n", 2);
		cmd->file_error = 1;
		return (1);
	}
	res = heredoc_loop(fd, cmd, deli_type, minishell);
	if (res == 1)
		ft_putstr_fd("minishell: internal error:\
			 failed to write to heredoc temp file\n", 2);
	close(fd);
	return (res);
}
