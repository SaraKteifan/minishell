/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 19:54:17 by skteifan          #+#    #+#             */
/*   Updated: 2025/07/06 19:54:17 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token_struct(char *token, t_token_type type)
{
	t_token	*token_s;

	token_s = malloc(sizeof(t_token));
	if (!token_s)
		return (NULL);
	token_s->token = token;
	token_s->type = type;
	token_s->next = NULL;
	return (token_s);
}

void	add_token_at_end_of_tokens(t_token *token_s, t_token **token_list)
{
	t_token	*ptr;

	if (token_s == NULL)
		return ;
	if (*token_list == NULL)
	{
		*token_list = token_s;
		return ;
	}
	ptr = *token_list;
	while (ptr)
	{
		if (ptr->next == NULL)
		{
			ptr->next = token_s;
			return ;
		}
		ptr = ptr->next;
	}
}

int	add_token_to_tokens(t_token **token_list, char *token, t_token_type type)
{
	t_token	*token_s;

	token_s = create_token_struct(token, type);
	if (!token_s)
		return (1);
	add_token_at_end_of_tokens(token_s, token_list);
	return (0);
}
