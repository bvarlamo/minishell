/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarlamo <bvarlamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:40:12 by bvarlamo          #+#    #+#             */
/*   Updated: 2022/04/22 19:37:56 by bvarlamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*path_env(char *str)
{
	char	*path;
	int		i;

	path = malloc(sizeof(char) * ft_strlen(str));
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' && str[i + 1])
			path[i] = ':';
		else if (str[i] != '\n')
			path[i] = str[i];
		i++;
	}
	path[i - 1] = '\0';
	return (path);
}

void	check_pwd(t_data *data)
{
	int		i;
	char	*tmp;
	char	buff[200];

	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], "PWD=", 4) == 0)
			break ;
		i++;
	}
	if (!data->envp[i])
	{
		getcwd(buff, sizeof(buff));
		tmp = ft_strjoin("PWD=", buff);
		export_input(tmp, data);
		free(tmp);
	}
}

char	*get_path(int i, int fd)
{
	char	*tmp;
	char	*line;
	char	*paths[3];
	char	*path;

	paths[0] = "/etc/paths";
	paths[1] = "/etc/paths.d/munki";
	paths[2] = "/etc/paths.d/40-XQuartz";
	path = NULL;
	while (paths[i])
	{
		fd = open(paths[i++], O_RDONLY);
		line = get_next_line(fd);
		while (line)
		{
			tmp = path;
			path = ft_strjoin(path, line);
			free(line);
			if (tmp && *tmp)
				free(tmp);
			line = get_next_line(fd);
		}
		close(fd);
	}
	return (path_env(path));
}

void	old_pwd(t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], "OLDPWD=", 7) == 0)
		{
			tmp = data->envp[i];
			data->envp[i] = ft_strjoin("OLDPWD", NULL);
			free(tmp);
			break ;
		}
		i++;
	}
}

void	check_path(t_data *data)
{
	int		i;
	char	*tmp;

	check_pwd(data);
	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (!data->envp[i])
	{
		tmp = ft_strjoin("PATH=", get_path(0, 0));
		export_input(tmp, data);
		free(tmp);
	}
	old_pwd(data);
}
