NAME		=	./minishell

LIBFTDIR	= ./libft

CC			=	cc
CFLAGS		=	-g3 -fsanitize=address\
#-Wall -Wextra -Werror

#m1 mac 용

INCLUDES 	=	-I /opt/homebrew/opt/readline/include \
				-I ./libft/ \
				-I .
LIBS		=	-L /opt/homebrew/opt/readline/lib -lreadline \
				-L ./libft/ -lft

# cluster 용 

# INCLUDES 	=	-I ~/goinfre/.brew/opt/readline/include \
#  				-I ./libft/ \
#  				-I .

# LIBS		=	-L ~/goinfre/.brew/opt/readline/lib  -lreadline \
#  				-L ./libft/ -lft

SRCS			=	./main.c\
					./parse.c\
					./deque_arg_util.c\
					./deque_env_util.c\
					./deque_cmd_util.c\
					./parse_save.c\
					./parse_count_len.c\
					./parse_divide_pipe.c\
					./env_save.c\
					./env_replace.c\
					./exec_commands.c\
					./exec_child.c\
					./signal_handle.c\
					./free_util.c\
					./error_handle.c\

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