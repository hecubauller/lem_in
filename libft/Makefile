# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/06 18:14:41 by doberyn           #+#    #+#              #
#    Updated: 2019/09/20 00:59:20 by huller           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, $(NAME), norm, clean, fclean, re

RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
PINK = \033[35m
AQUA = \033[36m
GREY = \033[37m
MAG  =   \x1B[35m
RES  = \x1B[0m
UNDERLINE = \033[4m

NAME = libft.a

SRC_PATH = ./sources/
OBJ_PATH = ./objects/
INC_PATH = ./includes/

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I, $(INC_PATH))

SRC_NAME = ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memset.c \
		   ft_memchr.c ft_memcmp.c ft_strlen.c ft_strdup.c ft_strcpy.c \
		   ft_strncpy.c ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c \
		   ft_strrchr.c ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c \
		   ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
		   ft_isprint.c ft_toupper.c ft_tolower.c ft_memalloc.c ft_memdel.c\
		   ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c\
		   ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c\
		   ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_itoa.c ft_putchar.c\
		   ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c\
		   ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		   ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c \
		   ft_lstmap.c ft_strrev.c ft_abs.c ft_factorial.c ft_sqrt.c get_next_line.c\
		   ft_itoa_fp.c mexp.c str_ad.c e_zrs.c ft_ox.c pw.c str_ml.c\
		   fld_edge.c ft_p.c pw_to_str.c t_str.c fr_p.c ft_printf.c reader.c wzrs.c\
	   	   ft_c.c res_o_fr.c zrs.c ft_e.c ft_round.c rnd.c add_z.c int_p.c\
	       rnd_z.c apply_flags.c ft_fld.c rndg.c ft_g.c rndg_z.c c_str.c mantis.c\
	       ft_itoa_base.c s_str.c ft_rg.c res_w_fr.c ft_put_percent.c chck_xu.c\
	       chck_x.c chck_sr.c chck_p.c chck_o.c chck_g.c chck_f.c chck_e.c chck_di.c\
	       chck_c.c chck_b.c chck_u.c ft_u.c ft_s.c ft_free_output.c ft_bufjoin.c\
	       ft_put_out.c ft_solver.c ft_app_d_prs.c ft_add_pl.c ft_solver.c\
	       ft_app_width.c ft_app_fl.c ft_cycle6.c\

OBJ_NAME = $(SRC_NAME:.c=.o)

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@gcc -Wall -Werror -Wextra $(INC) -o $@ -c $<
	@echo -n •

$(NAME): $(OBJ)
	@echo "\n$(YELLOW)'Libft' is ready.$(RES)"
	@ar -rc $(NAME) $?
	@ranlib $(NAME)
	
norm:
	norminette 

clean: 
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -rf $(OBJ_PATH)
	@rm -f $(NAME)
	@echo "$(RED)'Libft' is deleted.$(RES)"

re: fclean all	
