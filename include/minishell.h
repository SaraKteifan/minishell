/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:37:01 by skteifan          #+#    #+#             */
/*   Updated: 2025/08/06 09:09:34 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <curses.h>
# include <term.h>

# define BUFFER_SIZE 10

/******************************************************************************
*                                   Structs                                   *
******************************************************************************/

typedef enum e_token_type
{
	T_WORD,
	T_SQUOTE,
	T_DQUOTE,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_HEREDOC
}	t_token_type;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	char			*token;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			*cmd_name;
	char			**args;
	char			*infile;
	char			*outfile;
	char			*heredoc_limiter;
	int				append;
	int				file_error;
	int				*fds;
	int				*p_fds;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_minishell
{
	t_env	*env_list;
	char	*executable_name;
	char	*input;
	t_token	*token_list;
	t_cmd	*cmd_list;
	int		exit_status;
}	t_minishell;

/******************************************************************************
*                             Function Prototypes                             *
******************************************************************************/

void	init_minishell(char *executable_name, t_minishell *minishell);

int		build_env_list(char **envp, t_env **env_list);
t_env	*create_env_var(char *key, char *value);
void	add_env_var_at_end(t_env *env_var, t_env **env_list);
char	*env_get(t_env **env_list, char *key);
int		env_set(t_env **env_list, char *key, char *value);
int		env_unset(t_env **env_list, char *key);
void	free_env_var(t_env *env_var);
void	free_env_list(t_env *env_list);
char	**env_list_to_array(t_env *env_list);

char	*read_input(void);
int		is_blank_line(const char *str);
int		check_unclosed_quotes(char *input);
int		is_space(char c);
int		is_operator(char c);
int		is_quote(char c);
int		tokenize_input(char *input, t_token **token_list,
			t_minishell *minishell);
int		handle_space(char *input, t_token **token_list, char *buffer);
int		handle_pipe_and_redir(t_token **token_list, char *buffer,
			char *value, t_token_type type);
int		handle_quotes(char *input, t_token **token_list, char *buffer, char c);
int		add_word_to_tokens(char *buffer, t_token **token_list);
int		add_token_to_tokens(t_token **token_list, char *token,
			t_token_type type);
void	free_token_node(t_token *token_node);
void	free_token_list(t_token *token_list);

int		expand_variables_in_tokens(t_minishell *minishell);
char	*expand_variable_in_string(char *token, t_minishell *minishell);
char	*get_expanded_token(char *token, t_minishell *minishell, int i);

int		parse_tokens(t_minishell *minishell);
int		is_syntax_valid(t_token *token_list);
int		is_redirection_type(t_token_type type);
int		handle_parser_redir(t_token *token_list, t_cmd *cmd,
			t_minishell *minishell);
int		try_to_open_infile(t_cmd *cmd);
int		try_to_open_outfile(t_cmd *cmd);
char	*generate_heredoc_path(t_cmd *cmd);
int		handle_heredoc(t_cmd *cmd, t_token_type deli_type,
			t_minishell *minishell);
int		build_parser_args(t_token *token_list, t_cmd *cmd);
void	free_args(char **args);
void	free_cmd(t_cmd *cmd);
void	free_cmd_list(t_cmd *cmd_list);

int		count_cmd(t_cmd *cmd_list);
int		execute_cmd_list(t_cmd *cmd_list, t_minishell *minishell);
int		execute_cmd_in_parent(t_cmd *cmd, t_minishell *minishell);
int		execute_one_command(t_cmd *cmd, t_minishell *minishell);
char	*ft_strjoin_free(char *s1, char *s2);
int		ft_execve(t_cmd *cmd, t_minishell *minishell);
int		ft_pipes(t_cmd *cmd_list, t_minishell *minishell);
int		check_file_error_or_no_cmd(t_cmd *cmd, t_minishell *minishell);
int		handle_redirections(t_cmd *cmd);
void	free_fds(int **fds, int count);
void	close_fds(int *fds);


int		is_special_builtin(char *cmd_name);
int		is_builtin(char *cmd_name);
int		find_and_launch_builtin(t_cmd *cmd, t_minishell *minishell);
int		find_and_launch_special_builtin(t_cmd *cmd, t_minishell *minishell);
int		ft_echo(char **args);
int  	ft_cd(char **args);
int		ft_pwd();
int 	ft_export(t_minishell *minishell, char **args);
int 	ft_unset(char **args, t_env **env_list);
int		ft_env(char **args, t_env *env_list);
int		ft_exit(char **args, t_env *env_list);

int		count_strings(char **s);

void	free_double_pointer(char **ptr);
void	cleanup_minishell(t_minishell *minishell);
void	malloc_fail(t_minishell *minishell);

#endif
