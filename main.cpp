#include<iostream>
#include<fstream>
#include<conio.h>
#include<windows.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
using namespace std;

void gotoRowCol(int rpos, int cpos)
{
    int xpos = cpos, ypos = rpos;
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = cpos;
    scrn.Y = rpos;
    SetConsoleCursorPosition(hOuput, scrn);
}

int sleeping()
{
    for (int a = 0; a < 1000000000; a++)
    {

    }
}

void Init_Board(char Board[], int Dim)
{
	for (int i=0; i<Dim*Dim; i++)
	{
		Board[i]='_';
	}
}
void Print_Board(char Board[], int Dim)
{
	cout<<endl<<endl;
	for (int i=0; i<Dim*Dim; i++)
	{
		cout<<"\t"<<Board[i];
		if((i+1)%Dim==0)
		{
			cout<<endl<<endl<<endl;
		}
	}
}
void Ask_for_move(int &ri, int &ci, int turn)
{
	cout<<"Player "<<turn+1<<" turn: ";
	cin>>ri>>ci;
}
void Change_turn(int & turn)
{
	if(turn==0)
	{
		turn=1;
	}
	else
	{
		turn=0;
	}
}
int Tow_D_to_One_D(int ri, int ci, int Dim)
{

	return ((ri-1)*Dim+(ci-1));
}
void Print_on_board(char Board[], int Dim, int ri, int ci, int turn, char P_symble[])
{
	int index=Tow_D_to_One_D(ri, ci, Dim);
	Board[index]=P_symble[turn];
}
bool Is_legal(char Board[], int ri, int ci, int Dim)
{
	if (ri>Dim || ci>Dim || ri<=0 || ci<=0)
	{
		return false;
	}
	int index=Tow_D_to_One_D(ri, ci, Dim);
	if (Board [index]!='_')
	{
		return false;
	}
	return true;
}
bool Draw(char Board[], int Dim)
{
	for (int i=0; i<Dim*Dim; i++)
	{
		if(Board[i]=='_')
		{ 
			return true;
		}
	}
}
bool vertical_Win(char Board[], int Dim, int ri, int ci,int turn, char P_symble[])
{ 


	for(ci=1; ci<=Dim; ci++)
	{
			int count=0;
		for(ri=1; ri<=Dim; ri++)
		{
			int index=Tow_D_to_One_D(ri, ci, Dim);
			if(Board[index]==P_symble[turn])
			{
				count++;
				if (count==Dim)
				{
				return true;
				}
			}
		}
	}
}

bool Horizental_Win(char Board[], int Dim, int ri, int ci,int turn, char P_symble[])
{ 
	for(ri=1; ri<=Dim; ri++)
	{
			int count=0;
		for(ci=1; ci<=Dim; ci++)
		{
			int index=Tow_D_to_One_D(ri, ci, Dim);
			if(Board[index]==P_symble[turn])
			{
				count++;
				if (count==Dim)
				{
				return true;
				}
			}
		}
	}
}

bool Diagonal1_Win(char Board[], int Dim, int ri, int ci,int turn, char P_symble[])
{ 
	int count=0;
	for(ri=1; ri<=Dim; ri++)
	{
			ci=ri;
			int index=Tow_D_to_One_D(ri, ci, Dim);
			if(Board[index]==P_symble[turn])
			{
				count++;
				if (count==Dim)
				{
				return true;
				}
			}
		
	}
}

bool Diagonal2_Win(char Board[], int Dim, int ri, int ci,int turn, char P_symble[])
{ 
		int count=0;
		ci=Dim;
		for(ri=1; ri<=Dim; ri++)
		{	
			int index=Tow_D_to_One_D(ri, ci, Dim);
			if(Board[index]==P_symble[turn])
			{
				count++;
				if (count==Dim)
				{
				return true;
				}
			}
			ci--;
		}
}

bool Win(char Board[], int Dim, int ri, int ci,int turn, char P_symble[])
{
	if(vertical_Win(Board, Dim, ri, ci, turn, P_symble)== true || 
	Horizental_Win(Board, Dim, ri, ci, turn, P_symble)== true || 
	Diagonal1_Win(Board, Dim, ri, ci, turn, P_symble)== true || 
	Diagonal2_Win(Board, Dim, ri, ci, turn, P_symble) == true)
	{
		return true;
	}
}

void writer(int &turn, char Board[],char &ch,int &Dim)
{
	ofstream write("tic tac file.txt");
	write<<turn<<ch<<Dim<<ch<<Board;
}

void reader(int &turn, char Board[],char& ch, int &Dim)
{
	ifstream read("tic tac file.txt");
	read>>turn>>ch>>Dim>>ch>>Board;
}

int main()
{
	int Dim, turn=0, ri, ci;
	char P_symble[2]={'X','O'},load,ch=',';
	char Board[Dim];
	cout<<"Press L for load game otherwise new game will open: ";
	cin>>load;
	Board[Dim*Dim];
	Init_Board(Board, Dim);
		if(load=='l'||load=='L')
	{
		reader(turn,Board,ch,Dim);
    }
    else
    {
	cout<<"Please enter your dimension for board: ";
	cin>>Dim;
    Board[Dim*Dim];
	Init_Board(Board, Dim);
		}
	do{

		Print_Board(Board, Dim);
		if(load=='l'||load=='L')
		{
			if (Win(Board, Dim, ri, ci, turn, P_symble)==true || Draw(Board,Dim)!=true)
			{
				break;
			}
		}
	do{
	Ask_for_move(ri, ci, turn);
	}
	while(Is_legal(Board, ri, ci, Dim)==false);
	Print_on_board(Board, Dim, ri, ci, turn, P_symble);	
	writer(turn,Board,ch,Dim);
	if (Win(Board, Dim, ri, ci, turn, P_symble)==true)
	{
		break;
	}
	Print_on_board(Board, Dim, ri, ci, turn, P_symble);
	Change_turn(turn);
	system("CLS");
	writer(turn,Board,ch,Dim);

	}
	while(Draw(Board,Dim)==true);
	system("CLS");
	Print_Board(Board, Dim);
	if(Win(Board, Dim, ri, ci, turn, P_symble)==true)
	{
    	cout<<"Player "<<turn+1<<"("<<P_symble[turn]<<")"<<": Win";
    }
    else
    {
        cout<<"\tGame is Draw";
	}
}