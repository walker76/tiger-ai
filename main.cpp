/*
 * Author: Schaeffer Duncan
 * Assignment Title: Group Project "The Tiger Game"
 * Assignment Description:
 * Due Date:
 * Date Created: 04/09/2018
 * Date Last Modified:
 */

#include <iostream>
#include <vector>
#include <cassert>
#include "Group_Four_Group_Project.h"
#include "SDL_Plotter.h"

SDL_Plotter *g;
int *data;
vector<Token_t> board;
const int SPEED = 10;
bool TRACE = false;

const int blackR = 0;
const int blackG = 0;
const int blackB = 0;
const int redR = 178;
const int redG = 34;
const int redB = 34;
const int blueR = 0;
const int blueG = 191;
const int blueB = 255;
const int whiteR = 255;
const int whiteG = 255;
const int whiteB = 255;

// Function declarations
void drawLine3(SDL_Plotter& g, Point_t one, Point_t two);
void drawLine4(SDL_Plotter& g, Point_t one, Point_t two);
void drawBack(SDL_Plotter& g);
void drawBoard(SDL_Plotter& g);
void plotAndUpdate();
void drawPieces(SDL_Plotter& g);
void initializePieces(vector<Token_t>& b);

//void drawLine(SDL_Plotter& g, Point_t one, Point_t two){
//    int j = one.row;
//    int i = one.col;
//    while(j < two.row && i < two.col){
//        i++;
//        j++;
//        g.plotPixel(j,i-350, blackR, blackG, blackB);
//    }
//}
//void drawLine2(SDL_Plotter& g, Point_t one, Point_t two){
//    int j = two.row;
//    int i = two.col;
//    while(j > one.row && i < one.col){
//        i++;
//        j--;
//        g.plotPixel(j,i-350, blackR, blackG, blackB);
//    }
//}

void drawLine3(SDL_Plotter& g, Point_t one, Point_t two){
    int j = one.row;
    int i = one.col;
    while(i < two.row && j < two.col){
        i++;
        j++;
        g.plotPixel(j, i+50, blackR, blackG, blackB);
    }
    plotAndUpdate();
}

void drawLine4(SDL_Plotter& g, Point_t one, Point_t two){
    int j = one.row;
    int i = one.col;
    while(j < two.row && i > two.col){
        i--;
        j++;
        g.plotPixel(j,i+50, blackR, blackG, blackB);
    }
}

void drawBack(SDL_Plotter& g){
    for(int i = 0; i < 500; i++){
        for(int j = 0; j < 750; j++){
            g.plotPixel(i,j, whiteR, whiteG, whiteB);
        }
    }
}

void drawBoard(SDL_Plotter& g){
    drawBack(g);
    for(int i = 50; i <= 450; i+=50){
        for(int j = 50; j < 450; j++){
            g.plotPixel(j,i+250, blackR, blackG, blackB);
        }
    }
    for(int i = 50; i < 450; i++){
        for(int j = 50; j <= 450; j+=50){
            g.plotPixel(j,i+250, blackR, blackG, blackB);
        }
    }
//    Point_t p1;
//    p1.row = 250;
//    p1.col = 450;
//    Point_t p2;
//    p2.row = 350;
//    p2.col = 550;
//    Point_t p3;
//    p3.row = 150;
//    p3.col = 550;
//    Point_t p4;
//    p4.row = 250;
//    p4.col = 650;
//    Point_t p5;
//    p5.row = 200;
//    p5.col = 500;
//    Point_t p6;
//    p6.row = 300;
//    p6.col = 600;
//    Point_t p7;
//    p7.row = 200;
//    p7.col = 600;
//    Point_t p8;
//    p8.row = 300;
//    p8.col = 500;
//
//    drawLine(g, p1, p2);
//    drawLine(g, p3, p4);
//    drawLine(g, p5, p6);
//
//    drawLine2(g, p3, p1);
//    drawLine2(g, p4, p2);
//    drawLine2(g, p7, p8);
    
    Point_t p1;
    p1.row = 350;
    p1.col = 150;
    Point_t p2;
    p2.row = 250;
    p2.col = 250;
    Point_t p3;
    p3.row = 150;
    p3.col = 150;
    Point_t p4;
    p4.row = 250;
    p4.col = 50;
    Point_t p5;
    p5.row = 200;
    p5.col = 300;
    Point_t p6;
    p6.row = 200;
    p6.col = 200;
    Point_t p7;
    p7.row = 200;
    p7.col = 100;
    Point_t p8;
    p8.row = 300;
    p8.col = 100;
    
    Point_t p9;
    p9.row = 450;
    p9.col = 450;
    Point_t p10;
    p10.row = 250;
    p10.col = 650;
    Point_t p11;
    p11.row = 50;
    p11.col = 450;
    
    drawLine3(g, p1, p4);
    drawLine3(g, p7, p5);
    drawLine3(g, p3, p2);
    
    drawLine4(g, p2, p1);
    drawLine4(g, p3, p4);
    drawLine4(g, p6, p8);
    
    drawLine3(g, p2, p9);
    drawLine3(g, p11, p10);
    
    drawLine4(g, p10, p9);
    drawLine4(g, p11, p2);
    
    plotAndUpdate();
}

void plotAndUpdate(){
    g->update();
    g->Sleep(SPEED);
}

void drawPieces(SDL_Plotter& g){
    for(int k = 0; k < int(board.size()); k++){
        for(int i = 0; i < 25; i++){
            for(int j = 0; j < 25; j++){
                if(board[k].color == RED){
                    g.plotPixel((board[k].location.col) + i-12,board[k].location.row + j-12, redR, redG, redB);
                } else if(board[k].color == BLUE){
                    g.plotPixel((board[k].location.col) + i-12,board[k].location.row + j-12, blueR, blueG, blueB);
                } else {
                    assert(false);
        }
    }
    //plotAndUpdate();
            }
    }
    plotAndUpdate();
}

void initializePieces(vector<Token_t>& b){
    int k = 0;
    Token_t temp1;
    temp1.location.row = 200;
    temp1.location.col = 250;
    temp1.color = RED;
    board.push_back(temp1);
    k++;
    for(int i = 650; i <= 700; i+=50){
        for(int j = 50; j <= 450; j+=50){
            Token_t temp;
            temp.location.row = i;
            temp.location.col = j;
            temp.color = BLUE;
            board.push_back(temp);
            k++;
        }
    }
}

int main() {
    g = new SDL_Plotter(750,500);
    drawBoard(*g);
    initializePieces(board);
    
    // if we are trying to implement the AI
    bool aiEnter = false;
    
    Point_t thePoint;
    Token_t theToken;
    
    
    if(aiEnter){
//        // uncomment below statement if we are testing tiger
//        Move_t ourMove = Move_Group_Four(board, RED);
//
//        //uncomment below statement if we are testing the men
//        Move_t ourMove = Move_Group_Four(board, BLUE);
//
//        //this is to test the code left in this if statement box
//        Move_t ourMove(theToken, thePoint);
//
//        int boardIndex = -1;
//        for(int i = 0; i < int(board.size()); i++){
//            if(ourMove.token == board[i]){
//                boardIndex = i;
//            }
//        }
//
//        board[boardIndex].location = thePoint;
//        drawBoard(*g);
//        drawPieces(*g);
        
    } else {
        //drawPieces(*g);
        bool keepGoing0 = true;
        while(keepGoing0){
            if(g->kbhit()){
                int index = -1;
                bool keepGoing1 = true;
                char tempChar = '\0';
                char tempChar2 = '\0';
                cout << "Enter piece ID and direction ID: ";
                while(keepGoing1){
                    cin.get(tempChar);
                    tempChar = toupper(tempChar);
                    switch(tempChar){
                        case 'A':theToken = board[1];
                            index = 1;
                            keepGoing1 = false;
                            break;
                        case 'B':theToken = board[2];
                            index = 2;
                            keepGoing1 = false;
                            break;
                        case 'C':theToken = board[3];
                            index = 3;
                            keepGoing1 = false;
                            break;
                        case 'D':theToken = board[4];
                            index = 4;
                            keepGoing1 = false;
                            break;
                        case 'E':theToken = board[5];
                            index = 5;
                            keepGoing1 = false;
                            break;
                        case 'F':theToken = board[6];
                            index = 6;
                            keepGoing1 = false;
                            break;
                        case 'G':theToken = board[7];
                            index = 7;
                            keepGoing1 = false;
                            break;
                        case 'H':theToken = board[8];
                            index = 8;
                            keepGoing1 = false;
                            break;
                        case 'I':theToken = board[9];
                            index = 9;
                            keepGoing1 = false;
                            break;
                        case 'J':theToken = board[10];
                            index = 10;
                            keepGoing1 = false;
                            break;
                        case 'K':theToken = board[11];
                            index = 11;
                            keepGoing1 = false;
                            break;
                        case 'L':theToken = board[12];
                            index = 12;
                            keepGoing1 = false;
                            break;
                        case 'M':theToken = board[13];
                            index = 13;
                            keepGoing1 = false;
                            break;
                        case 'N':theToken = board[14];
                            index = 14;
                            keepGoing1 = false;
                            break;
                        case 'O':theToken = board[15];
                            index = 15;
                            keepGoing1 = false;
                            break;
                        case 'P':theToken = board[16];
                            index = 16;
                            keepGoing1 = false;
                            break;
                        case 'Q':theToken = board[17];
                            index = 17;
                            keepGoing1 = false;
                            break;
                        case 'R':theToken = board[18];
                            index = 18;
                            keepGoing1 = false;
                            break;
                        case 'S':theToken = board[19];
                            index = 19;
                            keepGoing1 = false;
                            break;
                        case 'T':theToken = board[0];
                            index = 0;
                            keepGoing1 = false;
                            break;
                        case 'Y': g->clear();
                            keepGoing1 = false;
                            break;
                        case 'X': g->setQuit(true);
                            keepGoing1 = false;
                            break;
                        default:
                            keepGoing1 = true;
                            break;
                    }
                }
                
                if(tempChar != 'T'){
                    cout << char(index+64) << " -";
                } else {
                    cout << "T" << " -";
                }
                
                keepGoing1 = true;
                
                while(keepGoing1){
                    if(tempChar == 'T'){
                        for(int i = 0; i < 1; i++){
                            cin.get(tempChar);
                            tempChar = toupper(tempChar);
                            cin.get(tempChar2);
                            tempChar2 = toupper(tempChar2);
                            keepGoing1 = true;
                            while(keepGoing1){
                                switch(tempChar){
                                    case '2':thePoint = theToken.location;
                                        thePoint.row += 50;
                                        keepGoing1 = false;
                                        cout << " DOWN &";
                                        break;
                                    case '4':thePoint = theToken.location;
                                        thePoint.col += 50;
                                        keepGoing1 = false;
                                        cout << " RIGHT &";
                                        break;
                                    case '1':thePoint = theToken.location;
                                        thePoint.row -= 50;
                                        keepGoing1 = false;
                                        cout << " UP &";
                                        break;
                                    case '3':thePoint = theToken.location;
                                        thePoint.col -= 50;
                                        keepGoing1 = false;
                                        cout << " LEFT &";
                                        break;
                                    case '5': keepGoing0 = false;
                                        keepGoing1 = false;
                                        break;
                                    default:
                                        //cout << "Enter direction" << endl;
                                        break;
                                }
                                switch(tempChar2){
                                    case '2':
                                        thePoint.row += 50;
                                        keepGoing1 = false;
                                        cout << " DOWN";
                                        break;
                                    case '4':
                                        thePoint.col += 50;
                                        keepGoing1 = false;
                                        cout << " RIGHT";
                                        break;
                                    case '1':
                                        thePoint.row -= 50;
                                        keepGoing1 = false;
                                        cout << " UP";
                                        break;
                                    case '3':
                                        thePoint.col -= 50;
                                        keepGoing1 = false;
                                        cout << " LEFT";
                                        break;
                                    case '5': keepGoing0 = false;
                                        keepGoing1 = false;
                                        break;
                                    default:
                                        //cout << "Enter direction" << endl;
                                        break;
                                }
                            }
                            
                            cout << endl;
                        }
                    } else {
                        cin.get(tempChar);
                        tempChar = toupper(tempChar);
                        
                        switch(tempChar){
                            case '2':thePoint = theToken.location;
                                thePoint.row += 50;
                                keepGoing1 = false;
                                cout << " DOWN" << endl;
                                break;
                            case '4':thePoint = theToken.location;
                                thePoint.col += 50;
                                keepGoing1 = false;
                                cout << " RIGHT" << endl;
                                break;
                            case '1':thePoint = theToken.location;
                                thePoint.row -= 50;
                                keepGoing1 = false;
                                cout << " UP" << endl;
                                break;
                            case '3':thePoint = theToken.location;
                                thePoint.col -= 50;
                                keepGoing1 = false;
                                cout << " LEFT" << endl;
                                break;
                            case '5': keepGoing0 = false;
                                keepGoing1 = false;
                                break;
                            default:
                                //cout << "Enter direction" << endl;
                                break;
                        }
                    }
                    
                }
                
                keepGoing1 = true;
                board[index].location = thePoint;
                Move_t theMove(theToken, thePoint);
                drawBoard(*g);
                drawPieces(*g);
            }
            drawPieces(*g);
        }
    }
    return 0;
}
