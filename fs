     1	NAME 				= minishell
     2	BONUS_NAME 		= checker
     3	CFLAGS 			= #-Wall -Wextra -Werror
     4	CC 				= cc
     5	RM 				= rm -f
     6	LIBFT				= libft/libft.a
     7	PRINTF			= libft/ft_printf/libftprintf.a
      	
     8	# SRCS_BONUS=
      	
     9	SRCS_MAND= 		./src/main.c								\
    10					./src/parse.c								\
    11					./src/init.c								\
    12					./src/envp/envp_node.c						\
    13					./src/envp/export_node.c					\
    14					./src/builtins/env.c						\
    15					./src/builtins/export_with_args.c			\
    16					./src/builtins/unset.c						\
    17					./src/builtins/pwd.c						\
    18					./src/builtins/echo.c						\
    19					./src/builtins/cd.c							\
    20					./src/signals/sig_handler.c					\
    21					./src/signals/sig_init.c					\
    22					./src/utils/utils.c							\
    23					./src/utils/split_string.c					\
    24					./src/utils/cbc_str_join.c					\
    25					./src/tokenize/display_tokens.c				\
    26					./src/tokenize/tokenize_utils1.c			\
    27					./src/tokenize/tokenize_utils2.c			\
    28					./src/tokenize/tokenize.c					\
    29					./src/tokenize/check_der.c					\
    30					./src/tokenize/qoute_check.c				\
    31					./src/tokenize/check_pipe_dub.c				\
    32					./src/tokenize/ft_split_qotes.c				\
    33					./src/tokenize/redirections_utiles1.c		\
    34					./src/tokenize/redirections.c				\
    35					./src/tokenize/redirections_utiles2.c		\
    36					./src/expand/expand.c						\
    37					./src/expand/utils.c						\
    38					./src/expand/expand_var.c					\
    39					./src/expand/expand_quotes.c				\
    40					./src/expand/expand_exit.c					\
    41					./src/executor/executor.c					\
    42					./src/executor/utils.c						\
    43					./src/free/free_global_struct.c				\
    44					./src/free/free.c							\
    45					./get_next_line/get_next_line.c				\
    46					./get_next_line/get_next_line_utils.c		\
    47					./src/executor/ex_main.c					\
    48					./src/executor/file_create.c				\
      	
    49	M_OBJ 		= ${SRCS_MAND:.c=.o}
    50	B_OBJ 		= ${SRCS_BONUS:.c=.o}
      	
    51	%.o: %.c
    52		${CC} -c $< -o $@ ${CFLAGS}
      	
    53	${NAME}: ${LIBFT} ${PRINTF} ${M_OBJ}
    54			${CC} ${CFLAGS} ${M_OBJ} libft/ft_printf/libftprintf.a libft/libft.a -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include -o ${NAME}
      	
    55	# ${BONUS_NAME}:  ${LIBFT} ${PRINTF} ${B_OBJ}
    56	# 		${CC} ${CFLAGS} ${B_OBJ} libft/ft_printf/libftprintf.a libft/libft.a -o ${BONUS_NAME}
      	
      	
    57	${PRINTF}:	
    58			make all -C libft/ft_printf
      	
    59	${LIBFT}:	
    60			make all -C libft
    61			make bonus -C libft
      	
    62	all:	${NAME} 
      	
    63	# bonus:	${BONUS_NAME}
      	
    64	clean:	
    65			${RM} ${M_OBJ} 
    66			make fclean -C libft
    67			make fclean -C libft/ft_printf	
    68		
    69	fclean:	clean
    70			${RM} ${NAME}
      	
    71	re:	fclean all
      	
    72	.PHONY:	all clean fclean re
      	
      	
