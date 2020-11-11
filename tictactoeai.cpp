#include "tictactoeai.h"

#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

TicTacToeAI::TicTacToeAI()
{

}

Vector2 TicTacToeAI::choose_move(const std::shared_ptr<TicTacToeBoard> & board, Square opponent)
{
    auto result = minimax(board.get(), true, opponent, 0);

    //std::cout << "Chose move (" << result.move.x << ", " << result.move.y << ") with a score of " << result.value << std::endl;

    return result.move;
}

Square get_other_player(Square plr){
    switch (plr) {
        case Square::Circle:
            return Square::Cross;
        case Square::Cross:
            return Square::Circle;
        case Square::Empty:
            return Square::Empty;
    }
}

Choice TicTacToeAI::minimax(const TicTacToeBoard * board, bool opponents_turn, Square opponent, int depth)
{
    auto winner = board->has_winner();

    if(winner == opponent){
        return Choice{board->last_move(), 10 - depth, depth};
    }
    else if(winner == get_other_player(opponent)){
        return Choice{board->last_move(), -10 + depth, depth};
    }
    else if(!board->has_space_left()){
        return Choice{board->last_move(), 0, depth};
    }

    std::vector<Vector2> candidates(board->legal_moves());
    std::vector<Choice> candidate_choices;

    for(auto & i : candidates){
        TicTacToeBoard board_copy(*board);

        board_copy.place_marker(i, opponent);

        auto result = minimax(&board_copy, !opponents_turn, get_other_player(opponent), depth + 1);

        result.move = board_copy.last_move();

        candidate_choices.push_back(result);
    }

    Choice best_choice;
    int best_value = -100;
    Choice worst_choice;
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


Choice::Choice() : move{0,0}, value(0), depth(0) {}

Choice::Choice(Vector2 mv, int val, int dep) : move(mv), value(val), depth(dep) {}

Choice::Choice(const Choice &other) : move(other.move), value(other.value), depth(other.depth) {}

Choice &Choice::operator=(const Choice &other)
{
    move = other.move;
    value = other.value;
    depth = other.depth;
    return *this;
}
