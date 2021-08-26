# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/07 14:21:44 by pitriche          #+#    #+#              #
#    Updated: 2021/07/23 11:29:25 by pitriche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREY	= \033[030m
RED		= \033[031m
GREEN	= \033[032m
YELLOW	= \033[033m
BLUE	= \033[034m
MAGENTA	= \033[035m
CYAN	= \033[036m
RESET	= \033[0m

# **************************************************************************** #

NAME = 42run

CLASSES=	\
All		\
Display	\
Event	\
Game	\
Matrix	\
OpenGL	\
Time	\
Utils	\

CLASSES_HEADERS= $(addsuffix .hpp, $(CLASSES))
CLASSES_SRCS= $(addsuffix .cpp, $(CLASSES))

HEADERS = $(CLASSES_HEADERS) \
Defines.hpp	\

SRC_FILES = $(CLASSES_SRCS)	\
main.cpp		\


# **************************************************************************** #

CC = clang++

FL_OPTI = -O3 -flto
FLAGS = -Wall -Wextra -Wconversion -Wunused -std=c++11 $(FL_OPTI) \
-D 'GL_SILENCE_DEPRECATION='
# MacOS is a demon spawned low class abomination

CFLAGS = -c $(FLAGS)

SDL_DIR = frameworks
FRAMEWORKS = -F $(SDL_DIR) -framework SDL2 -Wl,-rpath $(SDL_DIR) \
-framework OpenGL

CINCLUDE = -I include -I frameworks/SDL2.framework/headers \

SRC_DIR = src/
SRC := $(addprefix $(SRC_DIR), $(SRC_FILES))

INCLUDE_DIR = include/
INCLUDE := $(addprefix $(INCLUDE_DIR), $(HEADERS))

OBJ_FILES = $(patsubst %.cpp, %.o, $(SRC_FILES))
OBJ_DIR = obj/
OBJ := $(addprefix $(OBJ_DIR), $(OBJ_FILES))

all: $(NAME)
	@echo "$(CYAN)$(NAME) ready sir !$(RESET)"

$(NAME): $(LIB) $(OBJ_DIR) $(OBJ)
	@echo "$(GREEN)objects done sir !$(RESET)"
	@$(CC) $(FRAMEWORKS) $(LFLAGS) -o $(NAME) $(OBJ)
	@echo "$(GREEN)$(NAME) compiled sir !$(RESET)"

$(OBJ_DIR)%.o : $(SRC_DIR)%.cpp $(INCLUDE)
	@$(CC) $(CINCLUDE) $(CFLAGS) -o $@ $<
	@echo -n '.'

$(OBJ_DIR) :
	@mkdir $(OBJ_DIR)
	@echo "$(GREEN)Object directory created sir !$(RESET)"

clean:
	@rm -f $(OBJ)
	@echo "$(RED)Objects deleted sir !$(RESET)"
	@rm -rf $(OBJ_DIR)
	@#echo "$(RED)Object directory deleted sir !$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) deleted sir !$(RESET)"

re: fclean all
