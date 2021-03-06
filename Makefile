# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/11 18:07:15 by mmerabet          #+#    #+#              #
#    Updated: 2018/01/28 22:39:17 by mmerabet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ft_ls
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra

LIBFTD		=	libft
LIBFT		=	$(LIBFTD)/libft.a

_FT_LSS	=		main.c ls_getoptions.c ls_getmodes.c ls_getnames.c \
				ls_getfile.c ls_cmpfile.c ls_formatfiles.c ls_filecolors.c \
				ls_printlong.c ls_printnormal.c ls_listfiles.c \
				ls_cmpfile_two.c \

SRCD		=	srcs/
ICLD		=	-Iincludes -I$(LIBFTD)/includes
FT_LSS		=	$(patsubst %,$(SRCD)/%,$(_FT_LSS))
_FT_LSO		=	$(_FT_LSS:.c=.o)
FT_LSO		=	$(FT_LSS:.c=.o)

SRCS		=	$(FT_LSS)
_OBJS		=	$(_FT_LSO)
OBJD		=	objs/
OBJS		=	$(addprefix $(SRCD),$(_OBJS))
OBJB		=	$(addprefix $(OBJD),$(_OBJS))

# COLORS
_GREY=\x1b[30m
_RED=\x1b[38;5;220m
_GREEN=\x1b[32m
_YELLOW=\x1b[33m
_BLUE=\x1b[34m
_PURPLE=\x1b[35m
_CYAN=\x1b[36m
_WHITE=\x1b[37m
_END=\x1b[0m
_SUCCESS=$(_RED)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJB)
	@echo "$(_RED)Compiling$(_END) $(NAME)$(_RED)...$(_END)"
	@$(CC) $(CFLAGS) $^ -o $(NAME) $(LIBFT) -lacl
	@echo  "$(NAME) : $(_SUCCESS)done$(_END)"

$(LIBFT):
	@make -C $(LIBFTD)

$(OBJD)%.o: $(SRCD)%.c
	@mkdir -p $(OBJD)
	@$(CC) $(CFLAGS) -o $@ -c $< $(ICLD)

clean:
	@make -C $(LIBFTD) clean
	@echo "$(NAME) clean: $(_RED)done$(_END)"
	@/bin/rm -f $(OBJB)

fclean: clean
	@make -C $(LIBFTD) fclean
	@echo "$(NAME) fclean: $(_RED)done$(_END)"
	@/bin/rm -f $(NAME)

re:
	@make fclean
	@make

.PHONY: all clean fclean re
