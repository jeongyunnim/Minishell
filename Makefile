NAME	=	./minishell

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror

INC		=	./minishell.h

SRC		=	./minishell.c

OBJ		=	$(SRC:%.c=%.o)

RM		=	rm -f

all		:	$(NAME)

$(NAME) :	$(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ)	:	$(SRC) $(INC)
	$(CC) $(CFLAGS) -c $^

clean	:
	$(RM) $(OBJ)

fclean	:	clean
	$(RM) $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re