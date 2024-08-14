# env: bash

sheferna@c3r7s2:/home/sheferna/Desktop$ env 1
env: ‘1’: No such file or directory

sheferna@c3r7s2:/home/sheferna/Desktop$ env ajkshdakjs
env: ‘ajkshdakjs’: No such file or directory

sheferna@c3r7s2:/home/sheferna/Desktop$ env -
sheferna@c3r7s2:/home/sheferna/Desktop$ 

sheferna@c3r7s2:/home/sheferna/Desktop$ env ?
env: ‘?’: No such file or directory

sheferna@c3r7s2:/home/sheferna/Desktop$ env .
env: ‘.’: Permission denied

sheferna@c3r7s2:/home/sheferna/Desktop$ env +
env: ‘+’: No such file or directory

sheferna@c3r7s2:/home/sheferna/Desktop$ env uioj gyufu
env: ‘uioj’: No such file or directory

sheferna@c3r7s2:/home/sheferna/Desktop$ env -1
env: invalid option -- '1'
Try 'env --help' for more information.

env env igual que si fuera env


# $?

bash-3.2$ env -
bash-3.2$ echo $?
0
bash-3.2$ env 1
env: 1: No such file or directory
bash-3.2$ echo $?
127
bash-3.2$ env asjdhajs
env: asjdhajs: No such file or directory
bash-3.2$ echo $?
127
bash-3.2$ env -
bash-3.2$ echo $?
0
bash-3.2$ env ?
env: ?: No such file or directory
bash-3.2$ echo $?
127
bash-3.2$ env .
env: .: Permission denied
bash-3.2$ echo $?
126
bash-3.2$ env +
env: +: No such file or directory
bash-3.2$ echo $?
127
bash-3.2$ env aljshd askjd
env: aljshd: No such file or directory
bash-3.2$ echo $?
127
bash-3.2$ env -1
env: invalid option -- '1'
Try 'env --help' for more information.
bash-3.2$ echo $?
1
bash-3.2$ env env
bash-3.2$ echo $?
0

# minishell

./minishell
minishell$ env 1
env: '1': No such file or directory
status: 127
minishell$ echo $?
127
minishell$ env asjhdas
env: 'asjhdas': No such file or directory
status: 127
minishell$ echo $?
127
minishell$ env -
status: 0
minishell$ echo $?
0
minishell$ env ?
env: '.': Permission denied
status: 126
minishell$ echo $?
126
minishell$ env .
env: '.': Permission denied
status: 126
minishell$ echo $?
126
minishell$ env +
env: '+': No such file or directory
status: 127
minishell$ echo $?
127
minishell$ env ajshd aksjd
env: 'ajshd': No such file or directory
status: 127
minishell$ echo $?
127
minishell$ env -1
env: invalid option -- '1'
Try 'env --help' for more information.
status: 1
minishell$ echo $?
1
minishell$ env env
minishell$ echo $?
0