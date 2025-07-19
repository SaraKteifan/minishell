/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:01:10 by skteifan          #+#    #+#             */
/*   Updated: 2025/07/18 20:01:10 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_cmd_file(t_token_type type, char *token, t_cmd *cmd)
{
	char	*tmp;

	tmp = ft_strdup(token);
	if (!tmp)
		return (1);
	if (type == T_REDIR_IN)
	{
		if (cmd->infile)
			free(cmd->infile);
		cmd->infile = tmp;
	}
	else if (type == T_REDIR_OUT || type == T_REDIR_APPEND)
	{
		if (cmd->outfile)
			free(cmd->outfile);
		cmd->outfile = tmp;
	}
	else if (type == T_HEREDOC)
	{
		if (cmd->heredoc_limiter)
			free(cmd->heredoc_limiter);
		cmd->heredoc_limiter = tmp;
	}
	return (0);
}

//int	handle_file(t_token_type type, t_cmd *cmd)
//{
//	if (type == T_HEREDOC)
//		handle_heredoc(cmd);
//	else
//		try_to_open_file(type, cmd);
//	return (0);
//}

int	handle_parser_redir(t_token *token_list, t_cmd *cmd)
{
	t_token	*current;

	current = token_list;
	while (current && current->type != T_PIPE)
	{
		if (is_redirection_type(current->type))
		{
			if (fill_cmd_file(current->type, current->next->token, cmd) == 1)
				return (1);
			if (current->type == T_REDIR_APPEND)
				cmd->append = 1;
			else if (current->type == T_REDIR_OUT)
				cmd->append = 0;
			//if (handle_file(current->type, cmd) == 1)
			//	return (1);
		}
		current = current->next;
	}
	return (0);
}
