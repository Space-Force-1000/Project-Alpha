#include "functions.h"

void display_position( thc::ChessRules &cr, const std::string &description )
{
    std::string fen = cr.ForsythPublish();
    std::string s = cr.ToDebugStr();
    printf( "%s\n", description.c_str() );
    printf( "FEN (Forsyth Edwards Notation) = %s\n", fen.c_str() );
    printf( "Position = %s\n", s.c_str() );
}

std::string GetLegalMoves( std::string currentPosition, ChessRules &cr, Move &mv)
{
    bool white = false;
    //check whether it is a white or black square
            for(int j=0; j<32 && !white; j++)
            {
                if (currentPosition == whitesquares_txt[j]) white = true;
            }
    char piece = cr.GetPieceFromSquare(currentPosition);
    printf("\nThis is the piece to be moved: %c\n", piece);
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
            if (mv_txt[0] == currentPosition[0])
            {
                //printf( "%s%s\n", mv_txt.c_str(), suffix );
                s += mv_txt + "\n";
                
            }
        }
        else if (mv_txt[0] == 'B')
        {
            if (white)
            {
                for(int j=0; j<32; j++)
                {
                    if ((std::string(1,mv_txt[1])+mv_txt[2]) == whitesquares_txt[j]) s += mv_txt + "\n";
                }
            }
            else
            {
                for(int j=0; j<32; j++)
                {
                    if ((std::string(1,mv_txt[1])+mv_txt[2]) == blacksquares_txt[j]) s += mv_txt + "\n";
                }
            }
        }
        else if(mv_txt[0] == 'R')
        {
            //condion to follow if a rook is in the current location
            if (mv_txt.length() == 3 || (mv_txt[mv_txt.length() - 1] == '+' && mv_txt.length() == 4)) 
            {
                if (mv_txt[1] == currentPosition [0]) s += mv_txt + "\n";
                else if (mv_txt[2] == currentPosition [1]) s += mv_txt + "\n";
            }
            else if (mv_txt[1]=='x') 
            {
                if (mv_txt[2] == currentPosition [0]) s += mv_txt + "\n";
                else if (mv_txt[3] == currentPosition [1]) s += mv_txt + "\n";
            }
        }
<<<<<<< Updated upstream
        else if (mv_txt[0] == 'N')
        {
            
        }
=======
>>>>>>> Stashed changes
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