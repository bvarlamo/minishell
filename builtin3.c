/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarlamo <bvarlamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 19:52:57 by bvarlamo          #+#    #+#             */
/*   Updated: 2022/04/23 15:43:00 by bvarlamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	export2(t_data *data, char *string, char *tmp3, char *str)
{
	int	y;

	y = 0;
	while (data->envp[y])
	{
		if (ft_strncmp(data->envp[y], tmp3, ft_strlen(tmp3)) == 0)
			break ;
		if (ft_strncmp(data->envp[y], string, ft_strlen(string) + 1) == 0)
			break ;
		y++;
	}
	free(string);
	if (data->envp[y])
	{
		string = data->envp[y];
		data->envp[y] = ft_strjoin(str, NULL);
		free(string);
	}
	else
		export_input(str, data);
}

void	export3(t_data *data, char *str)
{
	char	*tmp2;
	char	*tmp3;
	int		y;

	tmp2 = ft_strjoin(str, "=");
	tmp3 = ft_strjoin(str, "\0");
	y = 0;
	while (data->envp[y])
	{
		if (ft_strncmp(data->envp[y], tmp2, ft_strlen(tmp2)) == 0)
			break ;
		if (ft_strncmp(data->envp[y], tmp3, ft_strlen(tmp3) + 1) == 0)
			break ;
		y++;
	}
	if (data->envp[y])
		;
	else
		export_input(str, data);
	free(tmp3);
	free(tmp2);
}

void	export4(t_data *data, char *str)
{
	char	**tmp;
	char	*string;
	char	*tmp3;
	int		y;

	tmp = ft_split(str, '=');
	tmp3 = ft_strjoin(tmp[0], "=");
	string = ft_strjoin(tmp[0], NULL);
	export2(data, string, tmp3, str);
	y = 0;
	while (tmp[y])
		free(tmp[y++]);
	free(tmp);
	free(tmp3);
}

int	ex_check(char **str, t_data *data, int i, int y)
{
	int		flag;

	flag = 0;
	while (str[i])
	{
		y = 0;
		if (str[i][y] == '_' || ft_isalpha(str[i][y]) == 1)
			flag = 1;
		if (str[i][y] == '=')
			flag = 0;
		while (str[i][y] && str[i][y] != '=')
		{
			if (!ft_isalnum(str[i][y]) && str[i][y] != '_')
				flag = 0;
			y++;
		}
		if (!flag)
		{
			write(2, "wrong character\n", 17);
			data->err = 256;
			return (0);
		}
		i++;
	}
	return (1);
}

int	export(t_data *data, char **str)
{
	char	*tmp2;
	int		i;

	if (str[1])
	{
		i = 1;
		while (str[i])
		{
			if (ex_check(str, data, 1, 0) == 0)
				return (1);
			tmp2 = ft_strchr(str[i], '=');
			if (tmp2)
				export4(data, str[i]);
			else
				export3(data, str[i]);
			i++;
		}
	}
	else
		export_list(data, 0, 0);
	return (1);
}
