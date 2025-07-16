/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 21:33:30 by skteifan          #+#    #+#             */
/*   Updated: 2025/07/02 21:33:30 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	send_to_handler(char *input, t_token **token_list, char *buffer)
{
	int	res;

	res = 0;
	if (is_space(*input))
		res = handle_space(input, token_list, buffer);
	else if (*input == '|')
		res = handle_pipe_and_redir(token_list, buffer, "|", T_PIPE);
	else if (*input == '<' && *(input + 1) && *(input + 1) == '<')
		res = handle_pipe_and_redir(token_list, buffer, "<<", T_HEREDOC);
	else if (*input == '<')
		res = handle_pipe_and_redir(token_list, buffer, "<", T_REDIR_IN);
	else if (*input == '>' && *(input + 1) && *(input + 1) == '>')
		res = handle_pipe_and_redir(token_list, buffer, ">>", T_REDIR_APPEND);
	else if (*input == '>')
		res = handle_pipe_and_redir(token_list, buffer, ">", T_REDIR_OUT);
	else if (*input == '\'')
		res = handle_quotes(input, token_list, buffer, '\'');
	else if (*input == '"')
		res = handle_quotes(input, token_list, buffer, '"');
	return (res);
}

int	split_input_into_tokens(char *input, t_token **token_list,
							int i, char *buffer)
{
	int	pos;
	int	res;

	pos = 0;
	while (input[i] != '\0')
	{
		if (is_space(input[i]) || is_operator(input[i]) || is_quote(input[i]))
		{
			buffer[pos] = '\0';
			res = send_to_handler(&input[i], token_list, buffer);
			if (res == -1)
				return (-1);
			i += res;
			pos = 0;
		}
		else
			buffer[pos++] = input[i++];
	}
	if (pos != 0)
	{
		buffer[pos] = '\0';
		if (add_word_to_tokens(buffer, token_list) == -1)
			return (-1);
	}
	return (0);
}

int	tokenize_input(char *input, t_token **token_list)
{
	int		i;
	int		res;
	char	*buffer;

	if (check_unclosed_quotes(input) != 0 || is_blank_line(input))
	{
		free(input);
		return (1);
	}
	i = 0;
	buffer = malloc(ft_strlen(input) + 1);
	if (!buffer)
		return (-1);
	*buffer = '\0';
	res = split_input_into_tokens(input, token_list, i, buffer);
	free(buffer);
	if (res == -1)
		return (-1);
	return (0);
}

char	*read_input(void)
{
	char	*input;

	input = readline("minishell> ");
	if (input == NULL)
	{
		printf("exit\n");
		return (NULL);
	}
	if (input && !is_blank_line(input))
		add_history(input);
	return (input);
}
