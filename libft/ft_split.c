/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bakarabu <bakarabu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:49:11 by bakarabu          #+#    #+#             */
/*   Updated: 2024/10/23 21:08:10 by bakarabu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(char *a, char b)
{
	int	i;
	int	word;

	word = 0;
	i = 0;
	if (a[0] == '\0')
		return (0);
	while (a[i] != '\0')
	{
		while (a[i] == b && a[i] != '\0')
			i++;
		if (a[i] != '\0')
		{
			word++;
			while (a[i] != b && a[i] != '\0')
				i++;
		}
	}
	return (word);
}

char	**ft_split(char *s, char c)
{
	char	**result;
	int		i;
	size_t	start;
	int		re;
	size_t	end;

	i = 0;
	re = count_word(s, c);
	if(re == 0)
		re++;
	result = malloc (sizeof(char *) * (re + 1));
	re = 0;
	if (!result)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		end = i;
		if (end > start)
			result[re++] = ft_substr(s, start, end - start);
	}
	result[re] = (NULL);
	return (result);
}
