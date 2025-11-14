--------------------------------------------------------
Files Included
--------------------------------------------------------

ref_daxpy.cpp / ref_daxpy.hpp
ref_dgemv.cpp / ref_dgemv.hpp
ref_dgemm.cpp / ref_dgemm.hpp
ref_axpyt.cpp / ref_axpyt.hpp
ref_gemvt.cpp / ref_gemvt.hpp
ref_gemmt.cpp / ref_gemmt.hpp
refBLAS.hpp           # Master header
librefBLAS.so         # Shared library
test_refBLAS.cpp      # Test driver

--------------------------------------------------------
Build Instructions
--------------------------------------------------------

Step 1: Compile each source file into object files (.o)

g++ -std=c++11 -c -fPIC ref_daxpy.cpp   -o ref_daxpy.o
g++ -std=c++11 -c -fPIC ref_dgemv.cpp   -o ref_dgemv.o
g++ -std=c++11 -c -fPIC ref_dgemm.cpp   -o ref_dgemm.o
g++ -std=c++11 -c -fPIC ref_axpyt.cpp   -o ref_axpyt.o
g++ -std=c++11 -c -fPIC ref_gemvt.cpp   -o ref_gemvt.o
g++ -std=c++11 -c -fPIC ref_gemmt.cpp   -o ref_gemmt.o


Step 2: Link all object files into a shared library

    g++ -shared -o librefBLAS.so \
        ref_daxpy.o ref_dgemv.o ref_dgemm.o \
        ref_axpyt.o ref_gemvt.o ref_gemmt.o

--------------------------------------------------------
Testing the Shared Library
--------------------------------------------------------

Step 3: Compile the test driver

    g++ -std=c++11 test_refBLAS.cpp -I. -L. -lrefBLAS -o test_refBLAS

Step 4: Set the runtime library path and run the test

    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
    ./test_refBLAS
