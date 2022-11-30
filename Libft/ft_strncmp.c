/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarlamo <bvarlamo@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 19:54:06 by bvarlamo          #+#    #+#             */
/*   Updated: 2021/07/12 12:45:29 by bvarlamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t size)
{
	size_t	i;

	i = 0;
	if (!size)
		return (0);
	while (i < size && s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	if (size == i)
		i--;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}
