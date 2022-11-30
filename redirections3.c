/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarlamo <bvarlamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 18:11:35 by bvarlamo          #+#    #+#             */
/*   Updated: 2022/04/23 10:38:51 by bvarlamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	clean_line2(char *str, int *i)
{
	char	*tmp2;

	(*i)++;
	if (str[*i] == '<' || str[*i] == '>')
		(*i)++;
	while (str[*i] == ' ')
		(*i)++;
	while (str[*i] && (str[*i] != ' ' && str[*i] != '<' && str[*i] != '>'))
	{
		tmp2 = ft_strchr(&str[(*i) + 1], str[*i]);
		if ((str[*i] == '\'' || str[*i] == '\"') && tmp2)
			while (&str[*i] != &tmp2[0])
				(*i)++;
		(*i)++;
	}
}

void	clean_line(char **str, int red)
{
	int		i;
	int		y;
	char	*tmp;
	char	*tmp2;

	tmp = malloc(sizeof(char) * (ft_strlen(str[0]) - red + 1));
	i = 0;
	y = 0;
	while (str[0][i])
	{
		tmp2 = ft_strchr(&str[0][i + 1], str[0][i]);
		if ((str[0][i] == '\'' || str[0][i] == '\"') && tmp2)
		{
			while (&str[0][i] != tmp2)
				tmp[y++] = str[0][i++];
			tmp[y++] = str[0][i++];
		}
		else if (str[0][i] == '<' || str[0][i] == '>')
			clean_line2(str[0], &i);
		else
			tmp[y++] = str[0][i++];
	}
	tmp[y] = '\0';
	free(*str);
	*str = tmp;
}

void	checker(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] != ' ')
			break ;
		i++;
	}
	if (!str || !str[i])
	{
		write(2, "wrong characters\n", 17);
		data->err = 256;
		if (data->line)
			free(data->line);
		data->line = NULL;
		return ;
	}
}

void	checker2(char *str, t_data *data, int i)
{
	char	*tmp;
	int		y;

	y = 1;
	while (str[i])
	{
		tmp = ft_strchr(&str[i + 1], str[i]);
		if ((str[i] == '\'' || str[i] == '\"') && tmp)
			i = (ft_strchr(&str[i + 1], str[i]) - &str[0]) + 1;
		else if ((str[i] == '\'' || str[i] == '\"') && !tmp)
			y = 0;
		else if (str[i] == '\\' || str[i] == '~' || str[i] == '!'
			|| str[i] == '^' || str[i] == '@' || str[i] == '#' || str[i] == '*'
			|| str[i] == '{' || str[i] == '}' || str[i] == '&' || str[i] == ';')
			y = 0;
		if (y == 0 || (str[i] == '|' && str[i + 1] == '|'))
		{
			write(2, "wrong characters\n", 17);
			data->err = 256;
			free(data->line);
			data->line = NULL;
			return ;
		}
		i++;
	}
}
