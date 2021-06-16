#include <iostream>
#include <cmath>
#include <math.h>
#include <string>
#include <stack>
#include <algorithm>
#include <vector>
#include "calculator.h"


int main() {
    std::string expression;
    std::cout << "Enter mathematical expression that you would like to evaluate : \n";
    std::getline(std::cin, expression);
    Calculator calculator;

    std::cout << "Post-Fix : ";
    calculator.printPostFix(expression);
    std::cout << "Answer = "<< calculator.evaulate(expression) << std::endl;

    return 0;
}
