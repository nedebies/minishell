SRCS	=	main.c \
			./env/ft_environs.c \
			./env/ft_sort_env.c \
			./parsing/parser.c \
			./parsing/pre_parser.c \
			./parsing/init_cmds.c \
			./parsing/redir.c \
			./parsing/parse_line.c \
			./lexer/tokens.c \
			./executer/executor.c \
			./executer/executor_utils.c \
			./executer/process.c \
			./executer/builtins/builtins.c \
			./executer/builtins/ft_cd.c \
			./executer/builtins/ft_echo.c \
			./executer/builtins/ft_env.c \
			./executer/builtins/ft_exit.c \
			./executer/builtins/ft_export.c \
			./executer/builtins/ft_pwd.c \
			./executer/builtins/ft_unset.c \
			./libft/ft_atoi.c \
			./libft/ft_lstiter.c \
			./libft/ft_putstr_fd.c \
			./libft/ft_strnstr.c \
			./libft/ft_strcmp.c \
			./libft/ft_strchr.c \
			./libft/ft_strlen.c \
			./libft/ft_putendl_fd.c \
			./libft/ft_putchar_fd.c \
			./libft/ft_strncmp.c \
			./libft/ft_isalnum.c \
			./libft/ft_isdigit.c \
			./libft/ft_strjoin.c \
			./libft/ft_split.c \
			./libft/ft_strdup.c \
			./libft/ft_calloc.c \
			./libft/ft_substr.c \
			./libft/ft_memcpy.c \
			./libft/ft_itoa.c \
			./libft/ft_isalpha.c \
			./libft/ft_memset.c \
			./libft/ft_lstnew.c \
			./libft/ft_lstadd_back.c \
			./libft/ft_lstclear.c \
			./libft/ft_lstsize.c \
			./libft/ft_lstdelone.c \
			./libft/ft_strlcpy.c \
			ft_free_memory.c \
			ft_signal.c \
			error.c

OBJS	= $(SRCS:.c=.o)

NAME	= minishell

CC	= gcc

FLAGS	= -Wall -Wextra -Werror -I ~/.brew/opt/readline/include -g

INC		= -lreadline

HEADER	= minishell.h

all:	$(NAME)

%.o: %.c $(HEADER)
	@${CC} ${FLAGS} -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(INC)
	@echo "Compilation completed.\n./minishell is ready to use !"

clean:
	@rm -f $(OBJS)
	@echo "All <file>.o are removed."

fclean: clean
	@rm -f $(NAME)
	@echo "./minishell is removed."

re: fclean all

.PHONY:	clean fclean re