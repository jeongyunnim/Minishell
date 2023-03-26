NAME		=	./minishell

LIBFTDIR	= ./libft

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror \

INCLUDES 	=	-I ~/goinfre/.brew/opt/readline/include \
   				-I ./libft/ \
   				-I .

LIBS		=	-L ~/goinfre/.brew/opt/readline/lib  -lreadline \
   				-L ./libft/ -lft

SRCS			=	./main.c\
					./parse/parse.c\
					./parse/parse_save.c\
					./parse/parse_count_len.c\
					./parse/parse_divide_pipe.c\
					./parse/parse_util.c\
					./parse/parse_valid_check.c\
					./parse/env_save.c\
					./parse/env_replace.c\
					./parse/env_valid_check.c\
					./exec/exec_commands.c\
					./exec/exec_redirection.c\
					./exec/exec_heredoc.c\
					./exec/exec_child.c\
					./exec/exec_parent.c\
					./exec/exec_builtin.c\
					./init/init_info.c\
					./init/init_terminal_mode.c\
					./init/init_terminal.c\
					./util/deque_arg_util.c\
					./util/deque_env_util.c\
					./util/deque_cmd_util.c\
					./util/free_util.c\
					./util/error_handle.c\
					./util/asciiart.c\
					./builtin/ft_cd.c\
					./builtin/ft_echo.c\
					./builtin/ft_env.c\
					./builtin/ft_exit.c\
					./builtin/ft_export.c\
					./builtin/ft_export_utils.c\
					./builtin/ft_pwd.c\
					./builtin/ft_unset.c\
					./builtin/builtin_utils.c\
					./signal/signal_handle.c\

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