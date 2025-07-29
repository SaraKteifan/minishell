/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 21:35:36 by skteifan          #+#    #+#             */
/*   Updated: 2025/07/02 21:35:36 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_fail(t_minishell *minishell)
{
	cleanup_minishell(minishell);
	perror("Malloc Failed!");
	exit(1);
}
