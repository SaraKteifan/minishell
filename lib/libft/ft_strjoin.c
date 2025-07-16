/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 09:55:31 by skteifan          #+#    #+#             */
/*   Updated: 2024/09/18 10:49:24 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*joined;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	joined = malloc(i + j + 1);
	if (!joined)
		return (NULL);
	k = 0;
	while (k < i)
	{
		joined[k] = s1[k];
		k++;
	}
	while (k < i + j)
	{
		joined[k] = s2[k - i];
		k++;
	}
	joined[i + j] = '\0';
	return (joined);
}
