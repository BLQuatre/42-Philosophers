# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/25 10:30:46 by cauvray           #+#    #+#              #
#    Updated: 2025/06/27 03:38:29 by cauvray          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo_bonus
CC		= cc
CFLAGS	= -Wall -Wextra -Werror

SRCS_FILES =			\
	actions.c			\
	args.c				\
	init.c				\
	philo_bonus.c		\
	philosophers.c		\
	time.c

SRCS_DIR	= srcs
OBJS_DIR	= objs
OBJS_FILES	= $(SRCS_FILES:.c=.o)
OBJS		= $(addprefix $(OBJS_DIR)/, $(OBJS_FILES))

INC_DIR		= includes
INC_FLAGS	= -I $(INC_DIR)

GREEN	= \033[0;32m
CYAN	= \033[0;36m
RESET	= \033[0m
GRAY	= \033[90m

SUCCESS	= $(GREEN)[SUCCESS]$(RESET)
INFO	= $(CYAN)[INFO]$(RESET)

all: $(NAME)

$(OBJS_DIR):
	@if [ ! -d ./$(OBJS_DIR) ]; then \
		echo "$(INFO) Creating $(OBJS_DIR) directory..."; \
		echo "$(GRAY)mkdir -p $(OBJS_DIR)"; \
		mkdir -p $(OBJS_DIR); \
	fi

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	mkdir -p $(dir $@)
	@echo "$(INFO) Compiling $<...$(GRAY)"
	$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@


$(NAME): $(OBJS)
	@echo "$(INFO) Compiling $(NAME)... $(GRAY)"
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(SUCCESS) $(NAME) compiled."

clean:
	@echo "$(INFO) Removing $(OBJS_DIR)...$(GRAY)";
	rm -rf $(OBJS_DIR);
	@echo "$(SUCCESS) Objects and libs removed."

fclean: clean
	@echo "$(INFO) Removing $(NAME)...$(GRAY)"
	rm -f $(NAME)
	@echo "$(SUCCESS) $(NAME) removed."

re: fclean all

.PHONY: all clean fclean re
