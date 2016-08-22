#pragma once
#include <string>
#include <regex>
#include <sstream>
#include <cctype>
#include <stdexcept>

#define NUMBER_REGEX "[[:space:]]*[[:digit:]]+([.,]?[[:digit:]]+)?[[:space:]]*"
#define EXPRESSION_REGEX "[^/(-9\\s]+"

class Calculator
{
public:

	Calculator();

	//парсит выражение и возвращает ответ
	std::string GetAnswer(const std::string &expression, size_t digit);

	//округляеют до digit знаков после запятой и преобразуте в строку
	std::string RoundAndTransformToString(double number, size_t digit);

	//ищет ошибки в строке, возвращает список найденных ошибок
	std::string FindAndGetErrors(const std::string &str);

private:
	//Разбирает выражение на термы и считает его
	double CalcExpression(const std::string &expression, int &position);

	//разбирает выражение на факторы и считает их(устанавливает position на символ после терма)
	double CalcTerm(const std::string &term, int &position);

	//разбирает фактор(устанавливает position на символ после фактора)
	double CalcFactor(const std::string &factor, int &position);

	//преобразует строковое представление числа в double
	double ToDouble(const std::string &str);

	//выдает строку пригодную для парсинга(без пробелов и ,)
	std::string GetFormatString(const std::string &str);

	//удаляет все пробелы из строки(для удобства парсинга)
	std::string GetStringWithoutSpaces(const std::string &str);

	//парсит число из строки, устанавливает position на след символ после числа
	std::string GetStringNumber(const std::string &str, int &position);

	//удаляет незначащие нули в строковом представлении числа
	void DeleteNils(std::string &str, size_t digit);

private:

	//регулярное выражение для проверки всей строки
	std::regex expressionRegex;
	//регулярное выражение для проверки числа в строке
	std::regex numberRegex;
};
	