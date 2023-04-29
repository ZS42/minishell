/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:52:29 by mgoltay           #+#    #+#             */
/*   Updated: 2023/04/29 19:22:32 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_unclosed(char *line)
{
	int	i;
	int	j;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			j = 0;
			while (line[i + ++j] != line[i])
			{
				if (line[i + j] == '\0')
				{
					ft_putstr("Unclosed quote: ");
					write(1, &line[i], 1);
					ft_putstr("\n");
					return (0);
				}
			}
			i += j;
		}
	}
	return (1);
}

int	check_special(char *line)
{
	int	i;
	int	j;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			j = 1;
			while (line[i + j] && line[i + j] != line[i])
				j++;
			i += j;
		}
		if (is_in("\\;`", line[i]))
		{
			ft_putstr("Error with Line: ");
			write(1, &line[i], 1);
			ft_putstr("\n");
			return (0);
		}
	}
	return (1);
}

int	check_redir(t_elem *head)
{
	t_elem	*elem;

	elem = head;
	while (elem)
	{
		if (is_rdr(elem->type) && (!elem->next || elem->next->type != 0))
			return (syntax_error(head, elem));
		elem = elem->next;
	}
	return (1);
}

int	check_seps(t_elem *head)
{
	t_elem	*elem;

	elem = head;
	if (head && is_sep(head))
		return (syntax_error(head, elem));
	while (elem)
	{
		if (is_sep(elem) && is_sep(elem->next))
			return (syntax_error(head, elem));
		elem = elem->next;
	}
	return (1);
}

void	parse_line(t_shell *shell, char *line)
{
	t_elem	*head;

	if (!line || !line[0])
		return ;
	if (!check_unclosed(line) || !check_special(line))
	{
		g_exit_status = 1;
		return ;
	}
	head = lex(line);
	head = clean_elem(shell, head);
	if (!check_redir(head) || !check_seps(head))
	{
		g_exit_status = 1;
		return ;
	}
	convert(shell, head);
	if (!shell->cmd_list && line[0] != '$')
	{
		ft_putstr_fd("ruhan_zahra_shell: : command not found\n", 2);
		g_exit_status = 127;
	}
	if (shell->cmd_list)
		shell->nbr_pipes = count_pipes(shell->cmd_list[0]);
	free_elem(head);
}
