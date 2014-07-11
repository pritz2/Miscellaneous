#include "RPS.h"
#define INIT_HISTORY_MAX_SIZE 5

const char* Moves[4] = {"ROCK","PAPER","SCISSORS","QUIT"};
sig_atomic_t sigflag = 0;

/**
 * Signal Handler
 */
void abort_program(int sig) {
    sig++;
    sigflag = 1;
    fclose(stdin);
    return;
}

/**
 * RPS game initializer: all stats originally set to zero
 */
RPS::RPS() : playerScore(0), computerScore(0), totalGames(0)
{
    printf("\n");
    printf("/*************************************/\n");
    printf("/*                                   */\n");
    printf("/* Welcome to ROCK, PAPER, SCISSORS! */\n");
    printf("/*                                   */\n");
    printf("/* When prompted, enter rock, paper, */\n");
    printf("/* or scissors (or just enter r, p,  */\n");
    printf("/* or s). The computer is very       */\n");
    printf("/* intelligent and learns from you,  */\n");
    printf("/* so watch out!                     */\n");
    printf("/* Enter quit for your move at any   */\n");
    printf("/* time to end the game              */\n");
    printf("/*************************************/\n");
}

/**
 * Gets player move, calculates computer move,
 * and determines winner (or tie) and updates statistics
 */
void RPS::play()
{
    // Signal Handler
    signal(SIGINT, abort_program);
    
    bool keepPlaying = true;
    srand(time(NULL));
    
    while(keepPlaying) {
        // Get moves
        Move computerMove = computer.processMove(player.getHistory(),totalGames);
        Move playerMove = player.processMove(totalGames);
        
        if(playerMove == QUIT)
            break;
    
        printf("You played %s\n",Moves[playerMove]);
        printf("Computer played %s\n\n",Moves[computerMove]);
    
        // See who wins
        int compare = compareMove(playerMove, computerMove);
        switch (compare) {
            case 0: // Tie
                printf("Tie!\n\n");
                break;
            case 1: // User wins
                printf("%s beats %s. You won!\n\n",Moves[playerMove],Moves[computerMove]);
                playerScore++;
                break;
            case -1: // Computer wins
                printf("%s beats %s. You lost.\n\n",Moves[computerMove],Moves[playerMove]);
                computerScore++;
                break;
        }
        totalGames++;
        printf("%d Wins  |  %d Ties  |  %d Loses  |  %d Games",playerScore,totalGames-playerScore-computerScore,computerScore,totalGames);
        
        keepPlaying = playAgain();
    }
    printStats();
}

RPS::Player::Player()
{
    MoveHistory = (char*)malloc(INIT_HISTORY_MAX_SIZE*sizeof(char));
    MoveHistory[0] = '\0';
    HistoryMaxSize = INIT_HISTORY_MAX_SIZE;
}

RPS::Player::~Player()
{
    free(MoveHistory);
}

/**
 * Gets the player's move and update the history
 */
RPS::Move RPS::Player::processMove(const int &numMoves)
{
    Move ret = getMove();
    MoveHistory[numMoves] = Moves[ret][0];
    
    if(numMoves >= HistoryMaxSize) {
        HistoryMaxSize = HistoryMaxSize*2;
        MoveHistory = (char*)realloc(MoveHistory,HistoryMaxSize);
    }
    MoveHistory[numMoves+1] = '\0';
    return ret;
}

/**
 * Prompt the player for a move
 */
RPS::Move RPS::Player::getMove() {
    char input[10];
    printf("\nRock, Paper, or Scissors? ");
    std::cin >> input;
    if(sigflag != 0)
        return QUIT;
    switch(input[0]){
        case 'R':
        case 'r':
            return ROCK;
        case 'S':
        case 's':
            return SCISSORS;
        case 'P':
        case 'p':
            return PAPER;
        case 'Q':
        case 'q':
            return QUIT;
        default:
            return getMove();
    }
}

char* RPS::Player::getHistory() {
    return MoveHistory;
}

RPS::Computer::Computer()
{
    // empty
}

/**
 * Gets the computer's move, based on the player's
 * move history
 */
RPS::Move RPS::Computer::processMove(char* history, const int &numMoves)
{
    if(numMoves < 4)
        return decideMove(0,0,0);
    
    int numR  =0;
    int numP  =0;
    int numS  =0;
    char* start= history;
    char* recent = history+numMoves-4;
    
    // Search history for string of 4 previous moves
    while(*history != '\0') {
        if((*history     == recent[0]) &&
           (*(history+1) == recent[1]) &&
           (*(history+2) == recent[2]) &&
           (*(history+3) == recent[3]) ) {
            switch(*(history+4)) {
                case 'R':
                    numR++;
                    break;
                case 'P':
                    numP++;
                    break;
                case 'S':
                    numS++;
                    break;
            }
        }
        history++;
    }
    
    // Search history for string of 3 previous moves
    if((numR || numP || numS) == 0) {
        history = start;
        while(*history != '\0') {
            if((*history     == recent[1]) &&
               (*(history+1) == recent[2]) &&
               (*(history+2) == recent[3]) ) {
                switch(*(history+3)) {
                    case 'R':
                        numR++;
                        break;
                    case 'P':
                        numP++;
                        break;
                    case 'S':
                        numS++;
                        break;
                }
            }
            history++;
        }
    }
    
    // Search history for string of 2 previous moves
    if((numR || numP || numS) == 0) {
        history = start;
        while(*history != '\0') {
            if((*history     == recent[2]) &&
               (*(history+1) == recent[3]) ) {
                switch(*(history+2)) {
                    case 'R':
                        numR++;
                        break;
                    case 'P':
                        numP++;
                        break;
                    case 'S':
                        numS++;
                        break;
                }
            }
            history++;
        }
    }
    
    // Search history for string of previous move
    if((numR || numP || numS) == 0) {
        history = start;
        while(*history != '\0') {
            if(*history==recent[3]) {
                switch(*(history+1)) {
                    case 'R':
                        numR++;
                        break;
                    case 'P':
                        numP++;
                        break;
                    case 'S':
                        numS++;
                        break;
                }
            }
            history++;
        }
    }
    Move ret = decideMove(numR,numS,numP);
    return ret;
}
    
    
RPS::Move RPS::Computer::decideMove(int numR, int numS, int numP){
    double chance;
    if(numR > numP){
        if(numR > numS)
            return PAPER;
        else if(numR < numS)
            return ROCK;
        else {
            chance = rand()%100;
            if(chance>50)
                return PAPER;
            else
                return ROCK;
        }
    }
    else if(numP > numR) {
        if(numP > numS)
            return SCISSORS;
        else if(numP < numS)
            return ROCK;
        else {
            chance = rand()%100;
            if(chance>50)
                return SCISSORS;
            else
                return ROCK;
        }
    }
    else {
        if(numR < numS) {
            return ROCK;
        }
        else if(numR > numS) {
            chance = rand()%100;
            if(chance>50)
                return PAPER;
            else
                return SCISSORS;
        }
        else {
            chance = rand()%100;
            if(chance>66)
                return ROCK;
            else if(chance > 33)
                return PAPER;
            else
                return SCISSORS;
        }
    }
}

/**
 * Move comparer:
 * returns 1 for win, 0 for tie, -1 for loss
 */
int RPS::compareMove(Move move1, Move move2)
{
    if(move1 == move2)
        return 0;
    switch(move1){
        case ROCK:
            return (move2 == SCISSORS ? 1 : -1);
        case PAPER:
            return (move2 == ROCK ? 1 : -1);
        case SCISSORS:
            return (move2 == PAPER ? 1 : -1);
        default:
            return 0;
    }
    return 0;
}

/**
 * Simple play again prompt
 */
bool RPS::playAgain() {
    /*
    printf("Play again? ");
    char answer[10];
    std::cin >> answer;
    if(answer[0] == 'Y' || answer[0] == 'y')
        return true;
    return false;
    */
    return true;
}

/**
 * Prints game end statistics
 */
void RPS::printStats(){
    double winPercent, tiePercent, lossPercent;
    if(totalGames != 0) {
        winPercent = (double)playerScore/(double)totalGames * 100;
        lossPercent = (double)computerScore/(double)totalGames * 100;
        tiePercent = 100-winPercent-lossPercent;
    }
    else
        winPercent = lossPercent = tiePercent = 0;
    printf("\n");
    printf("/*************************************************/\n");
    printf("/* Win  percentage: %.2f%%                       */\n",winPercent);
    printf("/* Tie  percentage: %.2f%%                       */\n",tiePercent);
    printf("/* Loss percentage: %.2f%%                       */\n",lossPercent);
    printf("/*************************************************/\n");
}