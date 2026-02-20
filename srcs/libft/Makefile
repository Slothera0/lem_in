CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP

NAME = libft.a
F_OBJS = .objs/

SOURCES = ft_atoi.c \
ft_bzero.c \
ft_calloc.c \
ft_isalnum.c \
ft_isalpha.c \
ft_isascii.c \
ft_isdigit.c \
ft_isprint.c \
ft_memchr.c \
ft_memcmp.c \
ft_memcpy.c \
ft_memmove.c \
ft_memset.c \
ft_strchr.c \
ft_strdup.c \
ft_strlcat.c \
ft_strlcpy.c \
ft_strlen.c \
ft_sstrlen.c \
ft_strncmp.c \
ft_strnstr.c \
ft_strrchr.c \
ft_tolower.c \
ft_toupper.c \
ft_itoa.c \
ft_putchar_fd.c \
ft_putstr_fd.c \
ft_putendl_fd.c \
ft_putnbr_fd.c \
ft_split.c \
ft_striteri.c \
ft_strjoin.c \
ft_strmapi.c \
ft_strtrim.c \
ft_substr.c \
get_next_line.c \
get_next_line_utils.c \
ft_lstadd_back_bonus.c \
ft_lstadd_front_bonus.c \
ft_lstclear_bonus.c \
ft_lstdelone_bonus.c \
ft_lstiter_bonus.c \
ft_lstlast_bonus.c \
ft_lstmap_bonus.c \
ft_lstnew_bonus.c \
ft_lstsize_bonus.c \
ft_free_array.c

OBJS = $(SOURCES:%.c=$(F_OBJS)%.o)
DEPS = $(OBJS:.o=.d)

TOTAL := $(words $(SOURCES))
COUNT = 0

# Colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RESET = \033[0m

all: 
	@echo "$(BLUE)🔧 Compiling libft...$(RESET)"
	@$(MAKE) -s $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "$(GREEN)✔ $(NAME) created successfully!$(RESET)"

$(F_OBJS)%.o: %.c libft.h
	@mkdir -p $(dir $@)

	@$(eval COUNT=$(shell echo $$(($(COUNT)+1))))
	@PERCENT=$$(($(COUNT)*100/$(TOTAL))); \
	FILLED=$$(($$PERCENT/4)); \
	EMPTY=$$((25-$$FILLED)); \
	printf "$(GREEN)\r["; \
	printf "%0.s█" $$(seq 1 $$FILLED); \
	printf "%0.s░" $$(seq 1 $$EMPTY); \
	printf "] %d%%$(RESET)" $$PERCENT; \
	if [ $$PERCENT -eq 100 ]; then printf "\n"; fi

	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(YELLOW)🧹 Cleaning $(NAME) object files...$(RESET)"
	@rm -rf $(F_OBJS)
	@echo "$(GREEN)✔ Clean complete$(RESET)"

fclean: clean
	@echo "$(YELLOW)🗑 Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)✔ Full clean complete$(RESET)"

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
