/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:16:27 by mgoltay           #+#    #+#             */
/*   Updated: 2023/04/25 17:49:59 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	syntax_error(t_elem *head, t_elem *elem)
{
	ft_putstr_fd("ruhan_zahra_shell:", 2);
	ft_putstr_fd(" syntax error near unexpected token `", 2);
	write(2, elem->content, 1);
	ft_putstr_fd("'\n", 2);
	free_elem(head);
	return (0);
}

void	nosuch_error(char *str, int exitcode)
{
	ft_putstr_fd("ruhan_zahra_shell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory", 2);
	g_exit_status = exitcode;
	exit(g_exit_status);
}

void	perm_error(int exit_code)
{
	ft_putstr_fd("ruhan_zahra_shell:", 2);
	ft_putstr_fd(" Permission denied", 2);
	g_exit_status = exit_code;
	exit (g_exit_status);
}
