if [[ $# -ne 1 ]] 
then
     echo "Please write only the filename."
else
     if [[ ! -f "$1" ]]
     then
         echo "File does not exist."
     else
         cat "$1" /dev/tty | ./a.out
     fi
fi
