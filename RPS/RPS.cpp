#include "RPS.h"

const char* Moves[3] = {"ROCK","PAPER","SCISSORS"};

/* RPS game initializer: all stats originally set to zero
 **/
RPS::RPS() : playerScore(0), computerScore(0), totalGames(0)
{
    player = Player();
    computer = Computer();
}

/* Gets player move, calculates computer move,
 * and determines winner (or tie) and updates statistics
 **/
void RPS::play(double winPercent)
{
    printf("Rock, Paper, Scissors!\n");
    
    // Get moves
    Move playerMove = player.getMove();
    Move computerMove = computer.getMove(playerMove, winPercent);
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
    
    // Play again or quit
    if(playAgain())
        play(winPercent);
    else
        printStats();
}

RPS::Player::Player()
{
    // empty
}

/* Prompts the used for rock, paper, or scissors
 **/
RPS::Move RPS::Player::getMove()
{
    char ret[10];
    printf("\nRock, Paper, or Scissors? ");
    std::cin >> ret;
    switch(ret[0]){
        case 'R':
        case 'r': return ROCK;
        case 'S':
        case 's': return SCISSORS;
        case 'P':
        case 'p': return PAPER;
    }
    // Invalid input, try again
    return getMove();
}

RPS::Computer::Computer()
{
    // empty
}

/* Gets the computer's move, given a percentage of the
 * time the player should win. The percentage of the time
 * the player should lose is evenly split between ties
 * and losses
 **/
RPS::Move RPS::Computer::getMove(Move playerMove, double winPercent)
{
    winPercent = winPercent*100;
    srand(time(NULL));
    double win = rand()%100;
    double tiePercent = winPercent + (100-winPercent)/2.0;
    if(win < winPercent)
        return (Move)((playerMove+2)%3);
    else if (win < tiePercent)
        return playerMove;
    return (Move)((playerMove+1)%3);
}

/* Move comparer:
 * returns 1 for win, 0 for tie, -1 for loss
 **/
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
    }
    return 0;
}

/* Simple play again prompt
 **/
bool RPS::playAgain(){
    printf("Play again? ");
    char answer[10];
    std::cin >> answer;
    if(answer[0] == 'Y' || answer[0] == 'y')
        return true;
    return false;
}

/* Prints game end statistics
 **/
void RPS::printStats(){
    double winPercent = (double)playerScore/(double)totalGames * 100;
    printf("\nYou played %d games, and won %d of them, for a win percentage of %.2f%% \n\n",totalGames,playerScore,winPercent);
}