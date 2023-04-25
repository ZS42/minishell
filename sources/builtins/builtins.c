/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:58:15 by zsyyida           #+#    #+#             */
/*   Updated: 2023/04/25 17:23:19 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_builtins(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	else
		return (0);
}

void	ft_builtins_parent(t_shell *shell, t_list_cmd *cmd_list)
{
	if (ft_strncmp(cmd_list->cmd[0], "exit", 5) == 0)
		ft_exit(shell, cmd_list);
	if (ft_strncmp(cmd_list->cmd[0], "cd", 3) == 0)
		ft_cd(shell, cmd_list->cmd);
	if (ft_strncmp(cmd_list->cmd[0], "export", 7) == 0)
		ft_export(shell, cmd_list->cmd);
	if (ft_strncmp(cmd_list->cmd[0], "unset", 6) == 0)
		ft_unset(shell, cmd_list->cmd);
	if (ft_strncmp(cmd_list->cmd[0], "echo", 5) == 0)
		ft_echo(cmd_list->cmd);
	if (ft_strncmp(cmd_list->cmd[0], "pwd", 4) == 0)
		ft_pwd();
	if (ft_strncmp(cmd_list->cmd[0], "env", 4) == 0)
		ft_env(shell);
}

void	ft_builtins_child(t_shell *shell, t_list_cmd *cmd_list)
{
	if (ft_strncmp(cmd_list->cmd[0], "exit", 5) == 0)
		ft_exit(shell, cmd_list);
	if (ft_strncmp(cmd_list->cmd[0], "cd", 3) == 0)
		ft_cd(shell, cmd_list->cmd);
	if (ft_strncmp(cmd_list->cmd[0], "export", 7) == 0)
		ft_export(shell, cmd_list->cmd);
	if (ft_strncmp(cmd_list->cmd[0], "unset", 6) == 0)
		ft_unset(shell, cmd_list->cmd);
	if (ft_strncmp(cmd_list->cmd[0], "echo", 5) == 0)
		ft_echo(cmd_list->cmd);
	if (ft_strncmp(cmd_list->cmd[0], "pwd", 4) == 0)
		ft_pwd();
	if (ft_strncmp(cmd_list->cmd[0], "env", 4) == 0)
		ft_env(shell);
	exit (g_exit_status);
}
