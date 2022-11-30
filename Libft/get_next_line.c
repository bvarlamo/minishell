/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarlamo <bvarlamo@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 09:53:27 by bvarlamo          #+#    #+#             */
/*   Updated: 2022/03/12 10:49:08 by bvarlamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	point_is_true(char **subs1, char **line, char *point)
{
	char	*temp;
	char	*temp2;

	temp2 = *subs1;
	*subs1 = ft_strdup(++point);
	*point = '\0';
	temp = *line;
	*line = ft_strdup(temp2);
	free (temp2);
	free (temp);
}

char	*remain(char **subs1, char **line)
{
	char	*point;
	char	*temp;

	point = NULL;
	if (*subs1)
	{
		point = ft_strchr(*subs1, '\n');
		if (point)
		{
			point_is_true(subs1, line, point);
		}
		else
		{
			temp = *line;
			*line = ft_strdup(*subs1);
			free (temp);
			free (*subs1);
			*subs1 = NULL;
		}
	}
	return (point);
}

int	reading(int fd, char **line, char **subs1, char *buff)
{
	int		i;
	char	*p_to_n;
	char	*temp;

	i = read(fd, buff, BUFFER_SIZE);
	buff[i] = '\0';
	p_to_n = ft_strchr(buff, '\n');
	if (p_to_n && i > 0)
	{
		if (++p_to_n)
			*subs1 = ft_strdup(p_to_n);
		*p_to_n = '\0';
		temp = *line;
		*line = ft_strjoin(*line, buff);
		free (temp);
		return (1);
	}
	if (i > 0)
	{
		temp = *line;
		*line = ft_strjoin(*line, buff);
		free (temp);
		reading(fd, line, subs1, buff);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	char			buff[BUFFER_SIZE + 1];
	char			*line;
	char			*pton;
	static char		*subs1;
	int				i;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	line = malloc(0);
	line[0] = '\0';
	pton = remain(&subs1, &line);
	i = 0;
	if (!pton)
		i = reading(fd, &line, &subs1, buff);
	if (i == 0 && !subs1 && !line[0])
	{
		free (line);
		return (NULL);
	}
	return (line);
}
