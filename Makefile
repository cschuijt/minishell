OBJFILES := start.o
HEADER   := 
FLAGS    := -Werror -Wall -Wextra -g -I lib
RL_FLAGS := -lreadline
LIBFT_A  := lib/libft/libft.a
NAME     := minishell

$(NAME) : $(OBJFILES) $(LIBFT_A) $(HEADER) 
	$(CC) $(FLAGS) -o $(NAME) $(OBJFILES) $(LIBFT_A) $(RL_FLAGS)

all : $(NAME)

re : fclean all

clean :
	rm -f $(OBJFILES)

fclean :
	rm -f $(NAME) $(OBJFILES)

$(LIBFT_A) :
	make -C lib/libft

%.o : %.c $(HEADER)
	$(CC) -c $(FLAGS) -o $@ $<

.PHONY : clean fclean re
