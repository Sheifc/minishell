#!/bin/bash

# Path to the minishell executable
MINISHELL=./minishell

# Colores
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # Sin color

# Function to run a test
run_test() {
    local command="$1"
    local expected_output="$2"
    local test_description="$3"
    
    echo -e "\nRunning: $command\n"
    
    # Run the command in minishell and capture the output
    echo "$command" | $MINISHELL > minishell_output.txt 2>&1
    
    # Compare the output
    diff <(echo "$expected_output") minishell_output.txt > /dev/null 2>&1
    
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}[PASS] $test_description${NC}\n"
    else
        echo -e "${RED}[FAIL] $test_description${NC}\n"
        echo "Expected:"
        echo -e "$expected_output\n"
        echo "Got:"
        cat minishell_output.txt
        echo
    fi
    
    # Clean up
    rm minishell_output.txt
}

# Define your tests
run_test "echo hola || echo hello" "hola" "Test 1: echo hola || echo hello"
run_test "ec hola || echo hello" "Error: command not found: No such file or directory
hello" "Test 2: ec hola || echo hello"
run_test "ec || echo hola && echo hello" "Error: command not found: No such file or directory
hola
hello" "Test 3: ec || echo hola && echo hello"
run_test "echo hola && echo hello || echo bye" "hola
hello" "Test 4: echo hola && echo hello || echo bye"
run_test "echo hola && ec hello || echo bye" "hola
Error: command not found: No such file or directory
bye" "Test 5: echo hola && ec hello || echo bye"
run_test "(echo hola && ec hello) || echo bye" "hola
Error: command not found: No such file or directory
bye" "Test 6: (echo hola && ec hello) || echo bye"
run_test "echo hola && echo hello && echo bye" "hola
hello
bye" "Test 7: echo hola && echo hello && echo bye"
run_test "(echo hola && echo hello) && echo bye" "hola
hello
bye" "Test 8: (echo hola && echo hello) && echo bye"
run_test "echo hola || echo hello || echo bye" "hola" "Test 9: echo hola || echo hello || echo bye"
run_test "(echo hola || echo hello) || echo bye" "hola" "Test 10: (echo hola || echo hello) || echo bye"
run_test "echo hola || (echo hello && echo bye)" "hola" "Test 11: echo hola || (echo hello && echo bye)"
run_test "ec hola || (echo hello && echo bye)" "Error: command not found: No such file or directory
hello
bye" "Test 12: ec hola || (echo hello && echo bye)"
run_test "(echo hola && echo hello) || (echo bye && echo adios)" "hola
hello" "Test 13: (echo hola && echo hello) || (echo bye && echo adios)"
run_test "(echo hola || echo hello) && (echo bye && echo adios)" "hola
bye
adios" "Test 14: (echo hola || echo hello) && (echo bye && echo adios)"
run_test "(ec hola && echo hello) || (ec bye y echo adios)" "Error: command not found: No such file or directory
Error: command not found: No such file or directory" "Test 15: (ec hola && echo hello) || (ec bye && echo adios)"
run_test "(echo hola || echo hello) && (echo bye && echo adios)" "hola
bye" "Test 16: (echo hola || echo hello) && (echo bye && echo adios)"
run_test "(ec hola || echo hello) && (ec bye && echo adios)" "Error: command not found: No such file or directory
hello
Error: command not found: No such file or directory
adios" "Test 17: (ec hola || echo hello) && (ec bye y echo adios)"

echo -e "${GREEN}All tests completed.${NC}"
