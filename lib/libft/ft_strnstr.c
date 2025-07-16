/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 17:12:51 by skteifan          #+#    #+#             */
/*   Updated: 2024/09/18 10:41:37 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	check_occur(const char *big,
				const char *little, size_t len, size_t i)
{
	int	j;
	int	count;

	j = 0;
	count = ft_strlen(little);
	while (big[i] == little[j] && i < len
		&& big[i] != '\0' && little[j] != '\0')
	{
		j++;
		i++;
	}
	if (j == count)
		return (1);
	return (0);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	i = 0;
	if (little[i] == '\0')
		return ((char *)big);
	while (i < len && big[i] != '\0')
	{
		if (big[i] == little[0])
		{
			if (check_occur(big, little, len, i))
				return (&((char *)big)[i]);
		}
		i++;
	}
	return (NULL);
}
