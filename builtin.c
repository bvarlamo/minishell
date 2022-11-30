/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarlamo <bvarlamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:58:03 by bvarlamo          #+#    #+#             */
/*   Updated: 2022/04/22 19:37:47 by bvarlamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	echo(char **data, int i)
{
	size_t	y;
	char	flag;

	flag = '\n';
	while (data[i] && data[i][0] == '-')
	{
		y = 1;
		while (data[i][y] == 'n')
			y++;
		if (data[i][1] && y == ft_strlen(data[i]))
			flag = 0;
		else
			break ;
		i++;
	}
	while (data[i])
	{
		write(1, data[i], ft_strlen(data[i]));
		if (data[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (flag)
		write(1, &flag, 1);
	return (1);
}

int	cd(t_data *data, char **str, int i)
{
	char	dir[256];

	getcwd(dir, sizeof(dir));
	if (!str[1])
	{
		i = 0;
		while (str[i])
		{
			if (ft_strncmp(data->envp[i], "HOME=", 5) == 0)
			{
				chdir(&data->envp[i][5]);
				change_pwd(data, dir);
				break ;
			}
			i++;
		}
	}
	else if (!str[2] && chdir(str[1]) == 0)
		change_pwd(data, dir);
	else
	{
		write(2, "Invalid path\n", 13);
		data->err = 256;
	}
	return (1);
}

int	pwd(t_data *data)
{
	getcwd(data->cwd, sizeof(data->cwd));
	write(1, data->cwd, ft_strlen(data->cwd));
	write(1, "\n", 1);
	return (1);
}

int	env(t_data *data, char **str)
{
	int	i;

	if (str[1])
	{
		write(2, "to many arguments\n", 18);
		data->err = 127 * 256;
	}
	else
	{
		i = 0;
		while (data->envp[i])
		{
			if (ft_strchr(data->envp[i], '='))
			{
				write(1, data->envp[i], ft_strlen(data->envp[i]));
				write(1, "\n", 1);
			}
			i++;
		}
	}
	return (1);
}
