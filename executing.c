/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarlamo <bvarlamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 11:39:17 by bvarlamo          #+#    #+#             */
/*   Updated: 2022/04/22 19:37:54 by bvarlamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*cute2(char **paths, t_data *data, char *tmp2, char **str)
{
	char	*tmp;
	int		i;

	if (ft_strchr(tmp2, '/'))
	{
		getcwd(data->cwd, sizeof(data->cwd));
		tmp = ft_strjoin(data->cwd, "/");
		tmp2 = ft_strjoin(tmp, str[0]);
		free(tmp);
	}
	else
	{
		i = 0;
		while (paths[i])
		{
			tmp = ft_strjoin(paths[i], "/");
			tmp2 = ft_strjoin(tmp, str[0]);
			free(tmp);
			if (access(tmp2, X_OK) == 0)
				break ;
			free(tmp2);
			i++;
		}
	}
	return (tmp2);
}

void	ft_cute(char **str, t_data *data)
{
	int		i;
	char	**paths;
	char	*tmp2;

	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], "PATH=", 5) == 0)
			paths = ft_split(&data->envp[i][5], ':');
		i++;
	}
	i = 0;
	tmp2 = ft_strdup(str[0]);
	while (tmp2[i] == ' ')
		i++;
	if (tmp2[i] == '/')
		;
	else
		tmp2 = cute2(paths, data, tmp2, str);
	execve(tmp2, str, paths);
	write(2, str[0], ft_strlen(str[0]));
	write(2, ": command not found\n", 20);
	exit(127);
}

void	ft_execute2(t_data *data, int *fd, int i, int y)
{
	ft_execute4();
	if (i > 0)
	{
		if (data->in_fd[i] != 0)
			dup2(data->in_fd[i], STDIN_FILENO);
		else
			dup2(fd[(i - 1) * 2], STDIN_FILENO);
	}
	else
		dup2(data->in_fd[i], STDIN_FILENO);
	if (data->comands[i + 1])
	{
		close(fd[i * 2]);
		if (data->out_fd[i] != 1)
			dup2(data->out_fd[i], STDOUT_FILENO);
		else
			dup2(fd[(i * 2) + 1], STDOUT_FILENO);
	}
	else
		dup2(data->out_fd[i], STDOUT_FILENO);
	y = check_builtins(data, data->comands[i]);
	if (y == 0)
		ft_cute(data->comands[i], data);
	else
		exit(0);
}

void	ft_execute3(t_data *data, int id, int i, int y)
{
	int	*fd;

	fd = malloc(sizeof(int) * ((data->cmd_count - 1) * 2));
	pipe(fd);
	while (i < data->cmd_count)
	{
		id = fork();
		signal(SIGINT, SIG_IGN);
		signal(SIGTERM, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		if (id == 0)
			ft_execute2(data, fd, i, 0);
		if (i < (data->cmd_count - 1))
			close(fd[(i * 2) + 1]);
		if (i > 0)
			close(fd[(i - 1) * 2]);
		i++;
		if (i < (data->cmd_count - 1))
			pipe(fd + (i * 2));
	}
	y = waitpid(id, &data->err, 0);
	while (y > 0)
		y = waitpid(id, &data->err, 0);
	free(fd);
}

void	ft_execute(t_data *data)
{
	int	id;
	int	i;
	int	y;

	i = 0;
	if (!data->comands[1])
	{
		y = dup(STDIN_FILENO);
		dup2(data->in_fd[0], STDIN_FILENO);
		id = dup(STDOUT_FILENO);
		dup2(data->out_fd[0], STDOUT_FILENO);
		i = check_builtins(data, data->comands[0]);
		dup2(y, STDIN_FILENO);
		dup2(id, STDOUT_FILENO);
	}
	if (i == 0 && data->comands[i])
		ft_execute3(data, 0, 0, 0);
	signals();
	free(data->in_fd);
	free(data->out_fd);
}
