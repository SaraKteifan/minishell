/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 20:35:25 by skteifan          #+#    #+#             */
/*   Updated: 2025/07/27 15:16:46 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_list(t_token *token_list)
{
	t_token	*ptr;

	while (token_list)
	{
		ptr = token_list->next;
		free_token_node(token_list);
		token_list = ptr;
	}
}

void	free_env_list(t_env *env_list)
{
	t_env	*ptr;

	while (env_list)
	{
		ptr = env_list->next;
		free_env_var(env_list);
		env_list = ptr;
	}
}

void	free_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*ptr;

	while (cmd_list)
	{
		ptr = cmd_list->next;
		free_cmd(cmd_list);
		cmd_list = ptr;
	}
}

void	cleanup_minishell(t_minishell *minishell)
{
	if (minishell->env_list)
		free_env_list(minishell->env_list);
	free(minishell->input);
	if (minishell->token_list)
		free_token_list(minishell->token_list);
	if (minishell->cmd_list)
		free_cmd_list(minishell->cmd_list);
	rl_clear_history();
	minishell->env_list = NULL;
	minishell->input = NULL;
	minishell->token_list = NULL;
	minishell->cmd_list = NULL;
}
