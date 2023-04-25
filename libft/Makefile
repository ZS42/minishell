# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/23 15:19:20 by zsyyida           #+#    #+#              #
#    Updated: 2023/04/24 11:11:54 by zsyyida          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

INC_DIR = include
SRC_DIR = sources
OBJ_DIR = objects

SRCS = ft_isdigit.c ft_memset.c ft_strtrim.c ft_strrchr.c\
		ft_putchar_fd.c ft_strlcat.c ft_itoa.c ft_substr.c\
		ft_strlcpy.c ft_bzero.c ft_putnbr_fd.c ft_strlen_ft.c \
		ft_calloc.c ft_memchr.c ft_putstr_fd.c ft_memcmp.c \
		ft_memcpy_ft.c ft_memmove.c ft_strdup_ft.c ft_strjoin_ft.c \
		ft_strchr_ft.c ft_split.c ft_lstadd_back.c ft_lstadd_front.c \
		ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstnew.c \
		ft_lstsize.c ft_lstmap.c ft_isalnum.c\
		ft_free_s.c ft_free_p.c ft_atoi.c\
		ft_strncmp.c ft_strnstr.c get_next_line.c\
		get_next_line_utils.c ft_is_alpha.c ft_strndup.c

# to add prefix (put into folder) called objects all o files
OBJS_SRC = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

CC	= gcc
RM	= rm -rf
CFLAGS = -Wextra

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
# to put all in one line use @printf "\033[A\033[2K\r"
	@$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

all:	$(NAME)

$(NAME): $(OBJS_SRC)
	@ar rcs $(NAME) $(OBJS_SRC)
	@echo "libft ready"

clean:
	$(RM) $(OBJ_DIR)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re

