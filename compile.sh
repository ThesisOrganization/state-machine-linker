#files=$(python state_machine_linker.py)
#echo $files
#make $files

files=$(python state_machine_linker.py)

#echo $files

IFS='|'
read -ra divided <<< "$files"

#divided=($(echo $files | tr "|" "\n"))
#echo ${divided[0]}
#echo ${divided[1]}

file_c=${divided[0]}
file_h=${divided[1]}

#file_c=$(cat file_c.txt)
#file_h=$(cat file_h.txt)

make PASSING_C="$file_c" PASSING_H="$file_h"
