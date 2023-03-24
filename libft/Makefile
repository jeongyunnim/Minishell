CC 		=	cc
CFLAGS	=	-Wall -Wextra -Werror
NAME	= 	libft.a
INC		=	libft.h
SRC		=	./ft_atoi.c			\
			./ft_bzero.c		\
			./ft_calloc.c		\
			./ft_isalnum.c		\
			./ft_isalpha.c		\
			./ft_isascii.c		\
			./ft_isdigit.c		\
			./ft_isprint.c		\
			./ft_memchr.c		\
			./ft_memcmp.c		\
			./ft_memcpy.c		\
			./ft_memmove.c		\
			./ft_memset.c		\
			./ft_strchr.c		\
			./ft_strdup.c		\
			./ft_strlcat.c		\
			./ft_strlcpy.c		\
			./ft_strlen.c		\
			./ft_strncmp.c		\
			./ft_strcmp.c		\
			./ft_strnstr.c		\
			./ft_strrchr.c		\
			./ft_tolower.c		\
			./ft_toupper.c		\
			./ft_substr.c		\
			./ft_strjoin.c		\
			./ft_strtrim.c		\
			./ft_split.c		\
			./ft_itoa.c			\
			./ft_strmapi.c		\
			./ft_striteri.c		\
			./ft_putchar_fd.c	\
			./ft_putendl_fd.c	\
			./ft_putnbr_fd.c	\
			./ft_putstr_fd.c	\
			./ft_isspace.c		\

SRC_B	=	./ft_lstnew.c		\
			./ft_lstadd_front.c	\
			./ft_lstsize.c		\
			./ft_lstlast.c		\
			./ft_lstadd_back.c	\
			./ft_lstdelone.c	\
			./ft_lstclear.c		\
			./ft_lstiter.c		\
			./ft_lstmap.c		\

SRCS	=	$(SRC)				\
			$(SRC_B)			\

OBJ		=	$(SRC:%.c=%.o)
OBJ_B	=	$(SRC_B:%.c=%.o)
RM		=	rm -f
AR		=	ar rc

ifdef		WITH_BONUS
			OBJECTS = $(OBJ) $(OBJ_B)
else
			OBJECTS = $(OBJ)
endif

all		:	$(NAME)

$(NAME)	:	$(OBJECTS)
	$(AR) $@ $(OBJECTS)

$(OBJ)	:	$(SRC)
	$(CC) $(CFLAGS) -c $^ -I $(INC)

$(OBJ_B):	$(SRC_B)
	$(CC) $(CFLAGS) -c $^ -I $(INC)

clean	:
	$(RM) $(OBJ) $(OBJ_B)

fclean	: clean
	$(RM) $(NAME)

re : fclean all

bonus	:
	make WITH_BONUS=1 all

.PHONY : all clean fclean re bonus
