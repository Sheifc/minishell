# minishell

minishell$ asd
Error: command not found: No such file or directory
minishell$ echo $?
127
minishell$ echo $? $?
0 0
minishell$ asd
Error: command not found: No such file or directory
minishell$ echo $? $?
127?
minishell$ 
minishell$ 
exit

# bash

sheferna@c3r7s2:~/Desktop/minishell$ asd
Command 'asd' not found, but there are 21 similar ones.
sheferna@c3r7s2:~/Desktop/minishell$ echo $? $?
127 127
sheferna@c3r7s2:~/Desktop/minishell$ 

# minishell

minishell$ asd
Error: command not found: No such file or directory
minishell$ expr $? + $?
expr: syntax error: unexpected argument ‘127’
minishell$ exit
exit

# bash:

sheferna@c3r7s2:~/Desktop/minishell$ asd
Command 'asd' not found, but there are 21 similar ones.
sheferna@c3r7s2:~/Desktop/minishell$ expr $? + $?
254
sheferna@c3r7s2:~/Desktop/minishell$ 

# minishell

minishell$ echo $?$?
00
minishell$ expr $?$?
00
minishell$ expr $? + $?
2
minishell$ expr $? + $?
0
minishell$ expr $? + $?
2
minishell$ expr $? + $?
0
minishell$ expr $? + $?
2
minishell$ expr $? + $?
0
minishell$ expr $? + $?
2
minishell$ asd
Error: command not found: No such file or directory
minishell$ echo $? $?
127?
minishell$ asd
Error: command not found: No such file or directory
minishell$ expr $?
127
minishell$ echo $?
0
minishell$ asd
Error: command not found: No such file or directory
minishell$ expr $? + $?
expr: syntax error: unexpected argument ‘127’
minishell$ 