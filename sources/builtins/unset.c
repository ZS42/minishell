/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:44:27 by zsyyida           #+#    #+#             */
/*   Updated: 2023/04/26 19:12:46 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	error_unset(char *cmd)
{
	ft_putstr_fd("ruhan_zahra_shell: unset: `", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_exit_status = 1;
}

int	check_valid(char *line)
{
	int		i;
	char	*var;

	if (!ft_is_alpha(line[0]) && line[0] != '_')
		return (0);
	i = 0;
	var = ft_find_var(line);
	while (var[++i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
		{
			free(var);
			return (0);
		}
	}
	free(var);
	return (1);
}

void	unset_update(t_shell *shell, char *line)
{
	int		i;
	char	**new;

	i = does_exist(shell, line);
	if (!check_valid(line) || is_in(line, '='))
		error_unset(line);
	else if (i != -1)
	{
		new = remove_from2d(shell->env, i);
		ft_free_2d(shell->env);
		shell->env = new;
	}
}

void	ft_unset(t_shell *shell, char **cmd)
{
	int	i;

	g_exit_status = 0;
	if (!cmd[1])
		return ;
	i = 0;
	while (cmd[++i])
		unset_update(shell, cmd[i]);
}
