#ifndef ANSWER_HPP
#define ANSWER_HPP

typedef struct Answer {
	Answer() : status (1) { ; }
	Answer(int s) : status(s) { ; }
	Answer(std::string ret) : status(2), data(ret) { ; }
	int status; // 0 = Not Ok, 1 = Ok without answer, 2 = Ok with answer
	std::string data;
} Answer;

#endif