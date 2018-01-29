NAME		=	libft.a
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra

_PRINTFS	=	ft_printf.c ft_vprintf.c \
				ft_printf_parser.c ft_printf_format.c ft_init_formats.c \
				handler_s.c handler_d.c handler_u.c handler_p.c handler_x.c \
				handler_o.c handler_c.c handler_f.c handler_b.c handler_y.c \
				handler_color.c \
				perform_width.c proper_cast.c \

_LIBFTS	=	ft_abs.c ft_pow.c ft_sqrt.c ft_max.c \
			ft_atod.c ft_atoi.c ft_atol.c ft_atoll.c ft_atoui.c \
			ft_atoul.c ft_atoull.c ft_dtoa.c ft_btree_balance.c \
			ft_btree_copy.c ft_btree_erase.c ft_btree_dump.c ft_btree_root.c \
			ft_btree_fromlist.c ft_btree_insert.c ft_btree_left.c \
			ft_btree_move.c ft_btree_new.c ft_btree_right.c ft_btree_search.c \
			ft_btree_size.c ft_btree_swap.c ft_btree_tolist.c ft_btree_pos.c \
			ft_btree_splay.c ft_btree_balancem.c ft_btree_count.c \
			ft_btree_erase_all.c ft_btree_iter.c ft_btree_getcreate.c \
			ft_btree_getnew.c ft_btree_iterv.c ft_btree_tolistv.c \
			ft_btree_iter_d.c ft_btree_iterv_d.c ft_btree_insert_p.c \
			ft_isalnum.c ft_isalpha.c ft_isascii.c ft_iscntrl.c ft_isdigit.c \
			ft_islower.c ft_isprint.c ft_ispunct.c ft_isspace.c ft_isupper.c \
			ft_itoa.c ft_ltoa.c ft_lltoa.c ft_uitoa.c ft_ultoa.c ft_ulltoa.c \
			ft_lstatpos.c ft_lstcopy.c ft_lstend.c ft_lstfind.c ft_lstiter.c \
			ft_lstmap.c ft_lstnew.c ft_lstpush.c ft_lstsize.c ft_lstcount.c \
			ft_lsterase.c ft_lsterase_all.c ft_lstswap.c ft_lstsort.c \
			ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdup.c \
			ft_memalloc.c ft_memset.c ft_memjoin.c ft_memstr.c \
			ft_putchar.c ft_putdouble.c ft_putendl.c  ft_putnbr.c \
			ft_putptr.c ft_putstr.c ft_putullong_base.c ft_putunbr.c \
			ft_revstr.c ft_strafter.c ft_strbefore.c ft_strcat.c ft_strchr.c \
			ft_strclr.c ft_strcmp.c ft_strcount.c  ft_strcpy.c ft_strdup.c \
			ft_strequ.c ft_striter.c ft_strjoin.c ft_strjoinc.c ft_strjoincs.c \
			ft_strlen.c ft_strrepeat.c ft_strmap.c ft_strnew.c ft_strmatch.c \
			ft_strnrchr.c ft_strnrstr.c ft_strrep.c ft_strrepstr.c \
			ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtrim.c ft_swap.c \
			ft_strpbrk.c \
			ft_strforeach.c ft_swapptr.c ft_tobase.c ft_tolower.c ft_toupper.c \
			ft_wcharlen.c ft_getwchar.c ft_wstrlen.c ft_getwstr.c \
			ft_event_new.c ft_event_add.c ft_event_trigger.c ft_event_clean.c \
			ft_pevent_new.c ft_pevent_add.c ft_pevent_remove.c \
			ft_pevent_trigger.c ft_pevent_clean.c \
			get_next_line.c ft_timefnew.c \

SRCD		=	srcs
ICLD		=	includes
LIBFTS		=	$(addprefix $(SRCD)/,$(_LIBFTS))
_LIBFTO		=	$(_LIBFTS:.c=.o)
LIBFTO		=	$(LIBFTS:.c=.o)

PRINTFD		=	$(SRCD)/ft_printf
PRINTFS		=	$(addprefix $(PRINTFD)/,$(_PRINTFS))
_PRINTFO	=	$(_PRINTFS:.c=.o)
PRINTFO		=	$(PRINTFS:.c=.o)

SRCS		=	$(LIBFTS) $(PRINTFS)
_OBJS		=	$(_LIBFTO) $(_PRINTFO)
OBJD		=	objs
OBJS		=	$(LIBFTO) $(PRINTFO)
OBJB		=	$(addprefix $(OBJD)/,$(_OBJS))

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

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(SRCS)
	@echo "$(_RED)Compiling$(_END) $(NAME)$(_RED)...$(_END)"
	@$(CC) -c $(CFLAGS) $(SRCS) -I$(ICLD)
	@mkdir -p objs
	@mv $(_OBJS) $(OBJD)/
	@ar rc $(NAME) $(OBJB)
	@ranlib $(NAME)
	@echo  "$(NAME) : $(_SUCCESS)done$(_END)"

%.c:
	;

clean:
	@/bin/rm -f $(OBJB)
	@echo "$(NAME) clean: $(_RED)done$(_END)"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "$(NAME) fclean: $(_RED)done$(_END)"

re: fclean all
