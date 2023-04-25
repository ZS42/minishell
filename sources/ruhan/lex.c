/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:57:46 by mgoltay           #+#    #+#             */
/*   Updated: 2023/04/20 13:56:40 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_red(char *line, int *type, int *len)
{
	if (line[0] == '<' && line[1] == '<')
		*type = -2;
	else if (line[0] == '>' && line[1] == '>')
		*type = -3;
	else if (line[0] == '<')
		*type = '<';
	else if (line[0] == '>')
		*type = '>';
	else if (line[0] == '|' && line[1] == '|')
		*type = -4;
	else if (line[0] == '|')
		*type = '|';
	else if (line[0] == '&')
		*type = '&';
	*len = (*type < 0) + 1;
	if (*type == '&' && line[1] == '&')
		*len = 2;
}

void	handle_special(char *line, int *type, int *len)
{
	*len = 0;
	if (line[0] == '\t' || line[0] == ' ')
	{
		while (line[*len] == '\t' || line[*len] == ' ')
			(*len)++;
		*type = ' ';
	}
	else if (line[0] == '\'' || line[0] == '\"')
	{
		*len = *len + 2;
		while (line[*len - 1] != line[0])
			(*len)++;
		*type = line[0];
	}
	else if (line[0] == '$')
	{
		*len = lenofenv(line);
		*type = '$';
	}
	else if (is_in("<|&>", line[0]))
		handle_red(line, type, len);
}

void	update(char *line, int *type, int *len)
{
	if (!line || !line[0])
		*len = 0;
	else if (is_in("\t \' \" | $ & < >", *line))
		handle_special(line, type, len);
	else
	{
		*len = 0;
		while (line[*len] && !is_in("\t \' \" | $ & < >", line[*len]))
			(*len)++;
		*type = 0;
	}
}

t_elem	*lex(char *line)
{
	t_elem	*head;
	t_elem	*next;
	int		type;
	int		len;

	update(line, &type, &len);
	head = create_elem(line, len, type, NULL);
	line = line + len;
	next = head;
	while (next)
	{
		update(line, &type, &len);
		next->next = create_elem(line, len, type, next);
		line = line + len;
		next = next->next;
	}
	return (head);
}

t_elem	*clean_elem(t_shell *shell, t_elem *head)
{
	t_elem	*elem;

	elem = head;
	while (elem)
	{
		if (elem->type == '\'')
			remove_quotes(elem);
		if (elem->type == '\"')
			doubleq(shell, elem);
		if (elem->type == '$')
			sub_env(shell, elem);
		elem = elem->next;
	}
	head = remove_nulls(head);
	join_words(head);
	head = remove_spaces(head);
	return (head);
}
