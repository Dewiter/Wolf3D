# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rolevy <rolevy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/01 12:39:14 by rolevy            #+#    #+#              #
#    Updated: 2018/07/26 10:40:55 by rolevy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# ============================================================================ #
#								   Variable									   #
# ============================================================================ #

NAME		= wolf3d

CC			= clang $(sdl2-config --cflags) $(sdl2-config --libs)
CFLAGS		= $(SANITIZE) $(sdl2-config --cflags) $(sdl2-config --libs) -Wall -Wextra -Werror 
FLAGS		= $(FRAMEWORK) $(THREAD)
SANITIZE	= -fsanitize=address -g
FRAMEWORK	= -framework OpenGL -framework Appkit


LOGO		= ./assets/logo/logo

SRC			=	main.c						\
				env.c						\
				bind_hub.c					\
				quit.c						\
				map_parser.c				\
				set_var.c					\
				raycast.c					\
				draw_texture.c				\
				move.c						\
				texture.c					\
				memory.c					\
				fullscreen.c

INC			=	header.h					\
			/Users/rolevy/.brew/Cellar/sdl2/2.0.8/include/SDL2/SDL.h \
			/Users/rolevy/.brew/Cellar/sdl2_image/2.0.3/include/SDL2/SDL_image.h

DEP			=	-L $(PATH_LIB) -lft			\
				-L $(PATH_MLX) -lmlx		\
				-L $(PATH_GNL) -lgnl		\
				-L ~/.brew/lib -lSDL2 -lSDL2_image \
				$(FRAMEWORK) $(THREAD)		\

MAKE_DEP 	=	1

DEPENDENCIES=	make -C $(PATH_LIB) $(INSTRUCTION); \
				make -C $(PATH_MLX) $(INSTRUCTION); \
				make -C $(PATH_GNL) $(INSTRUCTION); \
				# /Users/rolevy/.brew/Cellar/sdl2_image/2.0.3/lib/libSDL2_image.a

PATH_SRC	= src/
PATH_MAPS	= Maps/
PATH_INC	= includes/
PATH_LIB	= import/libft/
PATH_MLX	= import/minilibx/
PATH_GNL	= import/GNL/
PATH_DUMP	= dump/

SRC_O = $(SRC:.c=.o)
ARG_O = $(addprefix $(PATH_DUMP),$(notdir $(SRC:.c=.o)))

# ============================================================================ #
#									Strings									   #
# ============================================================================ #

NRM = "\033[0m"
PROJECT_COLOR = "\033[38;2;233;175;23m"
RED = "\033[38;2;223;12;42m"
GREY = "\033[38;2;100;100;100m"
GREEN = "\033[38;2;50;200;26m"

OK = $(GREY)"["$(GREEN)" ✓ "$(GREY)"]"$(NRM)
KO = $(GREY)"["$(RED)" ✘ "$(GREY)"]"$(NRM)
HD = $(GREY)"["$(PROJECT_COLOR)"W3D"$(GREY)"]"$(NRM)

MAKING_PROGRESS = $(HD)" Generating "$(NAME)"...\n"$(NRM)
MAKING_SUCCESS = $(HD)" "$(OK)" "$(NAME)" generated!\n"$(NRM)
MAKING_FAILURE = $(HD)" "$(KO)" "$(NAME)" generation failure!\n"$(NRM)
MAKING_LIBFT = $(HD)" Changing make subdirectory -> "$(PATH_LIB)"\n"$(NRM)
MAKING_MLX = $(HD)" Changing make subdirectory -> "$(PATH_MLX)"\n"$(NRM)

COMPILING_SUCCESS = $(HD)" "$(OK)" "$(GREEN)"$@\n"$(NRM)
COMPILING_FAILURE = $(HD)" "$(KO)" "$(RED)" * - "$(GREY)"$@ "$(KO)"\n"

CLEANING_OBJECTS = $(HD)" Cleaning dumps "$(GREY)"("$(PATH_DUMP)")\n"$(NRM)
CLEANING_BINARY = $(HD)" CLeaning "$(NAME)"\n"$(NRM)

# ============================================================================ #
#									Path									   #
# ============================================================================ #

vpath %.c $(PATH_SRC)
vpath %.o $(PATH_DUMP)
vpath %.h $(PATH_INC)

# ============================================================================ #
#									Process									   #
# ============================================================================ #

$(NAME) : $(SRC_O) | $(INC)
	@$(eval INSTRUCTION := all)
	@if [ $(MAKE_DEP) == 1 ] ; then $(DEPENDENCIES) fi;
	@printf $(MAKING_PROGRESS)
	@$(CC) -o $(NAME) $(ARG_O) $(DEP) $(SANITIZE) $(FLAGS) $(CFLAGS); \
		if [ $$? != 1 ]; then printf $(MAKING_SUCCESS); exit 0; \
		else printf $(MAKING_FAILURE); exit 2; fi;

all : $(NAME)
	@echo $(PROJECT_COLOR)
	@cat $(LOGO)
	@echo $(NRM)

%.o : %.c $(INC) | $(PATH_DUMP)
	@$(CC) -c $< -o $(PATH_DUMP)$@ $(SANITIZE) $(CFLAGS); \
		if [ $$? != 1 ]; then printf $(COMPILING_SUCCESS); exit 0; \
		else printf $(COMPILING_FAILURE); exit 2; fi;

$(PATH_DUMP) :
	@mkdir $@

clean :
	@$(eval INSTRUCTION := clean)
	@if [ $(MAKE_DEP) == 1 ] ; then $(DEPENDENCIES) fi;
	@printf $(CLEANING_OBJECTS)
	@rm -f $(ARG_O)

fclean : clean
	@$(eval INSTRUCTION := fclean)
	@if [ $(MAKE_DEP) == 1 ] ; then $(DEPENDENCIES) fi;
	@printf $(CLEANING_BINARY)
	@rm -f $(NAME)
	@rm -rf $(NAME).dSYM

re : fclean all
