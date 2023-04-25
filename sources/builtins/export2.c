/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 16:04:12 by zsyyida           #+#    #+#             */
/*   Updated: 2023/04/25 17:23:44 by mgoltay          ###   ########.fr       */
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
