#include <iostream>
#include "arithmetic_expression.cpp"
using namespace std;

int main(){
  /* Create an output file */
  const char* remove_existing_directory = "rm -rf output_files";
  const char* create_directory = "mkdir output_files"; 
  system(remove_existing_directory);
  system(create_directory);
      
  /* Use 3 examples of expression trees */
  { // example 1:
    string expr1 = "a+b*c";
    arithmeticExpression ex1(expr1);
    ex1.buildTree();                                   
    cout << "expression 1: " << expr1 << endl;
    cout << "infix: "; ex1.infix(); cout << endl;
    cout << "prefix: "; ex1.prefix(); cout << endl;
    cout << "postfix: "; ex1.postfix(); cout << endl;
    ex1.visualizeTree("./output_files/expr1.dot");
    cout << endl;
  }
  { // example 2:
    string expr2 = "(a+b)*(c-d)";
    arithmeticExpression ex2(expr2);
    ex2.buildTree();
    cout << "expression 2: " << expr2 << endl;
    cout << "infix: "; ex2.infix(); cout << endl;
    cout << "prefix: "; ex2.prefix(); cout << endl;
    cout << "postfix: "; ex2.postfix(); cout << endl;
    ex2.visualizeTree("./output_files/expr2.dot");
    cout << endl;
  }
  { // example 3:
    string expr3 = "a + b * c - ( d * e + f ) * g";
    arithmeticExpression ex3(expr3);
    ex3.buildTree();
    cout << "expression 3: " << expr3 << endl;
    cout << "infix: "; ex3.infix(); cout << endl;
    cout << "prefix: "; ex3.prefix(); cout << endl;
    cout << "postfix: "; ex3.postfix(); cout << endl;
    ex3.visualizeTree("./output_files/expr3.dot");
    cout << endl;
  }
  
  cout << "Graphs of the arithmetic expression trees are writen to \"output_files directory\"." << endl;
  cout << "Arithmetic expression trees are writen to \"output_files directory\"." << endl;
  cout << endl;

  /* Take user input to build different arithmetic expressions */
  { 
    string my_expression = "";
    char c = 'Y';

    while ( true ) {
      cout << "Do you want to enter an arithmetic expression?" << endl;
      cout << "Enter Y to continue Or any other key to exit." << endl;
      cin >> c;
      cin.ignore();  // ignore carriage return
    
      if(!( c == 'Y' || c == 'y')) { break; }

      cout << "Enter an arithmetic expression: ";
      getline(cin, my_expression);
      cout << my_expression << endl;

      arithmeticExpression expression(my_expression);
      expression.buildTree();
      cout << "expression: " << my_expression << endl;
      cout << "infix     : "; expression.infix()  ; cout << endl;
      cout << "prefix    : "; expression.prefix() ; cout << endl;
      cout << "postfix   : "; expression.postfix(); cout << endl;
      expression.visualizeTree("./output_files/my_expression.dot");
      cout << endl;
    }
  }
  
  return 0;
}