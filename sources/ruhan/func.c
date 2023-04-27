/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:10:52 by mgoltay           #+#    #+#             */
/*   Updated: 2023/04/27 20:47:36 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_null_strjoin(char *s1, char *s2)
{
	char	*a;
	int		c1;
	int		c2;
	int		i;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	c1 = ft_strlen(s1);
	c2 = ft_strlen(s2);
	a = (char *)malloc(sizeof(char) * (c1 + c2) + 1);
	if (!a)
		return (NULL);
	i = -1;
	while (++i < c1)
		a[i] = s1[i];
	i = -1;
	while (++i < c2)
		a[c1 + i] = s2[i];
	a[c1 + c2] = '\0';
	return (a);
}

char	*ft_free_strjoin(char *s1, char *s2)
{
	char	*new;

	new = ft_null_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (new);
}

int	is_sep(t_elem *elem)
{
	if (elem == NULL || elem->type == '|')
		return (1);
	if (elem->type == '&' || elem->type == -4)
		return (1);
	return (0);
}

int	is_in(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (1);
	return (0);
}

void	ft_free_2d_int(int **s, int i)
{
	if (s)
	{
		while (--i >= 0)
			free(s[i]);
		free(s);
	}
}
