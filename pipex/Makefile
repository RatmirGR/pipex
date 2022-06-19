NAME = pipex

HEADER = pipex.h

FLAGS = -Wall -Wextra -Werror -I $(HEADER)

SRCS = main.c init_config.c pipex.c pipex_utils.c ft_split.c get_next_line.c\
 		get_next_line_utils.c error_utils.c

OBJS = $(patsubst %.c, %.o, $(SRCS))

all : $(NAME)

$(NAME) : $(OBJS)
	gcc $(FLAGS) -o $(NAME) $(OBJS)

%.o : %.c
	gcc $(FLAGS) -c $< -o $@

bonus : all

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re bonus


