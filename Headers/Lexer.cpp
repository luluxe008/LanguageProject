#include "Lexer.hpp"
#include "Errors.hpp"
#include <iostream>
#include <ctype.h>
using std::cout;
using std::endl;

/*--------------------Pour les output de std::cout--------------------*/

std::ostream& operator<<(std::ostream& flux, const TokenType& type){
	switch (type){
		case TokenType::INSTRUCTION:
			flux << "INSTRUCTION";
			break;
		case TokenType::INT:
			flux << "INT";
			break;
		case TokenType::IDENTIFIERS:
			flux << "IDENTIFIERS";
			break;
		case TokenType::STRING:
			flux << "STRING";
			break;
		case TokenType::KEYWORD:
			flux << "KEYWORD"; //func end
			break;
		case TokenType::COLON:
			flux << "COLON";
			break;
		case TokenType::TAB:
			flux << "TAB";
			break;
		default:
			flux << "UNKNOWN";
	}
	return flux;
}

std::ostream& operator<<(std::ostream& flux, const Token& token){
	if (token.value == "\t") flux << "[" << token.type << " : " << "TAB" << "]";
	else flux << "[" << token.type << " : " << token.value << "]";
	return flux;	
}

/*--------------------DEBUG--------------------*/

void Debug::cout_vector(const std::vector<Token>& vec){
	std::cout << vec.size();
	for (int i(0); i<vec.size(); i++){
		cout << vec[i];
	}
}


/*--------------------LEXER--------------------*/
Lexer::Lexer(std::string code, int line, std::string file) : _code(code), _pos(-1), _curr_char('\0'), _tokens(), _line(line), _file(file){
	//_code alias line ;)
	advance();
}

void Lexer::advance(){
	_pos++;
	if (_pos >= _code.length()){
		_curr_char = '\0';
	}
	_curr_char = _code[_pos];
}

std::string Lexer::make_word(){
	std::string word;
	while (isalpha(_curr_char)){
		word += _curr_char;
		advance();
	}
	//cout << word << endl;
	return word;
}

std::string Lexer::make_word_until_space(){ // PAS FINI
	std::string word;
	while (_curr_char != ' ' && _curr_char != '\0'){
		word += _curr_char;
		advance();
	}

	return word;
}

Token Lexer::make_number(){
	std::string number;
	while (isdigit(_curr_char)){
		number += _curr_char;
		advance();
	}
	
	return Token{TokenType::INT, number};
}

Token Lexer::make_string(){
	std::string str;
	advance(); // pour skip le premier guillemet
	while (_curr_char != '"'){
		if (_curr_char == '\0'){ //fin (EOF)
			throw Errors::UCC_Error(Errors::Position{_file, _line,(unsigned int) _pos}, _code); 
		}
		str += _curr_char;
		advance();
	}
	return Token{TokenType::STRING, str};
}

std::vector<Token> Lexer::make_tokens(){
	while (_curr_char != '\0'){
		if (isalpha(_curr_char)){ //si le char est alphabetique
			std::string word = make_word();
			if (word == "stop" || word == "pause" || word == "push" || word == "pop" || word == "cps" || word == "cpi" || word == "add"){ // instruction
				_tokens.push_back(Token{TokenType::INSTRUCTION, word});
			} 
			else if (word == "func" || word == "end"){ //keyword
				_tokens.push_back(Token{TokenType::KEYWORD, word}); 
			}
		       	else _tokens.push_back(Token{TokenType::IDENTIFIERS, word}); //identifier
		}

		else if (isdigit(_curr_char)){ //si le char est un nombre
			_tokens.push_back(make_number());
			//advance();
		}

		else if (_curr_char == '"'){
			_tokens.push_back(make_string());
			//advance();
		}
		
		else if (_curr_char == ':'){
			_tokens.push_back(Token{TokenType::COLON, std::string(":")});
			advance();
		}
		
		else if (_curr_char == '\t'){// tab
			_tokens.push_back(Token{TokenType::TAB, std::string("\t")});
			advance(); //tous les advance() sont a revoir( si il doivent etre place
					// ou non)
		}
		else if (_curr_char == '#'){
			break;
		}

		else {
			std::string err_word = make_word_until_space();
			throw Errors::Unknown_Token_Error(Errors::Position{_file, _line,
				(unsigned int) _pos}, (unsigned short)err_word.length(), _code);
		}

		advance();
	}
	return _tokens;	
}

Lexer::~Lexer(){

}

