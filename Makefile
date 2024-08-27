NAME	= philo

SRCS	= \
	check.c init.c message.c philo_state.c time_utils.c philo.c thread_utils.c

OBJS	= $(SRCS:.c=.o)

$(NAME)	: $(OBJS)
	cc -pthread -o $(NAME) $(OBJS)

$(OBJS)	: %.o : %.c
	cc -Wall -Werror -Wextra -pthread -c $<

all	: $(NAME)

clean	:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean	: clean
	rm -f $(NAME)

re	: fclean
	$(MAKE) all


.PHONY	: all clean fclean re