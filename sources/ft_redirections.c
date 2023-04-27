/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:19:27 by zsyyida           #+#    #+#             */
/*   Updated: 2023/04/27 18:29:32 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_in(t_list_rdr *rdr, t_shell *shell)
{
	if (access(rdr->file, F_OK | R_OK) == 0)
		rdr->fd_in = open(rdr->file, O_RDONLY, 0777);
	else
	{
		if (errno == 13)
			perm_error(13, shell);
		else
			nosuch_error(rdr->file, 1, shell);
	}
	dup2(rdr->fd_in, STDIN_FILENO);
}

void	exec_out(t_list_rdr *rdr, t_shell *shell)
{
	if (access(rdr->file, F_OK) != 0)
	{
		if (rdr->type == RDR_OUT_TRUNC)
			rdr->fd_out = open(rdr->file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
		else if (rdr->type == RDR_OUT_APPEND)
			rdr->fd_out = open(rdr->file, O_CREAT | O_WRONLY | O_APPEND, 0777);
	}
	else
	{
		if (access(rdr->file, F_OK | W_OK) == 0)
		{
			if (rdr->type == RDR_OUT_TRUNC)
				rdr->fd_out = open(rdr->file, O_CREAT
						| O_WRONLY | O_TRUNC, 0777);
			else if (rdr->type == RDR_OUT_APPEND)
				rdr->fd_out = open(rdr->file, O_CREAT
						| O_WRONLY | O_APPEND, 0777);
		}
		else
			perm_error(1, shell);
	}
	dup2(rdr->fd_out, STDOUT_FILENO);
}

char	*ft_here_doc(t_shell *shell, char *delimiter, char *herestring)
{
	char	*temp;
	int		i;
	int		fd;

	temp = "";
	delimiter = ft_strjoin_ft(delimiter, "\n");
	fd = dup(STDIN_FILENO);
	while (1)
	{
		write (1, "> ", 2);
		herestring = get_next_line(fd);
		if (ft_strncmp(herestring, delimiter, ft_strlen(delimiter) + 1) == 0)
			break ;
		temp = ft_strjoin_ft(temp, herestring);
		free(herestring);
	}
	herestring = temp;
	i = -1;
	while (herestring[++i])
		if (herestring[i] == '$' && lenofenv(&herestring[i]) > 1)
			handle_env(shell, &herestring, i--);
	close(fd);
	return (herestring);
}

void	exec_here_doc(t_list_rdr *rdr, t_shell *shell)
{
	char		*herestring;
	t_list_rdr	*ptr;
	t_list_rdr	*next;

	ptr = rdr;
	herestring = "";
	rdr->fd_in = open("here_doc", O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (rdr->fd_in < 0)
		nosuch_error(ptr->file, 1, shell);
	herestring = ft_here_doc(shell, ptr->file, herestring);
	if ((ptr->next && ptr->next->type != RDR_HEREDOC
			&& ptr->next->type != RDR_IN) || !ptr->next)
		dup2(rdr->fd_in, 0);
	write(rdr->fd_in, herestring, ft_strlen_ft(herestring));
	if (!ptr->next || ptr->next->type != RDR_HEREDOC)
	{
		next = ptr->next;
		ptr->next = make_rdr("here_doc", '<', rdr);
		ptr->next->next = next;
	}
	close(rdr->fd_in);
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
