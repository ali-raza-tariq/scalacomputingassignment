# a build command to build myprogram executable from myprogram.o and mylib.lib
main: main.cpp 
        g++ main main.cpp -std=c++11
