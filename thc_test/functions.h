#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "thc.h"
#include "thc.cpp"

std::string squares_txt[64] = {"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8","a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7","a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6","a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5","a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4", "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3", "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2", "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1"};
std::string whitesquares_txt[32];
std::string blacksquares_txt[32];

//This displays the current chess position as an array in the terminal window
void display_position( thc::ChessRules &cr, const std::string &description );

//This functions gets all the legal moves that a piece can make from a particular position
std::string GetLegalMoves( char piece, ChessRules &cr, Move &mv);