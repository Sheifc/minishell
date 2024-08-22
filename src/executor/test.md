# Echo
    - echo
    - echo hola
    - echo ""
    - echo "" hola
    - echo -n hola
    - echo -n -n hola
    - echo -n -nh -n hola
    - echo -nnnnnnnnn hola
    - echo $?hcudshfuewrf ew  wr 4ew""""
    - echo ""uhjkhnkj"hjbmb"'''' defdjhfkjb "iujiouhj"f'f'f'f'f''f'f'f'f'f'f'
    - echo ""uhjkhnkj"hjbmb"'''' defdjhfkjb "iujiouhj"f'f'a'j'o''i'w'q''q
    - echo ""aaaaaaaa"bbbbb"'''' ccccccccc "dddddddd"e'e'e
    - echo "ho   $USER"  'la   $LESS'   $USER$TERM
    - echo "ho   $USER"'la   $LESS'$USER$TERM
    - echo"ho   $USER"
    - echo"ho   $USE$LESS"
    - "echo ho   $USER"
    - "echo" "ho   $USER"
    - e"cho" "ho   $USER"
    -        echo "ho   $USER"
    - echo "$HOME '$LESS' $USER"
    - echo '$HOME "$LESS" $USER'
    - echo "$HOME '$LESS "pa $TERM" na' $USER"
    - echo '$HOME "$LESS 'pa $TERM' na" $USER'
    - echo '$'"HOME"

# Export
    - export a=b
    - export b=wawa
    - export b=lala
    - export c=lala=kaka
    - export a
    - export a=
    - export a= b=o
    - export a===
    - export a3=l
    - export 2a=lala
    - export !a=ma
    - export $USER=la
    - export $USER=$TERM
    - export $USER=$TERM$HOME
    - export $USER=$TERM$HOM
    - export $HOME=$USER
    - export $USER$SHLVL
    - export
    -            export
    - export ""
    - export a b=$LESS $USER $HOME=la $COLORTERM=pa c=d

# cd
    - directorio existe PASSED
    - directorio no existe PASSED
    - file existe PASSED
    - cd passed
    -            cd PASSED
    - cd - = $OLDPWD PASSED
    - cd ~ = $HOME PASSED
    - cd $HOME si $HOME no existe -----> unset $HOME no lo elimina?
    - cd directorio con distintos permisos PASSED

minishell$ unset $HOME

**** List of Commands: ****
 Command: unset
    Arg[0]: unset (5)
    Arg[1]: /Users/sheila (13)
  fd_in: -1, fd_out: -1
  next_operator: END [12]
  redirect: None [0]
  parenthesis: 0, parenthesis_status: None [0], 
minishell$ 

# Env
    - env PASSED
    - env lalal PASSED
    - env directorio PASSED

# pwd 
    - con y sin argumentos PASSED

# unset
    - con y sin argumentos PASSED
    - varios argumentos PASSED

# exit 
    - exit PASSED
    - exit 0 PASSED 
    - exit 1 PASSED 
    - exit 42 PASSED
    - exit lalal PASSED

# pipe
    - ls | wc PASSED
    - ls|wc PASSED
    - sort colors.txt | uniq | sort -r | wc PASSED
    - ls || wc FAILED, DEFENDIBLE
    - ls |   | wc bash: syntax error near unexpected token `|' bash-3.2$ echo $? 258
    - ls |   >/>>/</<< wc FAILED, SE EJECUTA > QUE NO DEBE PASAR Y AL HACER CONTROL D DA SEG FAULT POR SANITIZER
    - ls | wc | bash: syntax error: unexpected end of file bash-3.2$ echo $? 258
    - | bash: syntax error near unexpected token `|' bash-3.2$ echo $? 258
    - | ls | wc bash: syntax error near unexpected token `|' bash-3.2$ echo $? 258

# redirecciones
    - </<</>/>> bash: syntax error near unexpected token `newline' bash-3.2$ echo $? 258
    - echo hola >>>>>>> file bash: syntax error near unexpected token `>>' bash-3.2$ echo $? 258
    - echo hola <<<<<<< file bash: syntax error near unexpected token `<<<' bash-3.2$ echo $? 258
    - echo hola>file PASSED
    - echo hola </<</>/>>   </<</>/>> file FAILED SANITIZER bash-3.2$ echo hola </<</>/>>   </<</>/>> file bash: syntax error near unexpected token `<' bash-3.2$ echo $? 258
    - echo hola </<</>/>>   | file FAILED SANITIZER bash-3.2$ echo hola </<</>/>>   | file bash: syntax error near unexpected token `|' bash-3.2$ ECHO $? 258
    - echo hola > file </<</>/>> PASSED
    - echo hola > file FAILED: habiendo un archivo ya creado con el mismo nombre "file", crea otro nuevo con el mismo nombre "file", REVISAR
    - echo hola > file > file2 > file3 PASSED
    - echo hola > file > file2 > file3 | ls PASSED
    - wc < colors.txt PASSED
    - wc < colors.txt > file FAILED SANITIZER
    - cat colors.txt | wc PASSED
    - echo hola > file << EOF PASSED
    - cat << EOF > file PASSED
    - << EOF FAILED SANITIZER
    - cat << hola << que << tal FAILED
    - cat << hola << que << tal -> aplicarle señales a heredoc 
    - cat << EOF | ls   PASSED
    - echo hola | cat | cat | cat | cat | cat | cat | cat PASSED

# general
    - enter en input -> vacio PASSED
    - solo espacios PASSED
    - comillas sin cerrar PASSED
    - echo $? PASSED
    - unset $PATH -> ls -> /bin/ls PASSED
    - unset $HOME -> cd PASSED