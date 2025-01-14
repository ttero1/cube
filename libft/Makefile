
man_files        = ft_strlen.c \
             ft_memmove.c \
             ft_memcpy.c \
             ft_strlcpy.c \
             ft_strlcat.c \
             ft_isalpha.c \
             ft_isdigit.c \
             ft_isalnum.c \
             ft_isascii.c \
             ft_isprint.c \
             ft_memset.c \
             ft_bzero.c \
             ft_toupper.c \
             ft_tolower.c \
             ft_strchr.c \
             ft_strrchr.c \
             ft_strncmp.c \
             ft_memchr.c \
             ft_memcmp.c \
             ft_strnstr.c \
             ft_atoi.c \
             ft_calloc.c \
             ft_strdup.c \
             ft_substr.c \
             ft_strjoin.c \
             ft_strtrim.c \
             ft_split.c \
             ft_itoa.c \
             ft_strmapi.c \
             ft_striteri.c \
             ft_putchar_fd.c \
             ft_putstr_fd.c \
             ft_putendl_fd.c \
             ft_putnbr_fd.c \
			 ft_printf.c  \
			 ft_printf_utils.c  \
			 ft_printf_utils2.c  \
			 ft_printf_error.c  \
			 ft_printf_utils_error.c  \
			 ft_printf_utils2_error.c  \
             ft_atod.c  \


files_bonus        = ft_lstnew_bonus.c \
			 		ft_lstadd_front_bonus.c \
			 		ft_lstadd_back_bonus.c \
					ft_lstsize_bonus.c \
			 		ft_lstlast_bonus.c \
					ft_lstdelone_bonus.c \
			 		ft_lstclear_bonus.c \
			 		ft_lstiter_bonus.c \
			 		ft_lstmap_bonus.c \

Compiler    = cc

CmpFlags    = -Wall -Wextra -Werror

CFILES    = $(man_files)

OFILES    = $(CFILES:.c=.o)

BCFILES    = $(files_bonus)

BOFILES    = $(files_bonus:.c=.o)

NAME    = libft.a

$(NAME): $(OFILES)
	$(Compiler) $(CmpFlags) -c $(CFILES) -I./
	ar -rc $(NAME) $(OFILES)

all: $(NAME)

clean:
	rm -f $(OFILES)
	rm -f $(BOFILES)
	rm -f .bonus

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: .bonus

.bonus: $(OFILES) $(BOFILES)
	ar -rc $(NAME) $(OFILES) $(BOFILES)
	touch .bonus


.PHONY: all, clean, fclean, re, bonus
