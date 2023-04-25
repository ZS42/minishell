/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 13:34:55 by zsyyida           #+#    #+#             */
/*   Updated: 2023/04/25 17:23:30 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_getenv(t_shell *shell, char *var)
{
	int	i;
	int	len;

	if (!var || !shell || !shell->env)
		return (NULL);
	if (!var[0])
		return (ft_strdup_ft("$"));
	if (var[0] == '?' && var[1] == '\0')
		return (ft_itoa(g_exit_status));
	len = ft_strlen(var);
	i = -1;
	while (shell->env[++i])
		if (!ft_strncmp(shell->env[i], var, len) && shell->env[i][len] == '=')
			return (ft_strdup_ft(&shell->env[i][len + 1]));
	return (NULL);
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
