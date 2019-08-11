
class POS {
public:
	enum class InternalType {
		Noun = 0,
		Plural,
		NounPhrase,
		VerbParticiple,
		VerbTransitive,
		VerbIntransitive,
		Adjective,
		Adverb,
		Conjunction,
		Preposition,
		Interjection,
		Pronoun,
		ArticleDefinite,
		ArticleIndefinite,
		Nominative,
	};
	
	enum class PrimitiveType {
		Noun = ((int)InternalType::Noun | (int)InternalType::NounPhrase),
		Verb = ((int)InternalType::VerbParticiple | (int)InternalType::VerbTransitive | (int)InternalType::VerbIntransitive),
		Adjective = ((int)InternalType::Adjective),
		Adverb = ((int)InternalType::Adverb),
		Preposition = ((int)InternalType::Preposition),
		Interjection = ((int)InternalType::Interjection),
		Conjunction = ((int)InternalType::Conjunction),
		Pronoun = ((int)InternalType::Pronoun),
		Article = ((int)InternalType::ArticleDefinite | (int)InternalType::ArticleIndefinite),
	};
	
	bool is(InternalType t) {
		return data & (1 << (int)t);
	};
	
	bool is(PrimitiveType t) {
		return data & (1 << (int)t);
	};
	
	bool isPlural() { return data & (int)InternalType::Plural; };
	
	POS(uint32_t types) {
		data = types;
	};
	
	POS(char* s) {
		while(*s && *s != '\n') {
			switch(*s) {
				case 'N': data &= (int)InternalType::Noun; break;
				case 'p': data &= (int)InternalType::Plural | (int)InternalType::Noun; break;
				case 'h': data &= (int)InternalType::NounPhrase; break;
				case 'V': data &= (int)InternalType::VerbParticiple; break;
				case 't': data &= (int)InternalType::VerbTransitive; break;
				case 'i': data &= (int)InternalType::VerbIntransitive; break;
				case 'A': data &= (int)InternalType::Adjective; break;
				case 'v': data &= (int)InternalType::Adverb; break;
				case 'C': data &= (int)InternalType::Conjunction; break;
				case 'P': data &= (int)InternalType::Preposition; break;
				case '!': data &= (int)InternalType::Interjection; break;
				case 'r': data &= (int)InternalType::Pronoun; break;
				case 'D': data &= (int)InternalType::ArticleDefinite; break;
				case 'I': data &= (int)InternalType::ArticleIndefinite; break;
				case 'o': data &= (int)InternalType::Nominative; break;
				//case '|': 
				//default: 
					// nothing
			}
			s++;
		}
	};
	
private:
	uint32_t data;
	
};
