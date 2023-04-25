/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:00:06 by zsyyida           #+#    #+#             */
/*   Updated: 2022/08/30 03:25:41 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		len;
	int		i;

	len = 0;
	i = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] != '%')
			ft_print_char(format[i], &len);
		else if (format[i] == '%')
		{
			ft_parse_format(format[++i], ap, &len);
			while (format[i] == '#' || format[i] == '+' || format[i] == ' ')
				i++;
			if (format[i] >= '0' && format[i] <= '9')
				i = i + 1;
			ft_parse_bonus(format[i - 1], ap, format[i], &len);
		}
		i++;
	}
	va_end(ap);
	return (len);
}
