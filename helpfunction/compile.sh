clang -Wall -Werror -Wextra -c filematch.c
clang -Wall -Werror -Wextra -c hashtable.c
clang -Wall -Werror -Wextra -o run hashtable.o filematch.o proj.c