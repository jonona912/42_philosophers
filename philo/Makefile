# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/26 21:51:36 by zkhojazo          #+#    #+#              #
#    Updated: 2025/03/22 23:53:29 by zkhojazo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -g -Wall -Wextra -Werror

SRCS_DIR = srcs
OBJS_DIR = objs

SRCS = main_philosophers.c \
		ph_check_user_input.c \
		ph_mem_management.c \
		ph_one_philosopher.c \
		ph_prints.c \
		ph_queues.c \
		ph_set_philo_param.c \
		ph_set_user_input.c \
		ph_threads_1.c \
		ph_threads_2.c \
		ph_threads_helper.c \
		ph_threads_helper_2.c \
		ph_time_calc.c \
		philo_life_status.c

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lpthread

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re