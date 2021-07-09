#pragma once
#include <string>

namespace Errors{
struct Position{
	std::string file;
	unsigned int line; 
	unsigned int chr;
};
/* Ici on cree plusieurs classe de type Error car cela permet de mieux gerer les erreur et de
 * les classer plus simplement
 */
class Error{ //n'herite pas de std::exception
protected:
	std::string _name, _description, _line;
	Position _pos;
	Error(std::string, std::string, Position, std::string); /*constructeur protege pour que seulement
						     les classe fille puissent l'avoir*/
	static inline std::string get_hyphen(); // les petit | sur le cote
	static inline std::string generate_string_pos(Position&); // pour le 10:10 in file
	static std::string generate_string_char_pos(Position&); //pour faire le ^ sous l'erreur.
	static std::string generate_string_description(std::string, std::string); // pour generer le
       										//message d'erreur
	static std::string generate_string_char_to_char_pos(unsigned short, unsigned short);
	// pour faire le ~~~~~ sous le mot fautif
public:
	const std::string get_name();
	const std::string get_description();
	const Position get_pos();
	virtual void Print()=0; /*
				   ici pas de friend std::ostream& etc... mais plutot une fonction
				   virtuel pure.
				   Peut-etre la faire retourner std::string pour eviter de print dans
				   dans la sortie standard*/
};

class UCC_Error: public Error{
private:
	
public:
	UCC_Error(Position, std::string); 
	virtual void Print(); //la fonction virtuelle plut haut
};

class Unknown_Token_Error: public Error{
private:
	unsigned short _length;
public:
	Unknown_Token_Error(Position, unsigned short, std::string);
	virtual void Print();	

};


/*--------------------------------Warning--------------------------------*/
class Warn{
private:
	int level; /*5 = tres importante (est souvent une erreur)
		     4 = importante (peut etre une erreur)
		     3 = basique
		     2 = minine (peut etre desactiver)
		     1 = tres nimine (peut etre desactiver)
		     */
};

}
