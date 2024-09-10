# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/31 10:34:26 by kali              #+#    #+#              #
#    Updated: 2024/09/10 10:12:35 by agiliber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = lexer/lexer.c lexer/init_lexer.c parser/parsing_error.c parser/parser_utils.c main.c builtins/echo.c parser/parser.c lexer/lexer_utils.c \
	# builtins/ft_utiles_echo.c builtins/pwd.c builtins/builtins.c builtins/ft_utiles_echo2.c redirections/environment.c redirections/export.c
CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror -I./includes/
RM = rm -rf
NAME = minishell.a
OBJS = $(SRCS:.c=.o)

RED    = \033[31m
GREEN  = \033[32m
YELLOW = \033[33m
BLUE   = \033[34m
MAGENTA= \033[35m
CYAN   = \033[36m
RESET  = \033[0m

.SILENT:

all: minishell

minishell: $(NAME) $(OBJS)
	echo "${CYAN}Compiling Minishell...${RESET}"
	cc minishell.a -o minishell -lreadline
	echo "${GREEN}Succes!!!${RESET}"
$(NAME): $(OBJS)
	echo "${CYAN}Compiling libft...${RESET}"
	$(MAKE) --no-print-directory -C ./libft
	cp libft/libft.a $(NAME)
	ar rc $(NAME) $(OBJS)
clean:
	echo "${RED}Cleaning libft && Minishell...${RESET}"
	$(MAKE) clean --no-print-directory -C ./libft
	$(RM) $(OBJS) objs
	echo "${GREEN}Succes!!!${RESET}"

fclean: clean
	$(MAKE) fclean --no-print-directory -C ./libft
	echo "${RED}Cleaning exucutable files...${RESET}"
	$(RM) $(NAME) Minishell
	echo "${GREEN}Succes!!!${RESET}"
re: fclean all

.PHONY: all clean fclean re