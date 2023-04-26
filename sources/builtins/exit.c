/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:24:02 by zsyyida           #+#    #+#             */
/*   Updated: 2023/04/26 19:34:18 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// all errors should be printed to std error
// store exit status in global int to be able to aces it again
// also to set it when not exiting like when too many arguments
// check it with echo $? which should print exit status number

int	fits_in_long_long(char *str)
{
	long long	out;
	int			c;

	if (ft_strlen(str) > 20)
		return (0);
	if (ft_strncmp(str, "-9223372036854775808", 21) == 0)
		return (1);
	out = 0;
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		c = *str - '0';
		if (out > (LLONG_MAX - c) / 10)
			return (0);
		out = out * 10 + c;
		str++;
	}
	return (1);
}

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
			return (0);
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
		if (!ft_isdigit(cmd[i]))
			return (1);
		if (ft_atoi_exit(cmd) == -1)
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(t_shell *shell, t_list_cmd *l)
{
	ft_putstr_fd("exit\n", 1);
	g_exit_status = 0;
	if (l->cmd[1] && l->cmd[2])
	{
		ft_putstr_fd("ruhan_zahra_shell: exit: too many arguments\n", 2);
		g_exit_status = 1;
		return ;
	}
	else if (l->cmd[1] && (ft_check_numeric(l->cmd[1]) || !fits_in_long_long(l->cmd[1])))
	{
		ft_putstr_fd("reach", 2);
		ft_putstr_fd("ruhan_zahra_shell: exit: ", 2);
		ft_putstr_fd(l->cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		g_exit_status = 255;
	}
	else if (l->cmd[1])
	{
		if (ft_atoi_exit(l->cmd[1]) == -1)
			g_exit_status = 1;
		else
			g_exit_status = ft_atoi_exit(l->cmd[1]);
	}
	free_shell(shell);
	exit(g_exit_status);
}
