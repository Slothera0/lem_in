CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP

NAME = vizu-hex
F_OBJS = .objs/

SOURCES = 	main.c

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
	@echo "$(BLUE)🔧 Compiling vector...$(RESET)"
	@$(MAKE) -s $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lX11 -L/usr/X11R6/lib -I/usr/X11R6/include
	@echo "$(GREEN)✔ $(NAME) created successfully!$(RESET)"

$(F_OBJS)%.o: %.c
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
