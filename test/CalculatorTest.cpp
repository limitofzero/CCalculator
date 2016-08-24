#include "../calculator.h"
#include "UnitTest++/UnitTest++.h"


SUITE(CalculatorTests)
{
    Calculator calc;

    //тесты на правильный расчет выражений
    TEST(FirstExpression) 
    {
        CHECK_EQUAL(calc.GetAnswer("-1 + 5 -  3", 2), "1");
    }

    TEST(SecondExpression) 
    {
        CHECK_EQUAL(calc.GetAnswer("-10 + (8*2.5)-(3/1,5)", 2), "8");
    }

    TEST(ThirdExpression) 
    {
        CHECK_EQUAL(calc.GetAnswer("1+(2*(2.5 + 2.5 + (3-2))) - (3/1.5)", 2), "11");
    }

    //тесты на случай ввода неккоректных выражений
    TEST(AlphabetCharactersInExpression)
    {
        CHECK_THROW(calc.GetAnswer("1.1 + 2.1 + abc", 2), std::invalid_argument);
    }

    TEST(DivisionByZero)
    {
        CHECK_THROW(calc.GetAnswer("2 / 0", 2), std::invalid_argument);
    }

    TEST(EmptyString)
    {
        CHECK_THROW(calc.GetAnswer("", 2), std::invalid_argument);
    }
}

int main(int, const char *[])
{
    return UnitTest::RunAllTests();
}
