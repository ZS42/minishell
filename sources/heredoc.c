/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:24:29 by zsyyida           #+#    #+#             */
/*   Updated: 2023/04/24 15:54:36 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_here_doc(t_shell *shell, char *delimiter, char *herestring)
{
	char	*temp;
	int		i;
	int		fd;

	temp = "";
	delimiter = ft_strjoin_ft(delimiter, "\n");
	fd = dup(STDIN_FILENO);
	while (1)
	{
		write (1, "> ", 2);
		herestring = get_next_line(fd);
		if (ft_strncmp(herestring, delimiter, ft_strlen(delimiter) + 1) == 0)
			break ;
		temp = ft_strjoin_ft(temp, herestring);
		free(herestring);
	}
	herestring = temp;
	i = -1;
	while (herestring[++i])
		if (herestring[i] == '$' && lenofenv(&herestring[i]) > 1)
			handle_env(shell, &herestring, i--);
	close(fd);
	return (herestring);
}
