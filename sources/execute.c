/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 17:40:10 by zsyyida           #+#    #+#             */
/*   Updated: 2023/04/27 17:05:03 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	error_pipe(char **cmd, t_shell *shell)
{
	ft_putstr_fd("ruhan_zahra_shell: ", 2);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	g_exit_status = 127;
	free_shell(shell);
	exit (127);
}

void	ft_wait(int *pid, int nbr_pipes)
{
	int	i;
	int	p;

	i = 0;
	while (i < nbr_pipes + 1)
	{
		p = g_exit_status;
		waitpid(pid[i], &p, 0);
		if (p != g_exit_status)
			g_exit_status = WEXITSTATUS(p);
		i++;
	}
}

void	close_fds(t_shell *shell)
{
	int	j;

	j = 0;
	while (j < shell->nbr_pipes)
	{
		close(shell->fd[j][0]);
		close(shell->fd[j][1]);
		j++;
	}
}

void	ex_loop(t_shell *shell, t_list_cmd *ptr)
{
	int	i;

	i = 0;
	while (ptr)
	{
		if (ptr->cmd && !ft_strcmp(ptr->cmd[0], "./minishell"))
			ft_shlvl(shell, 1);
		if (ptr->cmd)
		{
			ptr->cmd_nbr = i;
			if (check_builtins(ptr->cmd[0]) && !shell->nbr_pipes
				&& !ptr->rdr && !ptr->next)
				ft_builtins_parent(shell, ptr->cmd);
			else if (ptr->cmd != NULL)
				ft_fork(shell, ptr, shell->pid);
		}
		else if (ptr->rdr)
			exec_rdr(shell, ptr->rdr);
		ptr = ptr->next;
		i++;
	}
}

void	execute(t_shell *shell, t_list_cmd *ptr)
{
	shell->pid = (int *)ft_calloc(shell->nbr_pipes + 1, sizeof(int));
	if (shell->nbr_pipes > 0)
		shell->fd = open_pipes(shell);
	ex_loop(shell, ptr);
	close_fds(shell);
	ft_wait(shell->pid, shell->nbr_pipes);
	signal(SIGINT, handle_sig);
	clean_shell(shell);
	unlink("here_doc");
}
