/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:23:46 by zsyyida           #+#    #+#             */
/*   Updated: 2023/04/26 18:09:19 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char**av, char **envp)
{
	char	*s;
	t_shell	*shell;

	if (ac != 1 || av[1])
		nosuch_error1(av[1], 127);
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, handle_sig);
	s = "1";
	shell = init_shell(envp);
	while (s != NULL)
	{
		s = readline("\e[34mruhan_zahra_shell\e[0m ");
		if (!s)
		{
			ft_putstr("exit\n");
			free_shell(shell);
			exit(0);
		}
		add_history (s);
		parse_line(shell, s);
		if (shell->cmd_list)
			execute(shell, shell->cmd_list[0]);
	}
}