/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bakarabu <bakarabu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:51:43 by bakarabu          #+#    #+#             */
/*   Updated: 2024/10/23 19:56:25 by bakarabu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = -1;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[++i])
	{
		if (haystack[i] == needle[j])
		{
			while (haystack[i + j] && needle[j]
				&& haystack[i + j] == needle[j] && i + j < len)
				j++;
			if (!needle[j])
				return ((char *)haystack + i);
			j = 0;
		}
	}
	return (0);
}
