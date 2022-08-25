SRCS	=	main.c \
			./parsing/parser_hdony.c \
			./parsing/parsing_smp_cmd_hdony.c \
			./parsing/parsing_cmp_cmd_hdony.c \
			./executer/ft_executer.c \
			./executer/process_manager.c \
			./executer/builtins/ft_builtins_manager.c \
			./executer/builtins/ft_echo.c \
			./executer/builtins/ft_cd.c \
			./executer/builtins/ft_pwd.c \
			./executer/builtins/ft_export.c \
			./executer/builtins/ft_env.c \
			./executer/builtins/ft_unset.c \
			./executer/builtins/ft_exit.c \
			./env/envp_manager.c \
			./expander/ft_expander.c \
			./libft/ft_putstr_fd.c \
			./libft/ft_strnstr.c \
			./libft/ft_strchr.c \
			./libft/ft_strlen.c \
			./libft/ft_putendl_fd.c \
			./libft/ft_strncmp.c \
			./libft/ft_isalnum.c \
			./libft/ft_isdigit.c \
			./libft/ft_strjoin.c \
			./libft/ft_split.c \
			./libft/ft_strdup.c \
			./libft/ft_substr.c \
			./libft/ft_isalpha.c \
			./libft/ft_memset.c \
			./libft/ft_strlcpy.c \
			./lexer/lexer.c \
			./lexer/lexer_split.c \
			./lexer/lexer_stringcount.c \
			./lexer/lexer_token.c \
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