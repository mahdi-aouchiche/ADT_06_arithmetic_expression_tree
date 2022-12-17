# Abstact Data Types : Arithmetic Expression Tree

Author: Mahdi Aouchiche (<https://github.com/mahdi-aouchiche/ADT_06_arithmetic_expression_tree>)

* Implement an arithmetic expression tree and display a visualization using graphviz program.
* Create a tree node of each operand and operation.
* Implement inflix, preflix, postflix functions which print the 3 different ways to read the arithmetic expression.
* Implement a visual tree function which displays the tree as a graph in output files folder using graphviz.
  * If the graphviz program is not installed or not installed correctly you can use an alternative to copy the ".dot" file and paste it in webgraphviz.com to see the expression tree visualization.
* Open the output_files folder and see all the ".dot" files and the visualization images of each tree in the given 3 examples.
* If the user inputs an arithmetic expression when prompted the ".dot" file and the visualization images are writen to "my_expression.dot" and "my_expression.jpg" respectively.

## To run the project nicely run the following commands

```c++
cmake -S . -B build
cmake --build build/ 
```

## 1 executable is created, use the following command to run an executable

```c++
// run the code
./build/arithmetic_expression
```
