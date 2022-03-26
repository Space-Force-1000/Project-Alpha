#include <stdio.h>
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
    piece = toupper(piece); // Now the function takes both upper and lowercase letters and finds the legal moves for the piece
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
        {if (mv_txt[0] == piece)
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
    return s;
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

    printf( "Are you mad or something\n" );
    std::string LegalMoves = GetLegalMoves('n', cr, mv); 
    printf("%s", LegalMoves.c_str());

    char piece = cr.GetPieceFromSquare("b2");
    printf("%c\n", piece);
}