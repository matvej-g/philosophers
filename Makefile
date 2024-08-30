NAME	= philo

SRCS	= \
	check.c init.c message.c philo_state.c time_utils.c philo.c thread_utils.c mtx_utils.c free_resources.c

OBJS	= $(SRCS:.c=.o)

$(NAME)	: $(OBJS)
	cc -pthread -o $(NAME) $(OBJS) -fsanitize=thread

$(OBJS)	: %.o : %.c
	cc -Wall -Werror -Wextra -fsanitize=thread -g -pthread -Ofast -c $<

all	: $(NAME)

clean	:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean	: clean
	rm -f $(NAME)

re	: fclean
	$(MAKE) all


.PHONY	: all clean fclean re