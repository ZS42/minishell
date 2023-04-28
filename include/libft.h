/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 20:34:17 by mgoltay           #+#    #+#             */
/*   Updated: 2023/04/28 16:10:58 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

int		ft_isdigit(int c);
int		ft_is_alpha(int c);
int		ft_isalnum(int c);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);

char	**ft_split(char const *s, char c);
int		ft_strlen(const char *s);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, int n);
char	*ft_strdup(const char *s);
char	*ft_strndup(char *s1, int len);
char	*ft_strjoin(char const *s1, char const *s2);

void	ft_putstr(char *str);
void	ft_putstr_fd(char *str, int fd);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);

int		ft_strlen_nl(char *str, int detect_nl);
int		isin(char *buffer, char c);
char	*ft_fstrjoin(char *dest, char *src);
char	*get_next_line(int fd);

#endif
