/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 23:19:33 by skteifan          #+#    #+#             */
/*   Updated: 2025/08/03 13:26:45 by skteifan         ###   ########.fr       */
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
	cmd->file_error = 0;
	cmd->fds = NULL;
	cmd->p_fds = NULL;
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

int	build_cmd_struct(t_token *token_list, t_cmd *cmd, t_minishell *minishell)
{
	if (handle_parser_redir(token_list, cmd, minishell) == -1)
		return (-1);
	if (build_parser_args(token_list, cmd) == 1)
		return (-1);
	return (0);
}

int	build_cmd_list(t_minishell *minishell)
{
	int		res;
	t_cmd	*cmd;
	t_token	*current;

	current = minishell->token_list;
	while (current)
	{
		cmd = create_cmd_node();
		if (!cmd)
			return (-1);
		res = build_cmd_struct(current, cmd, minishell);
		if (res == -1)
		{
			free_cmd(cmd);
			return (res);
		}
		add_cmd_node(cmd, &(minishell->cmd_list));
		while (current && current->type != T_PIPE)
			current = current->next;
		if (current)
			current = current->next;
	}
	return (0);
}

int	parse_tokens(t_minishell *minishell)
{
	int	res;

	if (is_syntax_valid(minishell->token_list) == 1)
	{
		minishell->exit_status = 2;
		return (1);
	}
	res = build_cmd_list(minishell);
	if (res == -1)
	{
		free_cmd_list(minishell->cmd_list);
		minishell->cmd_list = NULL;
		return (-1);
	}
	return (0);
}
