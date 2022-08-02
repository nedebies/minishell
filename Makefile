SRCS	=	main.c \
			./parsing/ft_parser.c \
			./executing/ft_executer.c \
			./expanding/ft_expander.c \
			./lexing/ft_lexer.c

OBJS	= $(SRCS:.c=.o)

NAME	= minishell

CC	= gcc

FLAGS	= -Wall -Wextra -Werror

INC		= -lreadline

HEADER	= minishell.h

all:	$(NAME)

%.o: %.c $(HEADER)
	@$(CC) $(FLAGS) -c $< -o $@

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