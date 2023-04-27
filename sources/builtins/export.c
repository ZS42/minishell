/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:15:13 by zsyyida           #+#    #+#             */
/*   Updated: 2023/04/27 17:24:54 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_to_env(t_shell *shell, char *line)
{
	int		len;
	char	**new;

	len = 0;
	while (shell->env[len])
		len++;
	new = ft_calloc(sizeof(char *), len + 2);
	len = -1;
	while (shell->env[++len])
		new[len] = ft_strdup_ft(shell->env[len]);
	new[len] = ft_strdup_ft(line);
	new[len + 1] = NULL;
	ft_free_2d(shell->env);
	shell->env = new;
}

int	does_exist(t_shell *shell, char *var)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(var);
	while (shell->env[++i])
		if (!strncmp(shell->env[i], var, len)
			&& (!shell->env[i][len] || shell->env[i][len] == '='))
			return (i);
	return (-1);
}

void	env_update(t_shell *shell, char *line)
{
	char	*var;
	int		i;

	if (!check_valid(line))
	{
		error_exp("export", line);
		return ;
	}
	var = ft_find_var(line);
	i = does_exist(shell, var);
	if (i != -1 && line[ft_strlen(var)] == '=')
	{
		if (shell->env[i])
			free(shell->env[i]);
		shell->env[i] = ft_strdup_ft(line);
	}
	else if (i == -1)
		add_to_env(shell, line);
	free(var);
}

void	ft_export(t_shell *shell, char **cmd)
{
	int	i;

	if (does_exist(shell, "OLDPWD") == -1)
		env_update(shell, "OLDPWD");
	g_exit_status = 0;
	i = 0;
	if (cmd[1])
		while (cmd[++i])
			env_update(shell, cmd[i]);
	else
		ft_print_export(shell);
}
