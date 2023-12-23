#include <iostream>
#include <bits/stdc++.h>

int brackets;
int bracketCount;
using namespace std;

bool bracketsCheck(const string& expr)
{
    stack<char> stack;
    char c;

    for (char i : expr)
    {
        if (i == '(')
        {
            stack.push(i);
            continue;
        }

        switch (i) {
            case ')':

                if (stack.empty())
                    return false;
                c = stack.top();
                if (c == '{' || c == '[')
                    return false;

                stack.pop();
                break;

            default :
                continue;

        }
    }
    return (stack.empty());
}

int operation (int a, int b,char sign){
    switch (sign) {
        case '+':{
            return a += b;
        }
        case '-':{
            return a -= b;
        }
        case '*':{
            return a *= b;
        }
        case '/': {
            if (b == 0) {
                cout << "division by 0" << endl;
                return -666;
            }
            else return a /= b;
        }
        default:
            return -666;
    }
}


int calc(const string& line,int start) {

    string temp;
    char ch;
    stack<int> stack;
    int temp1;
    char sign;


    for (int i=start;i<line.length();i++) {
        ch=line[i];
        if (isdigit(ch)) {
            temp += ch;
            continue;
        }
        if (ch == '+' || ch == '-' || ch == '/' || ch == '*') {

            if (stack.empty()) {
                if (temp.empty()) {
                    sign = ch;
                    continue;
                }
                if (sign) {
                    switch (sign) {
                        case '+':
                            stack.push(stoi(temp));
                            break;

                        case '-':
                            stack.push(-1 * stoi(temp));
                            break;

                        case '*':
                        case '/':
                            std::cout << "expression can't start with '*' or '/'" << std::endl;
                        default:
                            std::cout << &"unknown error"[sign] << std::endl;
                            return -666;
                    }
                }else stack.push(stoi(temp));
                std::cout << temp << std::endl;
                temp.clear();
                std::cout << temp << std::endl;
                sign = ch;
                continue;
            } else {
                switch (sign) {
                    case '+':
                        stack.push(stoi(temp));
                        temp.clear();
                        sign = ch;
                        continue;

                    case '-':
                        stack.push(-1 * stoi(temp));
                        temp.clear();
                        sign = ch;
                        continue;

                    case '*':
                        temp1 = stack.top();
                        stack.pop();
                        stack.push(temp1 * stoi(temp));
                        temp.clear();
                        sign = ch;
                        continue;

                    case '/':
                        if (stoi(temp) == 0) {
                            cout << "division by 0" << endl;
                            return -666;
                        }
                        temp1 = stack.top();
                        stack.pop();
                        stack.push(temp1 / stoi(temp));
                        temp.clear();
                        sign = ch;
                        continue;

                    default:
                        return -666;

                }
            }
        }
            if (ch == '=' || ch == ')') {
                if(ch == ')'){brackets=i;}
                if (ch == '=' and i != line.length() - 1){
                    std::cout << "'=' must be at the end" << std::endl;
                        return -666;
                }
                if (stack.empty()){
                    std::cout << sign << std::endl;
                    if (sign) {
                        switch (sign) {
                            case '+':
                                return stoi(temp);
                            case '-':
                                return -1*stoi(temp);
                            case '*':
                            case '/':
                                std::cout << "expression can't start with '*' or '/'" << std::endl;
                            default:
                                std::cout << "can't resolve = or ) with empty stack" << std::endl;
                                return -666;
                        }
                    }
                    return stoi(temp);
                }
                temp1 = (operation(stack.top(), stoi(temp), sign));
                stack.pop();
                while (!stack.empty()) {
                    temp1 += stack.top();
                    stack.pop();
                }
                return temp1;
            }
            if (ch == '('){
                temp1=calc(line,i+1);
                std::cout << temp1 << std::endl;
                temp= to_string(temp1);
                /*switch (sign) {
                    case '+':
                        stack.push(temp1);
                        break;

                    case '-':
                        stack.push(-1 * temp1);
                        break;

                    case '*':
                        temp1*=stack.top();
                        stack.pop();
                        stack.push(temp1);
                        break;

                        temp1 = stack.top();
                        stack.pop();
                        stack.push(temp1 * stoi(temp));
                        temp.clear();


                    case '/':
                        if (stoi(temp) == 0) {
                            cout << "division by 0" << endl;
                            return -666;
                        }
                        temp1/=stack.top();
                        stack.pop();
                        stack.push(temp1);
                        break;
                }*/
                i+=brackets+1;
                std::cout <<"end bracket:"<< i << std::endl;
                continue;
            }
            std::cout << "unknown symbol" << std::endl;
            return -666;
        }
        std::cout << "expression must end with '='" << std::endl;
        return -666;
}


int main() {
    string line;
    cin>>line;
    if (bracketsCheck(line)) {
        std::cout << calc(line,0) << std::endl;
    }
    else std::cout << "incorrect brackets" << std::endl;
    return 0;
}
