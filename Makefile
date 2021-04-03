all: checker.c 
	gcc checker.c ./libft/libft.a -o checker
	gcc push_swap.c ./libft/libft.a -o push_swap