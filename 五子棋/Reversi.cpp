#define _CRT_SECURE_NO_WARNINGS
#include "Reversi.h"

#define random(x) (rand()%x)
#define ROWS 19
#define COLS 19
#define ROUNDS 3

Reversi::Reversi(){
    client_socket = ClientSocket();
    oppositeColor = ownColor = -1;
}

Reversi::~Reversi(){}
void Reversi::setOwnColor(int color)
{
	if (color != 0 || color != 1)
		return;
	ownColor = color;
	oppositeColor = 1 - color;
}
;

/*
 send id and password to server by socket
 rtn != 0 represents socket transfer error
 */
void Reversi::authorize(const char *id , const char *pass)
{
    client_socket.connectServer();
    std::cout << "Authorize " << id << std::endl;
    char msgBuf[BUFSIZE];
    memset(msgBuf , 0 , BUFSIZE);
    msgBuf[0] = 'A';
    memcpy(&msgBuf[1] , id , 9);
    memcpy(&msgBuf[10] , pass , 6);
    int rtn = client_socket.sendMsg(msgBuf);
    if (rtn != 0) printf("Authorized Failed!\n");
}

// 用户id输入，服务器上需要有对应的账号密码：对应文件 players-0.txt
void Reversi::gameStart()
{
    char id[12] = {0}, passwd[10] = {0};
	strcpy(id, ID);
	strcpy(passwd, PASSWORD);
    authorize(id, passwd);
    
    printf("Game Start!\n");
    
    for (int round = 0 ; round < ROUNDS ; round++){
        roundStart(round);
        oneRound();
        roundOver(round);
    }
    gameOver();
    client_socket.close();
}

void Reversi::gameOver()
{
    printf("Game Over!\n");
}

//发一次消息，走哪一步，等两个消息，1.自己的步数行不行 2.对面走了哪一步 
void Reversi::roundStart(int round)
{
    printf("Round %d Ready Start!\n" , round);
	myround = round;
    // first time receive msg from server
    int rtn = client_socket.recvMsg();
    if (rtn != 0) return ;
    if(strlen(client_socket.getRecvMsg()) < 2)
        printf("Authorize Failed!\n");
    else
        printf("Round start received msg %s\n", client_socket.getRecvMsg());
    switch (client_socket.getRecvMsg()[1]) {
            // this client : black chessman
        case 'B':
            ownColor = 0;
            oppositeColor = 1;
            rtn = client_socket.sendMsg("BB");
            printf("Send BB -> rtn: %d\n", rtn);
            if (rtn != 0) return ;
            break;
        case 'W':
            ownColor = 1;
            oppositeColor = 0;
            rtn = client_socket.sendMsg("BW");
            printf("Send BW -> rtn: %d\n", rtn);
            if (rtn != 0) return ;
            break;
        default:
            printf("Authorized Failed!\n");
            break;
    }
	boardintial();
}

void Reversi::oneRound()
{
    int STEP = 1;
    switch (ownColor) {
        case 0:
            while (STEP < 10000) {
                
				pair<int, int> chess = step();                        // take action, send message
                
                // lazi only excute after server's message confirm  in observe function
                generateOneStepMessage(chess.first, chess.second);
                
                
                if (observe() >= 1) break;     // receive RET Code
                
                if (observe() >= 1) break;    // see white move
                STEP++;
                // saveChessBoard();
            }
            printf("One Round End\n");
            break;
        case 1:
            while (STEP < 10000) {
                
                if (observe() >= 1) break;    // see black move
                
				pair<int, int> chess = step();                        // take action, send message
                // lazi only excute after server's message confirm  in observe function
                generateOneStepMessage(chess.first,chess.second);
                
                
                if (observe() >= 1) break;     // receive RET Code
                // saveChessBoard();
                STEP++;
            }
            printf("One Round End\n");
            break;
            
        default:
            break;
    }
}

void Reversi::roundOver(int round)
{
    printf("Round %d Over!\n", round);
    // reset initializer

    ownColor = oppositeColor = -1;
}

int Reversi::observe()
{
	int rtn = 0;
	int recvrtn = client_socket.recvMsg();
	if (recvrtn != 0) return 1;
	printf("receive msg %s\n", client_socket.getRecvMsg());
	switch (client_socket.getRecvMsg()[0]) {
	case 'R':
	{
		switch (client_socket.getRecvMsg()[1]) {
		case 'Y':   // valid step
			switch (client_socket.getRecvMsg()[2]) {
			case 'P':   // update chessboard
			{
				int desRow = (client_socket.getRecvMsg()[3] - '0') * 10 + client_socket.getRecvMsg()[4] - '0';
				int desCol = (client_socket.getRecvMsg()[5] - '0') * 10 + client_socket.getRecvMsg()[6] - '0';
				int color = (client_socket.getRecvMsg()[7] - '0');
				//你应该在这里处理desRow和desCol，推荐使用函数
				handleMessage(desRow, desCol, color);

				printf("a valid step of : (%d %d)\n", desRow, desCol);
				break;
			}
			case 'N':   // R0N: enemy wrong step
			{
				//
				printf("a true judgement of no step\n");
				break;
			}
			}

			break;
		case 'W':
			// invalid step
			switch (client_socket.getRecvMsg()[2]) {
			case 'P': {
				int desRow = (client_socket.getRecvMsg()[3] - '0') * 10 + client_socket.getRecvMsg()[4] - '0';
				int desCol = (client_socket.getRecvMsg()[5] - '0') * 10 + client_socket.getRecvMsg()[6] - '0';
				int color = (client_socket.getRecvMsg()[7] - '0');
				printf("Invalid step , server random a true step of : (%d %d)\n", desRow, desCol);
				//你应该在这里处理desRow和desCol，推荐使用函数
				handleMessage(desRow, desCol, color);
				break;
			}
			case 'N': {
				printf("a wrong judgement of no step\n");
				break;
			}
			default:
				break;
			}
			break;
		case '1':

			printf("Error -1: Msg format error!\n");
			rtn = -1;
			break;
		case '2':

			printf("Error -2: Corrdinate error!\n");
			rtn = -2;
			break;
		case '4':

			printf("Error -4: Invalid step!\n");
			rtn = -4;
			break;
		default:

			printf("Error -5: Other error!\n");
			rtn = -5;
			break;
		}
		break;
	}
	case 'E':
	{
		switch (client_socket.getRecvMsg()[1]) {
		case '0':
			// game over
			rtn = 2;
			break;
		case '1':
			// round over
			rtn = 1;
		default:
			break;
		}
		break;
	}
	default:
		break;
	}
	return rtn;
}

void Reversi::generateOneStepMessage(int row, int col)
{
	char msg[BUFSIZE];
	memset(msg, 0, sizeof(msg));

	//put row and col in the message
	msg[0] = 'S';
	msg[1] = 'P';
	msg[2] = '0' + row / 10;
	msg[3] = '0' + row % 10;
	msg[4] = '0' + col / 10;
	msg[5] = '0' + col % 10;
	msg[6] = '\0';

	//print
	printf("generate one step at possition (%2d,%2d) : %s\n", row, col, msg);


	client_socket.sendMsg(msg);
}

/*-------------------------last three function--------------------------------
* step : find a good position to lazi your chess.
* saveChessBoard : save the chess board now.
* handleMessage: handle the message from server.
*/

pair<int, int> Reversi::step()
{
	int r, c, maxval = 0;
	for (int i = loc2w; i <= loc2s; ++i)
		for (int j = loc2a; j <= loc2d; ++j)
			if (board[i][j] == 0)
			{
				if (board[i - 1][j] || board[i][j - 1] || board[i + 1][j] || board[i][j + 1] || board[i - 1][j + 1] || board[i - 1][j - 1] || board[i + 1][j - 1] || board[i + 1][j + 1])
				{
					int temp = getvalue(i, j);
					if (temp > maxval)
					{
						maxval = temp;
						r = i;
						c = j;
					}
				}
			}
			else
				continue;
	return make_pair(r, c);
}



void Reversi::saveChessBoard(int row, int col, int color)
{
	fstream file;
	file.open(path, ios::app);
	if (!file.is_open())
		exit(-1);
	string name = color ? "White is down " : "Black is down ";
	file << name << '(' << row << ',' << col << ") ." << endl;
	for (int i = 0; i < 19; ++i)
	{
		for (int j = 0; j < 19; ++j)
			file << board[i][j] << ' ';
		file << endl;
	}
}

void Reversi::handleMessage(int row, int col, int color) 
{
	board[row][col] = (color==ownColor)?1:7;
	loc2a = loc2a < col - 1 ? loc2a : col - 1;
	loc2d = loc2d > col + 1 ? loc2d : col + 1;
	loc2w = loc2d < row - 1 ? loc2w : row - 1;
	loc2s = loc2s > row + 1 ? loc2s : row + 1;
	loc2a = loc2a < 0 ? 0 : loc2a;
	loc2d = loc2d %19;
	loc2w = loc2d <0 ? 0 : loc2w;
	loc2s = loc2s % 19;
	saveChessBoard(row, col, color);
}
void Reversi::boardintial()
{
	for (int i = 0; i < 19; ++i)
		for (int j = 0; j < 19; ++j)
			if (i == 9 && j == 9)
				board[i][j] = ownColor ? 1 : 7;
			else
				board[i][j] = 0;
	loc2a = 8;
	loc2d = 10;
	loc2s = 10;
	loc2w = 8;
	path = "C:\\Users\\27506\\Desktop\\clinet_win\\";
	string name;
	if (myround == 0)
		name= "Roundone.txt";
	else if (myround == 1)
		name= "Roundtwo.txt";
	else
		name= "Roundthree.txt";
	path += name;
	fstream file;
	file.open(path, ios::out);
	if (!file.is_open())
		exit(-1);
	file.close();
}
int Reversi::getvalue(int row, int col)
{
	int val = 0;
	string sp="",sa="";
	for (int i = 4; i!=0; i--)
	{
		int l = row - i;
		if (l < 0)
			continue;
		else
		{
			sp += (board[l][col] + '0');
			sa += (board[l][col] + '0');
		}
	}
	sp += '7';
	sa += '1';
	for (int i = 1; i < 5 ; ++i)
	{
		int r = row + i;
		if (r > 18)
			break;
		else
		{
			sp += (board[r][col] + '0');
			sa += (board[r][col] + '0');
		}
	}
	val += calculate(sp, sa);
	for (int i = 4; i !=0; i--)
	{
		int l = col - i;
		if (l < 0)
			continue;
		else
		{
			sp += (board[row][l] + '0');
			sa += (board[row][l] + '0');
		}
	}
	sp += '7';
	sa += '1';
	for (int i = 1; i < 5; ++i)
	{
		int r = col + i;
		if (r > 18)
			break;
		else
		{
			sp += (board[row][r] + '0');
			sa += (board[row][r] + '0');
		}
	}
	val += calculate(sp, sa);
	for (int i = 4; i !=0; i--)
	{
		int r = row + i;
		int c = col - i;
		if (c < 0||r>18)
			continue;
		else
		{
			sp += (board[r][c] + '0');
			sa += (board[r][c] + '0');
		}
	}
	sp += '7';
	sa += '1';
	for (int i = 1; i < 5; ++i)
	{
		int r = row - i;
		int c = col + i;
		if (r <0||c>18)
			break;
		else
		{
			sp += (board[r][c] + '0');
			sa += (board[r][c] + '0');
		}
	}
	val += calculate(sp, sa);
	for (int i = 4; i != 0; i--)
	{
		int r = row - i;
		int c = col - i;
		if (c < 0 || r<0)
			continue;
		else
		{
			sp += (board[r][c] + '0');
			sa += (board[r][c] + '0');
		}
	}
	sp += '7';
	sa += '1';
	for (int i = 1; i < 5; ++i)
	{
		int r = row + i;
		int c = col + i;
		if (r >18 || c>18)
			break;
		else
		{
			sp += (board[r][c] + '0');
			sa += (board[r][c] + '0');
		}
	}
	val += calculate(sp, sa);
	return val;
}
int Reversi::calculate(string& sp, string& sa)
{
	if (sp.size() < 6)
		return -1;
	int pre = 0, aft = 0, end = sp.size() - 6;
	for (int i = 0; i <= end; ++i)
	{
		string s = "";
		for (int j = i; j < i + 6; ++j)
			s += sp[j];
		if (value.count(s))
			pre=(abs(pre)>abs(value[s]))?pre:value[s];
	}
	for (int i = 0; i <= end; ++i)
	{
		string s = "";
		for (int j = i; j < i + 6; ++j)
			s += sa[j];
		if (value.count(s))
			aft = (abs(aft) > abs(value[s])) ? aft : value[s];
	}
	sp = "";
	sa = "";
	return aft - pre;
}