del *.a
del *.so
del *.o

gcc -c Object_WH_G.c -o Object_WH_G.o
rem gcc -c BaseTypeInteger.c -o BaseTypeInteger.o
rem gcc -c BaseTypeLong.c -o BaseTypeLong.o
rem gcc -c BaseTypeChar.c -o BaseTypeChar.o
rem gcc -c BaseTypeFloat.c -o BaseTypeFloat.o
rem gcc -c BaseTypeDouble.c -o BaseTypeDouble.o
rem gcc -c BaseTypeString.c -o BaseTypeString.o

ar qs libBaseType.a *.o

gcc -c BaseTypeTester.c -o BaseTypeTester.o

gcc BaseTypeTester.o -L. -static -lBaseType -o test.exe

rem gcc -g BaseTypeObject.c BaseTypeInteger.c TestBaseType.c -o test.exe