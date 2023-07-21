""" Using C - API
```
CC="gcc"
CFLAGS=$(llvm-config-14 --cflags)
LD="g++"
LDFLAGS=$(llvm-config-14 --libs --cflags --ldflags core analysis executionengine MCJIT interpreter native)

bill: bill.o
	$(LD) bill.o $(LDFLAGS) -o bill

bill.o: bill.c
	$(CC) $(CFLAGS) -c bill.c

CFLAGS= -I/usr/lib/llvm-14/include  -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -fsanitize=address -g
LD=g++
LDFLAGS= -I/usr/lib/llvm-14/include -std=c++14   -fno-exceptions -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -L/usr/lib/llvm-14/lib -lLLVM-14 -fsanitize=address -g
```
"""

import subprocess
import sys
import argparse

def execute_command(command):
    """Executes a command and returns its output."""
    command = [s for s in command if s != '']

    p = subprocess.Popen(command, stdout=subprocess.PIPE, 
                                    stderr=subprocess.PIPE)
    out, err = p.communicate()
    return(str(out.decode("utf-8")))


if __name__ == "__main__":
    cc = "gcc"
    llvm_cflags = execute_command(["llvm-config-14" ,"--cflags"])
    ld = "g++"
    ld_flags = execute_command("llvm-config-14 --libs --cflags --ldflags core analysis executionengine MCJIT interpreter native".split(' '))
    ld_flags += " -std=c++14   -fno-exceptions "
    ld_flags = ld_flags.replace("\n"," ")

    parser = argparse.ArgumentParser(
                    prog='llvm easy compilation',
                    description='this tool make it easy to compile llvm-c api code, just add the c file and it will generate an output and byte-code file and using the translte flag it will give you even the llvm ll file',
                    epilog='Text at the bottom of help')
    parser.add_argument('-filename', action='store', type=str, required=True)
    parser.add_argument('-src', action='store', choices=["c", "llvm"], default="c")
    args = parser.parse_args()
    

    if args.src == "c":
        print("creating object =====")
        cmd = f'{cc} {llvm_cflags} -c {args.filename}'
        print(cmd)
        execute_command(cmd.split(' '))
        print("creating executable ======")
        cmd = f'{ld} {str(args.filename).replace(".c",".o")} {ld_flags} -o {str(args.filename).replace(".c",".exec")}'
        print(cmd)
        execute_command(cmd.split(' '))




