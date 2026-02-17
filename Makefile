CC = cc

CFLAGS = -Wall -Wextra -Werror -MMD -MP
INCLUDES = -I ./includes

F_OBJS = .objs/
F_SRCS = srcs/
F_GNL = $(F_SRCS)get_next_line/

SRCS = $(F_SRCS)main.c \
       $(F_GNL)get_next_line.c \
       $(F_GNL)get_next_line_utils.c

OBJS = $(SRCS:%.c=$(F_OBJS)%.o)
DEPS = $(OBJS:.o=.d)

NAME = lem_in

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(F_OBJS)%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(F_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re