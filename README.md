# minishell started on : 3 March 2023
## what i have done : 
	1-	create a repl function that takes user's input;
	2-	copy envp data into a new data structure in a key value pair format
	3-	create the env builtin function
	4-	create the export functionality to the new envp linked list	(define new variables)
	5-	create the unset functionality to the new envp linked list		(delete existing variables)
	6-	add all builtins functions (export unset env pwd cd exit echo)
	6-	create signal handlers for ctrl+C ctrl+D ctrl+\
	
## other minor functions in utils.c
	1-	crate a free_split function that frees a char **list