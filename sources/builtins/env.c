/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 13:34:55 by zsyyida           #+#    #+#             */
/*   Updated: 2023/04/27 18:44:15 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_find_var(char *env)
{
	int	j;

	j = 0;
	while (env[j] && env[j] != '=')
		j++;
	return (ft_strndup(env, j));
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

void	ft_env(t_shell *shell)
{
	int		i;

	i = -1;
	if (!shell->env)
		exit (127);
	while (shell->env[++i])
		if (is_in(shell->env[i], '='))
			printf("%s\n", shell->env[i]);
}
