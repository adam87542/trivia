#include "Question.h"

Question::Question(QuestionAndAnswers questionAndAnswers)
{
	this->m_possibleAnswers.push_back(questionAndAnswers.firstAnswer);
	this->m_possibleAnswers.push_back(questionAndAnswers.secondAnswer);
	this->m_possibleAnswers.push_back(questionAndAnswers.thridAnswer);
	this->m_possibleAnswers.push_back(questionAndAnswers.fourthAnswer);
	this->m_question = questionAndAnswers.question;
	this->m_answer = questionAndAnswers.correctAnswer;

}

string Question::getQuestion()
{
	return this->m_question;
}

std::vector<string> Question::getPossibleAnswers()
{
	return this->m_possibleAnswers;
}

string Question::getCorrentAnswer()
{
	return this->m_answer;
}
