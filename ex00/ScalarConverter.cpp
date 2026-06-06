#include "ScalarConverter.hpp"

void convertToInt(const std::string input)
{
	char *endptr;
	errno = 0;
	
	// On parse la chaîne vers un double pour pouvoir gérer les très grands nombres
	double nb = std::strtod(input.c_str(), &endptr);

	// Si aucun chiffre n'a été trouvé (ex: "bonjour")
	if (endptr == input.c_str() 
		|| !(*endptr == '\0' || (*endptr == 'f' && endptr[1] == '\0')) //1
		|| errno == ERANGE || std::isnan(nb) || std::isinf(nb) //2
		|| std::floor(nb) != nb //3
		|| nb < std::numeric_limits<int>::min() || nb > std::numeric_limits<int>::max()) //4
		return (void)(std::cout << "int: impossible" << std::endl);
	//1 Si on n'est pas arrivé à la fin de la chaîne ET que ce n'est pas un float du type '42.0f'
	//2 Si c'est en dehors des limites (ERANGE), ou si c'est NaN / Infini
	//3 Si le nombre a une partie décimale non nulle (ex: 42.5), ce n'est pas un int valide
	//4 Si la valeur dépasse les limites d'un int de 32 bits (overflow/underflow)
	else
		std::cout << "int: " << static_cast<int>(nb) << std::endl;
}

void convertToChar(std::string input)
{
	if (input.size() == 1) {
		if (std::isdigit(input[0]))
			std::cerr << "char: Non displayable" << std::endl;
		else
			std::cout << "char: '" << input[0] << "'" << std::endl;
	}
	else { // La chaîne fait plus d'un caractère (ex: "42", "42.0", "nan")

		char *endptr;
		double nb = std::strtod(input.c_str(), &endptr);

		// Si pas un nombre
		if (endptr == input.c_str()
			|| std::isnan(nb) || std::isinf(nb)
			|| std::floor(nb) != nb)
			return (void)(std::cerr << "char: impossible" << std::endl);

		// Si on a bien lu un nombre ou un float (qui finit par 'f')
		if (!(endptr[0] == '\0') || !(endptr[0] == 'f' && endptr[1] == '\0'))
			std::cerr << "char: impossible" << std::endl;
	
		else if (!isascii(static_cast<int>(nb)))
			std::cerr << "char: impossible" << std::endl;

		// Le nombre doit être un caractère imprimable
		if (std::isprint(static_cast<int>(nb)))
			std::cout << "char: '" << static_cast<char>(nb) << "'" << std::endl;
		else
			std::cerr << "char: Non displayable" << std::endl;
	}
}

void convertToFloat(std::string str)
{
	float nb;
	char *endptr;

	nb = std::strtof(str.c_str(), &endptr);

	if (endptr == str.c_str())
		return (void)(std::cout << "float: impossible" << std::endl);

	if (endptr[0] == '\0' || (endptr[0] == 'f' && endptr[1] == '\0'))
	{
		if (std::isnan(nb))
			std::cout << "float: nanf" << std::endl;
		else if (std::isinf(nb) && nb > 0)
			std::cout << "float: +inff" << std::endl;
		else if (std::isinf(nb) && nb < 0)
			std::cout << "float: -inff" << std::endl;
		//forcer l'affichage du .0f
		else if (nb == static_cast<int>(nb)) {
			std::ostringstream oss;
			oss << std::fixed << std::setprecision(1) << nb << 'f';
			std::cout << "float: " << oss.str() << std::endl;
		}
		else
			std::cout << "float: " << nb << "f" << std::endl;
	}
	else
		std::cout << "float: impossible" << std::endl;
}

void convertToDouble(std::string str)
{
	double nb;
	char *endptr;

	// On parse en double
	nb = std::strtod(str.c_str(), &endptr);

	// Si aucun nombre n'est trouvé
	if (endptr == str.c_str())
		return (void)(std::cout << "double: impossible" << std::endl);

	// Si fin de chaîne ou s'il y a un 'f' à la fin
	if (endptr[0] == '\0' || (endptr[0] == 'f' && endptr[1] == '\0'))
	{
		// Cas spéciaux du double : nan, +inf, -inf
		if (std::isnan(nb))
			std::cout << "double: nan" << std::endl;
		else if (std::isinf(nb) && nb > 0)
			std::cout << "double: +inf" << std::endl;
		else if (std::isinf(nb) && nb < 0)
			std::cout << "double: -inf" << std::endl;
		// Si le nombre est un nombre rond (ex: 42.0)
		else if (nb == static_cast<int>(nb))
		{
			std::ostringstream oss;
			// On force l'affichage d'un zéro après la virgule (ex: 42.0)
			oss << std::fixed << std::setprecision(1) << nb;
			std::cout << "double: " << oss.str() << std::endl;
		}
		else
		{
			// Sinon, on l'affiche avec ses décimales
			std::cout << "double: " << nb << std::endl;
		}
	}
	else
		std::cout << "double: impossible" << std::endl;
}

// ==========================================
// METHODE PRINCIPALE DE LA CLASSE
// ==========================================
// Cette méthode va appeler chaque convertisseur à tour de rôle
void ScalarConverter::converter(std::string input)
{
	convertToChar(input);
	convertToInt(input);
	convertToFloat(input);
	convertToDouble(input);
}