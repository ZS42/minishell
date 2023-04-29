/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:46:05 by mgoltay           #+#    #+#             */
/*   Updated: 2023/04/29 18:43:52 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	hd_loop(char **herestring, char *delimiter)
{
	char	*input;

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
		*herestring = ft_free_strjoin(*herestring, input);
	}
	if (input)
		free(input);
}

char	*ft_here_doc(t_shell *shell, char *delimiter)
{
	char	*herestring;
	int		i;

	herestring = NULL;
	delimiter = ft_strjoin(delimiter, "\n");
	i = g_exit_status;
	g_exit_status = dup(STDIN_FILENO);
	hd_loop(&herestring, delimiter);
	if (g_exit_status != -1)
		close(g_exit_status);
	g_exit_status = i;
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
