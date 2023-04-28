/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:58:15 by zsyyida           #+#    #+#             */
/*   Updated: 2023/04/28 20:16:44 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_builtins(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	else
		return (0);
}

void	ft_builtins_parent(t_shell *shell, char **cmd)
{
	if (!ft_strcmp(cmd[0], "exit"))
		ft_exit(shell, cmd);
	if (!ft_strcmp(cmd[0], "cd"))
		ft_cd(shell, cmd);
	if (!ft_strcmp(cmd[0], "export"))
		ft_export(shell, cmd);
	if (!ft_strcmp(cmd[0], "unset"))
		ft_unset(shell, cmd);
	if (!ft_strcmp(cmd[0], "echo"))
		ft_echo(cmd);
	if (!ft_strcmp(cmd[0], "pwd"))
		ft_pwd();
	if (!ft_strcmp(cmd[0], "env"))
		ft_env(shell);
}

void	ft_builtins_child(t_shell *shell, t_list_cmd *cmd)
{
	ft_builtins_parent(shell, cmd->cmd);
	free_shell(shell);
	exit (g_exit_status);
}
