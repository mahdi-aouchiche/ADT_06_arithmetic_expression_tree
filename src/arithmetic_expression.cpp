#include "../header/arithmetic_expression.hpp"

arithmeticExpression::arithmeticExpression(const string & expression) {
  this->root = nullptr;
  this->infixExpression = expression;
}

arithmeticExpression::~arithmeticExpression() {
  this->delete_node(this->root);
}

void arithmeticExpression::delete_node(TreeNode * node) {
  if(node == nullptr) {
    return;
  }

  delete_node(node->right);
  delete_node(node->left);
  delete node;
}

void arithmeticExpression::buildTree() {
  
  // convert the infixExpression to postfix string
  this->infixExpression = this->infix_to_postfix(); 
  
  // generate the tree
  stack <TreeNode*> s;    // create a stack of TreeNode pointers
  
  // Go through the portfixExpression  
  char c; 
  TreeNode *newNode, *leftNode, *rightNode;

  for(unsigned i = 0; i < infixExpression.size(); ++i) {
    
    c = infixExpression.at(i);

    // if operand: push a new tree onto the stack
    if(c != '+' && c != '-' && c != '*' && c != '/'){ //c is not an operator
      newNode = new TreeNode( c , ('a' + i));
      s.push(newNode);

    } else {  // c is an operator  
      // if operator: pop two trees from the stack
      rightNode = s.top();  s.pop();
      leftNode  = s.top();  s.pop();

      // use the operator as the root of a new tree with popped trees as children 
      newNode = new TreeNode( c , ('a' + i));
      newNode->left  = leftNode;
      newNode->right = rightNode;  
      
      // push new tree onto the stack
      s.push(newNode);
    }
  }
  // assign the root node
  this->root = s.top();
  s.pop();
}

void arithmeticExpression::infix() {
  this->infix(this->root);
}

void arithmeticExpression::prefix() {
  this->prefix(this->root);
}

void arithmeticExpression::postfix() {
  this->postfix(this->root);
}

int arithmeticExpression::priority(char op) {
  int priority = 0;
  if(op == '('){
    priority =  3;
  }
  else if(op == '*' || op == '/'){
    priority = 2;
  }
  else if(op == '+' || op == '-'){
    priority = 1;
  }
  return priority;
}

string arithmeticExpression::infix_to_postfix() {
  stack <char> s;
  ostringstream oss;
  char c;
  for(unsigned i = 0; i < infixExpression.size(); ++i){
    c = infixExpression.at(i);
    if(c == ' '){
      continue;
    }
    if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
      if( c == '('){
        s.push(c);
      }
      else if(c == ')'){
        while(s.top() != '('){
          oss << s.top();
          s.pop();
        }
        s.pop();
      }
      else{
        while(!s.empty() && priority(c) <= priority(s.top())){
          if(s.top() == '('){
            break;
          }
          oss << s.top();
          s.pop();
        }
        s.push(c);
      }
    }
    else{ //c is an operand
      oss << c;
    }
  }
  while(!s.empty()){
    oss << s.top();
    s.pop();
  }
  return oss.str();
}

void arithmeticExpression::infix(TreeNode * node) {
  if (node == nullptr) {
    return;
  }

  if(node->left != nullptr) {
    cout << "(";        // print open parenthesis
  } 

  infix(node->left);    // First go to the left node
  cout << node->data;   // output the node's data
  infix(node->right);   // Second go to the right node

  if( node->right != nullptr ) {
    cout << ")";        // print closing parenthesis
  }
}

void arithmeticExpression::prefix(TreeNode * node) {
  if(node == nullptr) {
    return;
  }
  cout << node->data;         // output node's data 
  prefix(node->left);         // output left child data
  prefix(node->right);        // output right node data
}

void arithmeticExpression::postfix(TreeNode * node) {
  if(node == nullptr) {
    return;
  }
  postfix(node->left);      // visit the left nodes first 
  postfix(node->right);     // visit the right nodes second 
  cout << node->data;       // output node's data in the 
  // order in which they were visited 
}

void arithmeticExpression::visualizeTree(const string & outputFilename) {
  ofstream outFS(outputFilename.c_str());
  if(!outFS.is_open()){
    cout<<"Error opening "<< outputFilename<<endl;
    return;
  }

  outFS << "/* If you do not have graphviz program installed: " << endl; 
  outFS << " Use webgraphviz.com to display the visualizeTree." << endl; 
  outFS << " Copy the content of the .dot files generated, "    << endl;
  outFS << " and paste the digraph function to see the graph."  << endl;
  outFS << "*/ " << endl << endl;
  
  outFS << "digraph G {" << endl;
  // output the nodes 
  outFS << "// nodes:" << endl;
  visualizeNodes(outFS,root);
  // output the edges 
  outFS << "// edges:" << endl;
  visualizeTree(outFS,root);
  outFS << "}";

  outFS.close();

  try
  {
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    cout << "The \"sh: 1: dot not found\" exception results from missing graphviz program which displays a the graphs." << endl; 
    cout << "Try installing graphviz using the command: sudo apt-get install graphviz" <<endl;
  }
}

void arithmeticExpression::visualizeNodes(ofstream & outputfile, TreeNode * node) {
/*  a [color = red, peripheries=2, style = filled, label="a"];   */
  if(node == nullptr) {
    return;
  }
  
  // write the nodes in postfix 
  visualizeNodes(outputfile, node->left);
  visualizeNodes(outputfile, node->right);
  
  outputfile << node->key << " [shape=circle, color=red, peripheries=2, style=filled, label=\""; 
  outputfile << node->data << "\"]" << endl; 
}

void arithmeticExpression::visualizeTree(ofstream & outputfile, TreeNode * node) {
  
  if(node == nullptr) {
    return;
  }

  // write the edges 
  if(node->left != nullptr) {
    outputfile << node->key << " -> " << node->left->key << ";" << endl;
  } 
  if(node->right != nullptr) {
    outputfile << node->key << " -> " << node->right->key << ";" << endl;
  }
  visualizeTree( outputfile, node->left) ;
  visualizeTree( outputfile, node->right);
}
