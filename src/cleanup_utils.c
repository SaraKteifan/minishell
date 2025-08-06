/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 15:15:36 by skteifan          #+#    #+#             */
/*   Updated: 2025/07/28 12:52:48 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_node(t_token *token_node)
{
	free(token_node->token);
	free(token_node);
}

void	free_env_var(t_env *env_var)
{
	free(env_var->key);
	free(env_var->value);
	free(env_var);
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
		free(args[i++]);
	free(args);
}

void	free_cmd(t_cmd *cmd)
{
	if (cmd->heredoc_limiter)
	{
		unlink(cmd->infile);
		// if (unlink(cmd->infile) != 0)
		// 	return (1);
	}
	free(cmd->cmd_name);
	free_args(cmd->args);
	free(cmd->infile);
	free(cmd->outfile);
	free(cmd->heredoc_limiter);
	free(cmd);
}
