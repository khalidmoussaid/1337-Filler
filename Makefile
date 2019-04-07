NAME = kmoussai.filler
SRC = srcs/main.c srcs/math.c srcs/checker.c srcs/reader.c\
	  gnl/get_next_line.c
CFLAG = -Wall -Wextra -Werror
INC = includes


all: $(NAME)

$(NAME):
	make -C libft/ re
	gcc -c $(CFLAG) $(SRC) -I $(INC) 
	gcc -o $(NAME) *.o -L libft/ -lft

clean:
	make -C libft/ clean
	rm -Rf *.o

fclean:clean
	make -C libft/ fclean
	rm -Rf $(NAME) 

re: fclean $(NAME)
	
