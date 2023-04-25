/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:10:52 by mgoltay           #+#    #+#             */
/*   Updated: 2023/04/24 14:31:27 by zsyyida          ###   ########.fr       */
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
		return (ft_strdup_ft(s2));
	if (s2 == NULL)
		return (ft_strdup_ft(s1));
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

int	is_sep(t_elem *elem)
{
	if (elem == NULL || elem->type == '|')
		return (1);
	if (elem->type == '&' || elem->type == -4)
		return (1);
	return (0);
}

int	ft_isalnum(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= '0' && c <= '9')
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
