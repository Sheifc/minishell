(echo hola && echo hello) || echo bye

(echo hola && echo hello) && echo bye

(echo hola && echo hello) && (echo bye && ls)

(echo hola && echo hello) && (echo bye || ls)

(echo hola && echo hello) || (echo bye && ls)

(echo hola && echo hello) || (echo bye || ls)

(echo hola && ec) || echo bye FAILED

(ec && echo hello) || echo bye FAILED

(echo hola && ec) && echo bye FAILED

(ec && echo hello) && echo bye FAILED

(echo hola && echo hello) && (ec || ls) FAILED

BASH

bash-3.2$ (echo hola && echo hello) || echo bye
hola
hello
bash-3.2$ (echo hola && echo hello) && echo bye
hola
hello
bye
bash-3.2$ (echo hola && echo hello) && (echo bye && ls)
hola
hello
bye
Makefile                infile                  obj                     src
README.md               libft                   paren_tests.md          test_bonus_minishell.sh
includes                minishell               readline.supp
bash-3.2$ (echo hola && echo hello) && (echo bye || ls)
hola
hello
bye
bash-3.2$ (echo hola && echo hello) || (echo bye && ls)
hola
hello
bash-3.2$ (echo hola && echo hello) || (echo bye || ls)
hola
hello
bash-3.2$ (echo hola && ec) || echo bye
hola
bash: ec: command not found
bye
bash-3.2$ (ec && echo hello) || echo bye
bash: ec: command not found
bye
bash-3.2$ (echo hola && ec) && echo bye
hola
bash: ec: command not found
bash-3.2$ (ec && echo hello) && echo bye
bash: ec: command not found
bash-3.2$ (echo hola && echo hello) && (ec || ls)
hola
hello
bash: ec: command not found
Makefile                infile                  obj                     src
README.md               libft                   paren_tests.md          test_bonus_minishell.sh
includes                minishell               readline.supp
bash-3.2$ 
