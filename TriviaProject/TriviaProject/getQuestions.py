from pyopentdb import OpenTDBClient, Category, QuestionType, Difficulty
import sqlite3

def main():
	
	#Creating a basic connection to the database, if fail, exit
	try:
		con = sqlite3.connect("Trivia.sqlite")
	except Error as e:
		print(e)
		return

	#Getting the questions, easy,medium,hard , and then inserting it to the db
	client = OpenTDBClient()
	questions_easy = client.get_questions(amount=15,category=Category.SCIENCE_COMPUTERS,question_type=QuestionType.MULTIPLE,difficulty=Difficulty.EASY)
	enter_questions_to_db(questions_easy,con,"Easy")
	questions_medium = client.get_questions(amount=15,category=Category.SCIENCE_COMPUTERS,question_type=QuestionType.MULTIPLE,difficulty=Difficulty.MEDIUM)
	enter_questions_to_db(questions_medium,con,"Medium")
	questions_hard = client.get_questions(amount=15,category=Category.SCIENCE_COMPUTERS,question_type=QuestionType.MULTIPLE,difficulty=Difficulty.HARD)
	enter_questions_to_db(questions_hard,con,"Hard")
	print("Done")

def enter_questions_to_db(questions,con,dif):
	for question in questions:
		cursor = con.cursor()
		statment = "insert into questions values('"+ question.question.replace("'","") +"', + '" + dif + "','" + question.choices[0].replace("'","") +"','" + question.choices[1].replace("'","") +"','" + question.choices[2].replace("'","") +"','" + question.choices[3].replace("'","") +"','" + question.answer.replace("'","") +"'," + str(question.answer_index) +");"
		print(statment)
		cursor.execute(statment)
		con.commit()


if __name__ == "__main__":
	main()