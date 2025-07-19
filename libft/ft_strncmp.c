/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bakarabu <bakarabu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:51:31 by bakarabu          #+#    #+#             */
/*   Updated: 2024/10/23 19:51:33 by bakarabu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	a;

	a = 0;
	while ((s1[a] || s2[a]) && a < n)
	{
		if ((unsigned char)s1[a] > (unsigned char)s2[a])
			return (1);
		if ((unsigned char)s1[a] < (unsigned char)s2[a])
			return (-1);
		a++;
	}
	return (0);
}
