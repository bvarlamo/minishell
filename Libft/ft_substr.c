/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarlamo <bvarlamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 20:08:20 by bvarlamo          #+#    #+#             */
/*   Updated: 2022/04/13 11:50:09 by bvarlamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	char		*sub;

	if (!s)
		return (0);
	i = start;
	if (ft_strlen(s) < start)
		return (ft_strdup("\0"));
	while (s[i] != '\0')
		i++;
	if (len > (i - start))
		len = i - start;
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!(sub))
		return (0);
	i = 0;
	while (i < len)
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	sub[i] = '\0';
	return (sub);
}
