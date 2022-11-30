/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarlamo <bvarlamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:30:13 by bvarlamo          #+#    #+#             */
/*   Updated: 2022/04/23 16:14:05 by bvarlamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	free_com(t_data *data)
{
	int	i;
	int	y;

	i = 0;
	while (data->cmd_count && data->comands[i])
	{
		y = 0;
		while (data->comands[i][y])
		{
			free(data->comands[i][y]);
			y++;
		}
		free(data->comands[i]);
		i++;
	}
	free(data->comands);
}

void	init(t_data	*data)
{
	char	*promt;

	data->cmd_count = 0;
	getcwd(data->cwd, sizeof(data->cwd));
	promt = ft_strjoin(data->cwd, " : ");
	if (data->line && *data->line)
	{
		free (data->line);
		data->line = (char *) NULL;
	}
	data->line = readline(promt);
	if (data->line && *data->line)
		add_history (data->line);
	free(promt);
}

void	init_envp(t_data *data, char **envp)
{
	int	i;

	i = 0;
	data->err = 0;
	signals();
	while (envp[i])
		i++;
	data->envp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		data->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	data->envp[i] = NULL;
	check_path(data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 1 || argv[1])
		return (0);
	data.line = (char *) NULL;
	init_envp(&data, envp);
	while (1)
	{
		init(&data);
		if (!data.line)
			ft_exit(&data);
		if (ft_strncmp(data.line, "exit ", 5) == 0)
			ft_exit2(&data, data.line);
		if (data.line && *data.line)
			pipe_check(&data, data.line);
		if (data.line && *data.line)
			pipes(&data, 0);
		if (data.line && *data.line)
			ft_execute(&data);
		if (data.line && *data.line)
			free_com(&data);
	}
}
