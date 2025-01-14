NAME	:= cube
CFLAGS	:= -Wextra -Wall -Wunreachable-code -Ofast
#  -Werror
LIBMLX	:= ./MLX42

LIBFT = libft/libft.a
HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm  libft/libft.a

SRCS 	:= main.c
OBJS	:= ${SRCS:.c=.o}

all:$(NAME)

libmlx:
	@printf "✅\n"
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(LIBFT):
	@$(MAKE) -C libft > /dev/null
	@sleep 0.25

$(NAME): $(MLX) $(LIBFT) $(MLX) $(OBJS)
	@make libmlx
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@make clean -C ./libft
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@make fclean -C ./libft
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx
