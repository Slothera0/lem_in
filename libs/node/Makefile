CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP
INCLUDES = -I ../libft -I ../vector

NAME = node.a
F_OBJS = .objs/

SOURCES = 	create_link.c \
			create_node.c \
			free_node.c \
			get_node.c \
			get_node_name.c \
			get_node_type.c \
			get_start.c \
			print_node.c

LIBFT_PATH = ../libft
LIBFT = $(LIBFT_PATH)/libft.a

VECTOR_PATH = ../vector
VECTOR = $(VECTOR_PATH)/vector.a

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
	@echo "$(BLUE)🔧 Compiling node...$(RESET)"
	@$(MAKE) -s $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(VECTOR)
	@mkdir -p temp
	@cd temp && ar x ../$(LIBFT)
	@cd temp && ar x ../$(VECTOR)
	@ar rcs $(NAME) $(OBJS) temp/*.o
	@rm -rf temp
	@echo "$(GREEN)✔ $(NAME) created successfully!$(RESET)"

$(LIBFT):
	@$(MAKE) -sC $(LIBFT_PATH)

$(VECTOR):
	@$(MAKE) -sC $(VECTOR_PATH)

$(F_OBJS)%.o: %.c node.h
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

	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(YELLOW)🧹 Cleaning $(NAME) object files...$(RESET)"
	@rm -rf $(F_OBJS)
	@$(MAKE) -sC $(LIBFT_PATH) clean
	@$(MAKE) -sC $(VECTOR_PATH) clean
	@echo "$(GREEN)✔ Clean complete$(RESET)"

fclean: clean
	@echo "$(YELLOW)🗑 Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -sC $(LIBFT_PATH) fclean
	@$(MAKE) -sC $(VECTOR_PATH) fclean
	@echo "$(GREEN)✔ Full clean complete$(RESET)"

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
