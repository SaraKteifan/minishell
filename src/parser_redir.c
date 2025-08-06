/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:01:10 by skteifan          #+#    #+#             */
/*   Updated: 2025/08/06 08:57:45 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_cmd_out_file(t_token_type type, char *token, t_cmd *cmd)
{
	char	*tmp;

	tmp = ft_strdup(token);
	if (!tmp)
		return (-1);
	if (cmd->outfile)
		free(cmd->outfile);
	cmd->outfile = tmp;
	if (type == T_REDIR_APPEND)
		cmd->append = 1;
	else if (type == T_REDIR_OUT)
		cmd->append = 0;
	return (0);
}

int	fill_cmd_in_file(t_token_type type, char *token, t_cmd *cmd)
{
	char	*tmp;

	tmp = ft_strdup(token);
	if (!tmp)
		return (-1);
	if (cmd->heredoc_limiter)
	{
		if (unlink(cmd->infile) != 0)
			return (1);
		free(cmd->heredoc_limiter);
	}
	cmd->heredoc_limiter = NULL;
	if (cmd->infile)
		free(cmd->infile);
	cmd->infile = NULL;
	if (type == T_REDIR_IN)
		cmd->infile = tmp;
	else if (type == T_HEREDOC)
	{
		cmd->infile = generate_heredoc_path(cmd);
		if (!cmd->infile)
			return (-1);
		cmd->heredoc_limiter = tmp;
	}
	return (0);
}

int	handle_file(t_token_type type, t_cmd *cmd,
			t_token_type n_type, t_minishell *minishell)
{
	int	res;

	if (type == T_REDIR_OUT || type == T_REDIR_APPEND)
	{
		if (try_to_open_outfile(cmd) == 1)
			return (1);
	}
	else if (type == T_REDIR_IN)
	{
		if (try_to_open_infile(cmd) == 1)
			return (1);
	}
	else if (type == T_HEREDOC)
	{
		res = handle_heredoc(cmd, n_type, minishell);
		if (res != 0)
			return (res);
	}
	return (0);
}

int	fill_file(t_token_type type, char *token, t_cmd *cmd)
{
	int		res;

	res = 0;
	if (type == T_REDIR_OUT || type == T_REDIR_APPEND)
		res = fill_cmd_out_file(type, token, cmd);
	else if (type == T_REDIR_IN || type == T_HEREDOC)
	{
		res = fill_cmd_in_file(type, token, cmd);
		{
			if (res == 1)
			{
				ft_putstr_fd("minishell: internal error:\
					 failed to delete heredoc temp file\n", 2);
				cmd->file_error = 1;
			}
		}
	}
	return (res);
}

int	handle_parser_redir(t_token *token_list, t_cmd *cmd, t_minishell *minishell)
{
	int		res;
	t_token	*curr;

	curr = token_list;
	while (curr && curr->type != T_PIPE)
	{
		if (is_redirection_type(curr->type))
		{
			res = fill_file(curr->type, curr->next->token, cmd);
			if (res == 1)
				return (0);
			if (res == -1)
				return (-1);
			res = handle_file(curr->type, cmd, curr->next->type, minishell);
			if (res == 1)
				return (0);
			if (res == -1)
				return (-1);
		}
		curr = curr->next;
	}
	return (0);
}
