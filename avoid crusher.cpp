#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
using namespace std;

const int Wid = 30;
const int Hih = 25;
const int MaxC = 10;

int playerX, playerY;
int crshX[MaxC];
int crshY[MaxC];
int crshDir[MaxC];
int Score = 0;
bool isGameOver;

 void gotoxy(int x, int y){
 	COORD coord;
 	coord.X = x;
 	coord.Y = y;
 	
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
 }
 
 void Game(){
 	playerX = Wid/2;
 	playerY = Hih-2;
 	
 	//initializing crushers
 	for(int i=0; i<MaxC; i++){
 		crshX[i] = rand() % Wid;
 		crshY[i] = 1;
 		crshDir[i] = (rand() % 2 == 0)? -1 : 1;
	 }
	 
	  isGameOver= false;
 }
 
 void update(){
 	for(int i=0; i<MaxC; i++){
 		
 	//collision with player
	if(crshX[i] == playerX && crshY[i] == playerY){
		isGameOver = true;
	}
	
	//reverse from left and right edges
	if(crshX[i] == 1 || crshX[i] == Wid-2 ){
		
		crshDir[i] *= -1;
	}
	crshY[i]++;
	
	// if reached to bottom
	 if(crshY[i] > playerY){
	 	crshX[i] = rand() % Wid;
	 	crshY[i] = 1;
	 	crshDir[i]= (rand() % 2 ==0)? -1 : 1;
	 	Score++;
	 }
		
	 }
 }
 
 void wall(){
 	for(int i=0; i<=Hih+1; i++){
 		gotoxy(Wid,i);
 		cout<<"*";
 		
 	gotoxy(Wid+1,i);
	cout<<"*";
	
	gotoxy(Wid+2,i);
	cout<<"*";
	 }
	 
	for(int j=0; j<Wid; j++){
		gotoxy(j,Hih);
		cout<<"*";
		gotoxy(j,Hih+1);
		cout<<"*";
		gotoxy(j,Hih+2);
		cout<<"*";
	} 
 }
 
 void score(){
 	gotoxy(Wid+5, 8);
 	cout<<"Score: "<<Score<<endl;
 }
 
 void Render(){
 	system("cls");
 	wall();
 	score();
 	
 	// draw the game screen
 	for(int y=0; y<Hih; y++){
 		for(int x=0; x<Wid; x++){
 		gotoxy(x,y);
	if(x==playerX && y == playerY){
		cout<<"P";
	}
	else{
		bool isCrusher = false;
		
		for(int i=0; i<MaxC; i++){
			if(x==crshX[i] && y == crshY[i]){
				cout<<"X";
				isCrusher = true;
				break;
			}
		}
		if(!isCrusher){
			cout<<" ";
		}
	}	
		 }//2nd loop
	 }//1st loop
 }//render
 
 void input(){
 	if(_kbhit()){
 		char ch = _getch();
 		
 		if(ch==77 && playerX < Wid-2){
 			playerX++;
		 }
		 
	if (ch == 75 && playerX > 1){
            playerX--;
        }
	if (ch == 27) {
            isGameOver = true;
        }	
			 
	 }
 }
 
 int main(){
 	system("mode con: lines=40 cols=60");
 	
 	srand(time(0));
 	Game();
 	cout<<"Instructions:"<<endl;
 	cout<<"1. use Right and Left arrow keys for move"<<endl;
 	cout<<"2. Enter Esc for quit game"<<endl;
 	
 	system("pause");
 	while(!isGameOver){
 		input();
 		
 		update();
 		
 		Render();
 		
 		Sleep(10);
	 }
	 
	 gotoxy(2,Hih+4);
	 cout<<"Game Over! "<<endl;
	 
	 gotoxy(2,Hih+5);
	 cout<<"Final Score: "<<Score<<endl;
 }
