/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 09:53:29 by fjimenez          #+#    #+#             */
/*   Updated: 2020/02/21 12:53:41 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t 	ft_strlen(char *s)
{
	size_t i = 0;;

	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(char *str, int c)
{
	unsigned int i = 0, leng;
	
	if (!str)
		return (NULL);
	leng = ft_strlen(str);
	while (*str != '\0' && *str != c)
	{
		str++;
		i++;
	}
	if (*str != c && i == leng)
		return (NULL);
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char    *dest;
	size_t  i = 0, j = 0;

	if (!(dest = (char*)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1)))
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
	dest[i + j] = '\0';
	return (dest);
}

char	*ft_strdup(char *s)
{
	char 		*res;
	size_t		len;
	size_t		i;

	len = ft_strlen(s);
	if (!(res = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

int	ft_return(char **str, char **line, int ret)
{
	char *aux, *tmp;
	if (ret < 0)
	{
		if (*str != NULL)
		{
			free(*str);
			*str = NULL;
		}
		return (-1);
	}
	if (!ret && !*str)
	{
		*line = ft_strdup("");
		//free(*str);
		//*str = NULL;
		return (0);
	}
	if ((aux = ft_strchr(*str, '\n')))
	{
		*aux = 0;
		*line = ft_strdup(*str);
		tmp = ft_strdup(++aux);
		free(*str);
		*str = tmp;
		return (1);
	}
	else
	{
		*line = ft_strdup(*str);
		free(*str);
		*str = NULL;
		return (0);
	}
}

int			get_next_line(char **line)
{
	char		buf[65];
	int			ret;
	char		*tmp;
	static char *str;

	if (!line)
		return (-1);
	while (ft_strchr(str, '\n') == NULL)
	{
		ret = read(0, buf, 64);
		if (ret < 0)
			return (-1);
		if (ret == 0)
			break;
		buf[ret] = 0;
		if (!str)
			str = ft_strdup(buf);
		else
		{
			tmp = ft_strjoin(str, buf);
			free(str);
			str = tmp;
		}
	}
	return (ft_return(&str, line, ret));
}
