/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:19:27 by zsyyida           #+#    #+#             */
/*   Updated: 2023/04/29 18:45:25 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_in(t_list_rdr *rdr, t_shell *shell, int check)
{
	if (access(rdr->file, F_OK | R_OK) == 0)
	{
		rdr->fd_in = open(rdr->file, O_RDONLY, 0777);
		dup2(rdr->fd_in, STDIN_FILENO);
		close(rdr->fd_in);
	}
	else if (errno == 13)
		perm_error(13, shell, check);
	else
		nosuch_error(rdr->file, 1, shell, check);
}

void	exec_out(t_list_rdr *rdr, t_shell *shell, int check)
{
	if (access(rdr->file, F_OK) || !access(rdr->file, F_OK | W_OK))
	{
		if (rdr->type == RDR_OUT_TRUNC)
			rdr->fd_out = open(rdr->file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
		else if (rdr->type == RDR_OUT_APPEND)
			rdr->fd_out = open(rdr->file, O_CREAT | O_WRONLY | O_APPEND, 0777);
	}
	else
		perm_error(1, shell, check);
	dup2(rdr->fd_out, STDOUT_FILENO);
	close(rdr->fd_out);
}

// for < RDR_IN
// for << ptr->type == RDR_HEREDOC
// for > ptr->type == RDR_OUT_TRUNC
// for >> RDR_OUT_APPEND

void	exec_rdr(t_shell *shell, t_list_rdr *ptr, int check)
{
	while (ptr)
	{
		if (ptr->file && (ptr->type == RDR_IN))
			exec_in(ptr, shell, check);
		else if (ptr->type == RDR_OUT_TRUNC || ptr->type == RDR_OUT_APPEND)
			exec_out(ptr, shell, check);
		if (ptr->type == RDR_HEREDOC)
			exec_here_doc(ptr, shell, check);
		ptr = ptr->next;
	}
}
