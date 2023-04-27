/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:19:27 by zsyyida           #+#    #+#             */
/*   Updated: 2023/04/27 19:49:10 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_in(t_list_rdr *rdr, t_shell *shell)
{
	if (access(rdr->file, F_OK | R_OK) == 0)
		rdr->fd_in = open(rdr->file, O_RDONLY, 0777);
	else if (errno == 13)
		perm_error(13, shell);
	else
		nosuch_error(rdr->file, 1, shell);
	dup2(rdr->fd_in, STDIN_FILENO);
}

void	exec_out(t_list_rdr *rdr, t_shell *shell)
{
	if (access(rdr->file, F_OK) || !access(rdr->file, F_OK | W_OK))
	{
		if (rdr->type == RDR_OUT_TRUNC)
			rdr->fd_out = open(rdr->file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
		else if (rdr->type == RDR_OUT_APPEND)
			rdr->fd_out = open(rdr->file, O_CREAT | O_WRONLY | O_APPEND, 0777);
	}
	else
		perm_error(1, shell);
	dup2(rdr->fd_out, STDOUT_FILENO);
}

char	*ft_here_doc(t_shell *shell, char *delimiter)
{
	char	*herestring;
	char	*input;
	int		i;

	herestring = NULL;
	delimiter = ft_strjoin_ft(delimiter, "\n");
	i = dup(STDIN_FILENO);
	while (1)
	{
		ft_putstr("> ");
		input = get_next_line(i);
		if (!input || !ft_strcmp(input, delimiter))
			break ;
		herestring = ft_free_strjoin(herestring, input);
	}
	close(i);
	if (input)
		free(input);
	free(delimiter);
	i = -1;
	while (herestring[++i])
		if (herestring[i] == '$' && lenofenv(&herestring[i]) > 1)
			handle_env(shell, &herestring, i--);
	return (herestring);
}

void	exec_here_doc(t_list_rdr *rdr, t_shell *shell)
{
	char		*herestring;
	t_list_rdr	*next;

	rdr->fd_in = open("here_doc", O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (rdr->fd_in < 0)
		nosuch_error(rdr->file, 1, shell);
	herestring = ft_here_doc(shell, rdr->file);
	if ((rdr->next && rdr->next->type != RDR_HEREDOC
			&& rdr->next->type != RDR_IN) || !rdr->next)
		dup2(rdr->fd_in, 0);
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

void	exec_rdr(t_shell *shell, t_list_rdr *ptr)
{
	while (ptr)
	{
		if (ptr->file && (ptr->type == RDR_IN))
			exec_in(ptr, shell);
		else if (ptr->type == RDR_OUT_TRUNC || ptr->type == RDR_OUT_APPEND)
			exec_out(ptr, shell);
		if (ptr->type == RDR_HEREDOC)
			exec_here_doc(ptr, shell);
		ptr = ptr->next;
	}
}
