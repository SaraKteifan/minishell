/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:20:04 by skteifan          #+#    #+#             */
/*   Updated: 2025/07/18 20:20:04 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_cmd_name(t_token *token_list, t_cmd *cmd)
{
	char	*cmd_name;
	t_token	*current;

	current = token_list;
	while (current && current->type != T_PIPE)
	{
		if (!is_redirection_type(current->type))
		{
			cmd_name = ft_strdup(current->token);
			if (!cmd_name)
				return (1);
			cmd->cmd_name = cmd_name;
			break ;
		}
		else
			current = current->next;
		current = current->next;
	}
	return (0);
}

int	count_args(t_token *token_list)
{
	int		i;
	t_token	*current;

	i = 0;
	current = token_list;
	while (current && current->type != T_PIPE)
	{
		if (!is_redirection_type(current->type))
			i++;
		else
			current = current->next;
		current = current->next;
	}
	return (i);
}

int	fill_cmd_args(t_token *token_list, t_cmd *cmd)
{
	int		i;
	char	**args;
	t_token	*current;

	i = 0;
	args = malloc((count_args(token_list) + 1) * sizeof(char *));
	if (!args)
		return (1);
	current = token_list;
	while (current && current->type != T_PIPE)
	{
		if (!is_redirection_type(current->type))
		{
			args[i] = ft_strdup(current->token);
			if (!args[i])
				return (1);
			i++;
		}
		else
			current = current->next;
		current = current->next;
	}
	args[i] = NULL;
	cmd->args = args;
	return (0);
}

int	build_parser_args(t_token *token_list, t_cmd *cmd)
{
	if (fill_cmd_name(token_list, cmd) == 1)
		return (1);
	if (fill_cmd_args(token_list, cmd) == 1)
		return (1);
	return (0);
}
