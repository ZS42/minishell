/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 20:23:55 by mgoltay           #+#    #+#             */
/*   Updated: 2023/04/27 20:49:46 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_strlen(const char *s)
{
	int	c;

	c = 0;
	while (s[c])
		c++;
	return (c);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i])
		i++;
	return (s1[i] - s2[i]);
}

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int	i;

	i = -1;
	while (++i < n)
		if (s1[i] != s2[i] || !s1[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

char	*ft_strdup(const char *s)
{
	char			*obj;
	unsigned int	i;
	unsigned int	len;

	len = 0;
	while (s[len])
		len++;
	obj = (char *)malloc(sizeof(char) * len + 1);
	if (!obj)
		return (NULL);
	i = -1;
	while (++i < len)
		obj[i] = s[i];
	obj[i] = '\0';
	return (obj);
}

char	*ft_strndup(char *s1, int len)
{
	char	*str;
	int		i;

	if (!s1 || !len)
		return (NULL);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (0);
	i = -1;
	while (++i < len)
		str[i] = s1[i];
	str[len] = '\0';
	return (str);
}
