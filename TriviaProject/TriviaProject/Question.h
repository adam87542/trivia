#pragma once
#include "Structs.h"
#include <string>

class Question
{
private:
	string m_question;
	string m_answer;
	std::vector<string> m_possibleAnswers;
public:
	Question(QuestionAndAnswers questionAndAnswers);
	string getQuestion();
	std::vector<string> getPossibleAnswers();
	string getCorrentAnswer();
};