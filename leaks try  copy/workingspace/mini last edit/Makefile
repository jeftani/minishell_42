NAME		=	minishell

LIB			=	libft/libft.a
CC			=	@cc

CFLAGS		=	-Wall -Wextra -Werror #-fsanitize=address -g3
READLINE	=	-lreadline

SRC_LIB		=	libft/ft_isalpha.c libft/ft_isdigit.c libft/ft_isalnum.c libft/ft_isascii.c \
				libft/ft_isprint.c libft/ft_strlen.c libft/ft_memset.c libft/ft_bzero.c \
				libft/ft_memcpy.c libft/ft_memmove.c libft/ft_strlcpy.c libft/ft_strlcat.c \
				libft/ft_toupper.c libft/ft_tolower.c libft/ft_strchr.c libft/ft_strrchr.c \
				libft/ft_strncmp.c libft/ft_memchr.c libft/ft_memcmp.c libft/ft_strnstr.c \
				libft/ft_atoi.c libft/ft_calloc.c libft/ft_strdup.c libft/ft_substr.c \
				libft/ft_strjoin.c libft/ft_strtrim.c libft/ft_split.c libft/ft_itoa.c \
				libft/ft_strmapi.c libft/ft_striteri.c libft/ft_putchar_fd.c libft/ft_putstr_fd.c \
				libft/ft_putendl_fd.c libft/ft_putnbr_fd.c
SRC			=	token.c token_help.c space_expand.c split_pipe.c remove_quoates.c spaces.c parse_special.c parse_base.c main.c utils/leaks.c \
				utils/ft_execute.c utils/ft_is_alpha.c utils/ft_isalnum.c utils/ft_strchr1.c utils/ft_strcmp.c utils/ft_strdup.c utils/ft_strjoin.c utils/ft_substr.c builtins/unset.c \
				builtins/echo.c  builtins/exit.c builtins/cd.c  utils/ft_putstr_fd.c utils/ft_isdigit.c utils/ft_atoi1.c utils/ft_strncmp1.c utils/env_stuff.c ft_all_redirections_con.c\
				builtins/env.c builtins/export.c builtins/pwd.c ft_execute1.c ft_execute2.c ft_execute3.c ft_execute4.c ft_all_redirections.c heredoc.c err_handler.c err_handler1.c builtins_extention/cd_ex.c builtins_extention/export_ex.c \


OBJ_LIB		=	$(SRC_LIB:.c=.o)
OBJ			=	$(SRC:.c=.o)

all		:	$(NAME)

$(NAME)	: $(OBJ) $(LIB)
	@printf "\e[38;5;236m \n ⚡︎⚡︎⚡︎⚡︎⚡︎⚡︎ COMPILING ⚡︎⚡︎⚡︎⚡︎⚡︎⚡︎\n\e[0m\n"
	$(CC) $(CFLAGS) $(READLINE) $(OBJ) $(LIB) -o $(NAME)
	@stty -echoctl
	@printf "\e[38;5;216m→	successfully build	✔︎\e[0m\n"

$(LIB)	:	$(SRC_LIB)
	@make -C libft
	@make -C libft bonus
	@make -C libft clean

clean	:
	@rm -f $(OBJ)
	@printf "\e[38;5;206m→	Objects files deleted 🗑\e[0m\n"

fclean	: clean
	@rm -f $(NAME)
	@make -C libft fclean
	@printf "\e[38;5;206m→	All files was deleted 🗑\e[0m\n"

re		: fclean all
