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
#include "functions.cpp"
#include "functions.h"

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
    for (int i=0; i<32; i++){whitesquares_txt[i] = squares_txt[2*i];}
    for (int i=0; i<32; i++){blacksquares_txt[i] = squares_txt[2*i + 1];}
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


