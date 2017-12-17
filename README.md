# interpreter

I design my Interpreter.cpp by C++ in Object-oriented approach and I used my tokenizer which I finished it last time.
In object-oriented approach, we do not have ParseTree class and I have many classes including Prog, Stmt, Decl.
Each class are with three methods parser, printer, executor.
I seperate my project into three parts.
First, Parser consumes stream of tokens, produces the abstract parse tree (PT).
Second, Printer prints the original program in a pretty format with the abstract parse tree (PT)
 which we obtain it from parser.
Third, executor truly executes the program and give the output from "Output".

I tested my program with programs from professor Neelam's website. I seperate the input file and coreProgram file.

TA can use my interpreter by type
g++ -o test Interpreter.cpp
./test coreProgram.txt InputData.txt
the last two items can be changed with coreProgram2.txt or coreProgram3.txt 
but please remember to change the Input file such as InputData2_1.txt.
 
