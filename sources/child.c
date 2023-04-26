/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 16:02:46 by zsyyida           #+#    #+#             */
/*   Updated: 2023/04/26 18:28:12 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_dupe_pipes(t_shell *shell, int i)
{
	if (i < shell->nbr_pipes)
		dup2(shell->fd[i][1], STDOUT_FILENO);
	if (i > 0)
		dup2(shell->fd[i - 1][0], STDIN_FILENO);
	close_fds(shell);
}

int	**open_pipes(t_shell *shell)
{
	int	i;

	i = 0;
	shell->fd = (int **)ft_calloc(shell->nbr_pipes, sizeof(int *));
	while (i < shell->nbr_pipes)
		shell->fd[i++] = (int *)ft_calloc(2, sizeof(int));
	i = -1;
	while (++i < shell->nbr_pipes)
		if (pipe (shell->fd[i]) == -1 || shell->fd[i][0] == -1
			|| shell->fd[i][1] == -1)
			error(shell->fd[i], shell);
	return (shell->fd);
}

void	ft_fork(t_shell *shell, t_list_cmd *cmd_list, int *pid)
{
	pid[cmd_list->cmd_nbr] = fork();
	if (pid[cmd_list->cmd_nbr] == -1)
		error_pipe(cmd_list->cmd, shell);
	if (pid[cmd_list->cmd_nbr] == 0)
		child_process(shell, cmd_list);
	else
		signal(SIGINT, SIG_IGN);
}

void	handle_error(t_list_cmd *cmd_list, t_shell *shell)
{
	struct stat	info;

	info.st_mode = 0;
	stat(cmd_list->cmd[0], &info);
	g_exit_status = 1;
	if (access(cmd_list->cmd[0], X_OK) == -1)
	{
		if (access(cmd_list->cmd[0], F_OK) == -1)
			nosuch_error(cmd_list->cmd[0], 127, shell);
		else
			perm_error(126, shell);
	}
	else if (S_ISDIR(info.st_mode))
	{
		ft_putstr_fd("ruhan_zahra_shell: ", 2);
		ft_putstr_fd(cmd_list->cmd[0], 2);
		ft_putstr_fd(": is a directory", 2);
		g_exit_status = 126;
	}
	else
		nosuch_error(cmd_list->cmd[0], 1, shell);
	free_shell(shell);
	exit(g_exit_status);
}

void	child_process(t_shell *shell, t_list_cmd *cmd_list)
{
	signal(SIGINT, handle_sig_child);
	signal(SIGQUIT, handle_sig_child);
	if (shell->nbr_pipes > 0)
		ft_dupe_pipes(shell, cmd_list->cmd_nbr);
	exec_rdr(shell, cmd_list->rdr);
	g_exit_status = 0;
	if (check_builtins(cmd_list->cmd[0]) == 1)
		ft_builtins_child(shell, cmd_list);
	else if (cmd_list->path != NULL && cmd_list->cmd != NULL)
	{
		if (execve(cmd_list->path, cmd_list->cmd, shell->env) == -1)
			handle_error(cmd_list, shell);
	}
	else if (!cmd_list->path && cmd_list->cmd)
	{
		ft_putstr_fd("ruhan_zahra_shell: ", 2);
		ft_putstr_fd(cmd_list->cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		g_exit_status = 127;
	}
	exit(g_exit_status);
}
