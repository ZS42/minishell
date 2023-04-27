/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:16:27 by mgoltay           #+#    #+#             */
/*   Updated: 2023/04/27 17:25:41 by mgoltay          ###   ########.fr       */
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

void	nosuch_error(char *str, int exitcode, t_shell *shell)
{
	ft_putstr_fd("ruhan_zahra_shell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory", 2);
	g_exit_status = exitcode;
	free_shell(shell);
	exit(g_exit_status);
}

void	nosuch_error1(char *str, int exitcode)
{
	ft_putstr_fd("ruhan_zahra_shell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory", 2);
	g_exit_status = exitcode;
	exit(g_exit_status);
}

void	error_exp(char *cmd, char *iden)
{
	ft_putstr_fd("ruhan_zahra_shell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(iden, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_exit_status = 1;
}

void	perm_error(int exit_code, t_shell *shell)
{
	ft_putstr_fd("ruhan_zahra_shell:", 2);
	ft_putstr_fd(" Permission denied", 2);
	g_exit_status = exit_code;
	free_shell(shell);
	exit (g_exit_status);
}
