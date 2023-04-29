/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 17:40:10 by zsyyida           #+#    #+#             */
/*   Updated: 2023/04/29 16:21:16 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	int		i;

	i = 0;
	while (ptr)
	{
		ptr->cmd_nbr = i++;
		if (ptr->cmd && !ft_strcmp(ptr->cmd[0], "./minishell"))
			ft_shlvl(shell, 1);
		if (ptr->cmd && check_builtins(ptr->cmd[0]) && !shell->nbr_pipes
			&& !ptr->rdr && !ptr->next)
			ft_builtins_parent(shell, ptr->cmd);
		else
			ft_fork(shell, ptr, shell->pid);
		ptr = ptr->next;
	}
}

void	execute(t_shell *shell, t_list_cmd *ptr)
{
	shell->pid = (int *)ft_calloc(shell->nbr_pipes + 1, sizeof(int));
	if (shell->nbr_pipes > 0)
		shell->fd = open_pipes(shell);
	signal(SIGQUIT, handle_quit);
	signal(SIGINT, handle_nl);
	ex_loop(shell, ptr);
	close_fds(shell);
	ft_wait(shell->pid, shell->nbr_pipes);
	clean_shell(shell);
	unlink("here_doc");
}
