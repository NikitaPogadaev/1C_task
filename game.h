//
// Created by nicku on 31.03.2022.
//

#include<vector>
#include<algorithm>
#include<iostream>
class Game {
public:
    class Token {
    public:
        int color_;
        int type_;
        int size_;
        Token(int color, int type, int size);
    };
    class Board {
    public:
        std::vector<std::vector<Token>> tokens_{
                {Token(1, 1, 1), Token(1, 1, 1), Token(1, 1, 1), Token(1, 1, 1), Token(1, 1, 1), Token(1, 1, 1), Token(1, 1, 1), Token(1, 1, 1), Token(1, 1, 1), Token(1, 1, 1)},
                {Token(1, 1, 1), Token(1, 1, 1), Token(-1, 0, 1), Token(1, 1, 1), Token(-1, 0, 1), Token(1, 1, 1), Token(-1, 0, 1), Token(1, 1, 1), Token(-1, 0, 1), Token(1, 1, 1)},
                {Token(1, 1, 1), Token(-1, 0, 1), Token(1, 1, 1), Token(-1, 0, 1), Token(1, 1, 1), Token(-1, 0, 1), Token(1, 1, 1), Token(-1, 0, 1), Token(1, 1, 1), Token(1, 1, 1)},
                {Token(1, 1, 1), Token(1, 1, 1), Token(-1, 0, 1), Token(1, 1, 1), Token(-1, 0, 1), Token(1, 1, 1), Token(-1, 0, 1), Token(1, 1, 1), Token(-1, 0, 1), Token(1, 1, 1)},
                {Token(1, 1, 1), Token(-1, 0, 1), Token(-1, 0, 1), Token(-1, 0, 1), Token(-1, 0, 1), Token(-1, 0, 1), Token(-1, 0, 1), Token(-1, 0, 1), Token(-1, 0, 1), Token(1, 1, 1)},
                {Token(1, 1, 1), Token(-1, 0, 1), Token(-1, 0, 1), Token(-1, 0, 1), Token(-1, 0, 1), Token(-1, 0, 1), Token(-1, 0, 1), Token(-1, 0, 1), Token(-1, 0, 1), Token(1, 1, 1)},
                {Token(1, 1, 1), Token(-1, 0, 1), Token(0, 1, 1), Token(-1, 0, 1), Token(0, 1, 1), Token(-1, 0, 1), Token(0, 1, 1), Token(-1, 0, 1), Token(0, 1, 1), Token(1, 1, 1)},
                {Token(1, 1, 1), Token(0, 1, 1), Token(-1, 0, 1), Token(0, 1, 1), Token(-1, 0, 1), Token(0, 1, 1), Token(-1, 0, 1), Token(0, 1, 1), Token(-1, 0, 1), Token(1, 1, 1)},
                {Token(1, 1, 1), Token(-1, 0, 1), Token(0, 1, 1), Token(-1, 0, 1), Token(0, 1, 1), Token(-1, 0, 1), Token(0, 1, 1), Token(-1, 0, 1), Token(0, 1, 1), Token(1, 1, 1)},
                {Token(1, 1, 1), Token(1, 1, 1), Token(1, 1, 1), Token(1, 1, 1), Token(1, 1, 1), Token(1, 1, 1), Token(1, 1, 1), Token(1, 1, 1), Token(1, 1, 1), Token(1, 1, 1)}
        };
    };
    void Run();
    void Exit(int who);
    void YourStep();
    void BotEasyStep();
    void BotDiffStep(int n, Board& min_deck, int& mini);
    bool IsCorrectUser(int x1, int y1, int x2, int y2);
    bool IsCorrectBot(int x1, int y1, int x2, int y2);
private:
    Board deck_;
    int first_{ 0 };
    int turn_{ 0 };
    int end_{ 0 };
    int depth_{ 3 };
};
#ifndef UNTITLED1_GAME_H
#define UNTITLED1_GAME_H

#endif //UNTITLED1_GAME_H
