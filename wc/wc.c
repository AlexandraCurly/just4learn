#include <stdio.h>
#include <stdbool.h>
enum State {
	Separator,
	Word,
	Sentence,
};

struct Result {
	int symbols, words, sentences;
};

bool is_letter(char s);

bool is_separator(char s);

bool is_dot(char s);

void process_letter(char s, enum State *state, struct Result *res);

void process_separator(char s, enum State *state, struct Result *res);

void process_dot(char s, enum State *state, struct Result *res);

int main() {

	struct Result res;
	res.symbols = 0;
	res.words = 0;
	res.sentences = 0;

	enum State state = Sentence;

	char cur;
	while((cur = getchar()) != EOF) {
		res.symbols++;

		if(is_letter(cur)) {
			process_letter(cur, &state, &res);
		}

		if(is_separator(cur)) {
			process_separator(cur, &state, &res);
		}

		if(is_dot(cur)) {
			process_dot(cur, &state, &res);
		}
	}

	printf("symbols: %d, words: %d, sentences: %d",
		res.symbols, res.words, res.sentences);
}

bool is_letter(char s) {
	return !is_separator(s) && !is_dot(s);
}

bool is_separator(char s) {
	return s == ' ' || s == '\t' || s == '\n' || s == '\r';
}

bool is_dot(char s) {
	return s == '.';
}

void process_letter(char s, enum State *state, struct Result *res) {
	        switch (*state) {
        case Separator:
                res->words++;
		break;
        case Word: break;
        case Sentence:
                res->words++;
                res->sentences++;
		break;
        }
        *state = Word;
}
void process_separator(char s, enum State *state, struct Result *res) {
        switch (*state) {
        case Separator:
		*state = Separator;
		break;
        case Word:
		*state = Separator;
		break;
        case Sentence:
		*state = Sentence;
		break;
        }
}

void process_dot(char s, enum State *state, struct Result *res) {
	*state = Sentence;
}

