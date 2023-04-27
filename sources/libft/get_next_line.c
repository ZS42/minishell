/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:08:34 by mgoltay           #+#    #+#             */
/*   Updated: 2023/04/27 20:37:10 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static void	update_buffer(char *buffer)
{
	int	i;
	int	len;
	int	max;

	i = -1;
	len = ft_strlen_nl(buffer, 1);
	max = ft_strlen_nl(buffer, 0);
	while (++i + len < max)
		buffer[i] = buffer[i + len];
	while (i <= BUFFER_SIZE)
		buffer[i++] = '\0';
}

static void	makeline(int fd, char buffer[], char **line)
{
	int	bytes;

	bytes = 1;
	while (bytes && !isin(*line, '\n'))
	{
		if (!buffer[0])
			bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			(*line)[0] = '\0';
			return ;
		}
		*line = ft_fstrjoin(*line, buffer);
		update_buffer(buffer);
	}
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || !BUFFER_SIZE)
		return (NULL);
	line = ft_fstrjoin(NULL, NULL);
	if (!line)
		return (NULL);
	makeline(fd, buffer, &line);
	if (!line[0])
	{
		free(line);
		return (NULL);
	}
	return (line);
}
