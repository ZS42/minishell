/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:47:24 by zsyyida           #+#    #+#             */
/*   Updated: 2023/04/25 17:23:33 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_option(char *opt)
{
	int	i;

	if (!opt || opt[0] != '-' || opt[1] != 'n')
		return (0);
	i = 0;
	while (opt[++i])
		if (opt[i] != 'n')
			return (0);
	return (1);
}

void	ft_echo(char **cmd)
{
	int	flag;
	int	i;

	flag = 0;
	i = 0;
	while (is_option(cmd[++i]))
		flag = 1;
	while (cmd[i])
	{
		ft_putstr(cmd[i]);
		if (cmd[++i])
			ft_putstr(" ");
	}
	if (!flag)
		ft_putstr("\n");
	g_exit_status = 0;
}
