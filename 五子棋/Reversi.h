#ifndef Reversi_h
#define Reversi_h
#include <stdio.h>
#include <ctime>
#include<map>
#include<string>
#include<fstream>
#include "ClientSocket.h"


using namespace std;

class Reversi{
private:
    ClientSocket client_socket;
    int ownColor;
    int oppositeColor;

	//function 

	 // according to chessman position (row , col) , generate one step message in order to send to server
    void generateOneStepMessage(int row, int col);

public:
	pair<int, int> step();
    
    void saveChessBoard(int row, int col, int color);

	void handleMessage(int row, int col, int color);
    int board[19][19] = {};
    int boundary_r, boundary_c;
    int loc2w, loc2a, loc2d, loc2s;
    int getvalue(int row, int col);
    int calculate(string& sp, string& sa);
    int myround;
    string path;
    map<string, int> value = {
        //己方
        {"011111",1100000},//连五
        {"111110",1100000},
        {"711111",1100000},
        {"111117",1100000},
        {"111111",1100000},
        {"011110",110000},//活四
        {"011117",15000},//冲四
        {"010111",15000},
        {"101110",15000},
        {"011011",15000},
        {"110110",15000},
        {"001110",11000},//活三
        {"011100",11000},
        {"010110",11000},
        {"001117",1000},//眠三
        {"010117",1000},
        {"011017",1000},
        {"010011",1000},
        {"100110",1000},
        {"010101",1000},
        {"101010",1000},
        {"701110",1000},
        {"011107",1000},
        {"001100",200},//活二
        {"001010",200},
        {"010100",200},
        {"010010",200},
        {"000117",100},//眠二
        {"001017",100},
        {"010017",100},
        {"010001",100},
        {"100010",100},//一子
        {"170000",10},
        {"017000",10},
        {"001700",10},
        {"000170",10},
        {"000017",10},
        //对手
        {"077777",-1000000},//连五
        {"777770",-1000000},
        {"177777",-1000000},
        {"777771",-1000000},
        {"777777",-1000000},
        {"077770",-100000},//活四

        {"077771",-12000},//冲四
        {"070777",-12000},
        {"707770",-12000},
        {"077077",-12000},
        {"770770",-12000},

        {"007777",-12000},
        {"177770",-12000},
        {"170777",-12000},
        {"707771",-12000},
        {"770771",-12000},
        {"177077",-12000},
        {"007770",-10000},//活三
        {"077700",-10000},
        {"070770",-10000},
        {"007771",-1000},//眠三
        {"070771",-1000},
        {"077071",-1000},
        {"070077",-1000},
        {"700770",-1000},
        {"070707",-1000},
        {"707070",-1000},
        {"107770",-1000},
        {"077701",-1000},
        {"007700",-200},//活二
        {"007070",-200},
        {"070700",-200},
        {"070070",-200},
        {"000771",-100},//眠二
        {"007071",-100},
        {"070071",-100},
        {"070007",-100},
        {"700070",-100}
    };
public:
    Reversi();
    ~Reversi();
	void setOwnColor(int color);

    void authorize(const char *id , const char *pass);
    
    void gameStart();
    
    void gameOver();
    
    void roundStart(int round);
    
    void oneRound();
    
    void roundOver(int round);
    
    int observe();
    void boardintial();
};

#endif /* Reversi_h */
