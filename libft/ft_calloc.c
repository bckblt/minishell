/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bakarabu <bakarabu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:45:07 by bakarabu          #+#    #+#             */
/*   Updated: 2024/10/23 20:24:44 by bakarabu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t	count, size_t	size)
{
	char	*a;
	size_t	i;

	i = 0;
	a = malloc(size * count);
	if (!a)
		return (NULL);
	while (i < size * count)
		a[i++] = 0;
	return (a);
}
