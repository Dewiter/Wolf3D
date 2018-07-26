# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rolevy <rolevy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/11 20:25:27 by rolevy            #+#    #+#              #
#    Updated: 2018/07/09 07:18:25 by rolevy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
CFLAGS	= -Wall -Wextra -Werror -march=native -g3 -fsanitize=address -O0 #-O3 -flto

SRC	=		ft_atoi.c		\
			ft_abs.c		\
			ft_bzero.c		\
			ft_isalnum.c	\
			ft_isalpha.c	\
			ft_isascii.c	\
			ft_isdigit.c	\
			ft_isprint.c	\
			ft_isspace.c	\
			ft_itoa.c		\
			ft_lstadd.c		\
			ft_lstdel.c		\
			ft_lstdelone.c	\
			ft_lstiter.c	\
			ft_lstmap.c		\
			ft_lstnew.c		\
			ft_memalloc.c	\
			ft_memccpy.c	\
			ft_memchr.c		\
			ft_memcmp.c		\
			ft_memcpy.c		\
			ft_memcpy_rev.c \
			ft_memdel.c		\
			ft_memmove.c	\
			ft_memset.c		\
			ft_power.c		\
			ft_putchar.c	\
			ft_putchar_fd.c \
			ft_putendl.c	\
			ft_putendl_fd.c \
			ft_putnbr.c		\
			ft_putnbr_fd.c	\
			ft_putstr.c		\
			ft_putstr_fd.c	\
			ft_sqrt.c		\
			ft_strcat.c		\
			ft_strncat.c	\
			ft_strchr.c		\
			ft_strclr.c		\
			ft_strcmp.c		\
			ft_strcpy.c		\
			ft_strdel.c		\
			ft_strdup.c		\
			ft_strequ.c		\
			ft_striter.c	\
			ft_striteri.c	\
			ft_strjoin.c	\
			ft_strlcat.c	\
			ft_strlen.c		\
			ft_strmap.c		\
			ft_strmapi.c	\
			ft_strncat.c	\
			ft_strncmp.c	\
			ft_strncpy.c	\
			ft_strndup.c	\
			ft_strnequ.c	\
			ft_strnew.c		\
			ft_strstr.c		\
			ft_strsub.c		\
			ft_strtrim.c	\
			ft_strnstr.c	\
			ft_strrchr.c	\
			ft_strsplit.c	\
			ft_tolower.c	\
			ft_toupper.c	\

OFILE	= $(SRC:.c=.o)
INC		= libft.h


ARG_O 		= $(addprefix $(PATH_DUMP),$(notdir $(SRC:.c=.o)))
PATH_DUMP	= dump/


# ============================================================================ #
#									Strings		   							   #
# ============================================================================ #

NRM = "\033[0m"
PROJECT_COLOR = "\033[38;2;75;150;225m"
RED = "\033[38;2;223;12;42m"
GREY = "\033[38;2;100;100;100m"
GREEN = "\033[38;2;50;200;26m"

OK = $(GREY)"["$(GREEN)" ✓ "$(GREY)"]"$(NRM)
KO = $(GREY)"["$(RED)" ✘ "$(GREY)"]"$(NRM)
HD = $(GREY)"["$(PROJECT_COLOR)"LFT"$(GREY)"]"$(NRM)

MAKING_PROGRESS = $(HD)" Generating "$(NAME)"...\n"$(NRM)
MAKING_ARCHIVE = $(HD)" Making "$(NAME)" archive...\n"$(NRM)
MAKING_OPTIM = $(HD)" Optimizing "$(NAME)" archive...\n"$(NRM)
MAKING_SUCCESS = $(HD)" "$(OK)" "$(NAME)" generated!\n"$(NRM)
MAKING_FAILURE = $(HD)" "$(KO)" "$(NAME)" generation failure!\n"$(NRM)

COMPILING_SUCCESS = $(HD)" "$(OK)" "$(GREEN)"$@\n"$(NRM)
COMPILING_FAILURE = $(HD)" "$(KO)" "$(RED)" * - "$(GREY)"$@ "$(KO)"\n"

CLEANING_OBJECTS = $(HD)" Cleaning dumps "$(GREY)"("$(PATH_DUMP)")\n"$(NRM)
CLEANING_BINARY = $(HD)" CLeaning "$(NAME)"\n"$(NRM)

# ============================================================================ #
#									Process									   #
# ============================================================================ #

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

fclean:
	@printf $(CLEANING_BINARY)
	@rm -f $(NAME)

re: clean all