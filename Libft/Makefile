# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bvarlamo <bvarlamo@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/17 12:04:02 by bvarlamo          #+#    #+#              #
#    Updated: 2021/07/17 14:09:22 by bvarlamo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MANDATORY=	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c \
		ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
		ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c \
		ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
		ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		get_next_line_utils.c get_next_line.c \


BNS	=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
		ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \

NAME	=	libft.a

CC	=	gcc

RM	=	rm -f

CFLAGS	=	-Wall -Wextra -Werror -c

AR	= 	ar rcs

MANDATORYO=	$(MANDATORY:.c=.o)

BNSO	=	$(BNS:.c=.o)

all :		$(NAME)

$(NAME) :	$(MANDATORYO)
	$(AR) $(NAME) $(MANDATORYO)

bonus	 :	$(BNSO)
	$(AR) $(NAME) $(BNSO)

$(MANDATORYO) :	$(MANDATORY)
	$(CC) $(CFLAGS) $(MANDATORY)

$(BNSO)	:	$(BNS)
	$(CC) $(CFLAGS) $(BNS)

clean :
	$(RM) $(MANDATORYO)
	$(RM) $(BNSO)

fclean :	clean
	$(RM) $(NAME)

re :		fclean all