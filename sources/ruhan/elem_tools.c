/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:41:04 by mgoltay           #+#    #+#             */
/*   Updated: 2023/04/20 13:56:32 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_elem	*create_elem(char *content, int len, int type, t_elem *prev)
{
	t_elem	*new;

	if (!content || !content[0] || !len)
		return (NULL);
	new = malloc(sizeof(t_elem));
	if (!new)
		return (NULL);
	new->type = type;
	new->content = ft_strndup(content, len);
	new->next = NULL;
	new->prev = prev;
	return (new);
}

void	free_next(t_elem *elem)
{
	t_elem	*next;

	if (!elem || !elem->next)
		return ;
	next = elem->next;
	elem->next = elem->next->next;
	if (elem->next)
		elem->next->prev = elem;
	next->next = NULL;
	free_elem(next);
}

void	free_single(t_elem **head)
{
	t_elem	*next;

	if (!head || !(*head))
		return ;
	if ((*head)->content)
		free((*head)->content);
	next = (*head)->next;
	if ((*head)->prev)
		(*head)->prev->next = next;
	if (next)
		next->prev = (*head)->prev;
	free(*head);
	*head = next;
}

int	get_count(t_elem *elem, int c)
{
	int	i;

	i = 0;
	while (elem)
	{
		if (elem->type == c)
			i++;
		elem = elem->next;
	}
	return (i);
}
