# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: huller <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 00:32:42 by huller            #+#    #+#              #
#    Updated: 2019/06/24 14:10:43 by huller           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	lem-in

# LEM-IN

SRC_PATH		=	srcs/
OBJ_PATH		=	srcs/obj/
INC_PATH		=	includes/

# LIBFT

LIB_PATH		=	libft/
LIB_INC_PATH	=	libft/includes/

# LEM-IN

SRC_NAME		=	main.c utils.c reader_room.c reader_tube.c reader.c \
					analyze_current_flow.c find_best_flow.c fast_print.c print.c
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

.PHONY:				all $(LIB_NAME) clean fclean re ant


all:				$(LIB_NAME) $(NAME) $(NAME2)

# LIBFT

$(LIB_NAME):
					@make -C $(LIB_PATH)
# LEM-IN

$(NAME):			$(LIB) $(OBJ)
					@gcc -Wall -Wextra -Werror $(OBJ) \
						-L $(LIB_PATH) -lft -o $(NAME)
					@echo "$(GRN)\nLinking [ $(NAME) ] SUCCESS$(RES)"

# LIBFT

$(LIB):				$(LIB_NAME)

# LEM-IN

$(OBJ_PATH)%.o:		$(SRC_PATH)%.c $(INC) $(LIB_INC)
					@mkdir -p $(OBJ_PATH)
					@gcc -Wall -Wextra -Wextra \
						-I $(INC_PATH) -I $(LIB_INC_PATH) -o $@ -c $<
					@echo ".\c"

clean:
					@make -C $(LIB_PATH) fclean
					@rm -f $(OBJ)
					@rm -rf $(OBJ_PATH)
					@echo "$(MAG)Cleaning [ $(NAME) ] OK$(RES)"

fclean:				clean
					@rm -f $(NAME)
					@echo "$(MAG)Delete [ $(NAME) ] OK$(RES)"

re:					fclean all
