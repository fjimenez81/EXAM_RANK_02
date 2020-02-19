/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 19:54:39 by acortes-          #+#    #+#             */
/*   Updated: 2020/01/21 21:27:41 by agarrido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

int	ft_strlen(const char *s)
{
	int	cont;

	cont = 0;
	while (s[cont])
	{
		cont++;
	}
	return (cont);
}

char	*ft_strcdup(const char *s1, char c)
{
	int		cont;
	char	*arr;
	int	len;

	len = 0;
	while (s1[len] != '\0' && s1[len] != c)
	{
		len++;
	}
	if (!(arr = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	cont = 0;
	while (cont < len)
	{
		arr[cont] = s1[cont];
		cont++;
	}
	arr[cont] = '\0';
	return (arr);
}

char	*ft_strchr(const char *s, int c)
{
	int	cont;

	cont = 0;
	while (s[cont])
	{
		if (s[cont] == (char)c)
			return ((char *)&s[cont]);
		cont++;
	}
	return (c == 0 ? ((char *)&s[cont]) : (0));
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*nuevo;
	int		len;
	int		cont;
	int		cont2;

	if (s1 == NULL)
		return (ft_strcdup("", '\0'));
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(nuevo = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	cont = 0;
	while (s1[cont])
	{
		nuevo[cont] = s1[cont];
		cont++;
	}
	cont2 = 0;
	while (s2[cont2])
	{
		nuevo[cont] = s2[cont2];
		cont++;
		cont2++;
	}
	nuevo[cont] = '\0';
	return (nuevo);
}

int	get_next_line(int fd, char **line)
{
	static char	*s1[2024];
	char		*arr;
	char		buf[BUFFER_SIZE + 1];
	int			x;

	!(s1[fd]) ? s1[fd] = ft_strcdup("", '\0') : 0;
	while ((x = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[x] = '\0';
		arr = ft_strjoin(s1[fd], buf);
		free(s1[fd]);
		if (ft_strchr((s1[fd] = arr), '\n'))
			break ;
	}
	if (x < 0 || line == NULL)
		return (-1);
	*line = ft_strcdup(s1[fd], '\n');
	arr = NULL;
	if (!(s1[fd][ft_strlen(*line)] == '\0'))
		arr = ft_strcdup(ft_strchr(s1[fd], '\n') + 1, '\0');
	free(s1[fd]);
	return (s1[fd] = arr) == NULL ? 0 : 1;
}
