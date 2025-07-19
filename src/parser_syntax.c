/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:45:25 by skteifan          #+#    #+#             */
/*   Updated: 2025/07/16 22:45:25 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_error(char *s)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("'\n", 2);
}

int	is_redirection_type(t_token_type type)
{
	if (type == T_REDIR_IN || type == T_REDIR_OUT
		|| type == T_REDIR_APPEND || type == T_HEREDOC)
		return (1);
	return (0);
}

int	check_first_token(t_token *token_list)
{
	if (token_list->type == T_PIPE)
	{
		put_error("|");
		return (1);
	}
	return (0);
}

int	check_last_token(t_token *token_list)
{
	t_token	*token;

	token = token_list;
	while (token->next != NULL)
		token = token->next;
	if (token->type == T_PIPE)
	{
		put_error("|");
		return (1);
	}
	if (is_redirection_type(token->type))
	{
		put_error("newline");
		return (1);
	}
	return (0);
}

int	is_syntax_valid(t_token *token_list)
{
	t_token	*token;

	if (check_first_token(token_list) == 1)
		return (1);
	token = token_list;
	while (token)
	{
		if ((token->type == T_PIPE || is_redirection_type(token->type))
			&& (token->next && token->next->type == T_PIPE))
		{
			put_error("|");
			return (1);
		}
		if (is_redirection_type(token->type)
			&& (token->next && is_redirection_type(token->next->type)))
		{
			put_error(token->next->token);
			return (1);
		}
		token = token->next;
	}
	if (check_last_token(token_list) == 1)
		return (1);
	return (0);
}
