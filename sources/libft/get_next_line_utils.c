/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:10:51 by mgoltay           #+#    #+#             */
/*   Updated: 2023/04/27 20:36:56 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_strlen_nl(char *str, int detect_nl)
{
	int	c;

	if (!str)
		return (0);
	c = 0;
	while (str[c])
		if (str[c++] == '\n' && detect_nl)
			break ;
	return (c);
}

int	isin(char *buffer, char c)
{
	while (*buffer)
		if (*(buffer++) == c)
			return (1);
	return (0);
}

char	*ft_fstrjoin(char *dest, char *src)
{
	int		c1;
	int		c2;
	char	*str;
	int		i;

	c1 = ft_strlen_nl(dest, 0);
	c2 = ft_strlen_nl(src, 1);
	str = (char *)malloc(sizeof(char) * (c1 + c2) + 1);
	if (!str)
		return (NULL);
	i = -1;
	while (++i < c1)
		str[i] = dest[i];
	i = -1;
	while (++i < c2)
		str[c1 + i] = src[i];
	str[c1 + c2] = '\0';
	if (dest)
		free(dest);
	return (str);
}
