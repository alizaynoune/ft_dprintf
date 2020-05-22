NAME = libftprintf.a
INC = include/

SRC = dprintf.c\
      print.c\
      main.c
OBJ = src/
OBP = ./obj/

OBJS = $(addprefix $(OBJ), $(SRC))
OBJL = $(addprefix $(OBP), $(SRC:.c=.o))
all:
	gcc $(OBJS) -L ./ -lft -I $(INC)

lib: $(OBP)
	ar rc $(NAME) ./obj/*
	ranlib $(NAME)

$(OBP)%.o: $(OBJS)%.c
	gcc -c $< -o $@ -I $(INC)
