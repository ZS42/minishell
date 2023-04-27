/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 17:39:45 by mgoltay           #+#    #+#             */
/*   Updated: 2023/04/27 20:49:57 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int	occ(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
		if (*(s++) != c)
			if (*s == c || !(*s))
				count++;
	return (count);
}

static char	*getword(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		flag;
	char	**strs;

	if (!s)
		return (0);
	strs = malloc((occ(s, c) + 1) * sizeof(char *));
	if (!strs)
		return (0);
	i = -1;
	j = 0;
	flag = -1;
	while (++i <= ft_strlen(s))
	{
		if (s[i] != c && flag < 0)
			flag = i;
		else if ((s[i] == c || !s[i]) && flag >= 0)
		{
			strs[j++] = getword(s, flag, i);
			flag = -1;
		}
	}
	strs[j] = 0;
	return (strs);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*a;
	int		c1;
	int		c2;
	int		i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
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
