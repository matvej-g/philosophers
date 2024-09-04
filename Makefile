NAME	= philo

SRCS	= \
	parameter_check.c init.c \
	philo.c philo_state.c philo_routine.c philo_check.c \
	message.c \
	time_utils.c thread_utils.c mtx_utils.c \
	free_resources.c \

OBJS	= $(SRCS:.c=.o)

$(NAME)	: $(OBJS)
	cc -pthread -o $(NAME) $(OBJS) 
	
#-fsanitize=thread -g3 -Ofast

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