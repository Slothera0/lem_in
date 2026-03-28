CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP
LDFLAGS = -lX11 -lGL -lpng -lz
INCLUDES = -I ./includes -I ../libs/libft -I ../libs/vector

F_OBJS = .objs/
F_SRCS = srcs/
F_PARSE = $(F_SRCS)parse/
F_REND = $(F_SRCS)rend/

SRCS = 	$(F_SRCS)main.c \
		$(F_REND)start_rend.c \
		$(F_REND)init_visual.c \
		$(F_REND)init_window.c \
		$(F_REND)load_png_texture.c \
		$(F_REND)clean_rend.c \
		$(F_REND)fill_map.c

OBJS = $(SRCS:%.c=$(F_OBJS)%.o)
DEPS = $(OBJS:.o=.d)

NAME = vizualizer

LIBFT_PATH = ../libs/libft
LIBFT = $(LIBFT_PATH)/libft.a

VECTOR_PATH = ../libs/vector
VECTOR = $(VECTOR_PATH)/vector.a

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

$(NAME): $(OBJS) $(LIBFT) $(VECTOR)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) $(LIBFT) $(VECTOR) -o $(NAME)
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
