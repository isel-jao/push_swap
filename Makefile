NAME		=	push_swap
NAME_B		=	checker

CC			=	gcc 
CFLAGS		=	-Wall -Wextra -Werror 

SRCS_DIR	=	./srcs/
OBJ_DIR		=	./objs/
INC_DIR		=	./includes/

SRCS		= 	push_swap.c
SRCS		+= 	stack_tools.c
SRCS		+= 	instructions.c
SRCS		+= 	parse.c
SRCS		+= 	sort_stack.c
SRCS		+= 	sort_stack_tools.c
SRCS		+= 	positions.c
SRCS		+= 	free_tab.c

SRCS_B		= 	checker.c
SRCS_B		+= 	stack_tools.c
SRCS_B		+= 	instructions.c
SRCS_B		+= 	parse.c
SRCS_B		+= 	sort_stack.c
SRCS_B		+= 	sort_stack_tools.c
SRCS_B		+= 	positions.c
SRCS_B		+= 	free_tab.c



OBJ			=	$(addprefix $(OBJ_DIR),$(SRCS:.c=.o))
OBJ_B		=	$(addprefix $(OBJ_DIR),$(SRCS_B:.c=.o))

INC			=	-I ./includes/ -I libft/includes/


RM			=	/bin/rm -f
RM_DIR		=	/bin/rm -rf

$(OBJ_DIR)%.o:$(SRCS_DIR)%.c $(INC_DIR)*.h
	$(CC) $(CFLAGS)	$(INC) -c $< -o $@

all:
	@mkdir -p $(OBJ_DIR)
	@$(MAKE) $(NAME) --no-print-directory

make_libft:
	@make -C libft/ --no-print-directory

$(NAME): $(OBJ) $(INC_DIR) make_libft
	@$(CC) $(CFLAGS) $(OBJ) ./libft/libft.a $(INC) -o $(NAME)

bonus:
	@mkdir -p $(OBJ_DIR)
	@$(MAKE) $(NAME_B) --no-print-directory

$(NAME_B): $(OBJ_B) $(INC_DIR) make_libft
	@$(CC) $(CFLAGS) $(OBJ_B) ./libft/libft.a  $(INC) -o $(NAME_B)

clean:
	@make clean -C libft/ --no-print-directory
	$(RM_DIR) $(OBJ_DIR)

fclean: clean
	rm -rf ${NAME_B} ${NAME}
	@make fclean -C libft/ --no-print-directory
re: clean all
