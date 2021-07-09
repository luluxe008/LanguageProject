#pragma once
#include <string>
#include <vector>

enum TokenType{
	INSTRUCTION,
	IDENTIFIERS,
	INT,
	STRING,
	KEYWORD,
	COLON,
	TAB
};

std::ostream& operator<<(std::ostream&, const TokenType&);

struct Token{
	TokenType type;
	const std::string value;
};

std::ostream& operator<<(std::ostream&, const Token&);

namespace Debug{
	void cout_vector(const std::vector<Token>&);
}

class Lexer{
private:
	std::vector<Token> _tokens;
	int _pos;
	unsigned int _line;
	char _curr_char;
	std::string _file;
	Token make_number();
	Token make_string();
	std::string make_word();
	std::string make_word_until_space();
	void advance();
	std::string _code;
public:
	Lexer(std::string, int, std::string);
	std::vector<Token> make_tokens();
	~Lexer();
};
