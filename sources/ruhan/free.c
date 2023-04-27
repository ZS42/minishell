/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:05:05 by mgoltay           #+#    #+#             */
/*   Updated: 2023/04/27 16:49:27 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_elem(t_elem *head)
{
	t_elem	*curr;

	while (head)
	{
		curr = head;
		head = head->next;
		if (curr->content)
			free(curr->content);
		free(curr);
	}
}

void	free_rdr(t_list_rdr *rdr)
{
	if (!rdr)
		return ;
	if (rdr->fd_in >= 0)
		close(rdr->fd_in);
	if (rdr->fd_out >= 0)
		close(rdr->fd_out);
	if (rdr->file)
		free(rdr->file);
	if (rdr->next)
		free_rdr(rdr->next);
	free(rdr);
}

void	free_cmd_list(t_list_cmd *cmd)
{
	int	i;

	if (!cmd)
		return ;
	i = -1;
	while (cmd->cmd && cmd->cmd[++i])
		free(cmd->cmd[i]);
	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->path)
		free(cmd->path);
	if (cmd->rdr)
		free_rdr(cmd->rdr);
	free_cmd_list(cmd->next);
	free(cmd);
}

void	clean_shell(t_shell *shell)
{
	int	i;

	if (shell->fd)
		ft_free_2d_int(shell->fd, shell->nbr_pipes);
	if (shell->cmd_list)
	{
		i = -1;
		while (shell->cmd_list[++i])
			free_cmd_list(shell->cmd_list[i]);
		free(shell->cmd_list);
	}
	if (shell->oper)
		free(shell->oper);
	if (shell->pid)
		free(shell->pid);
	shell->cmd_list = NULL;
	shell->oper = NULL;
	shell->pid = NULL;
	shell->fd = NULL;
	shell->nbr_pipes = 0;
	shell->size = 0;
}

void	free_shell(t_shell *shell)
{
	ft_free_2d(shell->env);
	clean_shell(shell);
	free(shell);
}

// void	handle_line(t_shell *shell)
// {
// 	int	i;

// 	i = -1;
// 	ZEXEC(shell->cmd_list[0]);
// 	while (++i < shell->size - 1)
// 	{
// 		if (shell->oper[i] && !g_exit_status)
// 			ZEXEC(shell->cmd_list[1 + i]);
// 		else if (!shell->oper[i] && g_exit_status)
// 			ZEXEC(shell->cmd_list[1 + i]);
// 		else
// 			exit(g_exit_status);
// 	}
// }
