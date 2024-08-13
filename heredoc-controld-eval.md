# heredoc: bash cuando se hace control D sale un warning y no se cierra, pinta por pantalla los prompts

sheferna@c3r7s2:~/Desktop/minishell$ cat << limit
as
d
asd
asd
dsa
> das
> 
bash: warning: here-document at line 18 delimited by end-of-file (wanted `limit')
as
d
asd
asd
dsa

das

# heredoc: minishell

sheferna@c3r7s2:~/Desktop/minishell$ ./minishell 
minishell$ cat << limit
> as
> d
> sda
> dsa
> ^C
minishell$ cat << limit
> asda
> sd
> dasd
> sa> minishell$ 
exit
sheferna@c3r7s2:~/Desktop/minishell$ ./minishell 
minishell$ asd
Error: command not found: No such file or directory
minishell$ asd
Error: command not found: No such file or directory
minishell$ cat << limit
> asd
> as
> d
> asd
minishell$ 