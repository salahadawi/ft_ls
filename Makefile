# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/10 19:27:20 by sadawi            #+#    #+#              #
#    Updated: 2020/04/13 14:57:06 by sadawi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
CFILES = column_padding.c create_struct.c free_memory.c get_terminal_stats.c \
handle_error.c helper_functions.c main.c mergesort_dir.c mergesort.c \
open_dir.c open_file.c print_digits.c print_ls.c print_modes.c print_row.c \
print_stats.c save_options.c save_stats.c sort_files.c \
sorting_algorithms_dir.c sorting_algorithms.c sorting_algorithms_rev.c \
sorting_algorithms_rev_dir.c
SRCS = $(addprefix srcs/, $(CFILES))
OBJS = $(addprefix objs/, $(notdir $(SRCS:.c=.o)))
INCLUDES = -I includes -I libft/includes
FLAGS = -Wall -Wextra -Werror
RUN_LIB = make -C libft/ fclean && make -C libft/

all: $(NAME)

$(NAME):
	@$(RUN_LIB)
	@rm -rf objs
	@echo Compiling $(NAME)...
	@gcc $(FLAGS) $(INCLUDES) -c $(SRCS)
	@mkdir objs
	@mv $(notdir $(SRCS:.c=.o)) objs
	@gcc $(FLAGS) $(INCLUDES) -o $(NAME) $(OBJS) libft/libft.a
	@echo $(NAME) compiled succesfully!

clean:
	@/bin/rm -f $(OBJS)
	@rm -rf objs
	@make -C libft/ clean
	@echo Clean successful!

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C libft/ fclean
	@echo Clean successful!

re: fclean all
