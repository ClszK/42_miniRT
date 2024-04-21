NAME		= 	miniRT

LIB_DIR		=	lib
SRCS_DIR	=	srcs
OBJS_DIR	=	obj
INC_DIR		=	includes	

LIBFT_DIR	=	$(LIB_DIR)/libft
MLX_DIR		=	$(LIB_DIR)/minilibx_opengl_20191021

SRCS_MAIN	=	main.c\
				utils.c
SRCS_VEC	= 	vec3_operator.c\
				vec3_operator2.c\
				vec3_utils.c
SRCS_MLX	=	my_mlx_utils.c\
				camera_utils.c
SRCS_RAY	=	ray_utils.c
SRCS_OBJ	=	object_utils.c\
				sphere.c
SRCS_DLS	=	double_lst.c\
				double_lst2.c
SRCS_LIGHT	=	light_utils.c

SRCS		=	$(SRCS_MAIN)\
				$(addprefix vec3/, $(SRCS_VEC))\
				$(addprefix views/, $(SRCS_MLX))\
				$(addprefix ray/, $(SRCS_RAY))\
				$(addprefix objects/, $(SRCS_OBJ))\
				$(addprefix double/, $(SRCS_DLS))\
				$(addprefix light/, $(SRCS_LIGHT))
				
OBJS		=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))\

CC			=	cc
CFLAGS		=	-Werror -Wall -Wextra -g3 -fsanitize=address
CPPFLAGS	=	-I$(LIBFT_DIR) -I$(MLX_DIR) -I$(INC_DIR)
CLIB		=	-L$(MLX_DIR) -lmlx -framework OpenGL -framework Appkit

all:	$(NAME)

$(NAME)	:	$(OBJS) 
	@make -C $(LIBFT_DIR)
	@make -C $(MLX_DIR)
	$(CC) $(OBJS) $(CFLAGS) $(CLIB) -L$(LIBFT_DIR) -lft -o $(NAME)

$(OBJS_DIR) :
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/vec3
	@mkdir -p $(OBJS_DIR)/views
	@mkdir -p $(OBJS_DIR)/ray
	@mkdir -p $(OBJS_DIR)/objects
	@mkdir -p $(OBJS_DIR)/double
	@mkdir -p $(OBJS_DIR)/light

$(OBJS_DIR)/%.o	:	$(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -rf $(NAME)
	@cd $(LIBFT_DIR) && make fclean
re: 
	make fclean
	make all

.PHONY: all clean fclean re 