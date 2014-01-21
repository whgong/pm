del test.exe

del DualLinkedList.o

del DualLinkedListTester.o

gcc -c DualLinkedList.c -o DualLinkedList.o

ar cqs libDualLinkedList.a DualLinkedList.o

gcc -c DualLinkedListTester.c -o DualLinkedListTester.o

gcc DualLinkedListTester.o -static -L. -lDualLinkedList -o test.exe