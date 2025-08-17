#pragma warning(disable: 4996)
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <vector>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

struct stQuiz {
	string question;
		string a;
		string b;
		string c;
	
};
enum enChoice {Rock=1,Paper=2,scissors=3};
enum enwinner { player = 1, computer=2, even=3 };
struct stRanked {
	string name;
	int  min;
	int sec;
};

int ReadPositiveNumber(string msg)
{
	int number=0;
	
	do{
		cout << msg;
		cin >> number;
	} while (number < 0);
	return number;
}

int RandomNumber(int from, int to)
{
	int number = rand() % (to - from+1) + from;
	return number;
}

enwinner OneRound(int RoundNumber)
{
	int player;
	int computer=RandomNumber(1,3);
	cout << "========================================================================================================================\n\n";
	cout << setw(35) << "ROUND " << RoundNumber<<"\n\n";
	cout << "========================================================================================================================\n";
	cout << setw(25) << "\n\nYour Choice : \n\n";
	cout << setw(15) << "ROCK : 1  \n\n";
	cout << setw(15) << "PAPER : 2 \n \n";
	cout << setw(15) << "SCISSORS : 3 \n\n";
	cout << "\nYour choice :  ";
	cin >> player;
	switch (computer) 
	{
	case enChoice::Rock:
		cout << "\nThe computer choise is : ROCK\n\n";
		break;
	case enChoice::Paper:
		cout << "\nThe computer choise is : PAPER\n\n";
		break;
	case enChoice::scissors:
		cout << "\nThe computer choise is : SCISSORS\n\n";
		break;
	}

	if (computer == enChoice::Paper && player == enChoice::Rock)
	{
		cout << setw(25) << "<The computer won this round>";
		cout << "\n\n========================================================================================================================\n";
		return enwinner::computer;
	}
	else if (computer == enChoice::Rock && player == enChoice::scissors)
	{
		cout << setw(25) << "<The computer won this round>";
		cout << "\n\n========================================================================================================================\n";
	return enwinner::computer;
	}
		
	else if (computer == enChoice::scissors && player == enChoice::Paper)
	{
		cout << setw(25) << "<The computer won this round>";
		cout << "\n\n========================================================================================================================\n";
		return enwinner::computer;
	}
	else if (computer == player)
	{
		cout << setw(25) << "<Even round!>";
		cout << "\n\n========================================================================================================================\n";
		return enwinner::even;
	}
	else
	{
		cout << setw(25) << "<You won this round>\a";
		cout << "\n\n========================================================================================================================\n";
		return enwinner::player;
	}
}

void RPS()
{
	cout << "===============================================================================================================\n\n";
	cout << setw(20) << "WELCOME TO ROCK PAPER SCISSORS GAME!! " <<"\n\n";
	cout << "================================================================================================================\n";

	int rounds = 0;
	char again = 'Y';
	do{
		system("color 07");
	int player = 0;
	int computer = 0;
		cout << "\nEnter how many rounds you want to play : ";
		cin >> rounds;
		for (int i = 1;i <= rounds;i++)
		{
			enwinner winer = OneRound(i);
			if (winer == enwinner::computer)
				computer++;
			else if (winer == enwinner::player)
				player++;
		}	
		if (player > computer)
		{
			cout << "\n CONGRATS YOU WON THE MATCH!\n\n";
			system("color 20");
		}
		else if (player < computer)
		{
			cout << "\n THE COMPUTER WON THE MATCH!\n\n";
			system("color C0");
		}
		else
		{
			cout << "\n EVEN MATCH!\n\n";
			system("color E0");
		}

		do {
			cout << "\n DO YOU WANT TO PLAY AGAIN ? (Y/N) : ";
	cin >> again;
	again = toupper(again);
		} while (again != 'Y' && again != 'N');
	
	} while (toupper(again) == 'Y');
}

vector <string> SendFromFileToVec()
{
	vector<string> vFile;
	fstream file;
	file.open("quiz.txt", ios::in);
	if (file.is_open())
	{
		string line;

		while (getline(file, line))
			vFile.push_back(line);

		file.close();

	}
	return vFile;

}

vector <string> SplitString(string S1, string Delim = "#")
{
	vector<string> vString;
	short pos = 0;
	string sWord;

	while ((pos = S1.find(Delim)) != std::string::npos)
	{
		sWord = S1.substr(0, pos);
		vString.push_back(sWord);
		S1.erase(0, pos + Delim.length());
	}
	if (S1 != "")
		vString.push_back(S1);

	return vString;
}

stQuiz lineToStruct(vector <string>  data)
{
	stQuiz quiz;
	quiz.question = data[0];
	quiz.a = data[1];
	quiz.b = data[2];
	quiz.c = data[3];
	
	
	return quiz;
}

stRanked lineToStructRanked(vector <string>  data)
{
	stRanked player;
	player.name= data[0];
	player.min = stoi(data[1]);
	player.sec = stoi(data[2]);

	return player;
}

vector<stQuiz> StructFromFile(string filename="quiz.txt")
{
	vector<stQuiz> quistions;
	stQuiz  quistion1;
	fstream file;
	file.open(filename, ios::in);
	if (file.is_open())
	{
		string line;
		while (getline(file, line))
		{
			quistion1 = lineToStruct(SplitString(line));
			quistions.push_back(quistion1);
		}
	}
	return quistions;
}

vector<stRanked> VectorofPlayers(string filename = "RankedPlayers.txt")
{
	vector<stRanked> players;
	stRanked  player;
	fstream file;
	file.open(filename, ios::in);
	if (file.is_open())
	{
		string line;
		while (getline(file, line))
		{
			player = lineToStructRanked(SplitString(line));
			players.push_back(player);
		}
	}
	return players;
}

bool check(short repeated[3],short number)
{
	for (int i = 0;i < 3;i++)
	{
		if (repeated[i] == number)
			return true;
	}
	return false;
}

char shuffle(string & RightAnswer,string & WrongAnswer,string & WrongAnswer2,string arrstring[3])
{
	char choise = char(RandomNumber(97, 99));

	switch (choise)
	{ 
	case 'a' :
		arrstring[0] = RightAnswer;
		arrstring[1] = WrongAnswer; 
		arrstring[2] = WrongAnswer2;
		break;
	case 'b':	
		arrstring[0] = WrongAnswer;
		arrstring[1] = RightAnswer;
		arrstring[2] = WrongAnswer2;
		break;
	case 'c':
		arrstring[0] = WrongAnswer;
		arrstring[1] = WrongAnswer2;
		arrstring[2] = RightAnswer;
		break;
	}
	return choise;
}

void Print3Quistions()
{
	vector <stQuiz>  stOfQuestions = StructFromFile();

	short repeated[3];

	for (int i = 0;i < 3;i++)
	{		
		short index;
		do {

			index = RandomNumber(0, stOfQuestions.size() - 1);
		} while (check(repeated, index));
		repeated[i] = index;

		
		cout << stOfQuestions[index].question << " : \n\n";

		string arrShuffle[3];
		char choise=shuffle(stOfQuestions[index].a, stOfQuestions[index].b, stOfQuestions[index].c, arrShuffle);

		cout << "a - " << arrShuffle[0] << "\n";
		cout << "b - " << arrShuffle[1] << "\n";
		cout << "c - " << arrShuffle[2] << "\n\n";
		char answer;
		do { cout << "Your answer  : ", cin >> answer; } while (tolower(answer) != 'a' && tolower(answer) != 'b' && tolower(answer) != 'c');
		if (tolower( answer) == choise)
		{
			cout << "\nCorrect answer!...\n";
			system("color 20");
		}
		else if (tolower(answer)!= choise)
		{
			cout << "\nWrong answer.\n";
			system("color C0");
			cout << "\nThe correct answer is : " << stOfQuestions[index].a<<"\n\n";
		}
		cout << "\n\n====================================================\n\n";
		
	}

}

vector<stRanked> Ordered(vector<stRanked> rank, int min, int sec, string name)
{
	vector<stRanked> NewList;
	bool inserted = false;
	int newTime = min * 60 + sec;

	for (int i = 0; i < rank.size(); i++)
	{
		int currentTime = rank[i].min * 60 + rank[i].sec;

		if (!inserted && newTime < currentTime) 
		{
			NewList.push_back({ name, min, sec });
			inserted = true;
		}

		NewList.push_back(rank[i]);
	}

	if (!inserted)
		NewList.push_back({ name, min, sec });

	return NewList;
}

void pattern()
{
	time_t t = time(0);
	tm* start = localtime(&t);
	int startmin= start->tm_min;
	int startsec= start->tm_sec;
	
	int counter=0;
	int answer=0;
	cout << "\n10, 20, 30, 40, ...... \tthe next number is ? : ";
	cin >> answer;
	if (answer == 50)
		counter++;
	cout << "\n1, 1, 2, 3, 5, 8, 13, ...... \tthe next number is ? : ";
	cin >> answer;
	if (answer == 21)
		counter++;
	cout << "\n7, 14, 21, 28, ...... \tthe next number is ? : ";
	cin >> answer;
	if (answer == 35)
		counter++;


	time_t f = time(0);
	tm* finish = localtime(&f);
	int finishmin = finish->tm_min;
	int finishsec = finish->tm_sec;

	if (counter == 3)
	{
		stRanked rank;
		cout << "Congrats you scored 3/3 , Enter your name please...";
		cin.ignore();
		 getline(cin,rank.name);
		rank.min = finishmin -startmin  ;
		rank.sec = finishsec - startsec;

	vector<stRanked> ranked =	VectorofPlayers("RankedPlayers.txt");

	vector<stRanked> newrank=Ordered(ranked, rank.min, rank.sec, rank.name);

	fstream file;
	file.open("RankedPlayers.txt", ios::out);
	if (file.is_open())
	{
		for (int i = 0;i < newrank.size();i++)
		{
			file << newrank[i].name << "#" << newrank[i].min << "#" << newrank[i].sec << endl;

		}
		file.close();
	}

	for (int i = 0;i < 5;i++)
	{
		cout << "\n\nPlayer "<<i+1 <<" ->" << newrank[i].name << " - Time : " << (newrank[i].min * 60) + newrank[i].sec << " seconds.\n";
	}

	}
	else
	{
		switch ( counter)
		{
		case 2:
			cout << "\nyou scored 2/3\n";
			break;
		case 1:
			cout << "\nyou scored 1/3\n";
			break;
		case 0:
			cout << "\nyou scored 0/3\n";
			break;
		}

	}

}





int main()
{
	srand((unsigned)time(NULL));
	int choice=0;
	char again;
	cout <<"\nWELCOME TO MY PROJECT.!!\n";
	do {
		cout << "\nChose the game you want to play : \n\nROCK PAPER SCISSORS -> 1\n\n3 RANDOM QUESTIONS -> 2\n\nPATTERN -> 3\n";

		do{
		cout << "\nThe number of the game you want to play : ";
		cin >> choice;
	     } while (choice > 4 || choice < 1);
		cout << "\n\n";
		switch (choice)
		{
		case 1:
			RPS();
			break;
		case 2:
			Print3Quistions();
			break;
		case 3: 
			pattern();
			break;

		}
		cout << "\n\nWOULD YOU LIKE TO PLAY ANOTHER GAME ? (Y/N) ";
		cin >> again;
		system("color 07");
	} while (toupper(again) == 'Y');
		
		//RPS();



  /* fstream file;
	file.open("RankedPlayers.txt", ios::out);
	if (file.is_open())
	{

		file << "Abdallah Braik#" << "0#40" << endl;
		file << "Mohammed Braik#" << "0#44" << endl;
		file << "Braik AbdellMoneim#" << "0#46" << endl;
		file << "Abdallah Elganainy#" << "0#50" << endl;

		file.close();
	}
*/ 
	return 0;
}