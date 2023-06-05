// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
    return 0;
}

std::string infx2pstfx(std::string inf) {
      TStack<char, 100> stack;
    std::string postfix;

    for (size_t i = 0; i < inf.length(); i++) {
        char ch = inf[i];

        if (ch == ' ')
            continue;

        if (isdigit(ch)) {
            while (i < inf.length() && (isdigit(inf[i]) || inf[i] == ' ')) {
                postfix += inf[i];
                i++;
            }
            postfix += ' ';
            i--;
        } else if (ch == '(') {
            stack.push(ch);
        } else if (ch == ')') {
            while (!stack.isEmpty() && stack.get() != '(') {
                postfix += stack.get();
                postfix += ' ';
                stack.pop();
            }
            if (!stack.isEmpty() && stack.get() != '(')
                return "Invalid Expression";
            stack.pop();
        } else if (isOperator(ch)) {
            while (!stack.isEmpty() && precedence(ch) <= precedence(stack.get())) {
                postfix += stack.get();
                postfix += ' ';
                stack.pop();
            }
            stack.push(ch);
        }
    }

    while (!stack.isEmpty()) {
        postfix += stack.get();
        postfix += ' ';
        stack.pop();
    }
    return postfix;
}

int eval(std::string post) {
      TStack<int, 100> stack;

    for (size_t i = 0; i < post.length(); i++) {
        char ch = post[i];

        if (ch == ' ')
            continue;

        if (isdigit(ch)) {
            int operand = 0;
            while (i < post.length() && isdigit(post[i])) {
                operand = (operand * 10) + (post[i] - '0');
                i++;
            }
            stack.push(operand);
            i--;
        } else if (isOperator(ch)) {
            int operand2 = stack.get();
            stack.pop();
            int operand1 = stack.get();
            stack.pop();

            int result;
            switch (ch) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    result = operand1 / operand2;
                    break;
            }

            stack.push(result);
        }
    }

    return stack.get();
}
