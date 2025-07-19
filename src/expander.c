/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 23:36:54 by skteifan          #+#    #+#             */
/*   Updated: 2025/07/13 19:29:42 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_variable_in_string(char *token, t_minishell *minishell)
{
	int		i;
	char	*tmp;
	char	*expanded_token;

	i = 0;
	expanded_token = ft_strdup(token);
	if (!expanded_token)
		return (NULL);
	while (expanded_token[i])
	{
		if (expanded_token[i] == '$' && expanded_token[i + 1] != '\0')
		{
			i++;
			tmp = get_expanded_token(expanded_token, minishell, i);
			free(expanded_token);
			if (!tmp)
				return (NULL);
			expanded_token = tmp;
			i = 0;
		}
		else
			i++;
	}
	return (expanded_token);
}

int	expand_variables_in_tokens(t_minishell *minishell)
{
	t_token	*current_token;
	char	*expanded_value;

	current_token = minishell->token_list;
	while (current_token)
	{
		if ((current_token->type == T_WORD || current_token->type == T_DQUOTE)
			&& ft_strchr(current_token->token, '$'))
		{
			expanded_value = expand_variable_in_string(current_token->token,
					minishell);
			if (!expanded_value)
				return (-1);
			free(current_token->token);
			current_token->token = expanded_value;
		}
		current_token = current_token->next;
	}
	return (0);
}
