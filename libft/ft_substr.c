/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bakarabu <bakarabu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:52:21 by bakarabu          #+#    #+#             */
/*   Updated: 2024/10/23 19:52:23 by bakarabu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*a;
	size_t	i;
	size_t	s_len;

	i = 0;
	s_len = ft_strlen(s);
	if (!s)
		return (NULL);
	if (start >= s_len)
	{
		a = (char *)malloc(sizeof(char) * 1);
		if (!a)
			return (0);
		a[0] = '\0';
		return (a);
	}
	if (len > s_len - start)
		len = s_len - start;
	a = malloc((len + 1) * sizeof(char));
	if (!a)
		return (0);
	while (i < len)
		a[i++] = s[start++];
	a[i] = '\0';
	return (a);
}
