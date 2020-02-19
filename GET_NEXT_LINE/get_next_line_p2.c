/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 07:38:34 by fjimenez          #+#    #+#             */
/*   Updated: 2020/02/19 08:53:43 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 128

int		ft_len_c(char *str, char c)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	if (str[i] == c)
		return (i);
	return (-1);
}

char *ft_strjoin(char *s1, char *s2)
{
	char *dest;
	int i = 0, j = 0;

	if (!(dest = malloc(sizeof(char) * (ft_len_c(s1, '\0') + ft_len_c(s2, '\0') + 1))))
		return (NULL);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		dest[i + j] = s2[j];
		j++;
	}
	free(s1);
	dest[i + j] = '\0';
	return (dest);
}

char *ft_substr(char *s, int start, int len)
{
	char *dest;
	int i = 0;

	if (!s || start > ft_len_c(s, '\0'))
		return (NULL);
	if (!(dest = malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (s[start] && len)
	{
		dest[i++] = s[start++];
		len--;
	}
	dest[i] = '\0';
	return (dest);
}

void *ft_calloc(int count, int size)
{
	void *mem;
	int total;

	total = count * size;
	if (!(mem = malloc(total)))
		return (NULL);
	while (total-- > 0)
		*(unsigned char*)mem++ = 0;
	return (mem - count * size);
}

int	get_next_line(char **line)
{
	static char *str;
	char *tmp;
	char buf[BUFFER_SIZE + 1];
	int ret;

	if (!line)
		return (-1);
	if (!str && !(str = ft_calloc(sizeof(char), 1)))
		return (-1);
	while (ft_len_c(str, '\n') < 0 && (ret = read(0, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = '\0';
		str = ft_strjoin(str, buf);
	}
	*line = ft_substr(str, 0, ft_len_c(str, '\n'));
	if (ft_len_c(str, '\n') < 0)
	{
		free(str);
		return (0);
	}
	tmp = str;
	str = ft_substr(str, ft_len_c(str, '\n') + 1, ft_len_c(str, '\0'));
	free(tmp);
	return (1);
}