# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/06 18:05:05 by vtavitia          #+#    #+#              #
#    Updated: 2023/07/10 12:52:34 by vtavitia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

GREEN = \033[3;32m
RED = \033[3;31m
RESET = \033[0m

SRCS = clean_up.c \
		parse_tools.c \
		philosophers.c \
		philosophers_utils.c \
		routine_helpers.c \
		run_threads.c \
		run_threads_helper.c

SRCPATH = mandatory/
OBJPATH = objects/

SOURCES = $(addprefix $(SRCPATH), $(SRCS))
OBJECTS = $(addprefix $(OBJPATH), $(SRCS:.c=.o))

CC = cc

FLAGS = -Wall -Werror -Wextra

HEADER = includes/philosophers.h

MANDATORY = @echo "$(GREEN)Creating mandatory Philosophers file!$(RESET)"
REMOVETEXT = @echo "$(RED)CLEANING UP!$(RESET)"

all: $(OBJPATH) $(NAME)

$(OBJPATH)%.o: $(SRCPATH)%.c
	@$(CC) $(CFLAGS) -I $(HEADER) -c $< -o $@

$(OBJPATH):
	@mkdir $(OBJPATH)
	
$(NAME):  $(OBJECTS) 
	@$(CC) $(FLAGS) -o $(NAME) $(OBJECTS)
	$(MANDATORY)

clean:
	@rm -rf $(OBJPATH)

fclean: clean
	@rm -f $(NAME)
	$(REMOVETEXT)

re: fclean all

.PHONY: all clean fclean re
