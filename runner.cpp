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
#include "Group_Four_Group_Project.h"

using namespace std;

vector<Token_t> board;

int main() {

    board.emplace_back(tokenMaker(RED, pointMaker(2,4)));
    board.emplace_back(tokenMaker(BLUE, pointMaker(11,0)));
    board.emplace_back(tokenMaker(BLUE, pointMaker(11,1)));
    board.emplace_back(tokenMaker(BLUE, pointMaker(11,2)));
    board.emplace_back(tokenMaker(BLUE, pointMaker(11,3)));
    board.emplace_back(tokenMaker(BLUE, pointMaker(11,4)));
    board.emplace_back(tokenMaker(BLUE, pointMaker(11,5)));
    board.emplace_back(tokenMaker(BLUE, pointMaker(11,6)));
    board.emplace_back(tokenMaker(BLUE, pointMaker(11,7)));
    board.emplace_back(tokenMaker(BLUE, pointMaker(11,8)));
    board.emplace_back(tokenMaker(BLUE, pointMaker(12,0)));
    board.emplace_back(tokenMaker(BLUE, pointMaker(12,1)));
    board.emplace_back(tokenMaker(BLUE, pointMaker(12,2)));
    board.emplace_back(tokenMaker(BLUE, pointMaker(12,3)));
    board.emplace_back(tokenMaker(BLUE, pointMaker(12,4)));
    board.emplace_back(tokenMaker(BLUE, pointMaker(12,5)));
    board.emplace_back(tokenMaker(BLUE, pointMaker(12,6)));
    board.emplace_back(tokenMaker(BLUE, pointMaker(12,7)));
    board.emplace_back(tokenMaker(BLUE, pointMaker(12,8)));

    //cout << "Finished placing back tokens" << endl;

    int counter  = 500;
    while(counter >= 0){
        cout << endl << endl << "Move " << counter << " - ";
        Move_t currentMove;
        if(counter % 2 == 0){
            cout << "Red Move" << endl;
            currentMove = Move_Group_Four(board, RED);
            //cout << "Tiger Move - " << currentMove.destination.row << " " << currentMove.destination.col << endl;
            for(int i = 0; i < board.size(); i++){
                if(board.at(i).color == RED)
                    board[i] = tokenMaker(RED, currentMove.destination);
            }
        } else {
            cout << "Blue Move" << endl;
            currentMove = Move_Group_Four(board, BLUE);
            for(unsigned int i = 0; i < board.size(); i++){
                if(board.at(i).location.row == currentMove.token.location.row && board.at(i).location.col == currentMove.token.location.col){
                    board[i] = tokenMaker(BLUE, currentMove.destination);
                }
            }
        }
        cout << "(" << currentMove.token.location.row << ", " << currentMove.token.location.col << ") - (" << currentMove.destination.row << ", " << currentMove.destination.col << ")" << endl;
        counter--;
    }

    return 0;
}

