# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rolevy <rolevy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/16 15:54:42 by rolevy            #+#    #+#              #
#    Updated: 2018/05/22 17:14:07 by rolevy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libgnl.a
SRC		= get_next_line.c
OFILE	= $(SRC:.c=.o)
INC		= get_next_line.h


ARG_O 	= $(addprefix $(PATH_DUMP),$(notdir $(SRC:.c=.o)))
PATH_DUMP	= dump/


NRM = "\033[0m"
PROJECT_COLOR = "\x1b[36m"
RED = "\033[38;2;223;12;42m"
GREY = "\033[38;2;100;100;100m"
GREEN = "\033[38;2;50;200;26m"

OK = $(GREY)"["$(GREEN)" ✓ "$(GREY)"]"$(NRM)
KO = $(GREY)"["$(RED)" ✘ "$(GREY)"]"$(NRM)
HD = $(GREY)"["$(PROJECT_COLOR)"GNL"$(GREY)"]"$(NRM)

MAKING_PROGRESS = $(HD)" Generating "$(NAME)"...\n"$(NRM)
MAKING_ARCHIVE = $(HD)" Making "$(NAME)" archive...\n"$(NRM)
MAKING_OPTIM = $(HD)" Optimizing "$(NAME)" archive...\n"$(NRM)
MAKING_SUCCESS = $(HD)" "$(OK)" "$(NAME)" generated!\n"$(NRM)
MAKING_FAILURE = $(HD)" "$(KO)" "$(NAME)" generation failure!\n"$(NRM)

COMPILING_SUCCESS = $(HD)" "$(OK)" "$(GREEN)"$@\n"$(NRM)
COMPILING_FAILURE = $(HD)" "$(KO)" "$(RED)" * - "$(GREY)"$@ "$(KO)"\n"

CLEANING_OBJECTS = $(HD)" Cleaning dumps "$(GREY)"("$(PATH_DUMP)")\n"$(NRM)
CLEANING_BINARY = $(HD)" CLeaning "$(NAME)"\n"$(NRM)

vpath %.o $(PATH_DUMP)

all: $(NAME)

$(NAME): $(OFILE) | $(INC)
	@printf $(MAKING_ARCHIVE)
	@ar rc $(NAME) $(ARG_O) && printf $(MAKING_OPTIM) && ranlib $(NAME); \
		if [ $$? != 1 ]; then printf $(MAKING_SUCCESS); exit 0; \
		else printf $(MAKING_FAILURE); exit 2; fi;

%.o : %.c $(INC) | $(PATH_DUMP)
	@$(CC) -c $< -o $(PATH_DUMP)$@ $(CFLAGS); \
		if [ $$? != 1 ]; then printf $(COMPILING_SUCCESS); exit 0; \
		else printf $(COMPILING_FAILURE) exit 2; fi;

clean:
	@printf $(CLEANING_OBJECTS)
	@rm -f $(ARG_O)

fclean: clean
	@printf $(CLEANING_BINARY)
	@rm -f $(NAME)

re: fclean all