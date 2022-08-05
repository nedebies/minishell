SRCS	=	main.c \
			./parsing/ft_parser.c \
			./executer/ft_executer.c \
			./executer/builtins/ft_echo.c \
			./executer/builtins/ft_cd.c \
			./executer/builtins/ft_pwd.c \
			./executer/builtins/ft_export.c \
			./executer/builtins/ft_unset.c \
			./executer/builtins/ft_env.c \
			./executer/builtins/ft_exit.c \
			./expander/ft_expander.c \
			./libft/ft_putstr_fd.c \
			./lexer/ft_lexer.c

OBJS	= $(SRCS:.c=.o)

NAME	= minishell

CC	= gcc

FLAGS	= -Wall -Wextra -Werror

INC		= -lreadline

HEADER	= minishell.h

all:	$(NAME)

%.o: %.c $(HEADER)
	@${CC} ${FLAGS} -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(INC) -o $(NAME) $(OBJS)
	@echo "Compilation completed.\n./minishell is ready to use !"

clean:
	@rm -f $(OBJS)
	@echo "All <file>.o are removed."

fclean: clean
	@rm -f $(NAME)
	@echo "./minishell is removed."

re: fclean all

.PHONY:	clean fclean re