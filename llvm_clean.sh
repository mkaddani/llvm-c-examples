CC="gcc"
CFLAGS=$(llvm-config-14 --cflags)
LD="g++"
LDFLAGS=$(llvm-config-14 --libs --cflags --ldflags core analysis executionengine MCJIT interpreter native)

if [ $# -ne 1 ]; 
    then echo "usage: ./llvm_c_execute.sh <file.c>"
	exit 1;
fi

echo $CC
echo $CFLAGS
echo $LD
echo $LDFLAGS

rm *.o *.exec *.bc *.out