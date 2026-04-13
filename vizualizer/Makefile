CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP
LDFLAGS = -lX11 -lGL -lpng -lz -lm
INCLUDES = -I ./includes -I ../libs/libft -I ../libs/vector -I ../libs/node -I ../includes

F_OBJS = .objs/
F_SRCS = srcs/
F_PARSE = $(F_SRCS)parse/
F_REND = $(F_SRCS)rend/

SRCS = 	$(F_SRCS)main.c \
		$(F_PARSE)read_term.c \
		$(F_PARSE)one_start_end.c \
		$(F_PARSE)get_nb_ant.c \
		$(F_PARSE)set_type.c \
		$(F_PARSE)normalize_coord.c \
		$(F_PARSE)check_coords.c \
		$(F_PARSE)read_ants_path.c \
		$(F_PARSE)create_path.c \
		$(F_PARSE)create_ants.c \
		$(F_REND)start_rend.c \
		$(F_REND)init_visual.c \
		$(F_REND)init_window.c \
		$(F_REND)load_png_texture.c \
		$(F_REND)clean_rend.c \
		$(F_REND)fill_map.c \
		$(F_REND)put_node.c \
		$(F_REND)load_map.c \
		$(F_REND)put_link.c \
		$(F_REND)put_ant.c \
		$(F_REND)ants_movements.c \
		$(F_REND)calculate_ant_step.c

OBJS = $(SRCS:%.c=$(F_OBJS)%.o)
DEPS = $(OBJS:.o=.d)

NAME = vizu-hex

NODE_PATH = ../libs/node
NODE = $(NODE_PATH)/node.a

TOTAL := $(words $(SRCS))
COUNT = 0

# 🎨 Colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RESET = \033[0m

all:
	@echo "$(BLUE)🔧 Compiling $(NAME)...$(RESET)"
	@$(MAKE) -s $(NAME)

$(NAME): $(OBJS) $(NODE)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) $(NODE) -o $(NAME)
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
	@echo "$(GREEN)✔ Clean complete$(RESET)"

fclean: clean
	@echo "$(YELLOW)🗑 Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -sC $(NODE_PATH) fclean
	@echo "$(GREEN)✔ Full clean complete$(RESET)"

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
