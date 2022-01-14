LIBFT_OBJS	= ${LIBFT:%.c=%.o}

SRCS	=	main.c ft_split.c execve.c utils.c \
			lst_handler.c signals.c\
			get_word.c quote_handler.c env_handler.c parsing_utils.c \
			return_handler.c execve_utils.c  heredoc_handler.c \
			redirect_utils.c redirect_handler.c startup.c parsing.c \
			utils2.c \

B_SRCS	=	builtins/builtin_utils.c builtins/echo.c \
			builtins/cd.c builtins/pwd.c builtins/unset.c \
			builtins/env.c builtins/exit.c builtins/export.c \
			builtins/export_utils.c

P_SRCS	=	pipes/pipe_parser.c pipes/cmd_list.c \
			pipes/pipes.c pipes/pipe_utils.c \

INCLUDES = minishell.h
LIBFT_A	= libft/libft.a

OBJS	= ${SRCS:%.c=%.o} ${B_SRCS:%.c=%.o} ${P_SRCS:%.c=%.o}

NAME	= minishell

CC		= gcc
RM		= rm -rf
FLAGS	= -Wall -Wextra -Werror
BREW	= homebrew

ifeq ($(USER), tcharmel)
BREW = .brew
endif

.o: .c	${INCLUDES}
		${CC} ${FLAGS} $< -o $@ -lreadline -I/Users/${USER}/${BREW}/Cellar/readline/8.1.1/include

all:	libft ${NAME}

${NAME}:	${OBJS} ${INCLUDES}
			${CC} ${FLAGS} ${OBJS} ${LIBFT_A} -lreadline -L/Users/${USER}/${BREW}/Cellar/readline/8.1.1/lib/ -ltermcap -o ${NAME}

libft:
	make -C libft

clean:
	${RM} ${OBJS}
	make -C libft clean

fclean: clean
	${RM} ${NAME}
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re libft
