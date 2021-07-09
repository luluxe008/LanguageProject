#include "../headers/Lexer.hpp"
#include "../headers/Errors.hpp"
#include <iostream>
using namespace Errors;
using namespace Debug;

void shell();

int main(){
	/*
	Lexer lexer(std::string("IF STOP Bro 1025 \"guillement mon bro\" func end"));
	try {
		cout_vector(lexer.make_tokens());
	}
	catch (Error &err){
		err.Print();
	}
	*/

	shell(); // interactive input
	return 0;
}


/*---------------------------Shell---------------------------*/

void shell(){
	Lexer* lexer(nullptr);
	std::string line;
	std::vector<Token> vec;
	int nb_line(0);
	while (true){
		nb_line++;
		std::cout << ">> ";
		line = "";
		//std::getline(std::cin, line);
		getline(std::cin, line);
		if (line == ".exit"){
			break;
			if (lexer){ //aloue
				lexer = nullptr;
				delete lexer;
			}
		}
		lexer = new Lexer(line, nb_line, std::string("stdin"));
		try{
			vec = lexer->make_tokens();
			cout_vector(vec);
			std::cout << std::endl;
		}
		catch (Error &err){
			err.Print();
		}
		delete lexer;
		lexer = nullptr;
	}
}
