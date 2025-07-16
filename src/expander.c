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

char	*expand_symbol(char c, t_minishell *minishell)
{
	if (c == '?')
		return (ft_itoa(minishell->exit_status));
	else if (c == '0')
		return (ft_strdup(minishell->executable_name));
	else
		return (ft_strdup(""));
}

char	*expand_env_var(char *token, t_minishell *minishell)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	key = malloc(ft_strlen(token) + 1);
	if (!key)
		return (NULL);
	while (token[i] && (ft_isalnum(token[i]) || token[i] == '_'))
	{
		key[i] = token[i];
		i++;
	}
	key[i] = '\0';
	value = env_get(&(minishell->env_list), key);
	free(key);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

int	count_key(char *token)
{
	int	i;

	i = 0;
	if (!ft_isalpha(token[i]) && token[i] != '_')
		return (1);
	while (token[i] && (ft_isalnum(token[i]) || token[i] == '_'))
		i++;
	return (i);
}

char	*get_expanded_token(char *token, t_minishell *minishell, int i)
{
	int		key_len;
	char	*value;
	char	*new_token;
	int		new_len;

	key_len = count_key(&token[i]);
	if (!ft_isalpha(token[i]) && token[i] != '_')
		value = expand_symbol(token[i], minishell);
	else
		value = expand_env_var(&token[i], minishell);
	if (!value)
		return (NULL);
	new_len = (i - 1) + ft_strlen(value) + ft_strlen(&token[i + key_len]) + 1;
	new_token = malloc(new_len);
	if (!new_token)
	{
		free(value);
		return (NULL);
	}
	ft_strlcpy(new_token, token, i);
	ft_strlcat(new_token, value, new_len);
	ft_strlcat(new_token, &token[i + key_len], new_len);
	free(value);
	return (new_token);
}

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
			expanded_value = expand_variable_in_string(current_token->token, minishell);
			if (!expanded_value)
				return (-1);
			free(current_token->token);
			current_token->token = expanded_value;
		}
		current_token = current_token->next;
	}
	return (0);
}
