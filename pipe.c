/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarlamo <bvarlamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 12:41:18 by bvarlamo          #+#    #+#             */
/*   Updated: 2022/04/23 15:20:05 by bvarlamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	pipe_check2(t_data *data, char *line)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (line[i])
		i++;
	while (line[--i] == ' ')
		;
	if (line[i] == '|')
	{
		tmp = readline("> ");
		tmp2 = data->line;
		data->line = ft_strjoin(tmp2, tmp);
		free(tmp);
		free(tmp2);
	}
}

void	pipe_check(t_data *data, char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '|')
	{
		free (data->line);
		data->line = (char *) NULL;
		write(2, "wrong charcter\n", 15);
		data->err = 258 * 256;
	}
	else
		pipe_check2(data, line);
}

void	free_tmp(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
}

void	free_exit(t_data *data, char *str, int code, char **tmp)
{
	int	i;

	free (data->line);
	data->line = (char *) NULL;
	i = 0;
	while (data->envp[i])
		free(data->envp[i++]);
	free(data->envp);
	write(2, "exit\n", 5);
	write(2, str, ft_strlen(str));
	free_tmp(tmp);
	exit(code);
}

void	ft_exit2(t_data *data, char *line)
{
	int		i;
	char	**tmp;

	tmp = ft_spliter(line, ' ', ' ');
	i = 0;
	if (tmp[1][0] == '-')
		i++;
	while (tmp[1] && tmp[1][i])
	{
		if (!ft_isdigit(tmp[1][i]))
			free_exit(data, "numeric arguments required\n", 255, tmp);
		i++;
	}
	i = ft_atoi(tmp[1]);
	if (tmp[2])
	{
		free (data->line);
		data->line = (char *) NULL;
		write(2, "too many arguments\n", 19);
		data->err = 256;
	}
	else
		free_exit(data, "", i % 256, tmp);
	free_tmp(tmp);
}
