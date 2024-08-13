
# EN RAMA EXECUTOR2: 13 AGOSTO

# LOS PASA COMO BASH

cat | cat | ls

cat /dev/random | head

pwd > out | echo sheila > out1 | cat < infile | sort

echo hi | echo hello | echo bye

echo hi > out > out1 > out2

export a > outfile

export > outfile

# NO LOS PASA

pwd > out | echo sheila > out1 | cat < infile > out2 | cat < infile | sort

cat < infile > out2 | cat < infile | sort



# NO LLEGAN BIEN LOS FDS NI EL STATUS: BONUS SIN PODER TESTEAR Y PENDIENTE DE TESTEAR EXEC ONE COMMAND - ACTUALMENTE NO PASA LA REDIRECCION MULTIPLE