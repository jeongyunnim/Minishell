NAME		=	./minishell

LIBFTDIR	= ./libft

CC			=	cc
CFLAGS		=	\
#-Wall -Wextra -Werror

INCLUDES 	=	-I ~/goinfre/.brew/opt/readline/include \
				-I ./libft/ \
				-I .

LIBS		=	-lreadline -L ~/goinfre/.brew/opt/readline/lib/ \
				-lhistory -L ~/goinfre/.brew/opt/readline/lib/ \
				-L ./libft/ -lft

SRCS			=	./minishell.c\
					./parse.c\
					./deque_util.c\
					./save_parse.c\

OBJS			=	$(SRCS:%.c=%.o)

AR			=	ar rcs
RM			=	rm -f

all			:	$(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $^

$(NAME)	: $(OBJS)
	make -C $(LIBFTDIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) $^ -o $@

all : $(NAME)

clean :
	make -C $(LIBFTDIR) clean
	$(RM) $(OBJS)

fclean : clean
	make -C $(LIBFTDIR) fclean
	$(RM) $(NAME)

re : fclean all

.PHONY		:	all clean fclean re