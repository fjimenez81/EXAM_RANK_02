/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 10:01:59 by fjimenez          #+#    #+#             */
/*   Updated: 2020/02/19 11:21:21 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

size_t ft_strlen(char *s)
{
	size_t i = 0;

	while (s[i] != '\0')
		i++;
	return (i);
}

int ft_numlen(long long n, int base_len)
{
	int i = 1;

	while (n >= base_len || n <= -base_len)
	{
		n = n / base_len;
		i++;
	}
	return (i);
}

void ft_putnum(long long n, int base_len, char *base)
{
	if (n >= base_len)
		ft_putnum(n / base_len, base_len, base);
	write(1, &base[n % base_len], 1);
}

int ft_printf(const char *format, ...)
{
	va_list args;
	char *base, *s, *str;
	long num;
	int prec = 0, width = 0, ret = 0, nlen = 0, pads = 0, zeros = 0, dot = 0, neg = 0, base_len;
	va_start(args, format);
	str = (char*)format;
	while (*str != '\0')
	{
		if (*str == '%')
		{
			str++;
			prec = 0, width = 0, nlen = 0, pads = 0, zeros = 0, dot = 0, neg = 0;
			while (*str >= '0' && *str <= '9')
			{
				width = width * 10 + (*str - '0');
				str++;
			}
			if (*str == '.')
			{
				str++;
				while (*str >= '0' && *str <= '9')
				{
					prec = prec * 10 + (*str - '0');
					str++;
				}
				dot = 1;
			}
			if (*str == 's')
			{
				s = va_arg(args, char*);
				if (!s)
					s = "(null)";
				nlen = ft_strlen(s);
			}
			if (*str == 'x')
			{
				num = va_arg(args, unsigned);
				base = "0123456789abcdef";
				base_len = 16;
				nlen = ft_numlen(num, base_len);
			}
			if (*str == 'd')
			{
				num = va_arg(args, int);
				base = "0123456789";
				base_len = 10;
				if (num < 0)
				{
					num *= -1;
					neg = 1;
				}
				nlen = ft_numlen(num, base_len) + neg;
			}
			if (dot == 1 && prec > nlen && *str != 's')
				zeros = prec - nlen + neg;
			else if (dot == 1 && prec < nlen && *str == 's')
				nlen = prec;
			else if (dot == 1 && prec == 0 && (*str == 's' || num == 0))
				nlen = 0;
			pads = width - nlen - zeros;
			while (pads-- > 0)
			{
				write(1, " ", 1);
				ret++;
			}
			if (neg == 1)
				write(1, "-", 1);
			while (zeros-- > 0)
			{
				write(1, "0", 1);
				ret++;
			}
			if (*str == 's')
				write(1, s, nlen);
			else if (nlen > 0)
				ft_putnum(num, base_len, base);
			ret += nlen;
			str++;
		}
		else
		{
			write(1, str, 1);
			str++;
			ret++;
		}
	}
	return (ret);
}
