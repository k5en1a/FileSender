OUT				=	client.c server.c

CC				= clang
CFLAGS			= -Wall -Wextra -Werror

NAME			= client server
O				= $(OUT:.c=.o)
$(NAME):		%: %.c
				$(CC) $(CFLAGS) -o $@ $<
all: 			$(NAME)

RM				= rm -f
clean:
				$(RM) $(O)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

%.o:			%.c
				$(CC) $(CFLAGS) -c $< -o $@

.PHONY:			all clean fclean re