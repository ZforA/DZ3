#include <iostream>
#include <string>


enum class Condition
{
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDED,
    LEFTB,
    RIGHTB,
    NUMBER,
    SPACE,
    ERROR,
    END,

} g_condition;
static double g_number{};
static std::string::iterator g_symbol;
std::string g_expression;


Condition matchCondition();
double calculate();


int main()
{
    try
    {
        std::cin >> g_expression;
        g_symbol = g_expression.begin();
        matchCondition();
        std::cout << calculate();
    }
    catch (...)
    {
        return 5;
    }
    return 0;
}


Condition matchCondition()
{
    g_condition = Condition::ERROR;
    if (g_symbol == g_expression.end()) g_condition = Condition::END;
    else
    {
        switch(*g_symbol)
        {
            case '-': g_condition = Condition::MINUS;    break;
            case '+': g_condition = Condition::PLUS;     break;
            case '/': g_condition = Condition::DIVIDED;  break;
            case '*': g_condition = Condition::MULTIPLY; break;
            case '(': g_condition = Condition::LEFTB;    break;
            case ')': g_condition = Condition::RIGHTB;   break;
            case ' ': g_condition = Condition::SPACE;    break;
        }


        if (isdigit(*g_symbol))
        {
            g_condition = Condition::NUMBER;
            g_number = 0.0;
        }


        while (isdigit(*g_symbol))
        {
            g_number = g_number * 10;
            g_number += (*g_symbol - '0');
            ++g_symbol;
        }

        if (g_condition != Condition::NUMBER) ++g_symbol;
    }
    return g_condition;
}

double calculateMulDiv();
double searchBrackets()
{
    double number{};
    switch(g_condition)
    {
        case Condition::NUMBER: matchCondition(); return g_number;
        case Condition::MINUS : matchCondition(); return -searchBrackets();
        case Condition::LEFTB :
            matchCondition();
            number = calculate();
            if (g_condition != Condition::RIGHTB) throw ") - expected";
            matchCondition();
            return number;
        case Condition::END: return 1;
        default: throw "\\_(-|-)_/";
    }
    return static_cast<double>(Condition::ERROR);
}


double calculateMulDiv()
{
    double number = searchBrackets();
    while (g_condition == Condition::MULTIPLY ||
           g_condition == Condition::DIVIDED)
    {
        switch (g_condition)
        {
            case Condition::MULTIPLY:   matchCondition(); number *= calculate(); break;
            case Condition::DIVIDED:    matchCondition(); number /= calculate(); break;
            default: break;
        }
    }
    return number;
}


double calculate()
{
    double number = calculateMulDiv();
    while (g_condition == Condition::PLUS ||
           g_condition == Condition::MINUS)
    {
        switch (g_condition)
        {
            case Condition::PLUS:       matchCondition(); number += calculateMulDiv(); break;
            case Condition::MINUS:      matchCondition(); number -= calculateMulDiv(); break;
            default: break;
        }
    }
    return number;
}
