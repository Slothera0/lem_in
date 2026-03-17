CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP
INCLUDES = -I ./includes -I ./srcs/libft -I ./srcs/vector

F_OBJS = .objs/
F_SRCS = srcs/
F_PARSE = $(F_SRCS)parse/
F_NODE = $(F_SRCS)node/
F_ALGO = $(F_SRCS)algo/

SRCS = 	$(F_SRCS)main.c \
		$(F_SRCS)error.c \
		$(F_SRCS)print_way.c \
		$(F_NODE)print_node.c $(F_NODE)get_node_name.c $(F_NODE)create_node.c $(F_NODE)create_link.c $(F_NODE)get_node.c  $(F_NODE)free_node.c $(F_NODE)get_start.c $(F_NODE)get_node_type.c \
       	$(F_PARSE)read_term.c $(F_PARSE)one_start_end.c \
		$(F_ALGO)find_all_ways.c

OBJS = $(SRCS:%.c=$(F_OBJS)%.o)
DEPS = $(OBJS:.o=.d)

NAME = lem_in

LIBFT_PATH = ./srcs/libft
LIBFT = $(LIBFT_PATH)/libft.a

VECTOR_PATH = ./srcs/vector
VECTOR = $(VECTOR_PATH)/vector.a

TOTAL := $(words $(SRCS))
COUNT = 0

# 🎨 Colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RESET = \033[0m

all:
	@echo "$(BLUE)🔧 Compiling lem_in...$(RESET)"
	@$(MAKE) -s $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(VECTOR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(VECTOR) -o $(NAME)
	@echo "$(GREEN)✔ $(NAME) created successfully!$(RESET)"

$(LIBFT):
	@$(MAKE) -sC $(LIBFT_PATH)

$(VECTOR):
	@$(MAKE) -sC $(VECTOR_PATH)

$(F_OBJS)%.o: %.c
	@mkdir -p $(dir $@)
	@$(eval COUNT=$(shell echo $$(($(COUNT)+1))))
	@PERCENT=$$(($(COUNT)*100/$(TOTAL))); \
	FILLED=$$((PERCENT/4)); \
	EMPTY=$$((25-FILLED)); \
	printf "$(GREEN)\r["; \
	printf "%0.s█" $$(seq 1 $$FILLED); \
	printf "%0.s░" $$(seq 1 $$EMPTY); \
	printf "] %d%%$(RESET)" $$PERCENT; \
	if [ $$PERCENT -eq 100 ]; then printf "\n"; fi

	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

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
