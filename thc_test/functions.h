#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "thc.h"
#include "thc.cpp"

//This displays the current chess position as an array in the terminal window
void display_position( thc::ChessRules &cr, const std::string &description );

//This functions gets all the legal moves that a piece can make from a particular position
std::string GetLegalMoves( char piece, ChessRules &cr, Move &mv);