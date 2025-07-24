/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 09:26:44 by skteifan          #+#    #+#             */
/*   Updated: 2025/07/24 09:26:44 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	try_to_open_file(t_token_type type, t_cmd *cmd)
{
	int	fd;

	if (type == T_REDIR_IN)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd < 0)
			
	}

}
