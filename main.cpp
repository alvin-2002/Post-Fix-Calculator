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
    Calculator calculator;

    std::cout << "Enter mathematical expression that you would like to evaluate : \n";
    std::getline(std::cin, expression);

    std::cout << "Post-Fix : ";
    calculator.printPostFix(expression);
    std::cout << "Answer = "<< calculator.evaulate(expression) << std::endl;

    return 0;
}
