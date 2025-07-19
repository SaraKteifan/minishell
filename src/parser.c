/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 23:19:33 by skteifan          #+#    #+#             */
/*   Updated: 2025/07/15 23:19:33 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_cmd_node(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd_name = NULL;
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->heredoc_limiter = NULL;
	cmd->append = 0;
	cmd->next = NULL;
	return (cmd);
}

void	add_cmd_node(t_cmd *cmd, t_cmd **cmd_list)
{
	t_cmd	*ptr;

	if (cmd == NULL)
		return ;
	if (*cmd_list == NULL)
	{
		*cmd_list = cmd;
		return ;
	}
	ptr = *cmd_list;
	while (ptr)
	{
		if (ptr->next == NULL)
		{
			ptr->next = cmd;
			return ;
		}
		ptr = ptr->next;
	}
}

int	build_cmd_struct(t_token *token_list, t_cmd *cmd)
{
	if (handle_parser_redir(token_list, cmd) == 1)
		return (1);
	if (build_parser_args(token_list, cmd) == 1)
		return (1);
	return (0);
}

int	build_cmd_list(t_token *token_list, t_cmd **cmd_list)
{
	t_cmd	*cmd;

	while (token_list)
	{
		cmd = create_cmd_node();
		if (!cmd)
			return (1);
		if (build_cmd_struct(token_list, cmd) == 1)
		{
			free(cmd);
			return (1);
		}
		add_cmd_node(cmd, cmd_list);
		while (token_list)
		{
			if (token_list->type == T_PIPE)
			{
				token_list = token_list->next;
				break ;
			}
			token_list = token_list->next;
		}
	}
	return (0);
}

int	parse_tokens(t_token *token_list, t_cmd **cmd_list)
{
	if (is_syntax_valid(token_list) == 1)
		return (1);
	if (build_cmd_list(token_list, cmd_list) == 1)
		return (-1);
	return (0);
}
