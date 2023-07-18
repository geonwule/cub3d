HEAD = includes

LIBFT_DIR = libft

LIBFT = libft.a

GNL_DIR		= srcs/get_next_line/

_GNL_SRCS	= get_next_line.c \
			  get_next_line_utils.c \

GNL_SRCS	= $(addprefix $(GNL_DIR), $(_GNL_SRCS))

PARSING_DIR	= srcs/parsing/

_PARSING_SRCS	= read_file.c		\
				  check.c			\
				  set.c				\
				  set_color.c		\
				  set_color_utils.c	\
				  check_map.c		\
				  check_map2.c		\

				  

PARSING_SRCS	= $(addprefix $(PARSING_DIR), $(_PARSING_SRCS))

INIT_DIR	= srcs/init/

_INIT_SRCS	=	init_vars_info.c	\
				init_vars.c			\
				init_background.c	\
				load_texture.c		\
				img_xpm_set.c		\


INIT_SRCS	= $(addprefix $(INIT_DIR), $(_INIT_SRCS))


NO_INIT_DIR	= srcs/init/

_NO_INIT_SRCS	=	init_vars_info.c	\
				init_vars.c			\
				init_background.c	\
				no_load_texture.c		\
				no_img_xpm_set.c		\


NO_INIT_SRCS	= $(addprefix $(NO_INIT_DIR), $(_NO_INIT_SRCS))

EVENT_DIR	= srcs/event/

_EVENT_SRCS	= check_key_and_mouse.c		\
			  check_key_and_mouse2.c	\
			  event_function1.c			\
			  event_function2.c			\
			  key_event.c				\
			  manage_monster.c			\
			  kill_monster.c			\
			  mouse_event.c				\
			  print_window1.c			\
			  print_window2.c			\
			  ray_casting.c				\
			  ray_function.c			\
			  ray_function_dda.c		\
			  rendering.c				\
			  mini_map_expan.c 			\
			  mini_map.c				\
			  sprite.c					\
			  sprite2.c \

_NO_EVENT_SRCS	= check_key_and_mouse.c		\
			  check_key_and_mouse2.c	\
			  no_event_function1.c			\
			  event_function2.c			\
			  key_event.c				\
			  manage_monster.c			\
			  kill_monster.c			\
			  mouse_event.c				\
			  print_window1.c			\
			  print_window2.c			\
			  ray_casting.c				\
			  ray_function.c			\
			  ray_function_dda.c		\
			  rendering.c				\
			  mini_map_expan.c 			\
			  mini_map.c				\
			  sprite.c					\
			  sprite2.c \

EVENT_SRCS	= $(addprefix $(EVENT_DIR), $(_EVENT_SRCS))
NO_EVENT_SRCS	= $(addprefix $(EVENT_DIR), $(_NO_EVENT_SRCS))

UTILS_DIR	= srcs/utils/

_UTILS_SRCS	=	print_error.c			\
				free.c					\
				alloc_copy_str.c		\
				size_arr_2d.c			\
				random_generator.c		\
				ft_malloc.c				\
				ft_open.c				\
				free_vars.c				\
				exit_game.c				\
				ft_get_data_addr.c		\
				ft_xpm_file_to_image.c	\

UTILS_SRCS	= $(addprefix $(UTILS_DIR), $(_UTILS_SRCS))


TEST_DIR	= srcs/test/

_TEST_SRCS	= print.c \

TEST_SRCS	= $(addprefix $(TEST_DIR), $(_TEST_SRCS))

SRCS = srcs/main.c \
	   ${PARSING_SRCS} \
	   ${GNL_SRCS} \
	   ${INIT_SRCS} \
	   ${EVENT_SRCS} \
	   ${TEST_SRCS} \
	   ${UTILS_SRCS} \

NO_SRCS = srcs/main_no_arg.c \
	   ${PARSING_SRCS} \
	   ${GNL_SRCS} \
	   ${NO_INIT_SRCS} \
	   ${NO_EVENT_SRCS} \
	   ${TEST_SRCS} \
	   ${UTILS_SRCS} \

BONUS_SRCS = \

OBJS_DIR	= objs

#OBJS = ${SRCS:.c=.o}
OBJS		=	$(SRCS:%.c=$(OBJS_DIR)/%.o)
NO_OBJS		=	$(NO_SRCS:%.c=$(OBJS_DIR)/%.o)

BONUS_OBJS = ${BONUS_SRCS:.c=.o}

#my m1
#MLXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

#cluster
MLXFLAGS = -Lmlx_opengl -lmlx -framework OpenGL -framework AppKit

#-L${MLXDIR} -lmlx -I${MLXDIR} -lX11 -lXext

CC = cc -g

CFLAGS = -Wall -Wextra -Werror

DEBUG_FLAG = -fsanitize=address  -g
#-fsanitize=undefined  -g
#-O2

NAME = cub3D
NO_NAME = nocub

BONUS_NAME = bonus_cub3d

#color
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

all : ${NAME}

#%.o : %.c
#	@${CC} ${CFLAGS} -c $< -o $@ -I ${HEAD}

$(OBJS_DIR)/%.o	: 	%.c
			@mkdir -p $(@D)
			@${CC} ${CFLAGS} -c $< -o $@ -I ${HEAD}
#			@cc $(CFLAGS) -c $^ $(HEAD) -o $@
#			@echo "${YELLOW}Compiling $<${END}"

${NAME} : ${OBJS}
	@make -C ${LIBFT_DIR}
	@cp ${LIBFT_DIR}/${LIBFT} .
	@echo "$(GREEN)libft compiled!$(DEF_COLOR)"
	@${CC} ${CFLAGS} $^ ${MLXFLAGS} ${LIBFT} -o ${NAME}
	@echo "$(GREEN)cub_3d compiled!$(DEF_COLOR)"

no : ${NO_OBJS}
	@make -C ${LIBFT_DIR}
	@cp ${LIBFT_DIR}/${LIBFT} .
	@echo "$(GREEN)libft compiled!$(DEF_COLOR)"
	@${CC} ${CFLAGS} $^ ${MLXFLAGS} ${LIBFT} -o ${NO_NAME}
	@echo "$(GREEN)cub_3d compiled!$(DEF_COLOR)"

bonus : ${BONUS_OBJS}
	@${CC} ${CFLAGS} $^ ${MLXFLAGS} ${LIBFT} -o ${BONUS_NAME}
	@echo "$(GREEN)cub_3d_bonus_compiled!$(DEF_COLOR)"

debug : ${OBJS}
	@${CC} ${DEBUG_FLAG} $^ ${MLXFLAGS} ${LIBFT} -o ${NAME}
	@echo "$(GREEN)debug compiled!$(DEF_COLOR)"

clean :
	@make clean -C ${LIBFT_DIR}
	@rm -rf ${OBJS_DIR}
	@rm -f ${BONUS_OBJS}
	@echo "$(BLUE)libft object files cleaned!$(DEF_COLOR)"
	@echo "$(BLUE)cub_3d object files cleaned!$(DEF_COLOR)"

fclean : clean
	@make fclean -C ${LIBFT_DIR}
	@rm -f ${LIBFT}
	@rm -f ${NAME}
	@rm -f ${NO_NAME}
	@rm -f ${BONUS_NAME}
	@rm -f debug
	@echo "$(YELLOW)libft library files cleaned!$(DEF_COLOR)"
	@echo "$(YELLOW)cub_3d library files cleaned!$(DEF_COLOR)"

re :
	${MAKE} fclean
	${MAKE} all
	@echo "$(MAGENTA)Cleaned and rebuilt everything for cub_3d!$(DEF_COLOR)"

.PHONY : all clean fclean re bonus debug
