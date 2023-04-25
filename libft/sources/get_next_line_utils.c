/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:47:49 by zsyyida           #+#    #+#             */
/*   Updated: 2023/04/20 14:04:58 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

//checks for next \n or \0
int	ft_strchr_gnl(char *storage, int c)
{
	int	i;

	i = 0;
	while (storage[i] != '\0')
	{
		if (storage[i] == (char) c)
			return (1);
		i++;
	}
	if (storage[i] == '\0')
		return (0);
	else
		return (2);
}

//finds length till  and including next \n
int	ft_line_len(char *storage, int c)
{
	int	i;

	i = 0;
	while (storage[i] && *storage)
	{
		if (storage[i] == (char) c)
		{
			i += 1;
			return (i);
		}
		i++;
	}
	return (0);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

//joins leftover in static to new read in buffer
char	*ft_strnjoin(char *s1, char *s2, int n)
{
	char		*output;
	int			l1;

	l1 = ft_strlen(s1);
	output = malloc(l1 + n + 1);
	if (!output)
		return (NULL);
	if (s1 != NULL)
		ft_memcpy(output, s1, l1);
	if (s2)
		ft_memcpy(output + l1, s2, n);
	output[l1 + n] = '\0';
	if (s1)
		ft_free(&s1);
	return (output);
}

// frees pointer and sets it to NULL
void	ft_free(char **p)
{
	free(*p);
	*p = NULL;
}
