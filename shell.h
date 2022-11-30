/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarlamo <bvarlamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:29:26 by bvarlamo          #+#    #+#             */
/*   Updated: 2022/04/23 13:15:27 by bvarlamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "Libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_data
{
	char	*line;
	char	**envp;
	char	***comands;
	char	cwd[1024];
	int		cmd_count;
	int		*in_fd;
	int		*out_fd;
	int		err;
	char	*err_mes;
}	t_data;

int		echo(char **str, int i);
int		cd(t_data *data, char **str, int i);
int		pwd(t_data *data);
void	pipes(t_data *data, int i);
char	*dollar_sign(char *str, t_data *data);
char	**ft_spliter(char *s, char a, char c);
char	*quotation(char *commands);
void	export_list(t_data *data, int i, int y);
void	export_input(char *str, t_data *data);
int		env(t_data *data, char **str);
int		export(t_data *data, char **str);
int		unset(t_data *data, char **str);
int		ft_exit(t_data *data);
int		change_pwd(t_data *data, char *str);
void	ft_execute(t_data *data);
void	ft_redirect(char **str, t_data *data, int i, int y);
void	check_path(t_data *data);
void	input(t_data *data, char *tmp, int t);
void	output(t_data *data, char *tmp, int t);
void	app_output(t_data *data, char *tmp, int t);
void	heredoc(t_data *data, char *tmp, int t);
void	clean_line(char **str, int red);
void	checker(char *str, t_data *data);
void	checker2(char *str, t_data *data, int i);
void	signals(void);
int		check_builtins(t_data *data, char **str);
void	ft_execute4(void);
char	*quest(char *str, char *add, t_data *data, int x);
void	pipe_check(t_data *data, char *line);
void	ft_exit2(t_data *data, char *line);

#endif