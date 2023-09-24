#include<iostream>
#include<cstdlib>

using namespace std;

enum enGameChoice 
{
	 Stone = 1 , Paper = 2 , Scissors = 3
};

enum enWinner
{
	Player = 1 , Computer  = 2 , Draw 
};

struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoice PlayerChoice ;
	enGameChoice ComputerChoice;
	enWinner RoundWinner;
	string WinnerName = "";

};

struct stGameResult
{
	short GameRounds = 0;
	short Player1WinnsTime = 0;
	short ComputerWinnsTime = 0;
	short DrawTimes = 0;
	enWinner GameWinner ;
	string WinnerName ="";
};

int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}

void SetScreen()
{
	system("color 0F");
	system("cls");
}

short  HowManyRounds()
{
	int GameRounds = 1;
	do
	{
		cout << "How many rounds do you want? ";
		cin >> GameRounds;
	} while (GameRounds < 0 || GameRounds > 10);

	return GameRounds;
}

enGameChoice ReadPlayerChoice()
{
	int PlayerChoice = 1;
	do {

		cout << "Your Choice [1]: Stone , [2]: Paper , [3]: Scissor? ";
		cin >> PlayerChoice;

	} while (PlayerChoice < 1 || PlayerChoice > 3);

	return (enGameChoice) PlayerChoice;
}

enGameChoice GetComputerChoice()
{
	return (enGameChoice)RandomNumber(1, 3);
}

enWinner RoundWinner(stRoundInfo RoundInfo)
{

	if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
		return enWinner::Draw;

	switch (RoundInfo.PlayerChoice)
	{

	case (enGameChoice::Stone):
		if (RoundInfo.ComputerChoice == enGameChoice::Paper)
			return enWinner::Computer;
		break;

	case (enGameChoice::Paper):
		if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
			return enWinner::Computer;
		break;

	case (enGameChoice::Scissors):
		if (RoundInfo.ComputerChoice == enGameChoice::Stone)
			return enWinner::Computer;
		break;

	}

	return enWinner::Player;


}

int ScreenColor(enWinner WinnerRound)
{
	if (WinnerRound == enWinner::Computer)
		return system("color 4F");
	else if (WinnerRound == enWinner::Player)
		return system("color 2F");
	else
		return system("color 6F");
}

string WinnerName(enWinner Winner)
{
	string arrWinnerName[3] = { "Player", "Computer", "Draw" };
	
	return arrWinnerName[Winner - 1];

}

string GetChoiceName(enGameChoice Choice)
{
	string ChoicesName[3] = { "Stone" , "Paper" , "Scissor" };

	return ChoicesName[Choice - 1];

}

void RoundResult(stRoundInfo RoundInfo )
{
	cout << "\nRound          : " << RoundInfo.RoundNumber << endl;
	cout << "Player Choice  : " << GetChoiceName(RoundInfo.PlayerChoice )<< endl;
	cout << "Computer Choice: " << GetChoiceName( RoundInfo.ComputerChoice )<< endl;
	cout << "Round Winner   : " << RoundInfo.WinnerName << endl;

	ScreenColor(RoundInfo.RoundWinner);
	

}

enWinner GameWinnerName(stGameResult GameInfo)

{
	if (GameInfo.Player1WinnsTime == GameInfo.ComputerWinnsTime)
		return enWinner::Draw;
	else if (GameInfo.Player1WinnsTime > GameInfo.ComputerWinnsTime)
		return enWinner::Player;
	else
	{
		return enWinner::Computer;
	}
}


stGameResult  FillGameReslult(short ComputerWinnTimes, short PlayerWinnTime, short DrawTime, short GameRounds)
{

	stGameResult GameResult;

	GameResult.GameRounds = GameRounds;
	GameResult.DrawTimes = DrawTime;
	GameResult.ComputerWinnsTime = ComputerWinnTimes;
	GameResult.Player1WinnsTime = PlayerWinnTime;
	GameResult.GameWinner = GameWinnerName(GameResult);
	GameResult.WinnerName = WinnerName(GameResult.GameWinner);

	return GameResult;




}

string Tab(int NumOfTabs)
{

	string tab = "";
	for (int i = 1; i <= NumOfTabs; i++)
	{
		tab += "\t";
		cout << tab;
	}
	return tab;
}

void ShowGameResult(stGameResult GameInfo)
{
	cout << Tab(2) << "_________ [Game Results] ________\n\n";
	cout <<Tab(2)  << "The Games Round     :" << GameInfo.GameRounds << endl;
	cout << Tab(2) << "Draws times         :"  << GameInfo.DrawTimes << endl;
	cout << Tab(2) << "Computer won times   :"  << GameInfo.ComputerWinnsTime << endl;
	cout << Tab(2) << "Player won times   :" << GameInfo.Player1WinnsTime<<endl;
	cout << Tab(2) << "Winner Game         :" << GameInfo.WinnerName << endl;

}

stGameResult PlayGame(int HowManyRound)
{

	stRoundInfo RoundInfo;
	short PlayerWinsTimes =0, ComputerWinsTimes = 0, DrawTimes = 0;

	for (short GameRound = 1; GameRound <= HowManyRound; GameRound++)
	{
		cout << "\n__________________ Round Number [ " << GameRound << " ] Start __________________ \n\n";

		RoundInfo.RoundNumber = GameRound;
		RoundInfo.PlayerChoice = ReadPlayerChoice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.RoundWinner = RoundWinner(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.RoundWinner);

		if (RoundInfo.RoundWinner == enWinner::Draw)
			DrawTimes++;
		else  if (RoundInfo.RoundWinner == enWinner::Computer)
			ComputerWinsTimes++;
		else
		{
			PlayerWinsTimes++;
		}

		RoundResult(RoundInfo);
	}

	return FillGameReslult(ComputerWinsTimes, PlayerWinsTimes, DrawTimes ,HowManyRound);



}



void GameOver()
{
	cout << Tab(1) << "_________________________________________________________________________\n\n";
	cout << Tab(1) <<"                                  ++Game Over++	    								\n\n";
	cout << Tab(1) << "_________________________________________________________________________\n\n";



}



void GameStrart()
{
	char PlayAgain = 'Y';

	do {

		SetScreen();
		stGameResult  GameResult = PlayGame(HowManyRounds());
		GameOver();
		ShowGameResult(GameResult);


		cout << "\nDo you want to play again? Y/N: ";
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');


	
}

int main()

{
	srand((unsigned)time(NULL));

	GameStrart();
}