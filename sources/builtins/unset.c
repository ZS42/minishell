/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:44:27 by zsyyida           #+#    #+#             */
/*   Updated: 2023/04/27 20:47:36 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

char	**remove_from2d(char **s, int i)
{
	int		len;
	char	**new;

	len = 0;
	if (!s)
		return (NULL);
	while (s[len])
		len++;
	if (i >= len || i < 0)
		return (ft_cpy_2d(s));
	new = ft_calloc(len, sizeof(char *));
	if (!new)
		return (NULL);
	len = -1;
	while (s[++len] && len < i)
		new[len] = ft_strdup(s[len]);
	while (s[++len])
		new[len - 1] = ft_strdup(s[len]);
	new[len - 1] = NULL;
	return (new);
}

void	unset_update(t_shell *shell, char *line)
{
	int		i;
	char	**new;

	i = does_exist(shell, line);
	if (!check_valid(line) || is_in(line, '='))
		error_exp("unset", line);
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
