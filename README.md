# Aplha Compiler And Virtual Machine   
### _hy340 project - spring 2023_
## About
A compiler and a virtual machine for the dynamically-typed programming language 'Alpha'.
Implementation:  
- Lexical Analysis: flex/C  
- Syntax Analysis: bison/C  
- Intermediate Code Generation: bison/C  
- Target Code Generation: C  
- Virtual Machine: C++  

Has been tested on: Ubuntu, Debian, MacOS  
Note: does not work on Windows

## Members
csd4623 Konstantinos Delis  
csd4807 Dimitris Kleinaftakis  
## Make Targets
`make all`: compile all files, creates executables _alphac_ and _avm_  
`make compiler`: compiles only the alpha compiler and creates _alphac_    
`make alphavm`: compiles only the alpha vm and creates _avm_   
`make clean`: remove executables, and compiler generated files (.o object files, .abc binary files and quads_out.txt if -debug has been used)  
`make cleanbinaries`: removes only binaries (.abc)  
`make cleanexecutables`: removes only executables ( _alphac_ and _avm_)  
`make again`: compiles all files and generates again lexer and parser (Warning: don't use if you don't have flex and bison installed)  

## How To Run  
   
### Alpha Compiler  
Run command `./alphac` on linux and `./alphac.out` on mac, with these flags:  
- `-in input.asc`: where input.asc in the alpha file that will be compiled. If skiped stdin will be used  
- `-o binaryFileName`:  where binaryFileName the name of the binary file that will be created. Default is 'binary.abc. Note: don't add file extension, '.abc' will be added by default  
- `-debug`: used for debugging. Syntax analysis, hashtable, intermediate/target code and constant tables will be printed  

### Alpha Virtual Machine  
After creating the binary file with the alpha compiler you can run it using command `./avm` on linux or `./avm.out` on mac, with these flags:  
- `binaryFile.abc`: where binaryFileName the name of the binary file was created. Note: avm allows only files with .abc file extension  
- `-debug`: used for debugging. Will print tables and instructions loaded from binary file and will print output for each instruction that is executaed

## Supported Library Functions  
function | description  
---|---  
_print(...)_ | prints all arguments from left to right  
_input(0)_ | reads either number of string ftrom stdin  
_typeof(1)_ | returns a string describing the type of the argument that was pushed  
_argument(1)_ | return the i-th argument of the current function call  
_totalarguments(0)_ | returns the total arguments passed to the current function call. Use with _argument(1)_ to create variatic functions  
_sin(1)_ | return sin of the argument(in degrees)  
_cos(1)_ | return cos of the argument(in degrees)  
_sqrt(1)_ | return sqrt of the argument  
_pow(2)_ | returns the first argument to the power indicated by the second argument  
_abs(1)_ | returns the absolute value of the argument  
_real2int(1)_ | rounds down the argument to an integer  
_assert(...)_ | works like C's assert() function but can take a list of boolean expressions instead of 1  
_objectcopy(1)_ | creates a shallow copy of the object(argument)  
_objecttotalmembers(1)_ | returns the total members of the object(argument)   
_objectmemberkeys(1)_ | returns a new table with all the keys of the object(argument)  
_objectmemberindices(1)_ | returns a new table with all the integer keys of the object(argument)  
_objectmemberstrings(1)_ | returns a new table with all the string keys of the object(argument)  

## Extra Features
Added extra library functions: pow, real2int, assert, abs, objectmemberindices, objectmemberstrings  
Added extra token: endl, works like std::endl from C++  

