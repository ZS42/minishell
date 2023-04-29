NAME = minishell

INC_DIR = include
SRC_DIR = sources
OBJ_DIR = object


LIB_READLINE = /usr/local/Cellar/readline/8.1/lib
READLINE_I = /usr/local/Cellar/readline/8.1/include

SRCS = main.c init.c execute.c child.c signals.c ft_redirections.c \
		builtins/env.c builtins/cd.c builtins/exit.c builtins/echo.c \
		builtins/pwd.c builtins/export.c path.c builtins/unset.c \
		builtins/builtins.c utilities.c heredoc.c \
		ruhan/convert.c ruhan/elem_tools.c ruhan/env.c ruhan/free.c ruhan/error.c \
		ruhan/func.c ruhan/lex.c ruhan/parse.c ruhan/redir.c ruhan/update.c \
		libft/ft_split.c libft/get_next_line_utils.c libft/get_next_line.c \
		libft/is.c libft/put.c libft/str.c \

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

CC	= gcc
RM	= rm -rf
CFLAGS = -Wall -Werror -Wextra -g3 #-fsanitize=address

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/ruhan
	@mkdir -p $(OBJ_DIR)/builtins
	@mkdir -p $(OBJ_DIR)/libft
	@$(CC) $(CFLAGS) -I $(READLINE_I) -I $(INC_DIR) -c $< -o $@

all:	$(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -I $(READLINE_I) -L $(LIB_READLINE) $(OBJS) -lreadline -o $(NAME)
	@printf "\x1B[32mminishell ready\\x1B[32m\n";

gpush:
	make fclean
	rm -rf minishell_tester
	git add .
	git commit -m sub
	git push

check:
	make re
	rm -rf minishell_tester
	git clone https://github.com/LucasKuhn/minishell_tester.git
	cd minishell_tester && ./tester
	cd ..

clean:
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)

re:	fclean all

# to remove all recipes that aren't files to avoid relinking
.PHONY:		all clean fclean re