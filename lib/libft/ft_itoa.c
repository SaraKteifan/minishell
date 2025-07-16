/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:01:39 by skteifan          #+#    #+#             */
/*   Updated: 2024/09/11 12:00:33 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	count_num(long int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*num;
	long int	l;
	int			i;

	l = n;
	i = count_num(l);
	num = malloc(i + 1);
	if (!num)
		return (NULL);
	num[i] = '\0';
	if (l == 0)
		num[0] = 48;
	if (l < 0)
	{
		l = -l;
		num[0] = '-';
	}
	while (l > 0)
	{
		num[--i] = (l % 10) + 48;
		l /= 10;
	}
	return (num);
}
