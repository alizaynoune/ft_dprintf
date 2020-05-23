NAME = libftprintf.a
INC = include/

SRC = dprintf.c\
      print.c\
 #     main.c
OBJ = src/
OBP = ./objs/

OBJS = $(addprefix $(OBJ), $(SRC))
OBJL = $(addprefix $(OBP), $(SRC:.c=.o))
test:
	gcc $(OBJS) src/main.c -L ./ -lft -I $(INC)

all: $(OBP)
	ar rc $(NAME) ./obj/*
	ranlib $(NAME)

$(OBP)%.o: $(OBJS)%.c
	gcc -c $< -o $@ -I $(INC)
