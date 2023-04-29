/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:19:27 by zsyyida           #+#    #+#             */
/*   Updated: 2023/04/29 17:40:07 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_in(t_list_rdr *rdr, t_shell *shell, int check)
{
	if (access(rdr->file, F_OK | R_OK) == 0)
	{
		rdr->fd_in = open(rdr->file, O_RDONLY, 0777);
		dup2(rdr->fd_in, STDIN_FILENO);
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
}

char	*ft_here_doc(t_shell *shell, char *delimiter)
{
	char	*herestring;
	char	*input;
	int		i;

	herestring = NULL;
	delimiter = ft_strjoin(delimiter, "\n");
	i = g_exit_status;
	g_exit_status = dup(STDIN_FILENO);
	while (1)
	{
		signal(SIGINT, handle_sig_hd);
		ft_putstr("> ");
		input = get_next_line(g_exit_status);
		if (!input || !ft_strcmp(input, delimiter))
		{
			ft_putstr("  \b\b");
			break ;
		}
		herestring = ft_free_strjoin(herestring, input);
	}
	if (g_exit_status != -1)
		close(g_exit_status);
	g_exit_status = i;
	if (input)
		free(input);
	free(delimiter);
	i = -1;
	while (herestring != NULL && herestring[++i])
		if (herestring[i] == '$' && lenofenv(&herestring[i]) > 1)
			handle_env(shell, &herestring, i--);
	return (herestring);
}

void	exec_here_doc(t_list_rdr *rdr, t_shell *shell, int check)
{
	char		*herestring;
	t_list_rdr	*next;

	rdr->fd_in = open("here_doc", O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (rdr->fd_in < 0)
		nosuch_error(rdr->file, 1, shell, check);
	herestring = ft_here_doc(shell, rdr->file);
	if ((rdr->next && rdr->next->type != RDR_HEREDOC
			&& rdr->next->type != RDR_IN) || !rdr->next)
		dup2(rdr->fd_in, 0);
	if (check)
		ft_putstr_fd(herestring, rdr->fd_in);
	free(herestring);
	close(rdr->fd_in);
	if (!rdr->next || rdr->next->type != RDR_HEREDOC)
	{
		next = rdr->next;
		rdr->next = make_rdr("here_doc", '<', rdr);
		rdr->next->next = next;
	}
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
