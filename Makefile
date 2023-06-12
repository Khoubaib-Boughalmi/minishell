NAME 				= minishell
CFLAGS             = -Wall -Werror -Wextra
CC 				= cc
RM 				= rm -f
LIBFT				= libft/libft.a
PRINTF			= libft/ft_printf/libftprintf.a

SRCS_MAND= 		./src/main.c								\
				./src/parse.c								\
				./src/parse2.c								\
				./src/init.c								\
				./src/envp/envp_node.c						\
				./src/envp/export_node.c					\
				./src/builtins/env.c						\
				./src/builtins/export_with_args.c			\
				./src/builtins/export_no_args.c				\
				./src/builtins/export_norm_file.c			\
				./src/builtins/export_get_key_val.c			\
				./src/builtins/unset.c						\
				./src/builtins/pwd.c						\
				./src/builtins/echo.c						\
				./src/builtins/cd.c							\
				./src/builtins/utils.c						\
				./src/builtins/exit.c						\
				./src/signals/sig_handler.c					\
				./src/signals/sig_init.c					\
				./src/utils/utils.c							\
				./src/utils/utils2.c						\
				./src/utils/split_string.c					\
				./src/utils/cbc_str_join.c					\
				./src/tokenize/tokenize_utils1.c			\
				./src/tokenize/tokenize_utils2.c			\
				./src/tokenize/tokenize.c					\
				./src/tokenize/check_der.c					\
				./src/tokenize/check_pipe_dub.c				\
				./src/tokenize/ft_split_qotes.c				\
				./src/tokenize/redirections_utiles1.c		\
				./src/tokenize/redirections.c				\
				./src/tokenize/redirections_utiles2.c		\
				./src/tokenize/token_insert.c				\
				./src/tokenize/rediraction_insert.c			\
				./src/tokenize/syntax_errors.c				\
				./src/expand/expand.c						\
				./src/expand/utils.c						\
				./src/expand/expand_var.c					\
				./src/expand/expand_var_redirect.c			\
				./src/expand/expand_quotes.c				\
				./src/expand/expand_quotes_red.c			\
				./src/expand/expand_redirections_fname.c	\
				./src/expand/expand_exit.c					\
				./src/expand/expand_redirection_vars.c		\
				./src/executor/executor.c					\
				./src/executor/utils.c						\
				./src/executor/utile_execute.c				\
				./src/executor/redirections.c				\
				./src/executor/exute.c						\
				./src/executor/reder_heredoc.c				\
				./src/executor/list_cmd_red.c				\
				./src/executor/utile_execute2.c				\
				./src/free/free_global_struct.c				\
				./src/free/free.c							\
				./get_next_line/get_next_line.c				\
				./get_next_line/get_next_line_utils.c		\
				./src/executor/ex_main.c					\
				./src/executor/file_create.c				\

M_OBJ 		= ${SRCS_MAND:.c=.o}

%.o: %.c
	${CC} -c $< -o $@ ${CFLAGS}

${NAME}: ${LIBFT} ${PRINTF} ${M_OBJ}
		${CC} ${CFLAGS} ${M_OBJ} libft/ft_printf/libftprintf.a libft/libft.a -lreadline -L /Users/rennatiq/Desktop/readline/8.2.1/lib -I  /Users/rennatiq/Desktop/readline/8.2.1/include -o ${NAME}

${PRINTF}:	
		make all -C libft/ft_printf

${LIBFT}:	
		make all -C libft
		make bonus -C libft

all:	${NAME} 

clean:	
		${RM} ${M_OBJ} 
		make fclean -C libft
		make fclean -C libft/ft_printf	
	
fclean:	clean
		${RM} ${NAME}

re:	fclean all

.PHONY:	all clean fclean re


