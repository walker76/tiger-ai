/*
 * Author: Andrew Walker, Schaeffer Duncan, Isaiah Bullard, Moises Narvaez, Evan Baker
 * Assignment Title: Group Project "The Tiger Game"
 * Assignment Description: This is the implementation of the AI for both the tiger and the men
 * Due Date: 04/26/18
 * Date Created: 04/09/2018
 * Date Last Modified: 04/26/18
 */

#ifndef TIGER_GAME_TIGER_H
#define TIGER_GAME_TIGER_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>

using namespace std;

enum Color_t {RED, BLUE};

struct Point_t{
	int row, col;
};

bool operator==(Point_t thisPoint, Point_t that){
    return (thisPoint.col == that.col) && (thisPoint.row == that.row);
}

Point_t pointMaker(int row, int col){
    Point_t p;
    p.row = row;
    p.col = col;
    return p;
}

struct Token_t{
	Color_t color;
	Point_t location;
};

bool operator==(Token_t thisToken, Token_t that){
    return (thisToken.color == that.color) && (thisToken.location == that.location);
}

Token_t tokenMaker(Color_t color, Point_t location){
	Token_t toReturn;
    toReturn.color = color;
    toReturn.location = location;
    return toReturn;
}

struct Move_t{
	Token_t token;
	Point_t destination;
};

struct Calculation{
    Point_t destination;
    double value;
    Token_t token;
    Calculation(Point_t destination, double value, Token_t token){
        this->value = value;
        this->destination = destination;
        this->token = token;
    }
};

class GameRecord{
public:
    static vector<vector<Token_t> > previousGame;
    static const int UP = 1;
    static const int RIGHT = 2;
    static const int DOWN = 3;
    static const int LEFT = 4;

    void addRecord(vector<Token_t> game){
        previousGame.emplace_back(game);
    }

    vector<vector<Token_t> > getGame(){
        return previousGame;
    }

};

vector<vector<Token_t> > GameRecord::previousGame;

void addRecord(vector<Token_t> game){
    GameRecord::previousGame.emplace_back(game);
}

int getPrimaryDirection(){
    if(GameRecord::previousGame.size() > 3){
        vector<Token_t> firstGame = GameRecord::previousGame.at(0);
        vector<Token_t> recentGame = *GameRecord::previousGame.end();

        Token_t tigerStart;
        Token_t tigerCurrent;
        for(unsigned int i = 0; i < firstGame.size(); i++){
            if(firstGame.at(i).color == RED)
                tigerStart = firstGame.at(i);
        }

        for(unsigned int i = 0; i < firstGame.size(); i++){
            if(firstGame.at(i).color == RED)
                tigerCurrent = firstGame.at(i);
        }

        if(abs(tigerStart.location.row - tigerCurrent.location.row) > abs(tigerStart.location.col - tigerCurrent.location.col)){
            if(tigerStart.location.row - tigerCurrent.location.row > 0){
                return GameRecord::UP;
            } else{
                return GameRecord::DOWN;
            }
        } else {
            if(tigerStart.location.col - tigerCurrent.location.col > 0){
                return GameRecord::RIGHT;
            } else{
                return GameRecord::LEFT;
            }
        }

    } else {
        return -1;
    }
}


Move_t  Move_Group_Four(vector<Token_t>, Color_t);
Move_t Move_Tiger(vector<Token_t>);
Move_t Move_Men(vector<Token_t>);
bool isValidMove(Point_t, Point_t);
bool isDiagonalMove(Point_t, Point_t);
double distance(Point_t, Point_t);
double calculateDanger(vector<Token_t>, Point_t);
double calculateTigerScore(vector<Token_t>);


Move_t  Move_Group_Four(vector<Token_t> tokens, Color_t turn){
    //GameRecord gr;
    //gr.addRecord(tokens);
    if(turn == RED){
        //cout << "Move_Group_Four - RED" << endl;
        return Move_Tiger(tokens);
    }
    else {
        //cout << "Move_Group_Four - BLUE" << endl;
        return Move_Men(tokens);
    }
}

Move_t Move_Tiger(vector<Token_t> tokens){
    vector<Calculation> possibleMoves;
    bool tigerFound = false;
    for(unsigned int i = 0; !tigerFound && i < tokens.size(); i++){
        Token_t tiger = tokens.at(i);
        if(tiger.color == RED){
            //cout << "Found Tiger at " << tiger.location.row << " " << tiger.location.col << endl;
            tigerFound = true;

            Point_t point = pointMaker(tiger.location.row - 1, tiger.location.col - 1);
            //cout << endl << "point - " << point.row << point.col << endl;
            //cout << "Point 1" << endl;
            if(isValidMove(tiger.location, point)){
                bool notInVector = true;
                for(unsigned int j = 0; j < tokens.size(); j++){
                    if(tokens.at(j).location.row == point.row && tokens.at(j).location.col == point.col){
                        notInVector = false;
                    }
                }
                if(notInVector){
                    //cout << "notInVector" << endl;
                    vector<Token_t> newBoard(tokens);
                    newBoard[i] = tokenMaker(RED, point);
                    possibleMoves.emplace_back(Calculation(point, calculateTigerScore(newBoard), tiger));
                } else {
                    Point_t extendedPoint = pointMaker(tiger.location.row - 2, tiger.location.col - 2);
                    if(isValidMove(point, extendedPoint)){
                        bool innerNotInVector = true;
                        for(unsigned int j = 0; j < tokens.size(); j++){
                            if(tokens.at(j).location.row == extendedPoint.row && tokens.at(j).location.col == extendedPoint.col){
                                innerNotInVector = false;
                            }
                        }
                        if(innerNotInVector){
                            vector<Token_t> newBoard(tokens);
                            newBoard[i] = tokenMaker(RED, extendedPoint);
                            possibleMoves.emplace_back(Calculation(extendedPoint, 100 * calculateTigerScore(newBoard), tiger));
                        }
                    }
                }
            }

            point = pointMaker(tiger.location.row - 1, tiger.location.col);
            //cout << endl << "point - " << point.row << point.col << endl;
            //cout << "Point 2" << endl;
            if(isValidMove(tiger.location, point)){
                bool notInVector = true;
                for(unsigned int j = 0; j < tokens.size(); j++){
                    if(tokens.at(j).location.row == point.row && tokens.at(j).location.col == point.col){
                        notInVector = false;
                    }
                }
                if(notInVector){
                    //cout << "notInVector" << endl;
                    vector<Token_t> newBoard(tokens);
                    newBoard[i] = tokenMaker(RED, point);
                    possibleMoves.emplace_back(Calculation(point, calculateTigerScore(newBoard), tiger));
                } else {
                    Point_t extendedPoint = pointMaker(tiger.location.row - 2, tiger.location.col);
                    if(isValidMove(point, extendedPoint)){
                        bool innerNotInVector = true;
                        for(unsigned int j = 0; j < tokens.size(); j++){
                            if(tokens.at(j).location.row == extendedPoint.row && tokens.at(j).location.col == extendedPoint.col){
                                innerNotInVector = false;
                            }
                        }
                        if(innerNotInVector){
                            vector<Token_t> newBoard(tokens);
                            newBoard[i] = tokenMaker(RED, extendedPoint);
                            possibleMoves.emplace_back(Calculation(extendedPoint, 100 * calculateTigerScore(newBoard), tiger));
                        }
                    }
                }
            }

            point = pointMaker(tiger.location.row - 1, tiger.location.col + 1);
            //cout << endl << "point - " << point.row << point.col << endl;
            //cout << "Point 3" << endl;
            if(isValidMove(tiger.location, point)){
                bool notInVector = true;
                for(unsigned int j = 0; j < tokens.size(); j++){
                    if(tokens.at(j).location.row == point.row && tokens.at(j).location.col == point.col){
                        notInVector = false;
                    }
                }
                if(notInVector){
                    //cout << "notInVector" << endl;
                    vector<Token_t> newBoard(tokens);
                    newBoard[i] = tokenMaker(RED, point);
                    possibleMoves.emplace_back(Calculation(point, calculateTigerScore(newBoard), tiger));
                } else {
                    Point_t extendedPoint = pointMaker(tiger.location.row - 2, tiger.location.col + 2);
                    if(isValidMove(point, extendedPoint)){
                        bool innerNotInVector = true;
                        for(unsigned int j = 0; j < tokens.size(); j++){
                            if(tokens.at(j).location.row == extendedPoint.row && tokens.at(j).location.col == extendedPoint.col){
                                innerNotInVector = false;
                            }
                        }
                        if(innerNotInVector){
                            vector<Token_t> newBoard(tokens);
                            newBoard[i] = tokenMaker(RED, extendedPoint);
                            possibleMoves.emplace_back(Calculation(extendedPoint, 100 * calculateTigerScore(newBoard), tiger));
                        }
                    }
                }
            }

            point = pointMaker(tiger.location.row, tiger.location.col - 1);
            //cout << endl << "point - " << point.row << point.col << endl;
            //cout << "Point 4" << endl;
            if(isValidMove(tiger.location, point)){
                bool notInVector = true;
                for(unsigned int j = 0; j < tokens.size(); j++){
                    if(tokens.at(j).location.row == point.row && tokens.at(j).location.col == point.col){
                        notInVector = false;
                    }
                }
                if(notInVector){
                    //cout << "notInVector" << endl;
                    vector<Token_t> newBoard(tokens);
                    newBoard[i] = tokenMaker(RED, point);
                    possibleMoves.emplace_back(Calculation(point, calculateTigerScore(newBoard), tiger));
                } else {
                    Point_t extendedPoint = pointMaker(tiger.location.row, tiger.location.col - 2);
                    if(isValidMove(point, extendedPoint)){
                        bool innerNotInVector = true;
                        for(unsigned int j = 0; j < tokens.size(); j++){
                            if(tokens.at(j).location.row == extendedPoint.row && tokens.at(j).location.col == extendedPoint.col){
                                innerNotInVector = false;
                            }
                        }
                        if(innerNotInVector){
                            vector<Token_t> newBoard(tokens);
                            newBoard[i] = tokenMaker(RED, extendedPoint);
                            possibleMoves.emplace_back(Calculation(extendedPoint, 100 * calculateTigerScore(newBoard), tiger));
                        }
                    }
                }
            }

            point = pointMaker(tiger.location.row, tiger.location.col + 1);
            //cout << endl << "point - " << point.row << point.col << endl;
            //cout << "Point 5" << endl;
            if(isValidMove(tiger.location, point)){
                bool notInVector = true;
                for(unsigned int j = 0; j < tokens.size(); j++){
                    if(tokens.at(j).location.row == point.row && tokens.at(j).location.col == point.col){
                        notInVector = false;
                    }
                }
                if(notInVector){
                    //cout << "notInVector" << endl;
                    vector<Token_t> newBoard(tokens);
                    newBoard[i] = tokenMaker(RED, point);
                    possibleMoves.emplace_back(Calculation(point, calculateTigerScore(newBoard), tiger));
                } else {
                    Point_t extendedPoint = pointMaker(tiger.location.row, tiger.location.col + 2);
                    if(isValidMove(point, extendedPoint)){
                        bool innerNotInVector = true;
                        for(unsigned int j = 0; j < tokens.size(); j++){
                            if(tokens.at(j).location.row == extendedPoint.row && tokens.at(j).location.col == extendedPoint.col){
                                innerNotInVector = false;
                            }
                        }
                        if(innerNotInVector){
                            vector<Token_t> newBoard(tokens);
                            newBoard[i] = tokenMaker(RED, extendedPoint);
                            possibleMoves.emplace_back(Calculation(extendedPoint, 100 * calculateTigerScore(newBoard), tiger));
                        }
                    }
                }
            }

            point = pointMaker(tiger.location.row + 1, tiger.location.col - 1);
            //cout << endl << "point - " << point.row << point.col << endl;
            //cout << "Point 6" << endl;
            if(isValidMove(tiger.location, point)){
                bool notInVector = true;
                for(unsigned int j = 0; j < tokens.size(); j++){
                    if(tokens.at(j).location.row == point.row && tokens.at(j).location.col == point.col){
                        notInVector = false;
                    }
                }
                if(notInVector){
                    //cout << "notInVector" << endl;
                    vector<Token_t> newBoard(tokens);
                    newBoard[i] = tokenMaker(RED, point);
                    possibleMoves.emplace_back(Calculation(point, calculateTigerScore(newBoard), tiger));
                } else {
                    Point_t extendedPoint = pointMaker(tiger.location.row + 2, tiger.location.col - 2);
                    if(isValidMove(point, extendedPoint)){
                        bool innerNotInVector = true;
                        for(unsigned int j = 0; j < tokens.size(); j++){
                            if(tokens.at(j).location.row == extendedPoint.row && tokens.at(j).location.col == extendedPoint.col){
                                innerNotInVector = false;
                            }
                        }
                        if(innerNotInVector){
                            vector<Token_t> newBoard(tokens);
                            newBoard[i] = tokenMaker(RED, extendedPoint);
                            possibleMoves.emplace_back(Calculation(extendedPoint, 100 * calculateTigerScore(newBoard), tiger));
                        }
                    }
                }
            }

            point = pointMaker(tiger.location.row + 1, tiger.location.col);
            //cout << endl << "point - " << point.row << point.col << endl;
            //cout << "Point 7" << endl;
            if(isValidMove(tiger.location, point)){
                bool notInVector = true;
                for(unsigned int j = 0; j < tokens.size(); j++){
                    if(tokens.at(j).location.row == point.row && tokens.at(j).location.col == point.col){
                        notInVector = false;
                    }
                }
                if(notInVector){
                    //cout << "notInVector" << endl;
                    vector<Token_t> newBoard(tokens);
                    newBoard[i] = tokenMaker(RED, point);
                    possibleMoves.emplace_back(Calculation(point, calculateTigerScore(newBoard), tiger));
                } else {
                    Point_t extendedPoint = pointMaker(tiger.location.row + 2, tiger.location.col);
                    if(isValidMove(point, extendedPoint)){
                        bool innerNotInVector = true;
                        for(unsigned int j = 0; j < tokens.size(); j++){
                            if(tokens.at(j).location.row == extendedPoint.row && tokens.at(j).location.col == extendedPoint.col){
                                innerNotInVector = false;
                            }
                        }
                        if(innerNotInVector){
                            vector<Token_t> newBoard(tokens);
                            newBoard[i] = tokenMaker(RED, extendedPoint);
                            possibleMoves.emplace_back(Calculation(extendedPoint, 100 * calculateTigerScore(newBoard), tiger));
                        }
                    }
                }
            }

            point = pointMaker(tiger.location.row + 1, tiger.location.col + 1);
            //cout << endl << "point - " << point.row << point.col << endl;
            //cout << "Point 8" << endl;
            if(isValidMove(tiger.location, point)){
                bool notInVector = true;
                for(unsigned int j = 0; j < tokens.size(); j++){
                    if(tokens.at(j).location.row == point.row && tokens.at(j).location.col == point.col){
                        notInVector = false;
                    }
                }
                if(notInVector){
                    //cout << "notInVector" << endl;
                    vector<Token_t> newBoard(tokens);
                    newBoard[i] = tokenMaker(RED, point);
                    possibleMoves.emplace_back(Calculation(point, calculateTigerScore(newBoard), tiger));
                } else {
                    Point_t extendedPoint = pointMaker(tiger.location.row + 2, tiger.location.col + 2);
                    if(isValidMove(point, extendedPoint)){
                        bool innerNotInVector = true;
                        for(unsigned int j = 0; j < tokens.size(); j++){
                            if(tokens.at(j).location.row == extendedPoint.row && tokens.at(j).location.col == extendedPoint.col){
                                innerNotInVector = false;
                            }
                        }
                        if(innerNotInVector){
                            vector<Token_t> newBoard(tokens);
                            newBoard[i] = tokenMaker(RED, extendedPoint);
                            possibleMoves.emplace_back(Calculation(extendedPoint, 100 * calculateTigerScore(newBoard), tiger));
                        }
                    }
                }
            }
        }
        //cout << "Done calculating points" << endl;
    }

    //cout << "About to calculate maxMove" << endl;
    //cout << possibleMoves.size() << endl;
    Calculation maxMove = possibleMoves.at(0);
    for(unsigned int i = 0; i < possibleMoves.size(); i++){
        if(possibleMoves.at(i).value > maxMove.value)
            maxMove = possibleMoves.at(i);
    }
    Move_t toReturn;
    toReturn.token = maxMove.token;
    toReturn.destination = maxMove.destination;
    return toReturn;
}

Move_t Move_Men(vector<Token_t> tokens) {
    vector<Calculation> possibleMoves;

    Token_t tiger;
    for (unsigned int i = 0; i < tokens.size(); i++) {
        Token_t currentToken = tokens.at(i);
        if (currentToken.color == RED) {
            tiger = currentToken;
        }
    }
    for (unsigned int i = 0; i < tokens.size(); i++) {
        Token_t currentToken = tokens.at(i);
        if (currentToken.color == BLUE) {

            double dangerMultiplier = 1.0;
            bool noBackup = true;
            if (distance(currentToken.location, tiger.location) <= 1) {

                if (currentToken.location.row == tiger.location.row) {
                    for (int j = 0; j < tokens.size(); j++) {
                        if (tokens.at(i).location.row == currentToken.location.row &&
                            distance(currentToken.location, tokens.at(i).location) <= 1) {
                            noBackup = false;
                        }
                    }
                }

                if (currentToken.location.col == tiger.location.col) {
                    for (int j = 0; j < tokens.size(); j++) {
                        if (tokens.at(i).location.col == currentToken.location.col &&
                            distance(currentToken.location, tokens.at(i).location) <= 1) {
                            noBackup = false;
                        }
                    }
                }

                if (noBackup)
                    dangerMultiplier *= 0.001;
            }

            Point_t point = pointMaker(currentToken.location.row - 1, currentToken.location.col - 1);
            if (isValidMove(currentToken.location, point)) {
                bool notInVector = true;
                for (unsigned int j = 0; j < tokens.size(); j++) {
                    if (tokens.at(j).location.row == point.row && tokens.at(j).location.col == point.col) {
                        notInVector = false;
                    }
                }
                if (notInVector) {
                    vector<Token_t> newBoard(tokens);
                    newBoard[i] = tokenMaker(BLUE, point);
                    possibleMoves.emplace_back(
                            Calculation(point, dangerMultiplier * calculateDanger(newBoard, point), currentToken));
                }
            }

            Point_t point2 = pointMaker(currentToken.location.row - 1, currentToken.location.col);
            if (isValidMove(currentToken.location, point2)) {
                bool notInVector = true;
                for (unsigned int j = 0; j < tokens.size(); j++) {
                    if (tokens.at(j).location.row == point2.row && tokens.at(j).location.col == point2.col) {
                        notInVector = false;
                    }
                }
                if (notInVector) {
                    vector<Token_t> newBoard(tokens);
                    newBoard[i] = tokenMaker(BLUE, point2);
                    possibleMoves.emplace_back(
                            Calculation(point2, dangerMultiplier * calculateDanger(newBoard, point2), currentToken));
                }
            }

            Point_t point3 = pointMaker(currentToken.location.row - 1, currentToken.location.col + 1);
            if (isValidMove(currentToken.location, point3)) {
                bool notInVector = true;
                for (unsigned int j = 0; j < tokens.size(); j++) {
                    if (tokens.at(j).location.row == point3.row && tokens.at(j).location.col == point3.col) {
                        notInVector = false;
                    }
                }
                if (notInVector) {
                    vector<Token_t> newBoard(tokens);
                    newBoard[i] = tokenMaker(BLUE, point3);
                    possibleMoves.emplace_back(
                            Calculation(point3, dangerMultiplier * calculateDanger(newBoard, point3), currentToken));
                }
            }

            Point_t point4 = pointMaker(currentToken.location.row, currentToken.location.col - 1);
            if (isValidMove(currentToken.location, point4)) {
                bool notInVector = true;
                for (unsigned int j = 0; j < tokens.size(); j++) {
                    if (tokens.at(j).location.row == point4.row && tokens.at(j).location.col == point4.col) {
                        notInVector = false;
                    }
                }
                if (notInVector) {
                    vector<Token_t> newBoard(tokens);
                    newBoard[i] = tokenMaker(BLUE, point4);
                    possibleMoves.emplace_back(
                            Calculation(point4, dangerMultiplier * calculateDanger(newBoard, point4), currentToken));
                }
            }

            Point_t point5 = pointMaker(currentToken.location.row, currentToken.location.col + 1);
            if (isValidMove(currentToken.location, point5)) {
                bool notInVector = true;
                for (unsigned int j = 0; j < tokens.size(); j++) {
                    if (tokens.at(j).location.row == point5.row && tokens.at(j).location.col == point5.col) {
                        notInVector = false;
                    }
                }
                if (notInVector) {
                    vector<Token_t> newBoard(tokens);
                    newBoard[i] = tokenMaker(BLUE, point5);
                    possibleMoves.emplace_back(
                            Calculation(point5, dangerMultiplier * calculateDanger(newBoard, point5), currentToken));
                }
            }

            Point_t point6 = pointMaker(currentToken.location.row + 1, currentToken.location.col - 1);
            if (isValidMove(currentToken.location, point6)) {
                bool notInVector = true;
                for (unsigned int j = 0; j < tokens.size(); j++) {
                    if (tokens.at(j).location.row == point6.row && tokens.at(j).location.col == point6.col) {
                        notInVector = false;
                    }
                }
                if (notInVector) {
                    vector<Token_t> newBoard(tokens);
                    newBoard[i] = tokenMaker(BLUE, point6);
                    possibleMoves.emplace_back(
                            Calculation(point6, dangerMultiplier * calculateDanger(newBoard, point6), currentToken));
                }
            }

            Point_t point7 = pointMaker(currentToken.location.row + 1, currentToken.location.col);
            if (isValidMove(currentToken.location, point7)) {
                bool notInVector = true;
                for (unsigned int j = 0; j < tokens.size(); j++) {
                    if (tokens.at(j).location.row == point7.row && tokens.at(j).location.col == point7.col) {
                        notInVector = false;
                    }
                }
                if (notInVector) {
                    vector<Token_t> newBoard(tokens);
                    newBoard[i] = tokenMaker(BLUE, point7);
                    possibleMoves.emplace_back(
                            Calculation(point7, dangerMultiplier * calculateDanger(newBoard, point7), currentToken));
                }
            }

            Point_t point8 = pointMaker(currentToken.location.row + 1, currentToken.location.col + 1);
            if (isValidMove(currentToken.location, point8)) {
                bool notInVector = true;
                for (unsigned int j = 0; j < tokens.size(); j++) {
                    if (tokens.at(j).location.row == point8.row && tokens.at(j).location.col == point8.col) {
                        notInVector = false;
                    }
                }
                if (notInVector) {
                    vector<Token_t> newBoard(tokens);
                    newBoard[i] = tokenMaker(BLUE, point8);
                    possibleMoves.emplace_back(
                            Calculation(point8, dangerMultiplier * calculateDanger(newBoard, point8), currentToken));
                }
            }

        }
    }

    Calculation minMove = possibleMoves.at(0);
    for (unsigned int i = 0; i < possibleMoves.size(); i++) {
        if (possibleMoves.at(i).value < minMove.value)
            minMove = possibleMoves.at(i);
    }

    Move_t toReturn;
    toReturn.token = minMove.token;
    toReturn.destination = minMove.destination;
    return toReturn;
}

bool isValidMove(Point_t currentPos, Point_t move) {

    //cout << "isValidMove - " << move.row << " " << move.col << endl;
    static Point_t illegalMoves[] = {pointMaker(0, 0), pointMaker(0, 1), pointMaker(0, 2), pointMaker(0, 3),
                                     pointMaker(0, 5), pointMaker(0, 6), pointMaker(0, 7), pointMaker(0, 8),
                                     pointMaker(1, 0), pointMaker(1, 1), pointMaker(1, 2), pointMaker(1, 6),
                                     pointMaker(1, 7), pointMaker(1, 8),
                                     pointMaker(2, 0), pointMaker(2, 1), pointMaker(2, 7), pointMaker(2, 8),
                                     pointMaker(3, 0), pointMaker(3, 1), pointMaker(3, 2), pointMaker(3, 6),
                                     pointMaker(3, 7), pointMaker(3, 8),
                                        pointMaker(1,4), pointMaker(2,3), pointMaker(2,5), pointMaker(3,4)};

    if (move.col < 0 || move.col > 8 || move.row < 0 || move.row > 12) {
        return false;
    }

    //cout << "Passed Bounds check" << endl;

    for (int i = 0; i < 28; i++) {
        if (illegalMoves[i].row == move.row && illegalMoves[i].col == move.col)
            return false;
    }

    //cout << "Not in the illegalMoves" << endl;

    bool isValid = true;

    if (isDiagonalMove(currentPos, move)) {
        //cout << "Is Diagonal Move" << endl;
        isValid = false;
        switch (currentPos.row) {
            case 0:
                if (currentPos.col == 4)
                    isValid = (move.row == 1 && move.col == 3) ||
                              (move.row == 1 && move.col == 5);
                break;
            case 1:
                if (currentPos.col == 3) {
                    // I don't think (1, 4) is a plot point on the board
                    isValid = (move.row == 0 && move.col == 4) ||
                              (move.row == 2 && move.col == 2) ||
                              (move.row == 2 && move.col == 4);
                }

                if (currentPos.col == 5) {
                    // I don't think (1, 4) is a plot point on the board
                    isValid = (move.row == 0 && move.col == 4) ||
                              (move.row == 2 && move.col == 4) ||
                              (move.row == 2 && move.col == 6);
                }
                break;
            case 2:
                if (currentPos.col == 2) {
                    isValid = (move.row == 1 && move.col == 3) ||
                              (move.row == 3 && move.col == 3);
                }

                if (currentPos.col == 4) {
                    // I don't think (1, 4) is a plot point on the board
                    isValid = (move.row == 1 && move.col == 3) ||
                              (move.row == 1 && move.col == 4) ||
                              (move.row == 3 && move.col == 3) ||
                              (move.row == 3 && move.col == 4);
                }

                if (currentPos.col == 6) {
                    isValid = (move.row == 1 && move.col == 5) ||
                              (move.row == 3 && move.col == 5);
                }
                break;
            case 3:
                if (currentPos.col == 3) {
                    isValid = (move.row == 2 && move.col == 2) ||
                              (move.row == 2 && move.col == 4) ||
                              (move.row == 4 && move.col == 4);
                }

                if (currentPos.col == 5) {
                    isValid = (move.row == 2 && move.col == 4) ||
                              (move.row == 2 && move.col == 6) ||
                              (move.row == 4 && move.col == 4);
                }
                break;
            case 4:
                if (currentPos.col == 4) {
                    isValid = (move.row == 3 && move.col == 3) ||
                              (move.row == 3 && move.col == 5) ||
                              (move.row == 5 && move.col == 3) ||
                              (move.row == 5 && move.col == 5);
                }
                break;
            case 5:
                if (currentPos.col == 3) {
                    isValid = (move.row == 6 && move.col == 2) ||
                              (move.row == 4 && move.col == 4);
                }

                if (currentPos.col == 5) {
                    isValid = (move.row == 6 && move.col == 6) ||
                              (move.row == 4 && move.col == 4);
                }
                break;
            case 6:
                if (currentPos.col == 2) {
                    isValid = (move.row == 7 && move.col == 1) ||
                              (move.row == 5 && move.col == 3);
                }

                if (currentPos.col == 6) {
                    isValid = (move.row == 7 && move.col == 7) ||
                              (move.row == 5 && move.col == 5);
                }
                break;
            case 7:
                if (currentPos.col == 1) {
                    isValid = (move.row == 8 && move.col == 0) ||
                              (move.row == 6 && move.col == 2);
                }

                if (currentPos.col == 7) {
                    isValid = (move.row == 8 && move.col == 8) ||
                              (move.row == 6 && move.col == 6);
                }
                break;
            case 8:
                if (currentPos.col == 0) {
                    isValid = (move.row == 9 && move.col == 1) ||
                              (move.row == 7 && move.col == 1);
                }
                if (currentPos.col == 7) {
                    isValid = (move.row == 8 && move.col == 8) ||
                              (move.row == 10 && move.col == 6);
                }
                break;
            case 10:
                if (currentPos.col == 2) {
                    isValid = (move.row == 11 && move.col == 3) ||
                              (move.row == 9 && move.col == 1);
                }

                if (currentPos.col == 6) {
                    isValid = (move.row == 9 && move.col == 7) ||
                              (move.row == 11 && move.col == 5);
                }
                break;
            case 11:
                if (currentPos.col == 3) {
                    isValid = (move.row == 10 && move.col == 2) ||
                              (move.row == 12 && move.col == 4);
                }

                if (currentPos.col == 5) {
                    isValid = (move.row == 10 && move.col == 6) ||
                              (move.row == 12 && move.col == 4);
                }
                break;
            case 12:
                if (currentPos.col == 4) {
                    isValid = (move.row == 11 && move.col == 3) ||
                              (move.row == 11 && move.col == 4);
                }
                break;
            default:
                break;
        }
    }

    return isValid;
}

bool isDiagonalMove(Point_t p1, Point_t p2){
    return abs(p1.row - p2.row) == abs(p1.col - p2.col);
}

double distance(Point_t p1, Point_t p2){
    return sqrt(pow(p1.row - p2.row, 2) + pow(p1.col - p2.col, 2));
}

double calculateDanger(vector<Token_t> tokens, Point_t calculatingPoint) {
    double calculatedDanger = 1;
    Token_t tiger;
    unsigned int tigerIndex = 0, CPIndex = 0;
    for (unsigned int i = 0; i < tokens.size(); i++) {
        if (tokens.at(i).color == RED) {
            tiger = tokens.at(i);
            // You never set the tiger index
            tigerIndex = i;
        } else if (tokens.at(i).location.row == calculatingPoint.row &&
                   tokens.at(i).location.col == calculatingPoint.col)
            CPIndex = i;
    }

    double distanceToTiger = distance(tiger.location, calculatingPoint);
    if (distanceToTiger < 2)
        calculatedDanger *= 1.1;

    if (distanceToTiger > 3)
        calculatedDanger *= 0.7;

    if (calculatingPoint.row > 8) {
        calculatedDanger *= 1.2;
    }

    int numWithinSafety = 0;
    for (unsigned int i = 0; i < tokens.size(); i++) {
        if (i != tigerIndex && i != CPIndex) {
            if (distance(tokens.at(i).location, calculatingPoint) < 3) {
                calculatedDanger *= .91;
                numWithinSafety++;
            }
        }
    }

    calculatedDanger *= (1 - static_cast<double>(numWithinSafety) / 100);
    if (calculatingPoint.row == tiger.location.row) {
        bool hasBackup = false;
        for (unsigned int i = 0; i < tokens.size(); i++) {
            if (i != CPIndex && tokens.at(i).location.row == calculatingPoint.row) {
                if (distance(tokens.at(i).location, calculatingPoint) < 1) {
                    calculatedDanger *= 0.85;
                    hasBackup = true;
                }
            }
        }
        if (!hasBackup)
            calculatedDanger *= 1.3;
    }

    if (calculatingPoint.col == tiger.location.col) {
        bool hasBackup = false;
        for (unsigned int i = 0; i < tokens.size(); i++) {
            if (i != CPIndex && tokens.at(i).location.col == calculatingPoint.col) {
                if (distance(tokens.at(i).location, calculatingPoint) < 1) {
                    calculatedDanger *= 0.85;
                    hasBackup = true;
                }
            }
        }
        if (!hasBackup)
            calculatedDanger *= 1.3;
    }

    GameRecord gr;
    int primaryDirection = getPrimaryDirection();
    switch (primaryDirection) {
        case GameRecord::UP :
            if (calculatingPoint.row > 7) calculatedDanger *= 0.93;
            break;
        case GameRecord::RIGHT :
            if (calculatingPoint.col < 7) calculatedDanger *= 0.93;
            break;
        case GameRecord::DOWN :
            if (calculatingPoint.row < 7) calculatedDanger *= 0.93;
            break;
        case GameRecord::LEFT :
            if (calculatingPoint.col > 7) calculatedDanger *= 0.93;
            break;
        default :
            calculatedDanger *= 1;
            break;
    }

    return calculatedDanger;
}

double calculateTigerScore(vector<Token_t> tokens){

    double calculatedScore = 1;
    Token_t tiger;
    unsigned int tigerIndex = 0;
    for(unsigned int i = 0; i < tokens.size(); i++){
        if(tokens.at(i).color == RED) {
            tiger = tokens.at(i);
            tigerIndex = i;
        }
    }

    unsigned int numWithinBoundary = 0;
    for(unsigned int i = 0; i < tokens.size(); i++){
        if(i != tigerIndex){
            if(distance(tokens.at(i).location, tiger.location)  <= 2){
                calculatedScore *= 1.2;
                numWithinBoundary++;
            }
        }
    }

    if(numWithinBoundary > 3)
        calculatedScore *= 0.8;

    if(distance(tiger.location, pointMaker(8,4)) >= 4)
        calculatedScore *= pow((0.99), distance(tiger.location, pointMaker(8,4)));

    for(unsigned int i = 0; i < tokens.size(); i++){
        if(tokens.at(i).color == BLUE)
            if(distance(tiger.location, tokens.at(i).location) >= 4)
                calculatedScore *= ( pow((0.95), distance(tiger.location, pointMaker(8,4))));
    }

    srand(numWithinBoundary);
    calculatedScore *= rand();

    //NEED TO CHECK IF IT'S MOVING INTO CORNERS AND STOP

    return calculatedScore;

}
#endif //TIGER_GAME_TIGER_H
