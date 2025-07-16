/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 14:08:23 by skteifan          #+#    #+#             */
/*   Updated: 2024/09/18 10:39:07 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	char	*ptr1;
	char	*ptr2;

	i = 0;
	ptr1 = (char *) s1;
	ptr2 = (char *) s2;
	while (i < n)
	{
		if (ptr1[i] != ptr2[i])
			return ((unsigned char) ptr1[i] - (unsigned char) ptr2[i]);
		i++;
	}
	return (0);
}
