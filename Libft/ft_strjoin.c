/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarlamo <bvarlamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 20:14:43 by bvarlamo          #+#    #+#             */
/*   Updated: 2022/04/12 11:44:42 by bvarlamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		i;
	int		i2;

	i = ft_strlen(s1) + ft_strlen(s2);
	s3 = (char *)malloc(sizeof(char) * (i + 1));
	if (!(s3))
		return (0);
	i = 0;
	while (s1 && s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	i2 = 0;
	while (s2 && s2[i2])
	{
		s3[i] = s2[i2];
		i++;
		i2++;
	}
	s3[i] = '\0';
	return (s3);
}
