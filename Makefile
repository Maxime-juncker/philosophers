NAME = philo

# colors
RED = 			\033[31m
GREEN = 		\033[32m
YELLOW = 		\033[33m
RESET = 		\033[0m
BLUE = 			\033[34m
CURSOR_OFF =	\e[?25l
CURSOR_ON = 	\e[?25h

# paths
OBJS_D		= obj/
SRCS_D		= src/
BIN_D		= bin/
LOG_D		= log/
INCLUDES_D	= includes/

SRCS =	philosophers.c	\
		debug.c			\
		ft_atoi.c		\
		main.c			\
		utils.c			\

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
all : header $(BIN_D)$(NAME)

.PHONY: header
header:
	printf "$(YELLOW)"
	printf "\n========================="
	printf "\n ___   _ _   _   _      _    __    _    ___   _ _   ___   ___ "
	printf "\n| o \\ | U | | | | |    / \\  / _|  / \\  | o \\ | U | | __| | o \\"
	printf "\n|  _/ |   | | | | |_  ( o ) \\_ \\ ( o ) |  _/ |   | | _|  |   /"
	printf "\n|_|   |_n_| |_| |___|  \\_/  |__/  \\_/  |_|   |_n_| |___| |_|\\\\"
	printf "\n\n=========================\n"
	printf "[Author]: $(GREEN)Maxime Juncker"
	printf "$(YELLOW)\t[github]: $(GREEN)https://github.com/Maxime-juncker\n\n"

$(BIN_D)$(NAME): $(OBJS) $(BIN_D)
	printf "$(BLUE)compiling: [$$(ls obj | wc -l)/$(shell ls src | wc -l)] [OK]\r\n"
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN_D)$(NAME)
	printf "$(GREEN)$(NAME): success\n"
	printf "\n---------------------$(CURSOR_ON)\n\n"

$(OBJS_D)%.o: $(SRCS_D)%.c includes/philosophers.h Makefile | $(OBJS_D)
	printf "$(CURSOR_OFF)$(BLUE)"
	printf "compiling: [$$(ls obj | wc -l)/$(shell ls src | wc -l)]\r"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_D):
	mkdir -p $(OBJS_D)

$(BIN_D):
	mkdir -p $(BIN_D)

$(LOG_D):
	mkdir -p $(LOG_D)

.PHONY: clean
clean:
	$(RM) $(LOG_D)
	$(RM) $(OBJS_D)
	printf "\n$(RED)clean:\t$(NAME)\n\n$(RESET)"
	printf "$(RED)---------------------\n\n$(RESET)"

.PHONY: fclean
fclean:
	$(RM) $(BIN_D)
	printf "\n$(RED)fclean:\t$(NAME)$(RESET)"
	$(MAKE) clean

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
