#include "ScalarConverter.hpp"

void convertToInt(const std::string input)
{
	char *endptr;
	errno = 0;
	double nb;

	nb = std::strtod(input.c_str(), &endptr);

	if (endptr == input.c_str())
		return (void)(std::cout << "int: impossible" << std::endl);
	if (!(*endptr == '\0' || (*endptr == 'f' && endptr[1] == '\0')))
		return (void)(std::cout << "int: impossible" << std::endl);
	if (errno == ERANGE || std::isnan(nb) || std::isinf(nb))
		return (void)(std::cout << "int: impossible" << std::endl);
	if (std::floor(nb) != nb)
		return (void)(std::cout << "int: impossible" << std::endl);
	if (nb < std::numeric_limits<int>::min() || nb > std::numeric_limits<int>::max())
		return (void)(std::cout << "int: impossible" << std::endl);
	std::cout << "int: " << static_cast<int>(nb) << std::endl;
}

void convertToChar(std::string input)
{
	if (input.size() == 1)
	{
		if (std::isdigit(input[0]))
			std::cerr << "char: Non displayable" << std::endl;
		else
			std::cout << "char: '" << input[0] << "'" << std::endl;
	}
	else
	{
		double nb;
		char *endptr;

		nb = std::strtod(input.c_str(), &endptr);

		if (endptr == input.c_str())
			return (void)(std::cerr << "char: impossible" << std::endl);

		if (std::isnan(nb) || std::isinf(nb))
			return (void)(std::cerr << "char: impossible" << std::endl);

		if (std::floor(nb) != nb)
			return (void)(std::cerr << "char: impossible" << std::endl);

		if (endptr[0] == '\0' || (endptr[0] == 'f' && endptr[1] == '\0'))
		{
			if (isascii(static_cast<int>(nb)))
			{
				if (std::isprint(static_cast<int>(nb)))
					std::cout << "char: '" << static_cast<char>(nb) << "'" << std::endl;
				else
					std::cerr << "char: Non displayable" << std::endl;
			}
			else
				std::cerr << "char: impossible" << std::endl;
		}
		else
			std::cerr << "char: impossible" << std::endl;
	}
}


// Convert input to float and print with .0f when it is an integer value.
void convertToFloat(std::string str)
{
	float nb;
	char *endptr;

	nb = std::strtof(str.c_str(), &endptr);

	if (endptr == str.c_str())
		return (void)(std::cout << "float: impossible" << std::endl);

	// Accept plain numbers or floats with a trailing 'f'.
	if (endptr[0] == '\0' || (endptr[0] == 'f' && endptr[1] == '\0'))
	{
		if (std::isnan(nb))
			std::cout << "float: nanf" << std::endl;
		else if (std::isinf(nb) && nb > 0)
			std::cout << "float: +inff" << std::endl;
		else if (std::isinf(nb) && nb < 0)
			std::cout << "float: -inff" << std::endl;
		else if (nb == static_cast<int>(nb))
		{
			std::ostringstream oss;
			oss << std::fixed << std::setprecision(1) << nb << "f";
			std::cout << "float: " << oss.str() << std::endl;
		}
		else
		{
			std::cout << "float: " << nb << "f" << std::endl;
		}
	}
	else
		std::cout << "float: impossible" << std::endl;
}

// Convert input to double and print with .0 when it is an integer value.
void convertToDouble(std::string str)
{
	double nb;
	char *endptr;

	nb = std::strtod(str.c_str(), &endptr);

	if (endptr == str.c_str())
		return (void)(std::cout << "double: impossible" << std::endl);

	// Accept plain numbers or floats with a trailing 'f'.
	if (endptr[0] == '\0' || (endptr[0] == 'f' && endptr[1] == '\0'))
	{
		if (std::isnan(nb))
			std::cout << "double: nan" << std::endl;
		else if (std::isinf(nb) && nb > 0)
			std::cout << "double: +inf" << std::endl;
		else if (std::isinf(nb) && nb < 0)
			std::cout << "double: -inf" << std::endl;
		else if (nb == static_cast<int>(nb))
		{
			std::ostringstream oss;
			oss << std::fixed << std::setprecision(1) << nb;
			std::cout << "double: " << oss.str() << std::endl;
		}
		else
		{
			std::cout << "double: " << nb << std::endl;
		}
	}
	else
		std::cout << "double: impossible" << std::endl;
}

void ScalarConverter::converter(std::string input)
{
	convertToChar(input);
	convertToInt(input);
	convertToFloat(input);
	convertToDouble(input);
}