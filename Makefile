NAME = philo

# colors
RED = 		\033[31m
GREEN = 	\033[32m
YELLOW =	\033[33m
RESET = 	\033[0m
BLUE = 		\033[34m

# paths
OBJS_D		= obj/
SRCS_D		= src/
BIN_D		= bin/
LOG_D		= log/
INCLUDES_D	= includes/

SRCS = philosophers.c	\
		debug.c			\

OBJS = $(SRCS:.c=.o)
HEADERS = includes/

# setting the path for src and obj files
OBJS := $(addprefix $(OBJS_D), $(OBJS))
SRCS := $(addprefix $(SRCS_D), $(SRCS))

# compiler settings
CC = cc
CFLAGS = -Wall -Werror -Wextra -I$(HEADERS) -g3
MAKEFLAGS += -s

# commands
RM = rm -fr

.PHONY: all
all : $(BIN_D)$(NAME)

$(BIN_D)$(NAME): $(OBJS) $(BIN_D)
	echo "$(GREEN)[CREATING EXE]: $(NAME)$(RESET)"
	$(CC) $(OBJS) $(CFLAGS) -o $(BIN_D)$(NAME)
	echo "$(GREEN)[SUCCESS]$(RESET)"

$(OBJS_D)%.o: $(SRCS_D)%.c includes/philosophers.h Makefile | $(OBJS_D)
	echo "$(BLUE)[COMPILING]: $@$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_D):
	echo "$(YELLOW)[CREATING]: $(OBJ_D)$(RESET)"
	mkdir -p $(OBJS_D)

$(BIN_D):
	echo "$(YELLOW)[CREATING]: $(BIN_D)$(RESET)"
	mkdir -p $(BIN_D)

$(LOG_D):
	echo "$(YELLOW)[CREATING]: $(LOG_D)$(RESET)"
	mkdir -p $(LOG_D)

.PHONY: clean
clean:
	echo "$(RED)[CLEAN]: obj / log files$(RESET)"
	$(RM) $(LOG_D)
	$(RM) $(OBJS_D)

.PHONY: fclean
fclean: clean
	echo "$(RED)[CLEAN]: bin$(RESET)"
	$(RM) $(BIN_D)

.PHONY: re
re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: debug
debug: all $(LOG_D)
	./$(BIN_D)$(NAME) > $(LOG_D)$(shell date --iso=seconds).log
	cat $(LOG_D)$(shell date --iso=seconds).log
	echo "$(BLUE)[SAVED]: log/$(shell date --iso=seconds).log$(RESET)"

.PHONY: clog
clog:
	$(RM) $(LOG_D)

run: debug
	$(BIN_D)a.out
