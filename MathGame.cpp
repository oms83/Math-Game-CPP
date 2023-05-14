#include<iostream>
#include<stdlib.h>
using namespace std;

enum enQuestionLevel { Easy=1, Middle=2, Hard=3, Mix=4 };
enum enQuestionType { Sum=1, Sub=2, Mul=3, Div=4, MIX=5 };
enum AnswerStatus { Right=1, Wrong=2 };
struct stGameResults
{
    int NumberOfQuestion;
    string QLevel;
    string OpType;
    int NumberOfRightAnswer=0;
    int NumberOfWrongAnswer=0;
};
enQuestionLevel AskUserToQuestionLevel()
{
    int QLevel;
    do
    {
        cout << "Enter question level  Easy[1]  Middle[2]  Hard[3]  Mix[4]: ";
        cin >> QLevel;
    }while(QLevel>4 || QLevel<1);
    return (enQuestionLevel)QLevel;
}
enQuestionType AskUserToOperatorType()
{
    int OpType;
    do
    {
        cout << "Enter operator type  Sum[1]  Sub[2]  Mul[3]  Div[4]  Mix[5]: ";
        cin >> OpType;
    }while(OpType>5 || OpType<1);
    return (enQuestionType)OpType;
}
enQuestionLevel CheckToQuestionLevel(enQuestionLevel QLevel)
{
    stGameResults GameResults;
    if(QLevel == enQuestionLevel::Easy)
    {
        GameResults.QLevel = QLevel;
        return enQuestionLevel::Easy;
    }
    else if(QLevel == enQuestionLevel::Middle)
    {
        GameResults.QLevel = QLevel;
        return enQuestionLevel::Middle;
    }
    else if(QLevel == enQuestionLevel::Hard)
    {
        GameResults.QLevel = QLevel;
        return enQuestionLevel::Hard;
    }
    else
    {
        GameResults.QLevel = QLevel;
        return enQuestionLevel::Mix;
    }
}
enQuestionType CheckToOperatorType(enQuestionType OpType)
{
    stGameResults GameResults;
    if(OpType == enQuestionType::Sum)
    {
        GameResults.OpType = OpType;
        return enQuestionType::Sum;
    }
    else if(OpType == enQuestionType::Sub)
    {
        GameResults.OpType = OpType;
        return enQuestionType::Sub;
    }
    else if(OpType == enQuestionType::Mul)
    {
        GameResults.OpType = OpType;
        return enQuestionType::Mul;
    }
    else if(OpType == enQuestionType::Div)
    {
        GameResults.OpType = OpType;
        return enQuestionType::Div;
    }
    else
    {
        GameResults.OpType = OpType;
        return enQuestionType::MIX;
    }
}
string OpName(enQuestionType TYPE)
{
    string arrQLevel[5] = { "Sum", "Sub", "Mul", "Div", "Mix" };
    return arrQLevel[TYPE-1];
}
string QLevelName(enQuestionLevel QLevel)
{
    string arrQuestionType[4] = {"Easy", "Middle", "Hard", "Mix" };
    return arrQuestionType[QLevel-1];
}
char OperatorCharacter(enQuestionType QType)
{
    char arrQChar[4] = {'+', '-', '*', '/'};
    return arrQChar[QType-1];
}
int RandomNumber(int From, int To)
{
    return rand()%(To-From+1)+From;
}
enQuestionType GetOperatorType()
{
    return (enQuestionType)RandomNumber(1, 4);
}
enQuestionLevel GetQuestionLevel()
{
    return enQuestionLevel(RandomNumber(1, 4));
}
void ShowQuestionScreen(int FNumber, int SNumber, enQuestionType QType)
{
    cout << "\n";
    cout << FNumber << endl;
    cout << SNumber << "\t" << OperatorCharacter(QType) << endl;
    cout << "___________\n";
}
int AnswerToQuestion()
{
    int Answer;
    cin >> Answer;
    return Answer;
}
int OperationsOnNumbers(int FNumber, int SNumber, enQuestionType OpType)
{
    if(OpType == enQuestionType::Sum)
    {
        return FNumber + SNumber;
    }
    else if(OpType == enQuestionType::Sub)
    {
        return FNumber - SNumber;
    }
    else if(OpType == enQuestionType::Mul)
    {
        return FNumber * SNumber;
    }
    else if(OpType == enQuestionType::Div)
    {
        return FNumber / SNumber;
    } 
    else
    {
        return OperationsOnNumbers(FNumber, SNumber, GetOperatorType());
    }
}
stGameResults FillGameResult(int HowManyQuestion, int NumberOfRightAnswer, int NumberOfWrongAnswer, enQuestionType OpType, enQuestionLevel QLevel)
{
    stGameResults GameResults;
    GameResults.NumberOfQuestion = HowManyQuestion;
    GameResults.NumberOfRightAnswer = NumberOfRightAnswer;
    GameResults.NumberOfWrongAnswer = NumberOfWrongAnswer;
    GameResults.OpType = OpName(OpType);
    GameResults.QLevel = QLevelName(QLevel);
    return GameResults;
}
void SetScreenColor(AnswerStatus Answer)
{
    switch(Answer)
    {
        case AnswerStatus::Wrong:
            system("color 4F");
            cout << "\a";
            break;
        case AnswerStatus::Right:
            system("color 9F");
            break;
    }
}
void ResetScreen()
{
    system("color 0F");
    system("cls");
}
void PrintQuestionAnswer(AnswerStatus Answer, int RightAnswer)
{
    if(Answer == AnswerStatus::Right)
    {
        cout << "Rigth Answer :) \n";
    }
    else
    {
        cout << "Worng Answer :(\n";
        cout << "The Right Answer is: " << RightAnswer << "\n";
    }
}
AnswerStatus RightOrWrong(int &RightAnswer, int &WrongAnswer, int UserAnswer, int ComputerAnswer)
{
    if( UserAnswer == ComputerAnswer)
    {
        RightAnswer++;
        PrintQuestionAnswer(AnswerStatus::Right, ComputerAnswer);
        SetScreenColor(AnswerStatus::Right);
        return AnswerStatus::Right;
    }
    else 
    {
        WrongAnswer++;
        PrintQuestionAnswer(AnswerStatus::Wrong, ComputerAnswer);
        SetScreenColor(AnswerStatus::Wrong);
        return AnswerStatus::Wrong;
    }
}
stGameResults PlayGame(int HowManyQuestion)
{
    int FirstNumber, SecondNumber, UserAnswer, ComputerAnswer, NumberOfRightAnswer=0, NumberOfWrongAnswer=0;
    enQuestionLevel QLevel = CheckToQuestionLevel(AskUserToQuestionLevel());
    enQuestionType OpType = CheckToOperatorType(AskUserToOperatorType());
    enQuestionType TempOpType = OpType;
    for(int question=1; question<=HowManyQuestion; question++)
    {
        OpType = enQuestionType::MIX;
        if(OpType == enQuestionType::MIX)
            OpType = GetOperatorType();
        cout << "\nQuestion [" << question << "/" << HowManyQuestion << "]\n"; 
        if(QLevel == enQuestionLevel::Easy)
        {
            FirstNumber = RandomNumber(1, 10);
            SecondNumber = RandomNumber(1, 10);
            ShowQuestionScreen(FirstNumber, SecondNumber, OpType);
            RightOrWrong(NumberOfRightAnswer, NumberOfWrongAnswer, AnswerToQuestion(), OperationsOnNumbers(FirstNumber, SecondNumber, OpType));
        }
        else if(QLevel == enQuestionLevel::Middle)
        {
            FirstNumber = RandomNumber(11, 20);
            SecondNumber = RandomNumber(11, 20);
            ShowQuestionScreen(FirstNumber, SecondNumber, OpType);
            RightOrWrong(NumberOfRightAnswer, NumberOfWrongAnswer, AnswerToQuestion(), OperationsOnNumbers(FirstNumber, SecondNumber, OpType));
        }
        else if(QLevel == enQuestionLevel::Hard)
        {
            FirstNumber = RandomNumber(21, 100);
            SecondNumber = RandomNumber(21, 100);
            ShowQuestionScreen(FirstNumber, SecondNumber, OpType);
            RightOrWrong(NumberOfRightAnswer, NumberOfWrongAnswer, AnswerToQuestion(), OperationsOnNumbers(FirstNumber, SecondNumber, OpType));
        }
        else
        {
            FirstNumber = RandomNumber(1, 100);
            SecondNumber = RandomNumber(1, 100);
            ShowQuestionScreen(FirstNumber, SecondNumber, OpType);
            RightOrWrong(NumberOfRightAnswer, NumberOfWrongAnswer, AnswerToQuestion(), OperationsOnNumbers(FirstNumber, SecondNumber, OpType));
        }
    }
    if(TempOpType == enQuestionType::MIX)
        return FillGameResult(HowManyQuestion, NumberOfRightAnswer, NumberOfWrongAnswer, TempOpType, QLevel);
    else
        return FillGameResult(HowManyQuestion, NumberOfRightAnswer, NumberOfWrongAnswer, OpType, QLevel);
}
int AskUserHowManyQuestion()
{
    int Number;
    do
    {
        cout << "How many question do you want to aswer: ";
        cin >> Number;
    }while(Number<=0);
    return Number;
}
void CheckToPassOrFail(int &NumberOfRightAnswer, int &NumberOfWrongAnswer)
{
    cout << "\n----------------------------------------\n";
    if(NumberOfRightAnswer>NumberOfWrongAnswer)
        cout << "   Final Results Is Pass :)";
    else 
        cout << "   Final Results Is Fail :)";
    cout << "\n----------------------------------------\n";

}
void PrintFinallQuizeResults(stGameResults GameResults)
{
    CheckToPassOrFail(GameResults.NumberOfRightAnswer, GameResults.NumberOfWrongAnswer);
    cout << "----------------------------------------\n";
    cout << "Number Of Question     : " << GameResults.NumberOfQuestion << endl;
    cout << "Question Level         : " << GameResults.QLevel << endl;
    cout << "OpType                 : " << GameResults.OpType << endl;
    cout << "Number Of Right Answer : " << GameResults.NumberOfRightAnswer << endl;
    cout << "Number Of Wrong Answer : " << GameResults.NumberOfWrongAnswer << endl;
    cout << "----------------------------------------\n";
}
void StartGame()
{
    char PlayAgain='Y';
    do
    {
        ResetScreen();
        PrintFinallQuizeResults(PlayGame(AskUserHowManyQuestion()));
        cout << "Do you want to play again? Y/N? "; 
        cin >> PlayAgain; 
    }while(PlayAgain=='Y' || PlayAgain=='y');
}
int main()
{
    srand(unsigned(time(NULL)));
    StartGame();
}




