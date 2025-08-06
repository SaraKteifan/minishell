/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 08:58:26 by skteifan          #+#    #+#             */
/*   Updated: 2025/08/06 08:58:36 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*generate_heredoc_path(t_cmd *cmd)
{
	char		*base;
	char		*num;
	char		*path;
	uintptr_t	addr;

	base = "/tmp/.heredoc_";
	addr = (uintptr_t)cmd;
	num = ft_itoa((int)addr);
	if (!num)
		return (NULL);
	path = ft_strjoin(base, num);
	free(num);
	return (path);
}
