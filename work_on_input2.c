/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_on_input2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarlamo <bvarlamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:38:33 by bvarlamo          #+#    #+#             */
/*   Updated: 2022/04/23 12:18:09 by bvarlamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	**cleaning(char **commands, t_data *data, int i, int y)
{
	char	**tmp;

	while (commands && commands[i])
	{
		commands[i] = dollar_sign(commands[i], data);
		commands[i] = quotation(commands[i]);
		i++;
	}
	tmp = commands;
	commands = malloc(sizeof(char *) * (i + 1));
	i = 0;
	y = 0;
	while (tmp && tmp[i])
	{
		commands[y++] = ft_strdup(tmp[i]);
		free(tmp[i++]);
	}
	free(tmp);
	commands[y] = NULL;
	return (commands);
}

void	pipes2(t_data *data, char **no_pipe, int *i)
{
	int	y;

	while (data->line && no_pipe[*i])
	{
		if (ft_strncmp(no_pipe[*i], "echo ", 5) != 0)
			checker2(no_pipe[*i], data, 0);
		checker(no_pipe[*i], data);
		(*i)++;
	}
	if (!data->line)
	{
		*i = 0;
		while (no_pipe[*i])
			free(no_pipe[(*i)++]);
		free(no_pipe);
		return ;
	}
	data->cmd_count = *i;
	data->in_fd = malloc(sizeof(int) * (*i));
	data->out_fd = malloc(sizeof(int) * (*i));
	y = 0;
	while (y < *i)
		data->in_fd[y++] = 0;
	while (y > 0)
		data->out_fd[--y] = 1;
}

void	pipes(t_data *data, int i)
{
	char	**no_pipe;

	no_pipe = ft_spliter(data->line, '|', '|');
	if (ft_strlen(no_pipe[0]) < 1)
	{
		checker(no_pipe[0], data);
		free(no_pipe);
		return ;
	}
	pipes2(data, no_pipe, &i);
	if (!data->line)
		return ;
	data->comands = malloc(sizeof(char **) * (i + 1));
	data->comands[i] = NULL;
	i = 0;
	while (no_pipe[i])
	{
		ft_redirect(&no_pipe[i], data, 0, i);
		data->comands[i] = ft_spliter(no_pipe[i], ' ', ' ');
		data->comands[i] = cleaning(data->comands[i], data, 0, 0);
		free(no_pipe[i++]);
	}
	free(no_pipe);
}

char	*quotation2(char *com)
{
	int		y;
	char	*tmp;
	int		i;

	y = 0;
	i = 0;
	while (com[y])
	{
		tmp = ft_strchr(&com[y + 1], com[y]);
		if ((com[y] == '\'' || com[y] == '\"') && tmp)
		{
			while (&com[y] != tmp)
				y++;
			i += 2;
		}
		y++;
	}
	tmp = malloc(sizeof(char) * (y - i + 1));
	return (tmp);
}

char	*quotation(char *com)
{
	int		y;
	char	*tmp;
	char	*tmp2;
	int		x;

	tmp = com;
	com = quotation2(com);
	y = 0;
	x = 0;
	while (tmp[y])
	{
		tmp2 = ft_strchr(&tmp[y + 1], tmp[y]);
		if ((tmp[y] == '\'' || tmp[y] == '\"') && tmp2)
		{
			y++;
			while (&tmp[y] != tmp2)
				com[x++] = tmp[y++];
			y++;
		}
		else
			com[x++] = tmp[y++];
	}
	com[x] = '\0';
	free(tmp);
	return (com);
}
