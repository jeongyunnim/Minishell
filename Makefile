NAME		=	./minishell

LIBFTDIR	= ./libft

CC			=	cc
CFLAGS		=	-g3 -fsanitize=address\
#-Wall -Wextra -Werror

INCLUDES 	=	-I -lreadline \
 				-I ./libft/ \
 				-I .
LIBS		=	-lreadline \
 				-L ./libft/ -lft

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