/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bakarabu <bakarabu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 04:53:21 by bakarabu          #+#    #+#             */
/*   Updated: 2025/07/18 12:46:29 by bakarabu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	chknl(char *buff)
{
	int	i;

	i = 0;
	if (!buff)
		return (0);
	while (buff[i])
	{
		if (buff[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*del(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str || str[0] == '\0')
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*update(char *str)
{
	char	*next_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free (str);
		return (NULL);
	}
	next_line = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!next_line)
		return (NULL);
	i++;
	while (str[i + j])
	{
		next_line[j] = str[i + j];
		j++;
	}
	next_line[j] = '\0';
	free (str);
	return (next_line);
}

static char	*ft_read(int fd, char *str)
{
	char	*buff;
	int		a;

	a = 1;
	buff = malloc(1 + 1);
	if (!buff)
		return (NULL);
	while (!chknl(str) && a != 0)
	{
		a = read(fd, buff, 1);
		if (a == -1)
		{
			free (str);
			free (buff);
			return (NULL);
		}
		buff[a] = '\0';
		str = ft_strjoin(str, buff);
	}
	free (buff);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str;

	if (fd <= 0)
		return (0);
	str = ft_read (fd, str);
	if (!str)
		return (NULL);
	line = del(str);
	str = update(str);
	return (line);
}
