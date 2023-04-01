clang -Wall -Werror -Wextra -c logic/filematch.c
clang -Wall -Werror -Wextra -c logic/hashtable.c
clang -Wall -Werror -Wextra -o run filematch.o hashtable.o logic/proj.c