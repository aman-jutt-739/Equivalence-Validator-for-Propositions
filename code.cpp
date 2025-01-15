//#include<iostream>
//#include<string>
//#include<stack>
//
//using namespace std;
//
//// Function to define precedence of operators
//int precedence(string opr) // setting which operator should get preference first
//{
//	if (opr == "~")   // Negation has the highest precedence
//	{
//		return 3;
//	}
//	else if (opr == "^" || opr == "V")  // AND (^) and OR (V) have same precedence
//	{
//		return 2;
//	}
//	else if (opr == "-" || opr == "<") // Implication (-) and biconditional (<) have lower precedence
//	{
//		return 1;
//	}
//	return 0; // Return 0 for non-operators
//}
//
//// Function to check if an operator should be popped from the stack
//bool prcdPost(string stackTop, string opr)
//{
//	if (stackTop == "(") // '(' doesn't have precedence over anything
//	{
//		return false;
//	}
//	if (opr == "(") // '(' should not be popped from stack until closed
//	{
//		return false;
//	}
//	if (opr == ")") // ')' triggers popping until '(' is found
//	{
//		return true;
//	}
//
//	int stackPrcd = precedence(stackTop); 
//	int oprPrcd = precedence(opr); 
//
//	if (stackPrcd >= oprPrcd) // Pop if stack operator has higher or equal precedence
//	{
//		return true;
//	}
//	return false; // Otherwise, return false to continue processing the operator
//}
//
//// Function to check if the character is a valid operator
//bool isOperator(string opr) // checking for valid operator
//{
//	if (opr == "~" || opr == "^" || opr == "V" || opr == "-" || opr == "<" || opr == "(" || opr == ")")
//	{
//		return true; // If the operator matches any valid operator, return true
//	}
//	return false; // Otherwise, return false
//}
//
//// Function to convert infix expression to postfix
//void infixToPostfix(string infix, string& postfix) // will change the expression to postfix
//{
//	stack<string> stackVar; // Stack to store operators
//	string symbol = ""; // string to store current symbol
//	string temp = ""; // Temporary string for processing multi-character operators like "<" and "->"
//
//	// Iterate through each character in the infix expression
//	for (int i = 0; i < infix.size(); i++)
//	{
//		if (infix[i] == ' ') // Skip spaces
//		{
//			continue;
//		}
//
//		symbol += infix[i]; // Add current character to symbol string
//		temp += infix[i]; // Store symbol temporarily
//
//		if (!isOperator(symbol)) // If symbol is not an operator, it’s an operand
//		{
//			postfix += symbol; // Append operand to postfix expression
//		}
//		else // If symbol is an operator
//		{
//			// Pop operators from stack with higher or equal precedence
//			while (!stackVar.empty() && prcdPost(stackVar.top(), symbol))
//			{
//				postfix += stackVar.top(); 
//				stackVar.pop(); 
//			}
//
//			if (symbol != ")") // If not a closing parenthesis, push operator to stack
//			{
//				stackVar.push(symbol);
//			}
//			else // If it’s a closing parenthesis, pop until opening parenthesis
//			{
//				while (!stackVar.empty() && stackVar.top() != "(")
//				{
//					postfix += stackVar.top();
//					stackVar.pop(); 
//				}
//
//				if (!stackVar.empty() && stackVar.top() == "(") // Pop the opening parenthesis
//				{
//					stackVar.pop();
//				}
//			}
//		}
//
//		// Reset symbol for next iteration
//		symbol = "";
//
//		// Handling multi-character operators
//		if (temp == "-")
//		{
//			i++; // Skip the next character for implication "->"
//		}
//		else if (temp == "<")
//		{
//			i += 2; // Skip the next two characters for biconditional "<->"
//		}
//
//		temp = ""; // Reset temporary string for multi-character operators
//	}
//
//	// Pop all remaining operators from stack and append to postfix expression
//	while (!stackVar.empty())
//	{
//		postfix += stackVar.top();
//		stackVar.pop();
//	}
//}
//
//// Function to evaluate a given operator with two boolean values
//bool evaluateOperator(bool num1, bool num2, string op)
//{
//	if (op == "^") // AND operation
//	{
//		return num1 && num2;
//	}
//	else if (op == "V") // OR operation
//	{
//		return num1 || num2;
//	}
//	else if (op == "-") // Implication operation
//	{
//		return !num1 || num2;
//	}
//	else if (op == "<") // Biconditional operation
//	{
//		return num1 == num2;
//	}
//
//	return false; // Return false for unsupported operator
//}
//
//// Function to evaluate postfix expression with given boolean values for variables
//bool evaluatePostfix(string postfix, bool values[], string variables)
//{
//	stack<bool> stackVar; 
//	string symbol = "";
//
//	// Iterate through each character in the postfix expression
//	for (int i = 0; i < postfix.size(); i++)
//	{
//		symbol += postfix[i]; 
//
//		if (!isOperator(symbol)) // If symbol is a variable, push its corresponding value onto stack
//		{
//			int index = variables.find(symbol); // Find the index of the variable
//			if (index != string::npos)
//			{
//				stackVar.push(values[index]); // Push the value of the variable onto the stack
//			}
//		}
//		else if (symbol == "~")  // If symbol is negation (~), pop the top value and negate it
//		{
//			bool val = stackVar.top();
//			stackVar.pop();
//			stackVar.push(!val); 
//		}
//		else // Otherwise, perform the binary operation
//		{
//			bool val2 = stackVar.top(); // Pop the second operand
//			stackVar.pop();
//			bool val1 = stackVar.top(); // Pop the first operand
//			stackVar.pop();
//			stackVar.push(evaluateOperator(val1, val2, symbol)); // Push the result of the operation
//		}
//
//		symbol = ""; // Reset symbol for next iteration
//	}
//
//	return stackVar.top(); // Return the final result after processing the postfix expression
//}
//
//// Function to generate and display the truth table for two boolean expressions
//void generateTruthTable(string expr1, string expr2, string variables)
//{
//	string postfix1 = "", postfix2 = "";
//	infixToPostfix(expr1, postfix1); // Convert first expression to postfix
//	infixToPostfix(expr2, postfix2); // Convert second expression to postfix
//
//	int numVars = variables.size(); // Number of variables
//	int rows = pow(2, numVars); // Number of rows in the truth table (2^n)
//
//	bool isEqual = true; // Flag to check if both expressions are logically equivalent
//
//	cout << "Truth Table:\n";
//	cout << variables << " | " << expr1 << " | " << expr2 << "\n";
//
//	// Iterate through all possible combinations of truth values
//	for (int i = 0; i < rows; i++)
//	{
//		bool values[10]; // Array to store truth values of variables
//		for (int j = 0; j < numVars; j++)
//		{
//			values[j] = (i & (1 << (numVars - j - 1))) != 0; // Assign truth values using bitwise operations
//		}
//
//		bool result1 = evaluatePostfix(postfix1, values, variables); // Evaluate first expression
//		bool result2 = evaluatePostfix(postfix2, values, variables); // Evaluate second expression
//
//		// Output truth values for each variable and result of both expressions
//		for (int j = 0; j < numVars; j++)
//		{
//			cout << values[j] << " ";
//		}
//		cout << "| " << result1 << " | " << result2;
//
//		// Check if both results are the same, if not, mark the expressions as different
//		if (result1 != result2)
//		{
//			isEqual = false;
//			cout << " <-- Differ";
//		}
//		cout << "\n";
//	}
//
//	// Output whether the expressions are logically equivalent or not
//	if (isEqual)
//	{
//		cout << "The expressions are logically equivalent.\n";
//	}
//	else
//	{
//		cout << "The expressions are not logically equivalent.\n";
//	}
//}
//
//int main()
//{
//	string expr1, expr2, variables;
//	cout << "Enter '~' for negation, '^' for AND, 'V' for OR, '->' for implication and '<->' for biconditional operation. \n";
//	cout << "Enter variables (e.g., pqr for p, q, r): ";
//	getline(cin, variables);             // getting variables of boolean equation
//	cout << "Enter 1st expression: ";
//	getline(cin, expr1);              // getting 1st boolean equation
//	cout << "Enter 2nd expression: ";     
//	getline(cin, expr2);                 // getting 2nd boolean equation
//
//	generateTruthTable(expr1, expr2, variables);   // generating truth table
//
//	system("pause");
//	return 0;
//}