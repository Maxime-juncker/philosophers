NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror $(INCLUDES_D)
MAKEFLAGS += --no-print-directory
ARGS = 20 2000 200 200 1

# ---------------------------------------------------------------------------- #
#                                  directories                                 #
# ---------------------------------------------------------------------------- #

VPATH = src/
OBJ_D = obj/
INCLUDES_D = -Iincludes/

# ---------------------------------------------------------------------------- #
#                                  srcs / objs                                 #
# ---------------------------------------------------------------------------- #

SRCS = 	main.c			\
		ft_atoi.c		\
		time.c			\
		utils.c			\
		philosophing.c	\

# ---------------------------------------------------------------------------- #
#                                 adding prefix                                #
# ---------------------------------------------------------------------------- #

OBJ := $(addprefix $(OBJ_D), $(SRCS:.c=.o))

# ---------------------------------------------------------------------------- #
#                                    colors                                    #
# ---------------------------------------------------------------------------- #

RESET 			= \033[0m
GRAY			=\033[90m
RED 			= \033[31m
GREEN 			= \033[32m
YELLOW 			= \033[33m
BLUE 			= \033[34m

RM = rm -fr

all: $(NAME)

# ---------------------------------------------------------------------------- #
#                                 creating exec                                #
# ---------------------------------------------------------------------------- #

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	printf "$(GREEN)$(NAME): success\n"
	printf "\n---------------------$(RESET)\n\n"

# ---------------------------------------------------------------------------- #
#                                   compiling                                  #
# ---------------------------------------------------------------------------- #

$(OBJ_D)%.o: %.c includes/philosophers.h | $(OBJ_D)
	$(CC) $(CFLAGS) -c $< -o $@
	printf "$(BLUE)"
	printf "$(GRAY)compiling: $(BLUE)%-40s $(GRAY)[%d/%d]\n" "$<" "$$(ls $(OBJ_D) | wc -l)" "$(words $(SRCS))"

# ---------------------------------------------------------------------------- #
#                                   cleaning                                   #
# ---------------------------------------------------------------------------- #
.PHONY: clean
clean:
	printf "$(RED)clean:\t$(NAME)\n\n"
	$(RM) $(OBJ_D)
	printf "$(RED)---------------------\n\n$(RESET)"

.PHONY: fclean
fclean:
	$(RM) $(BIN_D)$(NAME)
	printf "$(RED)fclean:\t$(NAME)\n"
	$(MAKE) clean

.PHONY: re
re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: run
run: all
	./$(NAME) $(ARGS)

.PHONY: hel
hel: all
	valgrind --tool=helgrind -s ./$(NAME) $(ARGS)

.PHONY: leaks
leaks: all
	valgrind --track-origins=yes --leak-check=full ./$(NAME) $(ARGS)
# ---------------------------------------------------------------------------- #
#                              create directories                              #
# ---------------------------------------------------------------------------- #
$(OBJ_D):
	mkdir -p $(OBJ_D)

$(BIN_D):
	mkdir -p $(BIN_D)

.SILENT:
