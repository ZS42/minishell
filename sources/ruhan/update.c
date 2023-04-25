/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:39:00 by mgoltay           #+#    #+#             */
/*   Updated: 2023/04/24 15:54:11 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	remove_quotes(t_elem *elem)
{
	char	*inside;
	int		len;

	len = ft_strlen(elem->content);
	inside = NULL;
	if (len > 2)
		inside = ft_strndup(&elem->content[1], len - 2);
	free(elem->content);
	elem->content = inside;
	elem->type = 0;
}

void	doubleq(t_shell *shell, t_elem *elem)
{
	int	i;

	if (!elem || !elem->content)
		return ;
	remove_quotes(elem);
	if (!elem || !elem->content)
		return ;
	i = -1;
	while (elem->content[++i])
		if (elem->content[i] == '$' && lenofenv(&elem->content[i]) > 1)
			handle_env(shell, &elem->content, i--);
}

t_elem	*remove_nulls(t_elem *head)
{
	t_elem	*elem;

	while (head && (!head->content || !head->content[0]))
		free_single(&head);
	elem = NULL;
	if (head)
		elem = (head)->next;
	while (elem)
	{
		if (!elem->content || !elem->content[0])
			free_single(&elem);
		else
			elem = elem->next;
	}
	return (head);
}

void	join_words(t_elem *elem)
{
	char	*join;

	while (elem && elem->next)
	{
		if (elem->type == 0 && elem->next->type == 0)
		{
			join = ft_null_strjoin(elem->content, elem->next->content);
			if (elem->content)
				free(elem->content);
			elem->content = join;
			free_next(elem);
		}
		else
			elem = elem->next;
	}
}

t_elem	*remove_spaces(t_elem *head)
{
	t_elem	*elem;

	while (head && head->type == ' ')
		free_single(&head);
	elem = head;
	while (elem && elem->next)
	{
		if (elem->next->type == ' ')
			free_next(elem);
		else
			elem = elem->next;
	}
	return (head);
}
