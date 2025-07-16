/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 20:15:02 by skteifan          #+#    #+#             */
/*   Updated: 2025/07/05 20:15:02 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_minishell(char *executable_name, t_minishell *minishell)
{
	minishell->env_list = NULL;
	minishell->executable_name = executable_name;
	minishell->input = NULL;
	minishell->token_list = NULL;
	minishell->exit_status = 0;
}
