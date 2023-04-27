/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:16:20 by mgoltay           #+#    #+#             */
/*   Updated: 2023/04/27 20:47:36 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_rdr(int type)
{
	if (type == '<' || type == '>')
		return (1);
	if (type == -2 || type == -3)
		return (1);
	return (0);
}

t_list_rdr	*make_rdr(char *str, int type, t_list_rdr *prev)
{
	t_list_rdr	*rdr;

	rdr = malloc(sizeof(t_list_rdr));
	rdr->file = ft_strdup(str);
	if (type == '<')
		rdr->type = RDR_IN;
	else if (type == '>')
		rdr->type = RDR_OUT_TRUNC;
	else if (type == -2)
		rdr->type = RDR_HEREDOC;
	else if (type == -3)
		rdr->type = RDR_OUT_APPEND;
	rdr->fd_in = -1;
	rdr->fd_out = -1;
	rdr->fd_pipe[0] = -1;
	rdr->fd_pipe[1] = -1;
	rdr->next = NULL;
	rdr->prev = prev;
	return (rdr);
}

t_elem	*remove_rdr(t_elem *head)
{
	t_elem	*elem;
	t_elem	*next;

	while (is_rdr(head->type))
	{
		free_single(&head);
		free_single(&head);
	}
	elem = head;
	while (elem && elem->next)
	{
		if (is_rdr(elem->next->type))
		{
			next = elem->next;
			elem->next = elem->next->next->next;
			next->next->next = NULL;
			free_elem(next);
		}
		else
			elem = elem->next;
	}
	return (head);
}

t_list_rdr	*get_rdr(t_elem *elem, t_list_rdr *prev)
{
	t_list_rdr	*rdr;

	if (!elem)
		return (NULL);
	rdr = NULL;
	while (elem && !rdr)
	{
		if (is_rdr(elem->type))
		{
			rdr = make_rdr(elem->next->content, elem->type, prev);
			rdr->next = get_rdr(elem->next->next, rdr);
		}
		elem = elem->next;
	}
	return (rdr);
}
