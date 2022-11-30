/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarlamo <bvarlamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 11:20:40 by bvarlamo          #+#    #+#             */
/*   Updated: 2022/04/22 19:37:52 by bvarlamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	*export_list2(t_data *data, int *tmp, int t, int i)
{
	int	y;
	int	x;

	while (data->envp[i])
	{
		tmp[i] = i;
		i++;
	}
	while (t < i)
	{
		y = t;
		while (y < i)
		{
			x = ft_strlen(data->envp[tmp[t]]);
			if (ft_strncmp(data->envp[tmp[t]], data->envp[tmp[y]], x) > 0)
			{
				x = tmp[y];
				tmp[y] = tmp[t];
				tmp[t] = x;
			}
			y++;
		}
		t++;
	}
	return (tmp);
}

void	export_list(t_data *data, int i, int y)
{
	int		*tmp;
	int		t;

	while (data->envp[i])
		i++;
	tmp = malloc(sizeof(int) * (i + 1));
	tmp = export_list2(data, tmp, 0, 0);
	while (y < i)
	{
		write(1, "declare -x ", 11);
		t = 0;
		while (data->envp[tmp[y]][t])
		{
			write(1, &data->envp[tmp[y]][t], 1);
			if (&data->envp[tmp[y]][t] == ft_strchr(data->envp[tmp[y]], '='))
				write(1, "\"", 1);
			t++;
		}
		if (ft_strchr(data->envp[tmp[y]], '='))
			write(1, "\"", 1);
		write(1, "\n", 1);
		y++;
	}
	free(tmp);
}

void	export_input(char *str, t_data *data)
{
	char	**tmp;
	int		i;

	tmp = data->envp;
	i = 0;
	while (tmp[i])
		i++;
	data->envp = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (tmp[i])
	{
		data->envp[i] = ft_strdup(tmp[i]);
		free(tmp[i]);
		i++;
	}
	free(tmp);
	data->envp[i] = ft_strdup(str);
	data->envp[i + 1] = NULL;
}

int	check_builtins(t_data *data, char **str)
{
	int	i;

	i = 0;
	if (str[0])
	{
		if (ft_strncmp(str[0], "echo", 5) == 0)
			i = echo(str, 1);
		else if (ft_strncmp(str[0], "cd", 3) == 0)
			i = cd(data, str, 0);
		else if (ft_strncmp(str[0], "pwd", 4) == 0)
			i = pwd(data);
		else if (ft_strncmp(str[0], "env", 4) == 0)
			i = env(data, str);
		else if (ft_strncmp(str[0], "export", 7) == 0)
			i = export(data, str);
		else if (ft_strncmp(str[0], "unset", 6) == 0)
			i = unset(data, str);
		else if (ft_strncmp(str[0], "exit", 6) == 0)
			i = ft_exit(data);
	}
	return (i);
}
