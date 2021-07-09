#include "Errors.hpp"
#include "Output.hpp"
#include <iostream>


/*---------------------------Classe Mere Error---------------------------*/
Errors::Error::Error(std::string name, std::string description, Errors::Position pos, std::string line): _name(name), _description(description), _pos(pos), _line(line){
	
}

const std::string Errors::Error::get_name(){
	return _name;
}

const std::string Errors::Error::get_description(){
	return _description;
}

const Errors::Position Errors::Error::get_pos(){
	return _pos;
}


/*---------------------------Fonctions Statiques---------------------------*/
std::string Errors::Error::get_hyphen(){
	return std::string(BACKWHITE) + std::string(BLACK) + "|" + std::string(RESET);
}

std::string Errors::Error::generate_string_pos(Position &pos){
	return std::string(CYAN) + std::to_string(pos.line) + ":" + std::to_string(pos.chr) + " in file \"" + pos.file + "\"" + std::string(RESET);
}

std::string Errors::Error::generate_string_char_pos(Position& pos){
	std::string str;
	for (short i; i<(short)pos.chr; i++){
		str += " ";
	}
	str += std::string(BOLDRED);
	str += "^";
	str += std::string(RESET);
	return str;
}

std::string Errors::Error::generate_string_description(std::string name, std::string description){
	return std::string(BOLDRED) + name + ": " + std::string(RESET) + std::string(RED) + description + std::string(RESET);
}

std::string Errors::Error::generate_string_char_to_char_pos(unsigned short begin, unsigned short length){
	std::string str;
	for (unsigned short i; i<begin; i++){
		str += " ";
	}
	str += std::string(BOLDRED);
	for (unsigned short i; i<length; i++){
		str += "~";
	}
	str += std::string(RESET);
	return str;
}

/*---------------------------UCC Error---------------------------*/
Errors::UCC_Error::UCC_Error(Position pos, std::string line) : Error(std::string("UCC Error"), std::string("Unfinished character chain"), pos, line){
	
}

void Errors::UCC_Error::Print(){
	std::cout << std::endl << get_hyphen() << generate_string_pos(_pos)
		<<"\n" << get_hyphen() << generate_string_description(_name, _description)
	       	<< "\n" << get_hyphen() 
		<< _line << "\n" << get_hyphen() << generate_string_char_pos(_pos) << std::endl;
}

/*---------------------------Unknown Error---------------------------*/

Errors::Unknown_Token_Error::Unknown_Token_Error(Position begin, unsigned short length, std::string line): Error(std::string("Unknown Token Error"), std::string("A token is unknown or undefined"), begin, line), _length(length)
{
	
}

void Errors::Unknown_Token_Error::Print(){
	std::cout << std::endl << get_hyphen() << generate_string_pos(_pos) << "\n" << get_hyphen() <<
		generate_string_description(_name, _description) << "\n" << get_hyphen() << _line << 
		"\n" << get_hyphen() << generate_string_char_to_char_pos(_pos.chr, _length) << std::endl;
}

