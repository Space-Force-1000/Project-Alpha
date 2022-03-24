/*

    Simple demo of THC Chess library

    This is a simple "hello world" exercise to get started with the THC chess library
    Just compile and link with thc.cpp. You only need thc.cpp and thc.h to use the
    THC library (see README.MD for more information)

 */

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "thc.h"
#include "thc.cpp"

void display_position( thc::ChessRules &cr, const std::string &description )
{
    std::string fen = cr.ForsythPublish();
    std::string s = cr.ToDebugStr();
    printf( "%s\n", description.c_str() );
    printf( "FEN (Forsyth Edwards Notation) = %s\n", fen.c_str() );
    printf( "Position = %s\n", s.c_str() );
}

int main()
{
    thc::ChessRules cr;
    display_position( cr, "Initial position" );
    char playMove[5] = "";
    thc::Move mv;
    thc::TERMINAL eval_position;
    thc::TERMINAL eval_f_position;
    bool legalM = false;
    bool legalF;
    std::string description = "Position after 1." + mv.NaturalOut(&cr);
    printf("%s\n\n","This is the start of the test");
    
    while(1)// while not checkmate
    {
        description = "Position after ..." + mv.NaturalOut(&cr);
        display_position( cr, description);
        scanf("%s", playMove);
        mv.TerseIn( &cr, playMove);
        bool legalM = cr.Evaluate( eval_position );
        if(legalM)// move is legal
        {
            cr.PlayMove(mv);
        }
        else{// else if an ilegal move
            printf("%s\n", "Please Enter a valid move");
        }
        legalF = cr.Evaluate( eval_f_position );

        if(eval_f_position == thc::TERMINAL_WCHECKMATE){
            printf("Black wins\n");
            break;
        }
        else if(eval_f_position == thc::TERMINAL_BCHECKMATE){
            printf("White wins\n");
            break;
        }
        else if(eval_f_position == thc::TERMINAL_WSTALEMATE){
            printf("Draw white stalemate\n");
            break;  
        }
        else if(eval_f_position == thc::TERMINAL_BSTALEMATE){
            printf("Draw black stale mate\n");
            break;
        }
    }
}

