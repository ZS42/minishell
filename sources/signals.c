/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:59:38 by zsyyida           #+#    #+#             */
/*   Updated: 2023/04/29 17:43:52 by mgoltay          ###   ########.fr       */
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

void	handle_sig_hd(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\b\b  ", g_exit_status);
		if (g_exit_status != -1)
			close(g_exit_status);
		g_exit_status = -1;
	}
}

void	handle_prompt(int sig)
{
	rl_on_new_line();
	rl_redisplay();
	ft_putstr("  \b\b\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	if (sig == SIGINT)
		g_exit_status = 1;
}

void	handle_nl(int sig)
{
	(void)sig;
	ft_putstr("\n");
	g_exit_status = 130;
	return ;
}

void	handle_quit(int sig)
{
	(void)sig;
	ft_putstr_fd("Quit: 3\n", 2);
	g_exit_status = 131;
}
