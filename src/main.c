/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:39:47 by skteifan          #+#    #+#             */
/*   Updated: 2025/06/30 19:39:47 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_loop(t_minishell *minishell)
{
	int	res;
	t_cmd	*ptr;
	int	i;

	while (1)
	{
		minishell->input = read_input();
		if (minishell->input == NULL)
			break ;
		res = tokenize_input(minishell->input, &(minishell->token_list));
		if (res == 1)
			continue ;
		if (res == -1)
			malloc_fail(minishell);
		if (expand_variables_in_tokens(minishell) != 0)
			malloc_fail(minishell);
		res = parse_tokens(minishell);
		if (res == 1)
		{
			free(minishell->input);
			free_token_list(minishell->token_list);
			minishell->token_list = NULL;
			continue ;
		}
		if (res == -1)
			malloc_fail(minishell);
		ptr = minishell->cmd_list;
		while (ptr)
		{
			printf("cmd name: [%s]\n", ptr->cmd_name);
			printf("infile: [%s]\n", ptr->infile);
			printf("outfile: [%s]\n", ptr->outfile);
			printf("heredoc: [%s]\n", ptr->heredoc_limiter);
			printf("append?: [%i]\n", ptr->append);
			i = 0;
			while (ptr->args[i])
			{
				printf("arg[%i]: [%s]\n", i, ptr->args[i]);
				i++;
			}
			ptr = ptr->next;
		}
		free(minishell->input);
		free_token_list(minishell->token_list);
		free_cmd_list(minishell->cmd_list);
		minishell->token_list = NULL;
		minishell->cmd_list = NULL;
	}
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;

	(void)argc;
	(void)argv;
	init_minishell(argv[0], &minishell);
	if (build_env_list(envp, &(minishell.env_list)) != 0)
		malloc_fail(&minishell);
	minishell_loop(&minishell);

	free_env_list(minishell.env_list);
	return (0);
}
