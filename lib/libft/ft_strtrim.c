/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:02:24 by skteifan          #+#    #+#             */
/*   Updated: 2024/09/18 10:55:43 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static	int	in_set(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	get_start(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (in_set(set, s1[i]))
			i++;
		else
			break ;
	}
	return (i);
}

static int	get_end(char const *s1, char const *set)
{
	int	j;

	j = ft_strlen(s1) - 1;
	while (j >= 0)
	{
		if (in_set(set, s1[j]))
			j--;
		else
			break ;
	}
	return (j);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	int		i;
	int		j;
	int		k;

	if (!s1)
		return (NULL);
	if (set[0] == '\0' || !set)
		return (ft_strdup(s1));
	i = get_start(s1, set);
	j = get_end(s1, set);
	if (i > j)
		return (ft_strdup(""));
	trimmed = malloc((j - i + 1) + 1);
	if (!trimmed)
		return (NULL);
	k = 0;
	while (i <= j)
		trimmed[k++] = s1[i++];
	trimmed[k] = '\0';
	return (trimmed);
}
