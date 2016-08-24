#include "calculator.h"
#include <iostream>
#include <iomanip>

std::string Calculator::GetAnswer(const std::string &expression, size_t digit)
{
	if (expression.empty())
	{
		throw  std::invalid_argument("Строка пуста");
	}

	//если в строке найдены ошибки, вызываем исключение
	auto errors = FindAndGetErrors(expression);
	if(errors.empty() == false)
	{
		throw  std::invalid_argument("строка содержит недопустимое выражение " + errors);
	}

	//форматируем строку(для удобства обработки) и парсим ее
	auto formatString = GetFormatString(expression);
	int startPosition = 0;
	auto answer = CalcExpression(formatString, startPosition);

	//округляем ответ и преобразуем в строку
	auto formatAnswer = RoundAndTransformToString(answer, digit);
	DeleteNils(formatAnswer, digit);
	return formatAnswer;
}

Calculator::Calculator() :
	numberRegex(NUMBER_REGEX),
	expressionRegex(EXPRESSION_REGEX)
{
}

double Calculator::CalcExpression(const std::string &expression, int &position)
{
	//парсим первый терм, затем в цикле парсим остальные пока не дойдем до конца строки
	auto answer = CalcTerm(expression, position);
	while (expression[position] != '\0')
	{
		char operation = expression[position];	
		if (operation != '+' && operation != '-')
		{
			return answer;
		}
		position++;

		auto term = CalcTerm(expression, position);
		if (operation == '+')//определяем выполняемую операцию
		{
			answer += term;
		}
		else
		{
			answer -= term;
		}
	}

	return answer;
}

std::string Calculator::FindAndGetErrors(const std::string &str)
{
	std::string errors;
	//std::regex regex("[^/(-9\\s]+");
	std::smatch smatch;

	auto tempStr = str;
	while(std::regex_search(tempStr, smatch, expressionRegex))
	{
		errors += smatch.str() + " ";
		tempStr = smatch.suffix().str();
	}

	return errors;
}

double Calculator::CalcTerm(const std::string &term, int &position)
{
	//парсим первый фактор
	double answer = CalcFactor(term, position);

	while(term[position] != '\0')
	{
		char operation = term[position];
		if (operation != '/' && operation != '*')
		{
			return answer;
		}
		position++;

		//парсим второй фактор
		double factor = CalcFactor(term, position);
		if (operation == '*')
		{
			answer *= factor;
		}
		else
		{
			if (factor != 0)
			{
				answer /= factor;
			}
			else
			{
				throw std::invalid_argument("Некорректная операция(деление на ноль)");
			}
		}
	}

	return answer;
}

double Calculator::CalcFactor(const std::string &factor, int &position)
{
	bool negative = false;//флаг, показывает, является ли число отрицательным
	if (factor[position] == '-')
	{
		negative = true;
		position++;
	}

	double answer;
	if (factor[position] == '(')//если выражение находится внутри другого, вызываем парсинг следующего
	{
		position++;
		answer = CalcExpression(factor, position);
		
		if (factor[position] != ')')
		{
			throw std::invalid_argument("в строке отсутствует )");
		}
		position++;
	}
	else
	{
		//парсим число и переводим его в double тип
		auto stringView = GetStringNumber(factor, position);
		answer = ToDouble(stringView);
	}

	if (negative)
	{
		return -answer;
	}
	return answer;
}

double Calculator::ToDouble(const std::string &str)
{
	std::istringstream inStream(str);
	double number;
	inStream >> number;

	return number;
}

std::string Calculator::GetStringWithoutSpaces(const std::string &str)
{
	std::string retString;

	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == ' ' || str[i] == '\0')
		{
			continue;
		}

		retString += str[i];
	}

	return retString;
}

std::string Calculator::GetFormatString(const std::string & str)
{
	//убираем пробелы
	std::string formatString = GetStringWithoutSpaces(str);
	
	//если запятые есть, то заменяем их на точки
	auto n = formatString.find(',');
	while (n != std::string::npos)
	{
		formatString[n] = '.';
		n = formatString.find(',');
	}

	return formatString;
}

std::string Calculator::GetStringNumber(const std::string &str, int &position)
{
	//копируем числа и точки до тех пор, пока не встретится операция
	std::string number;
	while (std::isdigit(str[position]) ||
	str[position] == '.')
	{
		number += str[position];
		position++;
	}

	//проверяем полученную строку, является ли она числом(на случай несколькольких лишних точек)
	//std::regex regexExpression("[[:space:]]*[[:digit:]]+([.,]?[[:digit:]]+)?[[:space:]]*");
	if (std::regex_match(number, numberRegex) == false)
	{
		throw std::invalid_argument("строка содержит недопустимое выражение " + number);
	}

	return number;
}

std::string Calculator::RoundAndTransformToString(double number, size_t digit)
{
	//получаем строковое представление с двумя знаками после запятой
	std::stringstream stream;
	stream << std::fixed << std::setprecision(digit);
	stream << number;

	return stream.str();
}

void Calculator::DeleteNils(std::string &str, size_t digit)
{
	auto minIndex = str.size() - digit;//индекс первого символа после точки
	for (size_t i = str.size() - 1; i >= minIndex; i--)
	{
		if (str[i] == '0')
		{
			str.erase(i);
			//если мы дошли до последнего нуля перед точкой, то удалим точку
			if (i == minIndex) str.erase(minIndex - 1);
		}
		else//если символ не ноль, то прерываем цикл
		{
			break;
		}
	}
}


