/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:15:13 by zsyyida           #+#    #+#             */
/*   Updated: 2023/04/27 20:47:36 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_exp_line(char *line)
{
	char	*str;

	ft_putstr("declare -x ");
	str = ft_find_var(line);
	ft_putstr(str);
	if (line[ft_strlen(str)] == '=')
	{
		ft_putstr("=\"");
		ft_putstr(&line[ft_strlen(str) + 1]);
		ft_putstr("\"");
	}
	ft_putstr("\n");
	free(str);
}

void	ft_print_export(t_shell *shell)
{
	char	**exp;
	int		i;

	exp = ft_cpy_2d(shell->env);
	sort_2d_array(exp);
	i = -1;
	while (exp[++i])
		if (ft_strncmp(exp[i], "_=", 2))
			print_exp_line(exp[i]);
	ft_free_2d(exp);
}

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
		new[len] = ft_strdup(shell->env[len]);
	new[len] = ft_strdup(line);
	new[len + 1] = NULL;
	ft_free_2d(shell->env);
	shell->env = new;
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
		shell->env[i] = ft_strdup(line);
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
