/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bakarabu <bakarabu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:47:02 by bakarabu          #+#    #+#             */
/*   Updated: 2024/10/23 21:41:54 by bakarabu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	void	*a;

	a = dest;
	if (!src && !dest)
		return (NULL);
	if (src < dest)
	{
		src += n;
		dest += n;
		while (n--)
			*(char *)--dest = *(const char *)--src;
	}
	else
	{
		ft_memcpy(dest, src, n);
	}
	return (a);
}
