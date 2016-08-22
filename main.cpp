#include <iostream>
#include <string>
#include "calculator.h"

int main()
{
	std::string expression;
	Calculator calculator;
	
	std::cout << "Входное выражение: ";
	while (std::getline(std::cin, expression))
	{
		std::string answer;
		try
		{
			answer = calculator.GetAnswer(expression, 2);
		}
		catch (std::invalid_argument e)
		{
			answer = e.what();
		};

		std::cout << "Результат: " << answer << "\n";
		std::cout << "Входное выражение: ";
	}
	
	return 0;
}
