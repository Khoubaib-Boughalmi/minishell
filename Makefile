NAME 				= minishell
BONUS_NAME 		= checker
CFLAGS 			= #-Wall -Wextra -Werror
CC 				= cc
RM 				= rm -f
LIBFT				= libft/libft.a
PRINTF			= libft/ft_printf/libftprintf.a

# SRCS_BONUS=

SRCS_MAND= 		./src/main.c								\
				./src/parse.c								\
				./src/init.c								\
				./src/envp/envp_node.c						\
				./src/envp/export_node.c					\
				./src/builtins/env.c						\
				./src/builtins/export_with_args.c			\
				./src/builtins/unset.c						\
				./src/builtins/pwd.c						\
				./src/builtins/echo.c						\
				./src/builtins/cd.c							\
				./src/builtins/utils.c							\
				./src/signals/sig_handler.c					\
				./src/signals/sig_init.c					\
				./src/utils/utils.c							\
				./src/utils/split_string.c					\
				./src/utils/cbc_str_join.c					\
				./src/tokenize/display_tokens.c				\
				./src/tokenize/tokenize_utils1.c			\
				./src/tokenize/tokenize_utils2.c			\
				./src/tokenize/tokenize.c					\
				./src/tokenize/check_der.c					\
				./src/tokenize/qoute_check.c				\
				./src/tokenize/check_pipe_dub.c				\
				./src/tokenize/ft_split_qotes.c				\
				./src/tokenize/redirections_utiles1.c		\
				./src/tokenize/redirections.c				\
				./src/tokenize/redirections_utiles2.c		\
				./src/expand/expand.c						\
				./src/expand/utils.c						\
				./src/expand/expand_var.c					\
				./src/expand/expand_quotes.c				\
				./src/expand/expand_exit.c					\
				./src/executor/executor.c					\
				./src/executor/utils.c						\
				./src/free/free_global_struct.c				\
				./src/free/free.c							\
				./get_next_line/get_next_line.c				\
				./get_next_line/get_next_line_utils.c		\
				./src/executor/ex_main.c					\
				./src/executor/file_create.c				\

M_OBJ 		= ${SRCS_MAND:.c=.o}
B_OBJ 		= ${SRCS_BONUS:.c=.o}

%.o: %.c
	${CC} -c $< -o $@ ${CFLAGS}

${NAME}: ${LIBFT} ${PRINTF} ${M_OBJ}
		${CC} ${CFLAGS} ${M_OBJ} libft/ft_printf/libftprintf.a libft/libft.a -lreadline -L ~/Desktop/readline/8.2.1/lib -I ~/Desktop/readline/8.2.1/include -o ${NAME}
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


