/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_on_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarlamo <bvarlamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:44:07 by bvarlamo          #+#    #+#             */
/*   Updated: 2022/04/23 14:55:03 by bvarlamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*extract2(char *cmd, char *place, char *string, char *tmp)
{
	int		i;
	int		y;
	char	*new;
	int		t_l;

	t_l = ft_strlen(tmp);
	new = malloc(sizeof(char) * (ft_strlen(cmd) - t_l + ft_strlen(string) + 1));
	i = 0;
	while (&cmd[i] != place)
	{
		new[i] = cmd[i];
		i++;
	}
	y = 0;
	while (string && string[y])
		new[i++] = string[y++];
	y = i - ft_strlen(string) + t_l;
	while (cmd[y])
		new[i++] = cmd[y++];
	new[i] = '\0';
	free(tmp);
	free(cmd);
	if (string)
		free(string);
	return (new);
}

char	*extract3(char *str)
{
	int		i;
	char	*tmp;

	i = 1;
	while (str[i] && str[i] != ' ' && str[i] != '\'' && str[i] != '\"'
		&& str[i] != '/' && str[i] != '$' && str[i] != '=')
		i++;
	tmp = malloc(sizeof(char) * (i + 1));
	return (tmp);
}

char	*extract(char *cmd, char *place, char *str, t_data *data)
{
	int		i;
	char	*string;
	char	*tmp;

	tmp = extract3(str);
	i = 1;
	while (str[i] && str[i] != ' ' && str[i] != '\'' && str[i] != '\"'
		&& str[i] != '/' && str[i] != '$' && str[i] != '=')
	{
		tmp[i - 1] = str[i];
		i++;
	}
	tmp[i - 1] = '=';
	tmp[i] = '\0';
	i = 0;
	string = NULL;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], tmp, ft_strlen(tmp)) == 0)
			string = ft_strdup(&data->envp[i][ft_strlen(tmp)]);
		i++;
	}
	return (extract2(cmd, place, string, tmp));
}

char	*dollar2(char *str, t_data *data, int *i)
{
	(*i)++;
	while (str[*i] && str[*i] != '\"')
	{
		if (str[*i] == '$' && str[*i + 1] == '?')
				str = quest(str, &str[*i], data, 0);
		else if (str[*i] == '$' && str[*i + 1] && str[*i + 1] != '\"')
		{
			str = extract(str, &str[*i], &str[*i], data);
			while (str[*i] && str[*i] != '$' && str[*i] != ' '
				&& str[*i] != '\"' && str[*i] != '/' && str[*i] != '=')
				(*i)++;
			(*i)--;
		}
		(*i)++;
	}
	return (str);
}

char	*dollar_sign(char *str, t_data *data)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && ft_strchr(&str[i + 1], '\''))
			i = (ft_strchr(&str[i + 1], '\'') - &str[0]);
		else if (str[i] == '\"' && ft_strchr(&str[i + 1], '\"'))
			str = dollar2(str, data, &i);
		else if (str[i] == '$' && str[i + 1] == '?')
				str = quest(str, &str[i], data, 0);
		else if (str[i] == '$' && str[i + 1])
		{
			str = extract(str, &str[i], &str[i], data);
			while (str[i] && str[i] != '$' && str[i] != ' '
				&& str[i] != '\"' && str[i] != '/' && str[i] != '=')
				i++;
			i--;
		}
		i++;
	}
	return (str);
}
