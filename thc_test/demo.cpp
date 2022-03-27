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

std::string GetLegalMoves( char piece, ChessRules &cr, Move &mv)
{
    std::string s = "";
    std::vector<thc::Move> moves;
    std::vector<bool> check;
    std::vector<bool> mate;
    std::vector<bool> stalemate;
    cr.GenLegalMoveList(  moves, check, mate, stalemate );
    unsigned int len = moves.size();
    for( unsigned int i=0; i<len; i++ )
    {
        mv = moves[i];
        std::string mv_txt = mv.NaturalOut(&cr);
        if (piece == 'P')
        {
            if (mv_txt[0] == 'a' || mv_txt[0] == 'b' || mv_txt[0] == 'c' || mv_txt[0] == 'd' || mv_txt[0] == 'e' || mv_txt[0] == 'f' || mv_txt[0] == 'g' || mv_txt[0] == 'h')
            {
                const char *suffix="";
                if( check[i] )
                    suffix = " (note '+' indicates check)";
                else if( mate[i] )
                    suffix = " (note '#' indicates mate)";
                //printf( "%s%s\n", mv_txt.c_str(), suffix );
                s += mv_txt + "\n";
                
            }
        }
        else
        {
            if (mv_txt[0] == piece)
            {
                const char *suffix="";
                if( check[i] )
                    suffix = " (note '+' indicates check)";
                else if( mate[i] )
                    suffix = " (note '#' indicates mate)";
                //printf( "%s%s\n", mv_txt.c_str(), suffix );
                s += mv_txt + "\n";
            }
        }
    }
    printf("%s\n", s.c_str());
    return s;
}

int main()
{
    thc::ChessRules cr;
    display_position( cr, "Initial position" );
    char currentPosition[3];
    char destPosition[3];
    char finalMove[5];
    thc::Move mv;
    thc::TERMINAL eval_position;
    thc::TERMINAL eval_f_position;
    bool legalM = false;
    bool legalF;
    std::string description = "Position after 1." + mv.NaturalOut(&cr);
    printf("%s\n\n","This is the start of the test");
    std::string legalMoves;
    while(1)// while not checkmate
    {
        description = "Position after ..." + mv.NaturalOut(&cr);
        display_position( cr, description);
        scanf("%s", currentPosition);
        char piece = cr.GetPieceFromSquare(currentPosition);
        printf("\nThis is the piece to be moved: %c\n", piece);
        legalMoves = GetLegalMoves( piece, cr, mv);
        scanf("%s", destPosition);
        
        if(legalMoves.find(destPosition)){
            printf("%s\n", "positon is valid");
            finalMove[0] = currentPosition[0];
            finalMove[1] = currentPosition[1];
            finalMove[2] = destPosition[0];
            finalMove[3] = destPosition[1];

            printf("final move is: %s\n",finalMove);

            mv.TerseIn( &cr, finalMove);
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
        else{
            printf("%s\n", "position is invalid");
        }
    }
}


