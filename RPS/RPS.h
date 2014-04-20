#ifndef RPS_H
#define RPS_H

#include <iostream>
#include <algorithm>
#include <cstdlib>

class RPS
{
public:
    
    // RPS constructor
    RPS();
    
    // Start the game
    void play(double winPercent);
    
private:
    
    enum Move{ ROCK, PAPER, SCISSORS };
    
    /* Player class, complete with
     * constructor and getMove()
     **/
    class Player{
    public:
        // User constructor
        Player();
        
        // getMove
        Move getMove();
        
    private:
        // empty
    };
    
    /* Computer class, complete with
     * constructor and getMove()
     **/
    class Computer{
    public:
        // Computer constructor
        Computer();
        
        // gets a move from the computer,
        // based off the player's move, to keep
        // win rate at 40% (and tie/ loss at 30%)
        Move getMove(Move playerMove, double winPercent);
    private:
        // empty
    };
    
    /* Returns a 1 if moves1 wins,
     * -1 is move1 loses, 0 if tie
     **/
    int compareMove(Move move1, Move move2);
    
    bool playAgain();
    
    void printStats();
    
    Computer computer;
    Player player;
    int playerScore;
    int computerScore;
    int totalGames;
    
};

#endif