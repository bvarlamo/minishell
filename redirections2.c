/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarlamo <bvarlamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 14:33:43 by bvarlamo          #+#    #+#             */
/*   Updated: 2022/04/23 14:59:54 by bvarlamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	input(t_data *data, char *tmp, int t)
{
	data->in_fd[t] = open(tmp, O_RDWR);
	if (data->in_fd[t] == -1)
	{
		write(2, "No file or directory\n", 21);
		data->err = 256;
		if (data->line)
			free(data->line);
		data->line = NULL;
	}
}

void	output(t_data *data, char *tmp, int t)
{
	data->out_fd[t] = open(tmp, O_TRUNC | O_RDWR);
	if (data->out_fd[t] == -1)
		data->out_fd[t] = open(tmp, O_RDWR | O_CREAT);
}

void	app_output(t_data *data, char *tmp, int t)
{
	data->out_fd[t] = open(tmp, O_RDWR | O_APPEND);
	if (data->out_fd[t] == -1)
		data->out_fd[t] = open(tmp, O_RDWR | O_CREAT | O_APPEND);
}

void	heredoc(t_data *data, char *tmp, int t)
{
	char	*tmp1;
	char	*tmp2;
	int		h_in[2];

	signal(SIGINT, SIG_DFL);
	tmp2 = ft_strjoin(tmp, NULL);
	tmp2 = quotation(tmp2);
	pipe(h_in);
	while (1)
	{
		tmp1 = readline("> ");
		if (!tmp1 || ft_strncmp(tmp, tmp1, ft_strlen(tmp) + 1) == 0)
			break ;
		write(h_in[1], tmp1, ft_strlen(tmp1));
		write(h_in[1], "\n", 1);
		free (tmp1);
	}
	free(tmp1);
	data->in_fd[t] = h_in[0];
	free(tmp2);
	close(h_in[1]);
}
