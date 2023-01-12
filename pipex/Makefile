NAME=pipex
FLAGS= -Wall -Wextra -Werror

AF=pipex.c ft_split.c pipex_utils.c

HLB=	$(AF:.c=.o)

all:	$(NAME)

$(NAME):	$(HLB)
	cc ${AF} -o ${NAME}
clean:
	rm -f $(HLB)

fclean: clean
	rm -f $(NAME)

re: fclean all