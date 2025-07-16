/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 23:15:35 by skteifan          #+#    #+#             */
/*   Updated: 2025/07/04 23:15:35 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_blank_line(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (!((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
			return (0);
		i++;
	}
	return (1);
}

int	check_unclosed_quotes(char *input)
{
	int	i;
	int	sq_open;
	int	dq_open;

	i = 0;
	sq_open = 0;
	dq_open = 0;
	while (input[i])
	{
		if (input[i] == '\'' && dq_open == 0)
			sq_open = !sq_open;
		else if (input[i] == '"' && sq_open == 0)
			dq_open = !dq_open;
		i++;
	}
	if (sq_open || dq_open)
	{
		ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
		return (1);
	}
	return (0);
}

int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}
