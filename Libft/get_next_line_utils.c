/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarlamo <bvarlamo@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 09:53:56 by bvarlamo          #+#    #+#             */
/*   Updated: 2022/03/12 10:48:57 by bvarlamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		i;
	int		i2;

	if (!s1 || !s2)
		return (0);
	i = ft_strlen(s1) + ft_strlen(s2);
	s3 = (char *)malloc(sizeof(char) * (i + 1));
	if (!(s3))
		return (0);
	i = 0;
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	i2 = 0;
	while (s2[i2])
	{
		s3[i] = s2[i2];
		i++;
		i2++;
	}
	s3[i] = '\0';
	return (s3);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strchr(const char *str, int c)
{
	size_t		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (unsigned char)c)
		{
			return ((char *)str + i);
		}
		i++;
	}
	if (str[i] == (unsigned char)c)
		return ((char *)str + i);
	return (0);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	i;

	if (!s1)
		return (NULL);
	str = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = 0;
	return (str);
}
