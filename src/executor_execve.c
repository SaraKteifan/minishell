/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_execve.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 12:06:16 by skteifan          #+#    #+#             */
/*   Updated: 2025/08/06 09:11:49 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path_var(char **envp)
{
	int		i;
	char	*path_var;

	i = 0;
	path_var = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_var = envp[i] + 5;
			break ;
		}
		i++;
	}
	return (path_var);
}

char	**get_paths_array(char **envp)
{
	char	**paths;
	char	*path_var;

	path_var = get_path_var(envp);
	if (!path_var)
		return (NULL);
	paths = ft_split(path_var, ':');
	return (paths);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	*full_path;

	paths = get_paths_array(envp);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin_free(full_path, cmd);
		if (access(full_path, X_OK) == 0)
		{
			free_double_pointer(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_double_pointer(paths);
	full_path = ft_strdup("");
	if (!full_path)
		return (NULL);
	return (full_path);
}

void	cmd_not_found(t_cmd *cmd, t_minishell *minishell)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->cmd_name, 2);
	ft_putstr_fd(": command not found\n", 2);
	minishell->exit_status = 127;
}

int	ft_execve(t_cmd *cmd, t_minishell *minishell)
{
	int		res;
	char	*path;
	char	**envp;

	envp = env_list_to_array(minishell->env_list);
	if (!envp)
		return (-1);
	path = get_cmd_path(cmd->cmd_name, envp);
	if (!path)
	{
		free_double_pointer(envp);
		return (-1);
	}
	if (ft_strlen(path) == 0)
	{
		cmd_not_found(cmd, minishell);
		free(path);
		free_double_pointer(envp);
		exit (127);
	}
	res = execve(path, cmd->args, envp);
	free(path);
	free_double_pointer(envp);
	exit (res);
}
