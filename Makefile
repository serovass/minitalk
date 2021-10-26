NAME_SERVER = server

NAME_CLIENT = client

LIST_SERVER = ft_server.c

LIST_CLIENT = ft_client.c

OBJ_SERVER = ${LIST_SERVER:.c=.o}

OBJ_CLIENT = ${LIST_CLIENT:.c=.o}

LIBFT_DIR	= ./libft
LIBFT		= ./libft/libft.a

FLAGS = -Wall -Wextra -Werror -include minitalk.h

all: $(NAME_SERVER) $(NAME_CLIENT)

bonus: $(NAME_SERVER) $(NAME_CLIENT)

%.o: %.c
			gcc $(FLAGS) -c $< -o $@

$(LIBFT):
		$(MAKE) -C libft

$(NAME_SERVER):	$(OBJ_SERVER) $(LIBFT)
				gcc $(FLAGS) $(OBJ_SERVER) $(LIBFT) -o $(NAME_SERVER)

$(NAME_CLIENT):	$(OBJ_CLIENT) $(LIBFT)
				gcc $(FLAGS) $(OBJ_CLIENT) $(LIBFT) -o $(NAME_CLIENT)

clean: 
		make -C $(LIBFT_DIR) clean
		rm -f $(OBJ_SERVER) $(OBJ_CLIENT)

fclean: clean
		@make -C $(LIBFT_DIR) fclean
		rm -f $(NAME_SERVER) $(NAME_CLIENT)

re:		fclean all

.PHONY: all clean fclean re bonus