/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 10:10:45 by skteifan          #+#    #+#             */
/*   Updated: 2025/08/05 11:15:26 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special_builtin(char *cmd_name)
{
	if (ft_strncmp(cmd_name, "cd", -1) == 0)
		return (1);
	else if (ft_strncmp(cmd_name, "export", -1) == 0)
		return (1);
	else if (ft_strncmp(cmd_name, "unset", -1) == 0)
		return (1);
	else if (ft_strncmp(cmd_name, "exit", -1) == 0)
		return (1);
	return (0);
}

int	is_builtin(char *cmd_name)
{
	if (ft_strncmp(cmd_name, "cd", -1) == 0)
		return (1);
	else if (ft_strncmp(cmd_name, "export", -1) == 0)
		return (1);
	else if (ft_strncmp(cmd_name, "unset", -1) == 0)
		return (1);
	else if (ft_strncmp(cmd_name, "exit", -1) == 0)
		return (1);
	else if (ft_strncmp(cmd_name, "echo", -1) == 0)
		return (1);
	else if (ft_strncmp(cmd_name, "pwd", -1) == 0)
		return (1);
	else if (ft_strncmp(cmd_name, "env", -1) == 0)
		return (1);
	return (0);
}

int	find_and_launch_special_builtin(t_cmd *cmd, t_minishell *minishell)
{
	int	res;

	res = 0;
	if (ft_strncmp(cmd->cmd_name, "cd", -1) == 0)
		res = ft_cd(cmd->args);
	else if (ft_strncmp(cmd->cmd_name, "export", -1) == 0)
		res = ft_export(minishell, cmd->args);
	else if (ft_strncmp(cmd->cmd_name, "unset", -1) == 0)
		res = ft_unset(cmd->args, &(minishell->env_list));
	else if (ft_strncmp(cmd->cmd_name, "exit", -1) == 0)
		ft_exit(cmd->args, minishell->env_list);
	return (res);
}

int	find_and_launch_builtin(t_cmd *cmd, t_minishell *minishell)
{
	int	res;

	res = 0;
	if (ft_strncmp(cmd->cmd_name, "cd", -1) == 0)
		res = ft_cd(cmd->args);
	else if (ft_strncmp(cmd->cmd_name, "export", -1) == 0)
		res = ft_export(minishell, cmd->args);
	else if (ft_strncmp(cmd->cmd_name, "unset", -1) == 0)
		res = ft_unset(cmd->args, &(minishell->env_list));
	else if (ft_strncmp(cmd->cmd_name, "exit", -1) == 0)
		ft_exit(cmd->args, minishell->env_list);
	else if (ft_strncmp(cmd->cmd_name, "echo", -1) == 0)
		res = ft_echo(cmd->args);
	else if (ft_strncmp(cmd->cmd_name, "pwd", -1) == 0)
		res = ft_pwd();
	else if (ft_strncmp(cmd->cmd_name, "env", -1) == 0)
		res = ft_env(cmd->args, minishell->env_list);
	exit (res);
}
