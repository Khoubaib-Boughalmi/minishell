NAME 				= minishell
BONUS_NAME 		= checker
CFLAGS 			= #-Wall -Wextra -Werror
CC 				= cc
RM 				= rm -f
LIBFT				= libft/libft.a
PRINTF			= libft/ft_printf/libftprintf.a

# SRCS_BONUS=

SRCS_MAND= 		./src/main.c							\
				./src/utils.c							\
				./src/parse.c							\
				./src/init.c							\
				./src/envp_node.c						\
				./src/builtins/env.c					\
				./src/builtins/export.c					\
				./src/builtins/unset.c					\
				./src/builtins/pwd.c					\
				./src/builtins/echo.c					\
				./src/builtins/cd.c						\
				./get_next_line/get_next_line.c			\
				./get_next_line/get_next_line_utils.c	\

M_OBJ 		= ${SRCS_MAND:.c=.o}
B_OBJ 		= ${SRCS_BONUS:.c=.o}

%.o: %.c
	${CC} -c $< -o $@ ${CFLAGS}

${NAME}: ${LIBFT} ${PRINTF} ${M_OBJ}
		${CC} ${CFLAGS} ${M_OBJ} libft/ft_printf/libftprintf.a libft/libft.a -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include -o ${NAME}

# ${BONUS_NAME}:  ${LIBFT} ${PRINTF} ${B_OBJ}
# 		${CC} ${CFLAGS} ${B_OBJ} libft/ft_printf/libftprintf.a libft/libft.a -o ${BONUS_NAME}


${PRINTF}:	
		make all -C libft/ft_printf

${LIBFT}:	
		make all -C libft
		make bonus -C libft

all:	${NAME} 

# bonus:	${BONUS_NAME}

clean:	
		${RM} ${M_OBJ} 
		make fclean -C libft
		make fclean -C libft/ft_printf	
	
fclean:	clean
		${RM} ${NAME}

re:	fclean all

.PHONY:	all clean fclean re
