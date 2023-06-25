HEAD = includes

LIBFT_DIR = libft

LIBFT = libft.a

GNL_DIR		= srcs/get_next_line/

_GNL_SRCS	= get_next_line.c \
			  get_next_line_utils.c \

GNL_SRCS	= $(addprefix $(GNL_DIR), $(_GNL_SRCS))

FUNC_DIR	= srcs/function/

_FUNC_SRCS	= function.c \
			  ft_lstcub.c \

FUNC_SRCS	= $(addprefix $(FUNC_DIR), $(_FUNC_SRCS))

PARSING_DIR	= srcs/parsing/

_PARSING_SRCS	= read_file.c \
				  free.c \
				  set.c \
				  utils.c \
				# map_read.c \
				# map_error.c \

PARSING_SRCS	= $(addprefix $(PARSING_DIR), $(_PARSING_SRCS))

INIT_DIR	= srcs/init/

_INIT_SRCS	= vars_init.c \
			  background_init.c \

INIT_SRCS	= $(addprefix $(INIT_DIR), $(_INIT_SRCS))

EVENT_DIR	= srcs/event/

_EVENT_SRCS	= key_event.c \
			  mouse_event.c \
			  rendering.c \
			  map_set.c \

EVENT_SRCS	= $(addprefix $(EVENT_DIR), $(_EVENT_SRCS))

TEST_DIR	= srcs/test/

_TEST_SRCS	= print.c \

TEST_SRCS	= $(addprefix $(TEST_DIR), $(_TEST_SRCS))

SRCS = srcs/main.c \
	   ${PARSING_SRCS} \
	   ${FUNC_SRCS} \
	   ${GNL_SRCS} \
	   ${INIT_SRCS} \
	   ${EVENT_SRCS} \
	   ${TEST_SRCS} \

BONUS_SRCS = \

OBJS_DIR	= objs

#OBJS = ${SRCS:.c=.o}
OBJS		=	$(SRCS:%.c=$(OBJS_DIR)/%.o)

BONUS_OBJS = ${BONUS_SRCS:.c=.o}

#my m1
#MLXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

#cluster
MLXFLAGS = -Lmlx_opengl -lmlx -framework OpenGL -framework AppKit

#-L${MLXDIR} -lmlx -I${MLXDIR} -lX11 -lXext

CC = cc

CFLAGS = -g
#-Wall -Wextra -Werror

DEBUG_FLAG = -fsanitize=address  -g
#-O2

NAME = cub3d

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
	@rm -f ${BONUS_NAME}
	@rm -f debug
	@echo "$(YELLOW)libft library files cleaned!$(DEF_COLOR)"
	@echo "$(YELLOW)cub_3d library files cleaned!$(DEF_COLOR)"

re :
	${MAKE} fclean
	${MAKE} all
	@echo "$(MAGENTA)Cleaned and rebuilt everything for cub_3d!$(DEF_COLOR)"

.PHONY : all clean fclean re bonus debug
