/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 14:56:06 by mgoltay           #+#    #+#             */
/*   Updated: 2023/04/28 21:52:50 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**parse_elem(t_elem *head)
{
	char	**strs;
	int		size;
	int		i;

	size = get_count(head, 0) - get_count(head, '<') - get_count(head, '>');
	size = size - get_count(head, -2) - get_count(head, -3);
	if (size <= 0)
		return (NULL);
	strs = ft_calloc(sizeof(char *), size + 1);
	i = -1;
	while (++i < size)
	{
		if (head && is_rdr(head->type))
			head = head->next->next;
		if (!head)
			strs[i] = NULL;
		else
		{
			strs[i] = ft_strdup(head->content);
			head = head->next;
		}
	}
	strs[size] = NULL;
	return (strs);
}

t_list_cmd	*make_cmd(t_shell *shell, t_elem *head, t_list_cmd *prev)
{
	t_list_cmd	*cmd;
	char		*temp;

	cmd = malloc(sizeof(t_list_cmd));
	cmd->rdr = get_rdr(head, NULL);
	cmd->cmd = parse_elem(head);
	if (head->content[0] == '.' && head->content[1] == '/')
	{
		temp = ft_getenv(shell, "PWD");
		cmd->path = ft_null_strjoin(temp, &head->content[1]);
		free(temp);
	}
	else if (head->content[0] == '/')
		cmd->path = ft_strdup(head->content);
	else if (cmd->cmd && !check_builtins(cmd->cmd[0]))
		cmd->path = path(shell, cmd->cmd[0]);
	else
		cmd->path = NULL;
	cmd->prev = prev;
	cmd->cmd_nbr = 0;
	return (cmd);
}

t_list_cmd	*seperate_cmd(t_shell *shell, t_elem *head, t_list_cmd *prev)
{
	t_elem		*elem;
	t_elem		*next;
	t_list_cmd	*cmd;

	if (!head)
		return (NULL);
	elem = head;
	while (elem->next && elem->next->type != '|')
		elem = elem->next;
	free_next(elem);
	next = elem->next;
	elem->next = NULL;
	cmd = make_cmd(shell, head, prev);
	elem->next = next;
	head = next;
	cmd->next = seperate_cmd(shell, next, cmd);
	return (cmd);
}

void	initialize_shell(t_shell *shell, t_elem *head)
{
	if (!head)
	{
		shell->size = 0;
		shell->cmd_list = NULL;
		shell->oper = NULL;
		return ;
	}
	shell->size = get_count(head, '&') + get_count(head, -4) + 1;
	shell->cmd_list = ft_calloc(sizeof(t_list_cmd *), shell->size + 1);
	shell->oper = ft_calloc(sizeof(int), shell->size - 1);
}

void	convert(t_shell *shell, t_elem *head)
{
	int		i;
	t_elem	*elem;
	t_elem	*next;

	initialize_shell(shell, head);
	if (!head)
		return ;
	i = -1;
	while (++i < shell->size)
	{
		elem = head;
		while (elem->next && elem->next->type != '&' && elem->next->type != -4)
			elem = elem->next;
		if (elem->next)
			shell->oper[i] = (elem->next->type == '&');
		free_next(elem);
		next = elem->next;
		elem->next = NULL;
		shell->cmd_list[i] = seperate_cmd(shell, head, NULL);
		elem->next = next;
		head = next;
	}
	shell->cmd_list[shell->size] = NULL;
}
