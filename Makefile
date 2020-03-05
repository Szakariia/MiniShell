# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: szakaria <szakaria@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/19 17:15:33 by szakaria          #+#    #+#              #
#    Updated: 2019/11/19 03:16:15 by szakaria         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror

_lCYAN = \x1b[96m
_lYELLOW = \x1b[93m
_lGREEN = \x1b[92m
_lBLUE = \x1b[94m
_RED = \x1b[31m
_BOLD = \x1b[1m
_END = \x1b[0m

LIB = libft/libft.a
LIB2 = GTN/get_next_line.c

FILE = mini_cd.c\
		mini_cd2.c\
		mini_echo.c\
		mini_filter.c\
		mini_filter1.c\
		mini_filter2.c\
		mini_filter3.c\
		mini_quote.c\
		mini_setenv.c\
		mini_setenv2.c\
		mini_stock.c\
		mini_stock2.c\
		mini_systeme.c\
		mini_unsetenv.c\
		minishell.c\
		minishell1.c\
		minishell2.c\
		myshell.c

OFILE =	mini_cd.o\
		mini_cd2.o\
		mini_echo.o\
		mini_filter.o\
		mini_filter1.o\
		mini_filter2.o\
		mini_filter3.o\
		mini_filter4.o\
		mini_quote.o\
		mini_setenv.o\
		mini_setenv2.o\
		mini_stock.o\
		mini_stock2.o\
		mini_systeme.o\
		mini_unsetenv.o\
		minishell.o\
		minishell1.o\
		minishell2.o\
		myshell.o

all: $(NAME)

$(NAME): $(OFILE) minishell.h
		@make -C libft
		@$(CC) -o $(NAME) -lreadline $(LIB) $(LIB2) $(OFILE)
		@echo "\n$(_lGREEN) -> The Programme was completed <-\n"

clean:
	@make -C libft clean
	@rm -rf $(OFILE)
	@echo "$(_lGREEN) > make clean $(_END)"

fclean : clean
	@make -C libft fclean
	@rm -rf $(NAME)
	@echo "$(_lGREEN) > make fclean $(_END)"

re: fclean all
	@echo "$(_lGREEN) > make re $(_END)"
