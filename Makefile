# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/30 17:48:56 by dkurcbar          #+#    #+#              #
#    Updated: 2023/11/07 17:39:02 by dkurcbar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

	#Paths
SRCS_PATH	=	src#		
SRCS_PATH_M	=	src_m#		
SRCS_PATH_B	=	src_b#										# the path to your sources without ending /
BIN_PATH  	=	bin#		
INCS_PATH	=	include#	


	# Common Variables #
SRC     	= $(wildcard $(SRCS_PATH)/*.c)#		
BIN_OBJ		= $(SRC:$(SRCS_PATH)%.c=$(BIN_PATH)%.o)#

	# Mandatory Variables #
SRC_M		= $(wildcard $(SRCS_PATH_M)/*.c)#
BIN_OBJ_M	= $(SRC_M:$(SRCS_PATH_M)%.c=$(BIN_PATH)%.o)#

	# Bonus Variables #
SRC_B		= $(wildcard $(SRCS_PATH_B)/*.c)#
BIN_OBJ_B	= $(SRC_B:$(SRCS_PATH_B)%.c=$(BIN_PATH)%.o)#
INCLUDE 	= include/philosophers.h

INC_LIB	:=	 -I$(INCS_PATH) 

CC		:=	gcc
CFLAG	:=	-Wall -Werror -Wextra -g #-fsanitize=thread
AR		:=	ar rcs
RM		:=	rm -f

all: 
	@mkdir -p bin
	@$(MAKE) --no-print-directory $(NAME)

$(NAME):  $(BIN_OBJ) $(BIN_OBJ_M) $(INCLUDE)  Makefile
	@$(CC) $(CFLAG) $(BIN_OBJ) $(BIN_OBJ_M) $(INC_LIB) $(FRAME) -g -o $(NAME) 
	@printf "$(_SUCCESS) $(NAME) compiled.\n"

	
	
$(BIN_PATH)/%.o: $(SRCS_PATH)/%.c $(INCLUDE) Makefile
	@$(CC) $(CFLAG) $(INC_LIB)  -c $< -o $@  && echo "Compiled: $< -> $@"

$(BIN_PATH)/%.o: $(SRCS_PATH_M)/%.c $(INCLUDE) Makefile
	@$(CC) $(CFLAG) $(INC_LIB)  -c $< -o $@  && echo "Compiled: $< -> $@"



clean:
	@ ${RM} ${BIN_OBJ}
	@$(foreach obj,${OBJ},echo "File deleted: ${obj}";)
	@printf "$(_INFO) Binary Files $(NAME) removed.\n"

fclean: 
	@ $(MAKE) clean
	@ $(RM) $(NAME) 
	@printf "$(_INFO) $(NAME) removed.\n"

re:	fclean all

.PHONY: all clean fclean re 

