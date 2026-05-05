CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP
INCLUDES = -I ./includes -I ./libs/libft -I ./libs/vector -I ./libs/node

F_OBJS = .objs/
F_SRCS = srcs/
F_PARSE = $(F_SRCS)parse/
F_ALGO = $(F_SRCS)algo/

SRCS = 	$(F_SRCS)main.c \
		$(F_SRCS)error.c \
		$(F_SRCS)print_path.c \
		$(F_SRCS)print_way.c \
		$(F_SRCS)print_all_path.c \
		$(F_NODE)print_node.c $(F_NODE)get_node_name.c $(F_NODE)create_node.c $(F_NODE)create_link.c $(F_NODE)get_node.c  $(F_NODE)free_node.c $(F_NODE)get_start.c $(F_NODE)get_node_type.c \
       	$(F_PARSE)read_term.c $(F_PARSE)one_start_end.c $(F_PARSE)is_a_num.c $(F_PARSE)get_nb_ant.c $(F_PARSE)set_type.c \
		$(F_ALGO)distrib_ants.c $(F_ALGO)print_walk.c \
		$(F_ALGO)bfs.c $(F_ALGO)add_flow_edge.c $(F_ALGO)create_door.c $(F_ALGO)create_fnode.c $(F_ALGO)free_edge.c $(F_ALGO)free_fnode.c $(F_ALGO)free_door.c $(F_ALGO)free_all.c
		
OBJS = $(SRCS:%.c=$(F_OBJS)%.o)
DEPS = $(OBJS:.o=.d)

NAME = lem_in

NODE_PATH = ./libs/node
NODE = $(NODE_PATH)/node.a

VIZUALIZER = ./vizualizer

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

$(NAME): $(OBJS) $(NODE)
	$(CC) $(CFLAGS) $(OBJS) $(NODE) -o $(NAME)
	@echo "$(GREEN)✔ $(NAME) created successfully!$(RESET)"

$(NODE):
	@$(MAKE) -sC $(NODE_PATH)

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
	@$(MAKE) -sC $(NODE_PATH) clean
	@$(MAKE) -sC $(VIZUALIZER) clean
	@echo "$(GREEN)✔ Clean complete$(RESET)"

fclean: clean
	@echo "$(YELLOW)🗑 Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -sC $(NODE_PATH) fclean
	@$(MAKE) -sC $(VIZUALIZER) fclean
	@echo "$(GREEN)✔ Full clean complete$(RESET)"

re: fclean all

bonus: all
	@$(MAKE) -sC $(VIZUALIZER)

-include $(DEPS)

.PHONY: all clean fclean re bonus
