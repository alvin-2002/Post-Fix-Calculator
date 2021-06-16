//
// Created by Alvin on 15/06/2021.
//

#ifndef STACK_CALCULATOR_CALCULATOR_H
#define STACK_CALCULATOR_CALCULATOR_H


class Calculator{
    private:
        bool isDigit(char input);
        bool isOperator(std::string input);
        int precedence(std::string symbol);
        double calculate(double firstNum, double secondNum, std::string symbol);
        std::vector<std::string> expressionList(std::string input);
        std::vector<std::string> getPostFix(std::string input);

    public:
        void printPostFix(std::string input);
        double evaulate(std::string input);
};

bool Calculator :: isDigit(char input){
    return (input >= '0' && input <= '9') || input == '.';
}

bool Calculator :: isOperator(std::string input){
    return (input == "+" || input == "-" || input == "*" || input == "/" || input == "^");
}

int Calculator :: precedence(std::string symbol){
    if (symbol == "+" || symbol == "-") return 1;
    if (symbol == "*" || symbol == "/") return 2;
    if (symbol == "^") return 3;

    return 0;
}

double Calculator :: calculate(double firstNum, double secondNum, std::string symbol){
    if (symbol == "+") return firstNum + secondNum;
    if (symbol == "-") return firstNum - secondNum;
    if (symbol == "*") return firstNum * secondNum;
    if (symbol == "/") return firstNum / secondNum;
    // firstNum ^ secondNum
    if (symbol == "^") return pow(firstNum, secondNum);
}

std::vector<std::string> Calculator :: expressionList(std::string input){
    // remove spacing
    std::string::iterator end_pos = std::remove(input.begin(), input.end(), ' ');
    input.erase(end_pos, input.end());

    std::vector<std::string> expressionList;
    std::string digits;

    for (int i = 0; i < input.length(); i++){
        std::string operatorSymbol = "";
        operatorSymbol.push_back(input[i]);
        // check for - or + next to an operator
        if (( isOperator(operatorSymbol) || input[i] == '(')
            // check out of bound
            && ( i + 1 < input.length() )
            && ( input[i+1] == '-' || input[i+1] == '+')
            ){

            if (digits != ""){
                expressionList.push_back(digits);
                digits = "";
            }
            expressionList.push_back(operatorSymbol);
            digits += input[i+1];
            i = i + 1;
        }
        // check if the expression starts with - or +
        else if (i == 0 && (input[i] == '-' || input[i] == '+')){
            digits += input[i];
        }
        else if (isOperator(operatorSymbol) || input[i] == '(' || input[i] == ')'){
            if (digits != ""){
                expressionList.push_back(digits);
                digits = "";
            }
            expressionList.push_back(operatorSymbol);
        }
        else if (isDigit(input[i])){
            digits += input[i];
        }
    }
    // last digit
    expressionList.push_back(digits);

    return expressionList;
}

std::vector<std::string> Calculator :: getPostFix(std::string input){
    std::vector<std::string> inputExpression = expressionList(input);
    std::vector<std::string> postfixNotation;
    std::stack<std::string> operatorSymbols;

    for (int i = 0; i < inputExpression.size(); i++){

        if (inputExpression[i] == "("){
            operatorSymbols.push(inputExpression[i]);
        }

        else if (isOperator(inputExpression[i])){
            // check if the precedence of current operator is greater than the operator on top of the stack
            if (operatorSymbols.empty() || inputExpression[i] == "(" || (precedence(inputExpression[i]) > precedence(operatorSymbols.top()))){
                operatorSymbols.push(inputExpression[i]);
            }

            else if ((precedence(inputExpression[i]) <= precedence(operatorSymbols.top()))) {
                // associativity of the operator is from right to left (exponent)
                if (inputExpression[i] == "^" && operatorSymbols.top() == "^"){
                    operatorSymbols.push(inputExpression[i]);
                }
                // associativity of the operator is from left to right (+, -, *, /)
                else{
                    while (!operatorSymbols.empty() && (precedence(inputExpression[i]) <= precedence(operatorSymbols.top()))){
//                        if (precedence(inputExpression[i]) > precedence(operatorSymbols.top())) break;
                        postfixNotation.push_back(operatorSymbols.top());
                        operatorSymbols.pop();
                    }
                    operatorSymbols.push(inputExpression[i]);
                }
            }

        }
        // push all operators inside the brackets
        else if (inputExpression[i] == ")"){
            while (operatorSymbols.top() != "("){
                postfixNotation.push_back(operatorSymbols.top());
                operatorSymbols.pop();
            }
            operatorSymbols.pop();
        }
        // is digit
        else{
            postfixNotation.push_back(inputExpression[i]);
        }

    }
    // push remaining operators in the stack into postfixNotation
    while (!operatorSymbols.empty()){
        postfixNotation.push_back(operatorSymbols.top());
        operatorSymbols.pop();
    }

    return postfixNotation;
}

double Calculator :: evaulate(std::string input){
    std::vector<std::string> postFix = getPostFix(input);
    double num1, num2;
    std::stack<double> stack;
    for (int i = 0; i < postFix.size(); i++){
        if (!isOperator(postFix[i])){
            // convert string digits into double
            stack.push(std::stod(postFix[i]));
        }else{
            if (stack.size() >= 2){
                // num1 (25) + num2 (10)
                num2 = stack.top();
                stack.pop();
                num1 = stack.top();
                stack.pop();

                // calculate
                double total = calculate(num1, num2, postFix[i]);
                stack.push(total);
            }
        }
    }

    return stack.top();
}

void Calculator :: printPostFix(std::string input){
    std::vector<std::string> postFix = getPostFix(input);
    for (auto token : postFix){
        std::cout << token << " ";
    }
    std::cout << std::endl;
}
#endif //STACK_CALCULATOR_CALCULATOR_H
