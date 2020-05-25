NAME = libftdprintf.a
GCC = gcc -Wall -Werror -Wextra -c
OBJS = objs/

#*
#*** src dire
#*

D_L_CONV = ./libft/convert/
D_L_COUNT = ./libft/count/
D_L_EDIT = ./libft/edit/
D_L_IS = ./libft/is/
D_L_LST = ./libft/lst/
D_L_MEM = ./libft/mem/
D_L_PUT = ./libft/put/
D_L_SRCH = ./libft/srch/
D_L_STR = ./libft/str/
D_L_FREE = ./libft/free/
D_DPRINTF = ./src/
D_INC = ./includes/

#*
#*** src file
#*

L_CONV = ft_atoi_all.c		\
	 ft_atoi.c		\
	 ft_atol.c		\
	 ft_atol_all.c		\
	 ft_atoll.c		\
	 ft_atoll_all.c		\
	 ft_itoa.c		\
	 ft_ltoa.c		\
	 ft_lltoa.c		\
	 ft_tolower.c		\
	 ft_toupper.c		\
	 ft_atoi_base.c		\
	 ft_power.c		\
	 ft_itoa_base.c

L_COUNT = count_words.c		\
	  ft_count_char.c	\
	  ft_strnlen.c		\
	  ft_strlen.c		\
	  start_end_words.c	\
	  ft_intlen.c

L_EDIT = ft_bzero.c		\
	 remove_last_space.c	\
	 ft_strclr.c		\
	 ft_skip_char.c

L_IS = ft_all_digit.c		\
       ft_isalnum.c		\
       ft_isalpha.c		\
       ft_isascii.c		\
       ft_isdigit.c		\
       ft_isprint.c

L_LST = ft_lstadd.c		\
	ft_lstdel.c		\
	ft_lstdelone.c		\
	ft_lstiter.c		\
	ft_lstmap.c		\
	ft_lstnew.c

L_MEM = ft_memalloc.c		\
	ft_memccpy.c		\
	ft_memchr.c		\
	ft_memcmp.c		\
	ft_memcpy.c		\
	ft_memdel.c		\
	ft_memmove.c		\
	ft_memset.c

L_PUT = ft_putchar.c		\
	ft_putchar_fd.c		\
	ft_putendl.c		\
	ft_putendl_fd.c		\
	ft_putnbr.c		\
	ft_putnbr_fd.c		\
	ft_putstr.c		\
	ft_putstr_fd.c

L_SRCH = ft_strchr.c		\
	 ft_strrchr.c		\
	 ft_strstr.c		\
	 ft_strnstr.c		\
	 ft_strchrstr.c

L_STR = ft_strcat.c		\
	ft_strcmp.c		\
	ft_strcpy.c		\
	ft_strdup.c		\
	ft_strequ.c		\
	ft_striter.c		\
	ft_striteri.c		\
	ft_strjoin.c		\
	ft_strlcat.c		\
	ft_strmap.c		\
	ft_strmapi.c		\
	ft_strncat.c		\
	ft_strncmp.c		\
	ft_strncpy.c		\
	ft_strndup.c		\
	ft_strnequ.c		\
	ft_strnew.c		\
	ft_strsplit.c		\
	ft_strsub.c		\
	ft_strtrim.c		\
	split_by_str.c

L_FREE = free_rev.c		\
	 free_tab_char.c	\
	 ft_strdel.c

DPRINTF = dprintf.c		\
	  specifier.c		\
	  get_args.c		\
	  helper_args.c		\
	  convert_args.c	\
	  _put.c		\
	  helper_put.c		\
	  tools.c		


LIB_INC = ./includes/libft.h
DPRINT_INC = ./includes/ft_printf.h

LIB_OBJ := $(addprefix $(OBJS), $(L_CONV:.c=.o))	\
	$(addprefix $(OBJS), $(L_COUNT:.c=.o))		\
	$(addprefix $(OBJS), $(L_EDIT:.c=.o))		\
	$(addprefix $(OBJS), $(L_IS:.c=.o))		\
	$(addprefix $(OBJS), $(L_LST:.c=.o))		\
	$(addprefix $(OBJS), $(L_MEM:.c=.o))		\
	$(addprefix $(OBJS), $(L_PUT:.c=.o))		\
	$(addprefix $(OBJS), $(L_STR:.c=.o))		\
	$(addprefix $(OBJS), $(L_FREE:.c=.o))		\
	$(addprefix $(OBJS), $(L_SRCH:.c=.o))
OBJ_ALL := $(LIB_OBJ) $(addprefix $(OBJS), $(DPRINTF:.c=.o))


#*
#*** colors
#*

DEF = \e[1;0m
RED = \e[1;31m
PURPLE = \e[1;34m
BLUE = \e[1;96m
GREEN = \e[1;32m
SILVER = \e[1;90m
YELLOW = \e[1;33m

#*
#*** functions
#*
define compile
@mkdir -p $(OBJS)
@$(GCC) $1 -o $2 -I $(D_INC)
@echo "$(SILVER)[$(PURPLE)Object file$(BLUE) $(notdir $2)$(SILVER)] $(GREEN)Created.$(DEF)"
endef

define to_lib
@ar rc $1 $2
@ranlib $1
@echo "$(SILVER)[$(PURPLE)Library file$(YELLOW) $(notdir $1)$(SILVER)] $(GREEN)Created.$(DEF)"

endef

define remove_lib
@rm -f $1
@echo "$(SILVER)[$(PURPLE)library file$(YELLOW)$1$(SILVER)] $(RED)deleted.$(DEF)"
endef

#*
#*** rules
#*

all: $(NAME)

$(NAME): $(OBJ_ALL)
	@$(call to_lib, $(NAME), $(OBJ_ALL))

$(OBJS)%.o: $(D_L_CONV)%.c $(LIB_INC)
	@$(call compile,$<, $@)

$(OBJS)%.o: $(D_L_COUNT)%.c $(LIB_INC)
	@$(call compile,$<, $@)

$(OBJS)%.o: $(D_L_EDIT)%.c $(LIB_INC)
	@$(call compile,$<, $@)

$(OBJS)%.o: $(D_L_IS)%.c $(LIB_INC)
	@$(call compile,$<, $@)

$(OBJS)%.o: $(D_L_LST)%.c $(LIB_INC)
	@$(call compile,$<, $@)

$(OBJS)%.o: $(D_L_MEM)%.c $(LIB_INC)
	@$(call compile,$<, $@)

$(OBJS)%.o: $(D_L_PUT)%.c $(LIB_INC)
	@$(call compile,$<, $@)

$(OBJS)%.o: $(D_L_STR)%.c $(LIB_INC)
	$(call compile,$<, $@)

$(OBJS)%.o: $(D_L_FREE)%.c $(LIB_INC)
	$(call compile, $<, $@)

$(OBJS)%.o: $(D_L_SRCH)%.c $(LIB_INC)
	$(call compile, $<, $@)

$(OBJS)%.o: $(D_DPRINTF)%.c $(DPRINTF_INC)
	$(call compile,$<, $@)

clean:
	@rm -rf $(OBJS)
	@echo "$(SILVER)[$(PURPLE)Path objects$(DEF) $(OBJS)$(SILVER)] $(RED)Deleted.$(DEF)"

fclean: clean
	@$(call remove_lib, $(NAME))

re: fclean all

.PHONY: re clean fclean all
