# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: huller <huller@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/01 20:42:02 by huller            #+#    #+#              #
#    Updated: 2020/05/24 14:30:03 by huller           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GRN				=	\x1B[32m
MAG				=	\x1B[35m
RES				=	\x1B[0m
YEL			    =   \033[33m

NAME			=	lem-in

# LEM-IN
SRC_PATH		=	srcs/
OBJ_PATH		=	srcs/obj/
INC_PATH		=	includes/

# LIBFT
LIB_PATH		=	libft/
LIB_INC_PATH	=	libft/includes/

# LEM-IN
SRC_NAME		=	main.c utils.c rooms_reader.c reader_tube.c reader.c \
					flow_analyzer.c find_flow.c print_all.c print.c
OBJ_NAME		=	$(SRC_NAME:.c=.o)
INC_NAME		=	lem_in.h

# LIBFT
LIB_NAME		=	libft.a
LIB_INC_NAME	=	libft.h


# LEM-IN
OBJ				=	$(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC				=	$(addprefix $(INC_PATH), $(INC_NAME))

# LIBFT
LIB				=	$(addprefix $(LIB_PATH), $(LIB_NAME))
LIB_INC			=	$(addprefix $(LIB_INC_PATH), $(LIB_INC_NAME))

.PHONY:				all $(LIB_NAME) clean fclean re


all:				$(LIB_NAME) $(NAME)

# LIBFT
$(LIB_NAME):
					@make -C $(LIB_PATH)
# LEM-IN
$(NAME):			$(LIB) $(OBJ)
					@gcc -Wall -Wextra -Werror $(OBJ) \
						-L $(LIB_PATH) -lft -o $(NAME)
					@echo "$(GRN)$(NAME) is created.$(RES)"

# LIBFT
$(LIB):				$(LIB_NAME)

# LEM-IN
$(OBJ_PATH)%.o:		$(SRC_PATH)%.c $(INC) $(LIB_INC)
					@mkdir -p $(OBJ_PATH)
					@gcc -Wall -Wextra -Wextra \
						-I $(INC_PATH) -I $(LIB_INC_PATH) -o $@ -c $<

clean:
					@make -C $(LIB_PATH) fclean
					@rm -f $(OBJ)
					@rm -rf $(OBJ_PATH)
					@echo "$(YEL)$(NAME) objects are deleted.$(RES)"

fclean:				clean
					@rm -f $(NAME)
					@echo "$(MAG)$(NAME) is deleted.$(RES)"

re:					fclean all
