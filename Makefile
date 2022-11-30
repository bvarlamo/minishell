# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bvarlamo <bvarlamo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/09 12:27:53 by bvarlamo          #+#    #+#              #
#    Updated: 2022/04/23 12:48:30 by bvarlamo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MINI		=	shell.c work_on_input.c work_on_input2.c splitter.c builtin.c envp.c builtin2.c executing.c redirections.c get_path.c redirections2.c redirections3.c signals.c builtin3.c pipe.c\

NAME		=	minishell

CC			=	gcc -g

RM			=	rm -f

CFLAGS		=	-Wall -Werror -Wextra

LIB			=	./Libft

INCLUDES	=	Libft/libft.a

RDLINE		=	-lreadline

MINIO		=	${MINI:.c=.o}

all			:	$(NAME)

${NAME}: ${MINIO}
				make -C ${LIB}
				${CC} ${CFLAGS} ${MINIO} ${INCLUDES} -o ${NAME} ${RDLINE} -L/usr/local/opt/readline/lib

%.o 	: 	%.c
			@$(CC) $(CFLAGS) -I/usr/local/opt/readline/include -c $< -o $@

clean :
		make clean -C ${LIB}
		$(RM) ${MINIO}

fclean : clean
		$(RM) $(NAME)
		$(RM) $(MINIO)
		make clean -C ${LIB}
		make fclean -C ${LIB}

re :			fclean all