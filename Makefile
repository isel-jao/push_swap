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
SRCS		+= 	ft_memmove.c
SRCS		+= 	ft_putstr.c
SRCS		+= 	ft_putendl.c
SRCS		+= 	ft_memcpy.c
SRCS		+= 	ft_strcmp.c

SRCS_B		= 	checker.c
SRCS_B		+= 	stack_tools.c
SRCS_B		+= 	instructions.c
SRCS_B		+= 	parse.c
SRCS_B		+= 	sort_stack.c
SRCS_B		+= 	sort_stack_tools.c
SRCS_B		+= 	positions.c
SRCS_B		+= 	ft_memmove.c
SRCS_B		+= 	ft_putstr.c
SRCS_B		+= 	ft_putendl.c
SRCS_B		+= 	ft_memcpy.c
SRCS_B		+= 	ft_strcmp.c



OBJ			=	$(addprefix $(OBJ_DIR),$(SRCS:.c=.o))
OBJ_B		=	$(addprefix $(OBJ_DIR),$(SRCS_B:.c=.o))

INC			=	-I ./includes/ 


RM			=	/bin/rm -f
RM_DIR		=	/bin/rm -rf

$(OBJ_DIR)%.o:$(SRCS_DIR)%.c $(INC_DIR)*.h
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

all:
	@mkdir -p $(OBJ_DIR)
	@$(MAKE) $(NAME) --no-print-directory

$(NAME): $(OBJ) $(INC_DIR) 
	@$(CC) $(CFLAGS) $(OBJ) $(INC) -o $(NAME)

bonus:
	@mkdir -p $(OBJ_DIR)
	@$(MAKE) $(NAME_B) --no-print-directory

$(NAME_B): $(OBJ_B) $(INC_DIR) 
	@$(CC) $(CFLAGS) $(OBJ_B) $(INC) -o $(NAME_B)

clean:
	$(RM_DIR) $(OBJ_DIR)

fclean: clean
	rm -rf ${NAME_B} ${NAME}
re: clean all