/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bakarabu <bakarabu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:52:09 by bakarabu          #+#    #+#             */
/*   Updated: 2024/10/23 22:44:59 by bakarabu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	chk1(char const *s1, char const *set)
{
	int	s;

	s = 0;
	while (s1[s] && ft_strchr(set, s1[s]))
		s++;
	return (s);
}

static int	chk2(char const *s1, char const *set)
{
	int	e;

	e = ft_strlen(s1) - 1;
	while (e >= 0 && ft_strchr(set, s1[e]))
		e--;
	return (e);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		s;
	int		e;
	char	*c;

	i = 0;
	s = chk1 (s1, set);
	e = chk2 (s1, set);
	if (s > e)
		return (ft_strdup(""));
	c = malloc(sizeof(char) * (e - s + 2));
	if (!c)
		return (NULL);
	while (i < (e - s + 1))
	{
		c[i] = s1[s + i];
		i++;
	}
	c[i] = 0;
	return (c);
}
