/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:59:38 by zsyyida           #+#    #+#             */
/*   Updated: 2023/04/25 14:06:38 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Function: void rl_replace_line (const char *text, int clear_undo) ¶
// Replace the contents of rl_line_buffer with text.
// The point and mark are preserved, if possible. If clear_undo
// is non-zero, the undo list associated with the current line is cleared.

// Function: int rl_on_new_line ()
// Tell the update routines that we have moved onto a new (empty) line,
// usually after ouputting a newline.

// Function: int rl_redisplay ()
// Change what's displayed on the screen to reflect the current contents
// of rl_line_buffer.

// SIGINT = 4
// SIGINT  ctrl + C

// SIGQUIT = 3?
// SIGQUIT ctrl + '\'

// ctrl + D is not signal but EOF
// should be handled where readline . Makes content of readline null

		// ft_putstr_fd("\e[34mruhan_zahra_shell\e[0m   \b\b", 2);
		// if (sig == 3)
		// 	return ;
		// ft_putstr_fd("\e[34mruhan_zahra_shell\e[0m ", 2);
// in parent have to disable SIGINT and put it back after waiting so
// that SIGINT doesnt work on bot parent and child together

void	handle_sig(int sig)
{
	ft_putstr_fd("\e[34mruhan_zahra_shell\e[0m   \b\b", 2);
	if (sig == SIGQUIT)
		return ;
	ft_putstr_fd("\n\e[34mruhan_zahra_shell\e[0m ", 2);
	g_exit_status = 1;
}

void	handle_sig_child(int sig)
{
	if (sig == SIGINT)
		g_exit_status = 130;
	if (sig == SIGQUIT)
		g_exit_status = 131;
	exit(g_exit_status);
}
