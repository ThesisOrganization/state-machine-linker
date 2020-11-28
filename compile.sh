#files=$(python state_machine_linker.py)
#echo $files
#make $files

python state_machine_linker.py

file_c=$(cat file_c.txt)
file_h=$(cat file_h.txt)

make PASSING_C="$file_c" PASSING_H="$file_h"
