/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarlamo <bvarlamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 12:43:27 by bvarlamo          #+#    #+#             */
/*   Updated: 2022/04/22 19:38:10 by bvarlamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	wcount(char const *s, char a, int i, char c)
{
	int		count;
	char	*flag;

	count = 0;
	while (s[i])
	{
		while ((s[i] == c || s[i] == a) && s[i])
			i++;
		if (s[i] != c && s[i])
		{
			while (s[i] && s[i] != c && s[i] != a)
			{
				flag = NULL;
				if (s[i] == '\'' || s[i] == '\"')
					flag = ft_strchr(&s[i + 1], s[i]);
				if (flag)
					while (s[++i] != *flag)
						;
				i++;
			}
			count++;
		}
	}
	return (count);
}

size_t	wordlen(const char *s, char a, char c)
{
	size_t		i;
	char		*flag;

	i = 0;
	if (a == '$')
		i++;
	while (s[i] != c && s[i] && s[i] != a)
	{
		flag = NULL;
		if (s[i] == '\'' || s[i] == '\"')
			flag = ft_strchr(&s[i + 1], (int)s[i]);
		if (flag)
		{
			i++;
			while (s[i] != *flag)
				i++;
		}
		i++;
	}
	return (i);
}

static char	**to_free(char **ps)
{
	int	i;

	i = 0;
	while (ps[i])
	{
		free(ps[i]);
		i++;
	}
	free(ps);
	return (0);
}

char	**ft_spliter(char *s, char a, char c)
{
	int		i;
	int		t;
	char	**ps;

	if (!s)
		return (0);
	ps = (char **)malloc(sizeof(char *) * (wcount(s, a, 0, c) + 1));
	if (!ps)
		return (0);
	i = 0;
	t = 0;
	while (s[i])
	{
		if (s[i] && s[i] != c)
		{
			ps[t] = (char *)ft_substr(s, i, wordlen(&s[i], a, c));
			if (!(ps[t]))
				return (to_free(ps));
			i = i + ft_strlen(ps[t]) - 1;
			t++;
		}
		i++;
	}
	ps[t] = NULL;
	return (ps);
}
