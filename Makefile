


all : 
	gcc -Wall -Wextra -Werror srcs/*.c libft/libft.a gnl/*.c -I includes
	cp a.out resources/players/khalid
