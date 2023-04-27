/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:05:58 by mgoltay           #+#    #+#             */
/*   Updated: 2023/04/27 20:47:36 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	lenofenv(char *str)
{
	int	i;

	if (str[0] != '$')
		return (0);
	i = 1;
	if (str[i] == '?')
		return (2);
	while (ft_isalnum(str[i]))
		i++;
	return (i);
}

char	*ft_getenv(t_shell *shell, char *var)
{
	int	i;
	int	len;

	if (!var || !shell || !shell->env)
		return (NULL);
	if (!var[0])
		return (ft_strdup("$"));
	if (var[0] == '?' && var[1] == '\0')
		return (ft_itoa(g_exit_status));
	len = ft_strlen(var);
	i = -1;
	while (shell->env[++i])
		if (!ft_strncmp(shell->env[i], var, len) && shell->env[i][len] == '=')
			return (ft_strdup(&shell->env[i][len + 1]));
	return (NULL);
}

void	sub_env(t_shell *shell, t_elem *elem)
{
	char	*env;

	env = ft_getenv(shell, &elem->content[1]);
	if (elem->content)
		free(elem->content);
	elem->content = env;
	elem->type = 0;
}

void	handle_env(t_shell *shell, char **content, int start)
{
	char	*before;
	char	*env;
	char	*after;
	int		sublen;

	before = ft_strndup(*content, start);
	sublen = lenofenv(&(*content)[start]);
	after = ft_strndup(&(*content)[start], sublen);
	env = ft_getenv(shell, &after[1]);
	free(after);
	after = ft_strdup(&(*content)[start + sublen]);
	free(*content);
	*content = ft_null_strjoin(before, env);
	free(before);
	free(env);
	before = ft_null_strjoin(*content, after);
	free(*content);
	free(after);
	*content = before;
}
