/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 10:37:22 by skteifan          #+#    #+#             */
/*   Updated: 2025/07/06 10:37:22 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_word_to_tokens(char *buffer, t_token **token_list)
{
	char	*token;

	token = ft_strdup(buffer);
	if (!token)
		return (-1);
	if (add_token_to_tokens(token_list, token, T_WORD) == 1)
	{
		free(token);
		return (-1);
	}
	return (0);
}

int	handle_space(char *input, t_token **token_list, char *buffer)
{
	int		i;

	i = 0;
	if (*buffer)
	{
		if (add_word_to_tokens(buffer, token_list) == -1)
			return (-1);
	}
	while (input[i] && ((input[i] >= 9 && input[i] <= 13) || input[i] == 32))
		i++;
	return (i);
}

int	handle_pipe_and_redir(t_token **token_list, char *buffer,
							char *value, t_token_type type)
{
	int		i;
	char	*token;

	i = 0;
	if (*buffer)
	{
		if (add_word_to_tokens(buffer, token_list) == -1)
			return (-1);
	}
	token = ft_strdup(value);
	if (!token)
		return (-1);
	i += ft_strlen(token);
	if (add_token_to_tokens(token_list, token, type) == 1)
	{
		free(token);
		return (-1);
	}
	return (i);
}

char	*get_quoted(char *input, int j)
{
	int		i;
	char	*quoted;

	i = 0;
	quoted = malloc(j + 1);
	if (!quoted)
		return (NULL);
	while (i < j)
	{
		quoted[i] = input[i];
		i++;
	}
	quoted[i] = '\0';
	return (quoted);
}

int	handle_quotes(char *input, t_token **token_list, char *buffer, char c)
{
	int				i;
	char			*token;
	t_token_type	type;

	i = 1;
	if (*buffer)
	{
		if (add_word_to_tokens(buffer, token_list) == -1)
			return (-1);
	}
	if (c == '\'')
		type = T_SQUOTE;
	else if (c == '"')
		type = T_DQUOTE;
	while (input[i] && input[i] != c)
		i++;
	token = get_quoted(input + 1, i - 1);
	if (!token)
		return (-1);
	if (add_token_to_tokens(token_list, token, type) == 1)
	{
		free(token);
		return (-1);
	}
	return (++i);
}
