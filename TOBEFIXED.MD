1 - in tokenizing function	: exp ls -la | | cat -e >> out.txt 
==outout==>	COMMAND: ls -la 
			PIPE: | 
			COMMAND: 
			PIPE: | 
			COMMAND: cat -e 
			REDIR: >> out.txt
							: exp ls -la || cat -e >> out.txt 
==outout==>	COMMAND: ls -la 
			PIPE: | 
			COMMAND: cat -e 
			REDIR: >> out.txt
							: exp ls -la || cat -e >>>>>> out.txt 
==outout==>	COMMAND: ls -la 
			PIPE: | 
			COMMAND: cat -e 
			REDIR: >> out.txt
							: exp ls -la |||||||| cat -e >> out.txt 
==outout==>	COMMAND: ls -la 
			PIPE: | 
			COMMAND: cat -e 
			REDIR: >> out.txt
							: exp ls -la ||ls|||||| cat -e >> out.txt 
==outout==>	COMMAND: ls -la 
			PIPE: | 
			COMMAND: ls 
			PIPE: | 
			COMMAND: cat -e 
			REDIR: >> out.txt