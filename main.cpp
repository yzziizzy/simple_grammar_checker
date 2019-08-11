#include <iostream>
#include <fstream>
#include <list>
#include <unordered_map>
#include <string>

#include <ctype.h>
#include <string.h>


#include "pos.hpp"


using namespace std;


typedef list<string*> Sentence;

void checkCaps(Sentence* sent);

bool word_char(uint32_t c) {
	if(c == ' ') return false;
	return 
// 		isalnum(c) ||
		isupper(c) ||
		islower(c) ||
		c == '-' ||
		c == '$' ||
		c == '@' ||
		c == '#' ||
		c == '%' ||
		c == '_'
		;
}

bool is_whitespace(uint32_t c) {
	return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

bool ends_word(uint32_t c) {
	return !(isalnum(c) || c == '-');
}

bool ends_sentence(uint32_t c) {
	return 
		c == '.' ||
		c == '!' ||
		c == '?';
}


// punctuation that can occur inside a sentence
bool interior_punct(uint32_t c) {
	return 
		c == ',' ||
		c == ';' ||
// 		c == '-' ||
		c == '\'' ||
		c == '"' ||
		c == '(' ||
		c == ')' ||
		c == ':';
}





void load_POS(string path, unordered_map<string, POS> dict);

int main(int argc, char* argv[]) {
	
	list<string*>* sentence = new list<string*>;
	
	
	unordered_map<string, POS> dict;
	load_POS("./part-of-speech.txt", dict);
	
	cout << "POS db loaded\n";
	
	char buffer[256];
	int i = 0;
	bool in_word = false;
	
	while(1) {
		char c;
		cin.get(c);
		
		if(cin.eof()) {
			break;
		}

		if(word_char(c)) {
			
			buffer[i++] = c;
			in_word = true;
// 			cout << "+ '" << c << "'";
		}
		else {
// 			cout << "-" << endl;
			if(in_word) {
				// cycle the word
				string* s = new string(buffer, i);
// 				cout << "word: '" << *s << "'\n"; 
				sentence->push_back(s);
				i = 0;
				in_word = false;
			}
			
			if(!is_whitespace(c)) {
				// push punctuation
				sentence->push_back(new string(&c, 1));
			}
			// else ignore whitespace
			
			if(ends_sentence(c)) {
// 				cout << "sentence ended\n";
				
				for(const string* s : *sentence) {
					cout << *s << " ";
				}
				cout << endl;
				
				checkCaps(sentence); 
				
				for(const string* s : *sentence) delete s; 
				delete sentence;
				sentence = new list<string*>;
			}
		}
		
		
	}
	
	
	
	
	
}







void checkCaps(Sentence* sent) {
	if(sent->size() == 0) return;
	
	string* s = sent->front();
	
	char c = (*s)[0];
	cout << c << endl;
	if(islower(c)) {
		cout << "sentence is not capitalized.\n";
	}
}




/*

N	Noun
P	Plural
h	Noun Phrase
V	Verb (usu participle)
t	Verb (transitive)
i	Verb (intransitive)
A	Adjective
v	Adverb
C	Conjunction
p	Preposition
!	Interjection
r	Pronoun
D	Definite Article
I	Indefinite Article
o	Nominative
*/

uint32_t masks = {
#define POS_NOUN_MASK         0b00000000 00000000 00000000 00000001
#define POS_PLURAL_MASK       0b00000000 00000000 00000000 00000010
#define POS_NOUN_PHR_MASK     0b00000000 00000000 00000000 00000100
#define POS_VERB_PART_MASK    0b00000000 00000000 00000000 00001000
#define POS_VERB_TRAN_MASK    0b00000000 00000000 00000000 00010000
#define POS_VERB_INT_MASK     0b00000000 00000000 00000000 00100000
#define POS_ADJECTIVE_MASK    0b00000000 00000000 00000000 01000000
#define POS_ADVERB_MASK       0b00000000 00000000 00000000 10000000
#define POS_CONJUNCTION_MASK  0b00000000 00000000 00000001 00000000
#define POS_PREPOSITION_MASK  0b00000000 00000000 00000010 00000000
#define POS_INTERJECTION_MASK 0b00000000 00000000 00000100 00000000
#define POS_PRONOUN_MASK      0b00000000 00000000 00001000 00000000
#define POS_ART_DEF_MASK      0b00000000 00000000 00010000 00000000
#define POS_ART_IND_MASK      0b00000000 00000000 00100000 00000000
#define POS_NOMINATIVE_MASK   0b00000000 00000000 01000000 00000000
};


void load_POS(string path, unordered_map<string, POS> dict) {
	
	// rad the file
	ifstream f(path.c_str(), ifstream::in);
	// um... failure?
	
	f.seekg(0, ios::end);
	size_t size = f.tellg();
	f.seekg(0);
	
	char* source = new char[size+1];
	
	f.read(source, size); 
	source[size] = 0;
	
	
	// process the contents
	char* s = source;
	
	while(*s) {
		char* end = strchr(s, '\t');
		if(!end) break;
		string word(s, end - s);
// 		cout << word << endl;
		dict.insert({word, POS(end)});
		s = strchr(end, '\n') + 1;
	}
}
