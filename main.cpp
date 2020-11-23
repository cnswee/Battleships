/*
This is main.cpp for Battleships.
From Swee.
Almost complete but I'm too lazy to update.
*/
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <string.h>
using namespace std;

// char x1[5];
// char y1[5];
// char x2[5];
// char y2[5];
// char direction1[5];
// char direction2[5];
// char fx1[64];
// char fy1[64];
// char fx2[64];
// char fy2[64];
// char gb1[8][8]={' '};
// char gb2[8][8]={' '};
// char fire1[8][8]={' '};
// char fire2[8][8]={' '};
// int turnNumber=0;
// string playerName;

// void ShowShip(char gb[8][8]){
//     cout<<"\n   A--B--C--D--E--F--G--H"<<endl;
//     cout<<"------------------------------"<<endl;
//     for(int i = 0;i < 8;i++){
//         cout<<i+1<<'|';
//         for(int j = 0;j < 8;j++){
//             cout<<"  "<<gb[j][i];
//         }
//         cout<<"\n------------------------------"<<endl;
//     }
// }

// int PlaceShip(char gb[8][8],char x,char y,char dir,char size){
//     int nx = x - 'A';
//     int ny = y - '1';
//     int nsize = size - '0';
//     switch(dir){
//         case 'N':
//             for(int i = 0;i < nsize;i++){
//                 if(gb[nx][ny - i] == 'S') return 0;
//                 if(ny - i < 0) return 0;
//                 gb[nx][ny-i] = 'S';
//             }
//             break;
//         case 'S':
//             for(int i = 0;i < nsize;i++){
//                 if(gb[nx][ny + i] == 'S') return 0;
//                 if(ny + i > 7) return 0;
//                 gb[nx][ny+i] = 'S';
//             }
//             break;
//         case 'W':
//             for(int i = 0;i < nsize;i++){
//                 if(gb[nx-i][ny] == 'S') return 0;
//                 if(nx - i < 0) return 0;
//                 gb[nx-i][ny] = 'S';
//             }
//             break;
//         case 'E':
//             for(int i = 0;i < nsize;i++){
//                 if(gb[nx+i][ny] == 'S') return 0;
//                 if(nx + i < 0) return 0;
//                 gb[nx+i][ny] = 'S';
//             }
//             break;
//     }
//     return 1;
// }

// void DisplayBoard(){
//     cout<<"\nTurn: "<<(turnNumber+1)<<endl;
//     cout<<"Displaying the current board state!"<<endl;
// }

// void PlayerFire(){
//     ClearScreen();
//     int restship = 17;
//     while(restship > 0){
//         DisplayBoard();
//         ShowShip(fire1);
//         cout<<"\nPlayer "<<playerName<<" enter coordinates to fire\n"<<"-------------------------------"<<endl;
//         GetCdt(&fx1[turnNumber],&fy1[turnNumber]);
//         while(fire1[fx1[turnNumber]][fy1[turnNumber]] == 'H'||fire1[fx1[turnNumber]][fy1[turnNumber]] == 'M'){
//             cout<<"\nInvalid entry!Please try again.\n";
//             GetCdt(&fx1[turnNumber],&fy1[turnNumber]);
//         }
//         int nfx1 = fx1[turnNumber]-'A';
//         int nfy1 = fy1[turnNumber]-'1';
//         cout<<"You fire at x:"<<fx1[turnNumber]<<" and y:"<<fy1[turnNumber]<<endl;
//         if(gb1[nfx1][nfy1]=='S'){
//             fire1[nfx1][nfy1]='H';
//             restship--;
//         }
//         else fire1[nfx1][nfy1]='M';
//         ShowShip(fire1);
//         turnNumber++;
//     }
//     cout<<playerName<<" won! Turn number: "<<turnNumber<<endl;
//     EnterToContinue();
// }
class Ship{
private:
    int size;
    int hits;
    string type;
public:
    Ship(){}
    Ship(int size,string type){
        this->size = size;
        this->type = type;
        this->hits = 0;
    }

    bool IsSunk(){
        if(hits == size) return true;
        else return false;
    }
    
    int GetSize(){
        return size;
    }

    string GetType(){
        return type;
    }

    void Hit(){
        if(hits < size) hits++;
    }
};

class BattleshipSquare{
private:
    Ship* ship;
    bool isFired;
public:
    char charsquare;
    BattleshipSquare(){
        ship = NULL;
        isFired = false;
    }

    void Reset(){
        ship = NULL;
        isFired = false;
    }

    bool AddShip(Ship* ship){
        this->ship = ship;
    }

    char GetStatus(){
        if(ship == NULL && isFired == false) return ' ';
        if(ship == NULL && isFired == true) return 'M';
        if(ship != NULL && isFired == false) return 'S';
        if(ship != NULL && isFired == true) return 'H';
    }

    void Fire(){
        if(ship != NULL && ship->IsSunk()==false){
            ship->Hit();
            isFired = true;
        }
    }
};

class Board{
private:
    char squares[8][8] = {' '};
public:
    void DisplayBoard( ){
        cout<<"\n   A--B--C--D--E--F--G--H"<<endl;
        cout<<"------------------------------"<<endl;
        for(int i = 0;i < 8;i++){
            cout<<i+1<<'|';
            for(int j = 0;j < 8;j++){
                cout<<"  "<<squares[j][i];
            }
            cout<<"\n------------------------------"<<endl;
        }
    }

    char GetSquareState(char x,char y){
        int nx = x - 'A';
        int ny = y - '1';
        if(squares[nx][ny] == ' ') return 'E';
        if(squares[nx][ny] == 'S') return 'O';
        if(squares[nx][ny] == 'H') return 'H';
        if(squares[nx][ny] == 'M') return 'M';
    }

    int PlaceShip(char x,char y,char dir,char size){
        int nx = x - 'A';
        int ny = y - '1';
        int nsize = size - '0';
        switch(dir){
            case 'N':
                for(int i = 0;i < nsize;i++){
                    if(squares[nx][ny - i] == 'S') return 0;
                    if(ny - i < 0) return 0;
                    squares[nx][ny-i] = 'S';
                }
                break;
            case 'S':
                for(int i = 0;i < nsize;i++){
                    if(squares[nx][ny + i] == 'S') return 0;
                    if(ny + i > 7) return 0;
                    squares[nx][ny+i] = 'S';
                }
                break;
            case 'W':
                for(int i = 0;i < nsize;i++){
                    if(squares[nx-i][ny] == 'S') return 0;
                    if(nx - i < 0) return 0;
                    squares[nx-i][ny] = 'S';
                }
                break;
            case 'E':
                for(int i = 0;i < nsize;i++){
                    if(squares[nx+i][ny] == 'S') return 0;
                    if(nx + i < 0) return 0;
                    squares[nx+i][ny] = 'S';
                }
                break;
        }
        return 1;
    }

    char FireAtSquare(char x,char y){
        int nx = x - 'A';
        int ny = y - '1';
        if(squares[nx][ny] == 'S') return 'H';
        else return 'M';
    }

    int ShipLeft(){
        int num = 0;
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                if(squares[i][j] == 'S') num++;
            }
        }
        return num;
    }

    void ResetBoard(){
         memset(squares,' ',sizeof(squares));
    }

    void SetBoard(char x,char y,char p){
        int nx = x - 'A';
        int ny = y - '1';
        squares[nx][ny] = p;
    }

    int CheckBoard(char x,char y){
        int nx = x - 'A';
        int ny = y - '1';
        return (squares[nx][ny] == 'H'||squares[nx][ny] == 'M');
    }
};

class Player{
private:
    string name;
    Board shipboard;
    Board firedboard;
public:
    void SetName(string name){
        this->name = name;
    }

    string GetName(){
        return name;
    }

    char Fire(char x,char y){
        return shipboard.FireAtSquare(x,y);
    }

    int PlaceShip(char x,char y,char dir,char size){
        return shipboard.PlaceShip(x, y, dir, size);
    }

    void DisplayBoard(){
        shipboard.DisplayBoard();
    }

    void DisplayFireBoard(){
        firedboard.DisplayBoard();
    }

    int CheckLost(){
        return shipboard.ShipLeft();
    }

    void ResetShip(){
        shipboard.ResetBoard();
    }

    void SetFireBoard(char x,char y,char p){
        firedboard.SetBoard(x,y,p);
    }

    void SetShipBoard(char x,char y,char p){
        shipboard.SetBoard(x,y,p);
    }

    int CheckHit(char x,char y){
        return firedboard.CheckBoard(x,y);
    }
};

Player player1;
Player player2;
string shiptype[5]={"Carrier","Battleship","Cruiser","Submarine","Destroyer"};
char shipsize[5]={'5','4','3','3','2'};

void ClearScreen(){
    if (system("CLS")) system("clear");
}

void EnterToContinue(){
    cout<<"Press enter to continue!";
    cin.clear(); //clears the stream
    cin.ignore(50,'\n'); //ignores next line(enter)
    cin.get(); //“cin>>” expects at least one char input, just enter doesn’t work
}

string GetName(int n){
    string playerName;
    cout<<"Enter player "<<n<<" name:"<<endl;
    cin>>playerName;
    return playerName;
}

void GetCdt(char* pxCdt,char* pyCdt){
    cout<<"Enter the x cordinates (A-H):";
    cin>>*pxCdt;
    while(*pxCdt<'A'||*pxCdt>'H'){
        cout<<"\nInvalid entry!Please try again.\n"<<"Enter the x cordinates (A-H):";
        cin>>*pxCdt;
    }

    cout<<"Enter the y cordinates (1-8):";
    cin>>*pyCdt;
    while(*pyCdt<'1'||*pyCdt>'8'){
        cout<<"\nInvalid entry!Please try again.\n"<<"Enter the y cordinates (1-8):";
        cin>>*pyCdt;
    }
}

void GetDir(char* pdir){
    cout<<"Enter the direction (N/E/S/W):";
    cin>>*pdir;
    while(*pdir != 'N'&&*pdir != 'E'&&*pdir != 'S'&&*pdir != 'W'){
        cout<<"\nInvalid entry!Please try again.\n"<<"Enter the direction (N/E/S/W):";
        cin>>*pdir;
    }
}

void AddShip1(){
    ClearScreen();
    cout<<"-------------------------------\n"<<"          Add Ship          \n"<<"-------------------------------"<<endl;
    cout<<"      No Name      Squares          \n"<<"-------------------------------"<<endl;
    cout<<"      1  Carrier      5          "<<endl;
    cout<<"      1  Battleship   4"<<endl;
    cout<<"      2  Cruiser      3"<<endl;
    cout<<"      1  Submarine    3"<<endl;
    cout<<"      1  Destroyer    2"<<endl;
    cout<<"-------------------------------"<<endl;
    char x[5];
    char y[5];
    char direction[5];
    int flag = 1;
    for(int i = 0;i < 5;i++){
        cout<<"\nPlayer 1 "<<"Adding a "<<shiptype[i]<<" size: "<<shipsize[i]<<endl;
        GetCdt(&x[i],&y[i]);
        GetDir(&direction[i]);
        if(player1.PlaceShip(x[i],y[i],direction[i],shipsize[i])==0){
            cout<<"\nInvalid entry!Please try again.\n";
            EnterToContinue();
            player1.ResetShip();
            flag = 0;
            break;
        }
        player1.DisplayBoard();
    }
    if(flag) {
        cout<<"All ship added!"<<endl;
        EnterToContinue();
    }
    if(!flag) AddShip1();
}

void AddShip2(){
    ClearScreen();
    cout<<"-------------------------------\n"<<"          Add Ship          \n"<<"-------------------------------"<<endl;
    cout<<"      No Name      Squares          \n"<<"-------------------------------"<<endl;
    cout<<"      1  Carrier      5          "<<endl;
    cout<<"      1  Battleship   4"<<endl;
    cout<<"      2  Cruiser      3"<<endl;
    cout<<"      1  Submarine    3"<<endl;
    cout<<"      1  Destroyer    2"<<endl;
    cout<<"-------------------------------"<<endl;
    char x[5];
    char y[5];
    char direction[5];
    int flag = 1;
    for(int i = 0;i < 5;i++){
        cout<<"\nPlayer 2 "<<"Adding a "<<shiptype[i]<<" size: "<<shipsize[i]<<endl;
        GetCdt(&x[i],&y[i]);
        GetDir(&direction[i]);
        if(player2.PlaceShip(x[i],y[i],direction[i],shipsize[i])==0){
            cout<<"\nInvalid entry!Please try again.\n";
            EnterToContinue();
            player2.ResetShip();
            flag = 0;
            break;
        }
        player2.DisplayBoard();
    }
    if(flag) {
        cout<<"All ship added!"<<endl;
        EnterToContinue();
    }
    if(!flag) AddShip2();
}

void Player2Fire1(){
    cout<<player2.GetName()<<" enter coordinates to fire"<<endl;
    player1.DisplayFireBoard();
    char x[1];
    char y[1];
    GetCdt(&x[0],&y[0]);
    while(player1.CheckHit(x[0],y[0])){
        cout<<"\nInvalid entry!Please try again.\n";
        GetCdt(&x[0],&y[0]);
    }
    player1.SetFireBoard(x[0],y[0],player1.Fire(x[0],y[0]));
    player1.SetShipBoard(x[0],y[0],player1.Fire(x[0],y[0]));
}

void Player1Fire2(){
    cout<<player1.GetName()<<" enter coordinates to fire"<<endl;
    player2.DisplayFireBoard();
    char x[1];
    char y[1];
    GetCdt(&x[0],&y[0]);
    while(player2.CheckHit(x[0],y[0])){
        cout<<"\nInvalid entry!Please try again.\n";
        GetCdt(&x[0],&y[0]);
    }
    player2.SetFireBoard(x[0],y[0],player2.Fire(x[0],y[0]));
    player2.SetShipBoard(x[0],y[0],player2.Fire(x[0],y[0]));
}

void StartGame(){
    string playerName = GetName(1);
    player1.SetName(playerName);
    playerName = GetName(2);
    player2.SetName(playerName);
    AddShip1();
    AddShip2();
    
    int turn = 0;
    while(true){
        ClearScreen();
        cout<<"Turn: "<<++turn<<endl;
        Player1Fire2();
        if(player2.CheckLost() == 0){
            cout<<"Player 1 win"<<endl;
            EnterToContinue();
            break;
        }
        ClearScreen();
        cout<<"Turn: "<<++turn<<endl;
        Player2Fire1();
        if(player1.CheckLost() == 0){
            cout<<"Player 2 win"<<endl;
            EnterToContinue();
            break;
        }
    }
    
}

void ExitGame(){
    cout<<"Exit"<<endl;
}

char DisplayMenu(){
    cout<<"-------------------------------\n"<<"          Battleships          \n"<<"          Main Menu          \n"<<"-------------------------------"<<endl;
    cout<<"          1.Start Game          \n"<<"          2.Exit Game          \n"<<endl;
    cout<<"Enter menu selection(1-2):";
    char menuChoice;
    cin>>menuChoice;
    return menuChoice;
}

int main(){
    char menuChoice;
    menuChoice = DisplayMenu();
    while(menuChoice != '1' && menuChoice != '2'){
        cout<<"Invalid entry!Please try again.\n\nEnter menu selection(1-2):";
        cin>>menuChoice;
    }
    switch(menuChoice){
        case '1': StartGame();break;
        case '2': ExitGame();break;

        default: break;
    }

    system( "PAUSE "); 
}