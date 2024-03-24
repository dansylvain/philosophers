#!/bin/bash

# Définition du nom du fichier de sortie
output_file="output.txt"

# Compilation
make > "$output_file" 2>&1

# Exécution avec valgrind --leak-check=full --show-leak-kinds=all
echo ">>> Running with valgrind --leak-check=full --show-leak-kinds=all" >> "$output_file"
valgrind --leak-check=full --show-leak-kinds=all ./philo 4 800 200 200 4 2>&1 | { grep -q "0x" && cat || echo "No memory leaks detected."; } 


# Exécution avec valgrind --tool=drd
echo ">>> Running with valgrind --tool=drd" >> "$output_file"
valgrind --tool=drd ./philo 4 800 200 200 4 2>&1 | { grep -q "0x" && cat || echo "No drd problem detected."; }
 

# Exécution avec valgrind --tool=helgrind
echo ">>> Running with valgrind --tool=helgrind" >> "$output_file"
valgrind --tool=helgrind ./philo 4 800 200 200 4 2>&1 | { grep -q "0x" && cat || echo "No helgrind proble detected."; } 
