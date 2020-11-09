#include "tictactoestrategy.h"

#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

TicTacToeStrategy::TicTacToeStrategy()
{

}

Vector2 TicTacToeStrategy::choose_move(const std::shared_ptr<TicTacToeBoard> & board, Player opponent)
{
    auto result = minimax(board.get(), true, opponent, 0);

    std::cout << "Chose move (" << result.move.x << ", " << result.move.y << ") with a score of " << result.value << std::endl;

    return result.move;
}

Player get_other_player(Player plr){
    switch (plr) {
        case Player::Circle:
            return Player::Cross;
        case Player::Cross:
            return Player::Circle;
        case Player::Empty:
            return Player::Empty;
    }
}

choice TicTacToeStrategy::minimax(const TicTacToeBoard * board, bool opponents_turn, Player opponent, int depth)
{
    auto winner = board->has_winner();

    if(winner == opponent){
        return choice{board->last_move(), 10 - depth, depth};
    }
    else if(winner == get_other_player(opponent)){
        return choice{board->last_move(), -10 + depth, depth};
    }
    else if(!board->has_space_left()){
        return choice{board->last_move(), 0, depth};
    }

    std::vector<Vector2> candidates(board->legal_moves());
    std::vector<choice> candidate_choices;

    for(auto & i : candidates){
        TicTacToeBoard board_copy(*board);

        board_copy.place_marker(i, opponent);

        auto result = minimax(&board_copy, !opponents_turn, get_other_player(opponent), depth + 1);

        result.move = board_copy.last_move();

        candidate_choices.push_back(result);
    }

    choice best_choice;
    int best_value = -100;
    choice worst_choice;
    int worst_value = 100;

    for(auto & choice : candidate_choices){
        if(opponents_turn && choice.value > best_value){
            best_choice = choice;
            best_value = choice.value;
        }
        else if(!opponents_turn && choice.value < worst_value){
            worst_choice = choice;
            worst_value = choice.value;
        }
    }

    return opponents_turn ? best_choice : worst_choice;
}


choice::choice() : move{0,0}, value(0), depth(0) {}

choice::choice(Vector2 mv, int val, int dep) : move(mv), value(val), depth(dep) {}

choice::choice(const choice &other) : move(other.move), value(other.value), depth(other.depth) {}

choice &choice::operator=(const choice &other)
{
    move = other.move;
    value = other.value;
    depth = other.depth;
    return *this;
}
