# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rolevy <rolevy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/28 13:14:01 by rolevy            #+#    #+#              #
#    Updated: 2018/06/24 15:27:50 by rolevy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ============================================================================ #
#								   Variable									   #
# ============================================================================ #

NOM	=libmlx.a
SRC	=	mlx_shaders.c				\
		mlx_new_window.m			\
		mlx_init_loop.m				\
		mlx_new_image.m				\
		mlx_xpm.c					\
		mlx_int_str_to_wordtab.c
INC	= ./mlx.h

OBJ1	=	$(SRC:.c=.o)
OBJ		=	$(OBJ1:.m=.o)
CFLAGS+	=	-O2 -frameword OpenGL

# ============================================================================ #
#									Strings									   #
# ============================================================================ #

NRM				=	"\033[0m"
PROJECT_COLOR	=	"\x1b[35m"
RED				=	"\033[38;2;223;12;42m"
GREY			=	"\033[38;2;100;100;100m"
GREEN			=	"\033[38;2;50;200;26m"

OK = $(GREY)"["$(GREEN)" ✓ "$(GREY)"]"$(NRM)
KO = $(GREY)"["$(RED)" ✘ "$(GREY)"]"$(NRM)
HD = $(GREY)"["$(PROJECT_COLOR)"MLX"$(GREY)"]"$(NRM)

MAKING_PROGRESS	=	$(HD)" Generating "$(NOM)"...\n"$(NRM)
MAKING_SUCCESS	=	$(HD)" "$(OK)" "$(NOM)" generated!\n"$(NRM)
MAKING_FAILURE	=	$(HD)" "$(KO)" "$(NOM)" generation failure!\n"$(NRM)

MAKING_ARCHIVE	=	$(HD)" Making "$(NOM)" archive...\n"$(NRM)
MAKING_OPTIM	=	$(HD)" Optimizing "$(NOM)" archive...\n"$(NRM)

COMPILING_SUCCESS = $(HD)" "$(OK)" "$(GREEN)"$@\n"$(NRM)
COMPILING_FAILURE = $(HD)" "$(KO)" "$(RED)" * - "$(GREY)"$@ "$(KO)"\n"

CLEANING_OBJECTS	=	$(HD)" Cleaning obj ""\n"$(NRM)
CLEANING_BINARY		=	$(HD)" CLeaning "$(NOM)"\n"$(NRM)


# ============================================================================ #
#									Rules									   #
# ============================================================================ #

all: $(NOM)

$(NOM):	$(OBJ)
	@printf $(MAKING_ARCHIVE)
	@ar rc $(NOM) $(OBJ) && printf $(MAKING_OPTIM) && ranlib $(NOM); \
		if [ $$? != 1 ]; then printf $(MAKING_SUCCESS); exit 0; \
		else printf $(MAKING_FAILURE); exit 2; fi;

%.o : %.c $(INC)
	@$(CC) -c $< -o ./$@ $(CFLAGS); \
		if [ $$? != 1 ]; then printf $(COMPILING_SUCCESS); exit 0; \
		else printf $(COMPILING_FAILURE) exit 2; fi;

%.o : %.m $(INC)
	@$(CC) -c $< -o ./$@ $(CFLAGS); \
		if [ $$? != 1 ]; then printf $(COMPILING_SUCCESS); exit 0; \
		else printf $(COMPILING_FAILURE) exit 2; fi;

clean:
	@printf $(CLEANING_OBJECTS)
	@rm -f $(NOM) $(OBJ) *~

fclean: clean
	@printf $(CLEANING_BINARY)
	@rm -f mlx_app

re: fclean all
