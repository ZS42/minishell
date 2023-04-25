/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:17:51 by zsyyida           #+#    #+#             */
/*   Updated: 2023/03/28 13:05:09 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memcpy(char *dst, char *src, int n)
{
	int	i;

	i = 0;
	if (dst == NULL && src == NULL)
		return (0);
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

// ft_str_dup with len duplicates upto and including /n
char	*ft_strdup(char *s1, int len)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (0);
	ft_memcpy(str, s1, len);
	str[len] = '\0';
	return (str);
}

// gives output based on if \0 (i = 0) or \n (i = 1)
//if \0 will duplicate into line so can free static variable
char	*ft_output(char **storage)
{
	char	*line;
	int		i;
	int		len;

	line = NULL;
	i = 0;
	if (!*storage || ft_strlen(*storage) == 0)
	{
		ft_free(storage);
		return (NULL);
	}
	i = ft_strchr_gnl(*storage, '\n');
	if (i == 0)
	{
		len = ft_strlen(*storage);
		line = ft_strdup(*storage, len);
		ft_free(storage);
	}
	else if (i == 1)
	{
		line = ft_nl_output (storage);
	}
	else if (i == 2)
		return (NULL);
	return (line);
}

// will duplicate into line upto \n
// will free static if at end
//if not at end will update static to leftover after \n using temp updated_line
char	*ft_nl_output(char	**storage)
{
	char	*line;
	int		len;
	char	*updated_line;
	int		i;

	i = 0;
	i = ft_strlen(*storage);
	updated_line = NULL;
	len = ft_line_len(*storage, '\n');
	line = ft_strdup(*storage, len);
	if (i == (len))
		ft_free(storage);
	else
	{
		updated_line = ft_strdup(*storage + len, (i - len));
		ft_free (storage);
		*storage = updated_line;
	}
	return (line);
}

//buff an array to read string.Can use array bc we know BUFFER_SIZE
//dont need to malloc buff bc we know size
//bytes is the number of bytes read.
//result is the read line upto and including \n or \0 that will be returned
//put in a condition to not reenter loop if '\n' or '\0'
//do not put condition ft_strchr = 0 bc we are always putting \0 in
//strjoin so it will always break. Instead put if bytes < BUFFER_SIZE
char	*get_next_line(int fd)
{
	static char	*storage;
	char		buff[BUFFER_SIZE + 1];
	char		*next_line;
	int			bytes;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > 999)
		return (NULL);
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		buff[bytes] = '\0';
		storage = ft_strnjoin(storage, buff, bytes);
		if (bytes < BUFFER_SIZE || (ft_strchr_gnl(storage, '\n') == 1))
			break ;
	}
	next_line = ft_output (&storage);
	if (ft_strlen(next_line) == 0)
	{
		ft_free (&storage);
		return (NULL);
	}
	return (next_line);
}
