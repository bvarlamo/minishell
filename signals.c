/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarlamo <bvarlamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 15:56:37 by bvarlamo          #+#    #+#             */
/*   Updated: 2022/04/22 19:38:09 by bvarlamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signals(void)
{
	struct termios		ter;
	struct sigaction	sig;
	struct sigaction	sig2;

	tcgetattr(STDIN_FILENO, &ter);
	ter.c_lflag = ter.c_lflag & ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &ter);
	sig = (struct sigaction){};
	sig2 = (struct sigaction){};
	sig.sa_handler = &handler;
	sig2.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sig2, NULL);
	sigaction(SIGINT, &sig, NULL);
}

void	ft_execute4(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

char	*quest(char *str, char *add, t_data *data, int x)
{
	char	*tmp;
	int		i;
	int		y;
	char	*string;

	i = 0;
	while (str[i])
		i++;
	string = ft_itoa((data->err / 256));
	tmp = malloc(sizeof(char) * (i - 1 + (ft_strlen(string))));
	i = 0;
	y = 0;
	while (&str[i] != add)
		tmp[y++] = str[i++];
	x = 0;
	while (string[x])
		tmp[y++] = string[x++];
	i = i + 2;
	while (str[i])
		tmp[y++] = str[i++];
	tmp[y] = '\0';
	free(str);
	return (tmp);
}
