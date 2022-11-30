/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarlamo <bvarlamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:38:13 by bvarlamo          #+#    #+#             */
/*   Updated: 2022/04/22 19:38:00 by bvarlamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	double_c(t_data *data, char *red, char tmp, int t)
{
	int		y;
	char	tmp2[100];
	char	*tmp3;
	int		i;

	i = 0;
	while (red[i] == ' ')
		i++;
	y = 0;
	while (red[i] && red[i] != '>' && red[i] != '<' && red[i] != ' ')
	{
		tmp3 = ft_strchr(&red[i + 1], red[i]);
		if ((red[i] == '\'' || red[i] == '\"') && tmp3)
			while (&red[i] != &tmp3[0])
				tmp2[y++] = red[i++];
		tmp2[y++] = red[i++];
	}
	tmp2[y] = '\0';
	if (tmp == '<')
		heredoc(data, tmp2, t);
	else
		app_output(data, tmp2, t);
	free(red);
}

void	single_c(t_data *data, char *red, char tmp, int t)
{
	int		y;
	char	tmp2[100];
	char	*tmp3;
	int		i;

	i = 0;
	while (red[i] == ' ')
	i++;
	y = 0;
	while (red[i] && red[i] != '>' && red[i] != '<' && red[i] != ' ')
	{
		tmp3 = ft_strchr(&red[i + 1], red[i]);
		if ((red[i] == '\'' || red[i] == '\"') && tmp3)
			while (&red[i] != &tmp3[0])
				tmp2[y++] = red[i++];
		tmp2[y++] = red[i++];
	}
	tmp2[y] = '\0';
	if (tmp == '<')
		input(data, tmp2, t);
	else
		output(data, tmp2, t);
	free(red);
}

void	file_names(char *red, t_data *data, int i, int t)
{
	char	tmp;
	char	*tmp2;

	while (red[i] && data->line)
	{
		if (red[i] == '<' || red[i] == '>')
		{
			tmp = red[i++];
			if (red[i] == tmp)
				i++;
			tmp2 = ft_strdup(&red[i]);
			tmp2 = dollar_sign(tmp2, data);
			tmp2 = quotation(tmp2);
			checker(tmp2, data);
			if (data->line)
			{
				if (i > 1 && red[i - 1] == tmp && red[i - 2] == tmp)
					double_c(data, tmp2, tmp, t);
				else
					single_c(data, tmp2, tmp, t);
			}
			break ;
		}
		i++;
	}
}

void	ft_redirect2(char *str, char *tmp, int *i, int *y)
{
	char	*tmp2;

	tmp[(*y)++] = str[(*i)++];
	if (str[(*i)] == '<' || str[(*i)] == '>')
		tmp[(*y)++] = str[(*i)++];
	while (str[(*i)] == ' ')
		tmp[(*y)++] = str[(*i)++];
	while (str[(*i)] && (str[(*i)] != ' '
			&& str[(*i)] != '<' && str[(*i)] != '>'))
	{
		tmp2 = ft_strchr(&str[(*i) + 1], str[(*i)]);
		if ((str[(*i)] == '\'' || str[(*i)] == '\"') && tmp2)
			while (&str[(*i)] != &tmp2[0])
				tmp[(*y)++] = str[(*i)++];
		tmp[(*y)++] = str[(*i)++];
	}
	tmp[*y] = '\0';
}

void	ft_redirect(char **str, t_data *data, int i, int t)
{
	char	tmp[500];
	char	*tmp2;
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (str[0][i] && data->line)
	{
		tmp2 = ft_strchr(&str[0][i + 1], str[0][i]);
		if ((str[0][i] == '\'' || str[0][i] == '\"') && tmp2)
			i = tmp2 - &str[0][0] + 1;
		else if (str[0][i] == '<' || str[0][i] == '>')
		{
			ft_redirect2(*str, tmp, &i, &y);
			tmp2 = ft_strdup(&tmp[x]);
			file_names(tmp2, data, 0, t);
			free(tmp2);
			x = y;
		}
		else
			i++;
	}
	if (tmp[0] && data->line)
		clean_line(str, y);
}
