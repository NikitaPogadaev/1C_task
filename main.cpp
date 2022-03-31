
#include<vector>
#include"game.h"
#include<iostream>




Game::Token::Token(int color, int type = 1, int size = 1) : color_(color), type_(type), size_(size) {}

void Game::Exit(int who) {
    end_ = who;
}

bool Game::IsCorrectUser(int x1, int y1, int x2, int y2) {
    if (x1 < 1 || x1 > 8 || x2 < 1 || x2 > 8 || y1 < 1 || y1 > 8 || y2 < 1 || y2 > 8) {
        return false;
    }
    auto ch1 = deck_.tokens_[x1][y1];
    auto ch2 = deck_.tokens_[x2][y2];
    if (ch1.color_ != first_ || ch2.color_ != -1) {
        return false;
    }

    /*
    auto mid = deck_.tokens_[x1 + 1][y1 + 1];
    auto top = deck_.tokens_[x1 + 2][y1 + 2];
    if (mid.color_ == (first_ ^ 1) && top.color_ == -1) {
        return true;
    }*/

    if (x1 == x2 - 1 && (y1 == y2 - 1 || y1 == y2 + 1)) {
        return true;
    }
    if (x1 == x2 + 1 && (y1 == y2 - 1 || y1 == y2 + 1) && ch1.type_ == 2) {
        return true;
    }
    if (x1 == x2 - 2 && (y1 == y2 - 2 || y1 == y2 + 2)) {
        auto mid = deck_.tokens_[(x1 + x2) / 2][(y1 + y2) / 2];
        if (mid.color_ == (first_ ^ 1)) {
            return true;
        }
    }
    if (x1 == x2 + 2 && (y1 == y2 - 2 || y1 == y2 + 2) && ch1.type_ == 2) {
        auto mid = deck_.tokens_[(x1 + x2) / 2][(y1 + y2) / 2];
        if (mid.color_ == (first_ ^ 1)) {
            return true;
        }
    }


    return false;
}
bool Game::IsCorrectBot(int x1, int y1, int x2, int y2) {
    if (x1 < 1 || x1 > 8 || x2 < 1 || x2 > 8 || y1 < 1 || y1 > 8 || y2 < 1 || y2 > 8) {
        return false;
    }
    auto ch1 = deck_.tokens_[x1][y1];
    auto ch2 = deck_.tokens_[x2][y2];
    if (ch1.color_ != first_ ^ 1 || ch2.color_ != -1) {
        return false;
    }
    if (x1 == x2 + 1 && (y1 == y2 - 1 || y1 == y2 + 1)) {
        return true;
    }
    if (x1 == x2 + 1 && (y1 == y2 - 1 || y1 == y2 + 1) && ch1.type_ == 2) {
        return true;
    }
    if (x1 == x2 + 2 && (y1 == y2 - 2 || y1 == y2 + 2)) {
        auto mid = deck_.tokens_[(x1 + x2) / 2][(y1 + y2) / 2];
        if (mid.color_ == first_) {
            return true;
        }
    }
    if (x1 == x2 - 2 && (y1 == y2 - 2 || y1 == y2 + 2) && ch1.type_ == 2) {
        auto mid = deck_.tokens_[(x1 + x2) / 2][(y1 + y2) / 2];
        if (mid.color_ == first_) {
            return true;
        }
    }
    return false;
}

void Game::Run() {
    std::cout << "Game is run, choose difficulty and color!";
    std::cin >> depth_ >> first_;
    while (!end_) {
        if (first_ == turn_) {
            std::cout << "Your step!";
            YourStep();
        }
        else {
            std::cout << "Bot step!";
            if (!depth_) {
                BotEasyStep();
            }
            else {
                int sum = 0;
                Board& min_deck = deck_;
                for (auto i : deck_.tokens_) {
                    for (auto j : i) {
                        if (j.color_ == first_ ^ 1) {
                            sum -= j.size_;
                        }
                        if (j.color_ == first_) {
                            sum += j.size_;
                        }
                    }
                }
                BotDiffStep(depth_, min_deck, sum);
            }
        }
        turn_ ^= 1;
    }
    std::cout << "Game is ended";
    if (end_ == 1) {
        std::cout << "White win";
    }
    else {
        std::cout << "Black win";
    }
}

void Game::YourStep() {
    while (1) {
        std::cout << "Enter amount of steps and steps";
        int n;
        std::cin >> n;
        if (n < 2) {
            continue;
        }
        Board copy_deck = deck_;
        int st1, st2;
        std::cin >> st1 >> st2;
        int i = 1;
        for (; i <= n; ++i) {
            int x, y;
            std::cin >> x >> y;
            if (!IsCorrectUser(st1, st2, x, y)) {
                deck_ = copy_deck;
                break;
            }
            auto temp = deck_.tokens_[st1][st2];
            deck_.tokens_[st1][st2] = Token(-1, 0);
            deck_.tokens_[(st1 + x) / 2][(st2 + y) / 2] = Token(-1, 0);
            deck_.tokens_[x][y] = temp;
            st1 = x;
            st2 = y;
        }
        if (i < n) {
            continue;
            std::cout << "Wrong step";
        }
        if (IsCorrectUser(st1, st2, st1 + 2, st2 + 2) || IsCorrectUser(st1, st2, st1 + 2, st2 - 2)) {
            std::cout << "Wrong step";
            deck_ = copy_deck;
            continue;
        }
        break;
    }
}

void Game::BotEasyStep() {
    for (int i = 1; i <= 8; ++i) {
        for (int j = 1; j <= 8; ++j) {
            if (deck_.tokens_[i][j].color_ == first_ ^ 1 && (IsCorrectBot(i, j, i - 2, j - 2) || IsCorrectBot(i, j, i - 2, j + 2) || IsCorrectBot(i, j, i + 2, j - 2) || IsCorrectBot(i, j, i + 2, j + 2))) {
                while (IsCorrectBot(i, j, i - 2, j - 2) || IsCorrectBot(i, j, i - 2, j + 2) || IsCorrectBot(i, j, i + 2, j - 2) || IsCorrectBot(i, j, i + 2, j + 2)) {
                    if (IsCorrectBot(i, j, i - 2, j - 2)) {
                        deck_.tokens_[i - 2][j - 2] = deck_.tokens_[i][j];
                        deck_.tokens_[i][j] = Token(-1, 0);
                        deck_.tokens_[i - 1][j - 1] = Token(-1, 0);
                        i = i - 2;
                        j = j - 2;
                    }
                    if (IsCorrectBot(i, j, i - 2, j + 2)) {
                        deck_.tokens_[i - 2][j + 2] = deck_.tokens_[i][j];
                        deck_.tokens_[i][j] = Token(-1, 0);
                        deck_.tokens_[i - 1][j + 1] = Token(-1, 0);
                        i = i - 2;
                        j = j + 2;
                    }
                    if (IsCorrectBot(i, j, i + 2, j - 2)) {
                        deck_.tokens_[i + 2][j - 2] = deck_.tokens_[i][j];
                        deck_.tokens_[i][j] = Token(-1, 0);
                        deck_.tokens_[i + 1][j - 1] = Token(-1, 0);
                        i = i + 2;
                        j = j - 2;
                    }
                    if (IsCorrectBot(i, j, i + 2, j + 2)) {
                        deck_.tokens_[i + 2][j + 2] = deck_.tokens_[i][j];
                        deck_.tokens_[i][j] = Token(-1, 0);
                        deck_.tokens_[i + 1][j + 1] = Token(-1, 0);
                        i = i + 2;
                        j = j + 2;
                    }
                }
                return;
            }
        }
    }

    for (int i = 1; i <= 8; ++i) {
        for (int j = 1; j <= 8; ++j) {
            if (IsCorrectBot(i, j, i - 1, j - 1)) {
                deck_.tokens_[i - 1][j - 1] = deck_.tokens_[i][j];
                deck_.tokens_[i][j] = Token(-1, 0);
                return;
            }
            if (IsCorrectBot(i, j, i - 1, j + 1)) {
                deck_.tokens_[i - 1][j + 1] = deck_.tokens_[i][j];
                deck_.tokens_[i][j] = Token(-1, 0);
                return;
            }
            if (IsCorrectBot(i, j, i + 1, j - 1)) {
                deck_.tokens_[i + 1][j - 1] = deck_.tokens_[i][j];
                deck_.tokens_[i][j] = Token(-1, 0);
                return;
            }
            if (IsCorrectBot(i, j, i + 1, j + 1)) {
                deck_.tokens_[i + 1][j + 1] = deck_.tokens_[i][j];
                deck_.tokens_[i][j] = Token(-1, 0);
                return;
            }
        }
    }

}


void Game::BotDiffStep(int n, Board& min_deck, int& mini) {
    if (n == 0) {
        int sum = 0;
        for (auto i : deck_.tokens_) {
            for (auto j : i) {
                if (j.color_ == first_ ^ 1) {
                    sum -= j.size_;
                }
                if (j.color_ == first_) {
                    sum += j.size_;
                }
            }
        }
        if (sum >= mini) {
            mini = sum;
            min_deck = deck_;
        }
        return;
    }
    for (int i = 1; i <= 8; ++i) {
        for (int j = 1; j <= 8; ++j) {
            if (deck_.tokens_[i][j].color_ == first_ ^ 1 && (IsCorrectBot(i, j, i - 2, j - 2) || IsCorrectBot(i, j, i - 2, j + 2) || IsCorrectBot(i, j, i + 2, j - 2) || IsCorrectBot(i, j, i + 2, j + 2))) {
                while (IsCorrectBot(i, j, i - 2, j - 2) || IsCorrectBot(i, j, i - 2, j + 2) || IsCorrectBot(i, j, i + 2, j - 2) || IsCorrectBot(i, j, i + 2, j + 2)) {
                    if (IsCorrectBot(i, j, i - 2, j - 2)) {
                        deck_.tokens_[i - 2][j - 2] = deck_.tokens_[i][j];
                        deck_.tokens_[i][j] = Token(-1, 0);
                        deck_.tokens_[i - 1][j - 1] = Token(-1, 0);
                        i = i - 2;
                        j = j - 2;
                        BotDiffStep(n - 1, deck_, mini);
                    }
                    if (IsCorrectBot(i, j, i - 2, j + 2)) {
                        deck_.tokens_[i - 2][j + 2] = deck_.tokens_[i][j];
                        deck_.tokens_[i][j] = Token(-1, 0);
                        deck_.tokens_[i - 1][j + 1] = Token(-1, 0);
                        i = i - 2;
                        j = j + 2;
                        BotDiffStep(n - 1, deck_, mini);
                    }
                    if (IsCorrectBot(i, j, i + 2, j - 2)) {
                        deck_.tokens_[i + 2][j - 2] = deck_.tokens_[i][j];
                        deck_.tokens_[i][j] = Token(-1, 0);
                        deck_.tokens_[i + 1][j - 1] = Token(-1, 0);
                        i = i + 2;
                        j = j - 2;
                        BotDiffStep(n - 1, deck_, mini);
                    }
                    if (IsCorrectBot(i, j, i + 2, j + 2)) {
                        deck_.tokens_[i + 2][j + 2] = deck_.tokens_[i][j];
                        deck_.tokens_[i][j] = Token(-1, 0);
                        deck_.tokens_[i + 1][j + 1] = Token(-1, 0);
                        i = i + 2;
                        j = j + 2;
                        BotDiffStep(n - 1, deck_, mini);
                    }
                }
            }
        }
    }

    for (int i = 1; i <= 8; ++i) {
        for (int j = 1; j <= 8; ++j) {
            if (IsCorrectBot(i, j, i - 1, j - 1)) {
                deck_.tokens_[i - 1][j - 1] = deck_.tokens_[i][j];
                deck_.tokens_[i][j] = Token(-1, 0);
                BotDiffStep(n - 1, deck_, mini);
            }
            if (IsCorrectBot(i, j, i - 1, j + 1)) {
                deck_.tokens_[i - 1][j + 1] = deck_.tokens_[i][j];
                deck_.tokens_[i][j] = Token(-1, 0);
                BotDiffStep(n - 1, deck_, mini);
            }
            if (IsCorrectBot(i, j, i + 1, j - 1)) {
                deck_.tokens_[i + 1][j - 1] = deck_.tokens_[i][j];
                deck_.tokens_[i][j] = Token(-1, 0);
                BotDiffStep(n - 1, deck_, mini);
            }
            if (IsCorrectBot(i, j, i + 1, j + 1)) {
                deck_.tokens_[i + 1][j + 1] = deck_.tokens_[i][j];
                deck_.tokens_[i][j] = Token(-1, 0);
                BotDiffStep(n - 1, deck_, mini);
            }
        }
    }
}

int main(){
    Game game;
    game.Run();
    return 0;
}