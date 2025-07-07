/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bakarabu <bakarabu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:51:55 by bakarabu          #+#    #+#             */
/*   Updated: 2024/10/23 19:51:57 by bakarabu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*a;

	a = 0;
	while (*s)
	{
		if (*s == (char)c)
			a = (char *)s;
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (a);
}
