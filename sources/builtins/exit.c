/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:24:02 by zsyyida           #+#    #+#             */
/*   Updated: 2023/04/29 16:48:07 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// all errors should be printed to std error
// store exit status in global int to be able to aces it again
// also to set it when not exiting like when too many arguments
// check it with echo $? which should print exit status number

int	ft_atoi_exit(const char *str)
{
	long long int	result;
	int				sign;
	int				i;

	result = 0;
	i = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		result = result * 10 + str[i] - '0';
		if (result > 9223372036854775807 && sign > 0)
			return (-1);
		else if (result > 9223372036854775807 && sign < 0)
			return (-1);
		i++;
	}
	return (sign * result);
}

int	ft_check_numeric(char *cmd)
{
	int	i;

	if (!cmd)
		return (0);
	i = 0;
	if (cmd[i] == '+' || cmd[i] == '-')
		i++;
	while (cmd[i] != '\0')
	{
		if (ft_strncmp(cmd, "9223372036854775808", 19) >= 0)
			return (1);
		if (!ft_isdigit(cmd[i]))
			return (1);
		if (ft_atoi_exit(cmd) == -1)
			return (1);
		i++;
	}
	return (0);
}

void	ft_not_num_error(char *cmd)
{
	if (ft_strcmp(cmd, "9223372036854775807"))
	{
		ft_putstr_fd("ruhan_zahra_shell: exit: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	g_exit_status = 255;
}

void	ft_exit(t_shell *shell, char **cmd)
{
	if (!(shell->cmd_list[0] && shell->cmd_list[0]->next))
		ft_putstr("exit\n");
	g_exit_status = 0;
	if (cmd[1] && cmd[2])
	{
		ft_putstr_fd("ruhan_zahra_shell: exit: too many arguments\n", 2);
		g_exit_status = 1;
		return ;
	}
	else if (cmd[1] && (ft_check_numeric(cmd[1])))
		ft_not_num_error(cmd[1]);
	else if (cmd[1])
	{
		if (ft_atoi_exit(cmd[1]) == -1)
			g_exit_status = 1;
		else
			g_exit_status = ft_atoi_exit(cmd[1]);
	}
	free_shell(shell);
	exit(g_exit_status);
}
