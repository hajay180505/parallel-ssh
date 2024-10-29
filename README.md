# parallel-ssh

Installation
------------

Pull the source code and run `make` to compile `sshp`:

``` console
$ make
cc -o src/fdwatcher.o -c -D USE_KQUEUE=0 -Wall -Werror -Wextra -Wpedantic -O2 src/fdwatcher.c
cc -o sshp -Wall -Werror -Wextra -Wpedantic -O2 src/sshp.c src/fdwatcher.o
$ ./sshp -v
v1.0.0
```
