NAME		=	./minishell

LIBFTDIR	= ./libft

CC			=	cc
CFLAGS		=	-g3 -fsanitize=address\
#-Wall -Wextra -Werror

INCLUDES =	-I /opt/homebrew/opt/readline/include \
			-I ./libft/ \
			-I .

LIBS	 = 	-lreadline -L /opt/homebrew/opt/readline/lib/ \
			-lhistory -L /opt/homebrew/opt/readline/lib/ \
			-L ./libft/ -lft

#    INCLUDES 	=	-I ~/goinfre/.brew/opt/readline/include \
#     				-I ./libft/ \
#     				-I .

#    LIBS		=	-lreadline -L ~/goinfre/.brew/opt/readline/lib/ \
#     				-lhistory -L ~/goinfre/.brew/opt/readline/lib/ \
#     				-L ./libft/ -lft

SRCS			=	./minishell.c\
					./parse.c\
					./deque_arg_util.c\
					./deque_env_util.c\
					./parse_save.c\
					./parse_count_len.c\
					./parse_prioritize.c\
					./env_save.c\
					./env_replace.c\

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