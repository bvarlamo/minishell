/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarlamo <bvarlamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 10:45:33 by bvarlamo          #+#    #+#             */
/*   Updated: 2022/04/23 12:20:30 by bvarlamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	delete_env(t_data *data, char *var)
{
	char	**tmp;
	int		i;
	int		y;

	i = 0;
	while (data->envp[i])
		i++;
	tmp = data->envp;
	data->envp = malloc(sizeof(char *) * i);
	i = 0;
	y = 0;
	while (tmp[i])
	{
		if (tmp[i] == var)
			free(tmp[i]);
		else
		{
			data->envp[y] = tmp[i];
			y++;
		}
		i++;
	}
	free(tmp);
	data->envp[y] = NULL;
	return (1);
}

int	unset(t_data *data, char **str)
{
	int		i;
	int		y;
	int		x;

	i = 1;
	while (data->comands[0][i])
	{
		y = 0;
		while (data->envp[y])
		{
			x = ft_strlen(str[i]);
			if (ft_strncmp(data->envp[y], str[i], x) == 0)
			{
				if (data->envp[y][x] == '=' || data->envp[y][x] == '\0')
				{
					delete_env(data, data->envp[y]);
					y--;
				}
			}
			y++;
		}
		i++;
	}
	return (1);
}

int	ft_exit(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
		free(data->envp[i++]);
	free(data->envp);
	if (data->line)
		free(data->line);
	write(2, "exit\n", 5);
	exit(data->err / 256);
	return (data->err);
}

void	change_oldpwd(t_data *data, char *str)
{
	int		y;
	char	*tmp;

	y = 0;
	while (data->envp[y])
	{
		if (ft_strncmp(data->envp[y], "OLDPWD", 6) == 0)
		{
			tmp = data->envp[y];
			data->envp[y] = ft_strjoin("OLDPWD=", str);
			free(tmp);
			break ;
		}
		y++;
	}
	if (!data->envp[y])
	{
		tmp = ft_strjoin("OLDPWD=", str);
		export_input(tmp, data);
		free(tmp);
	}
}

int	change_pwd(t_data *data, char *str)
{
	int		y;
	char	buf[256];
	char	*tmp;

	y = 0;
	getcwd(buf, sizeof(buf));
	while (data->envp[y])
	{
		if (ft_strncmp(data->envp[y], "PWD=", 4) == 0)
		{
			tmp = data->envp[y];
			data->envp[y] = ft_strjoin("PWD=", buf);
			free(tmp);
			break ;
		}
		y++;
	}
	if (!data->envp[y])
	{
		tmp = ft_strjoin("PWD=", buf);
		export_input(tmp, data);
		free(tmp);
	}
	change_oldpwd(data, str);
	return (1);
}
