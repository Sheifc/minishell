
# EN RAMA EXECUTOR2: 12 AGOSTO

# LOS PASA COMO BASH

cat | cat | ls

cat /dev/random | head

pwd > out | echo sheila > out1 | cat < infile | sort

echo hi | echo hello | echo bye

# NO LOS PASA

pwd > out | echo sheila > out1 | cat < infile > out2 | cat < infile | sort

cat < infile > out2 | cat < infile | sort

echo hi > out > out1 > out2

# NO LLEGAN BIEN LOS FDS NI EL STATUS: BONUS SIN PODER TESTEAR Y PENDIENTE DE TESTEAR EXEC ONE COMMAND - ACTUALMENTE NO PASA LA REDIRECCION MULTIPLE