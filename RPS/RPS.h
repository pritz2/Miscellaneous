/**
 * @file RPS.h
 * Artificial Intelligence rock-paper-scissors program
 *
 * @author Lucas Pritz
 * @date Summer 2014
 *
 * Revision history:
 * April 2014    Created basic RPS program.
 * July 2014     Added AI aspect, when computer guess player's next choice
 *                 based off player's move history.
 */

#ifndef RPS_H
#define RPS_H

#include <iostream>
#include <algorithm>
#include <cstdlib>

/**
 * RPS class: encapsulates the game.
 */
class RPS
{
public:
    
    /**
     * Constructs the environment.
     */
    RPS();
    
    /**
     * Plays the game, continually deciding the computer's move
     * and then asking the player for their move until a SIGINT
     * is sent, signaling the end of the game.
     */
    void play();
    
    /**
     * Display statistics upon game end
     */
    void printStats();
    
private:
    
    enum Move{ ROCK, PAPER, SCISSORS, QUIT };
    
    /**
     * Player class.
     **/
    class Player{
    public:
        /**
         * Player constructor
         */
        Player();
        
        /**
         * Player destructor
         */
        ~Player();
        
        /**
         * Gets the player's move, and updates the history appropriately.
         *
         * @param Player's most recent move history
         * @param Player's overall move history
         * @param Number of moves thus far
         * @param Maximum size of the move history dynamic array
         * @return The move selected by the player
         */
        Move processMove(const int &numMoves);
        
        char* getHistory();
        
    private:
        /**
         * Prompts the player for their moves
         *
         * @return The player's selected move
         */
        Move getMove();
        
        char* MoveHistory;     // Player's move history
        size_t HistoryMaxSize; // Maximum size of dynamic move history
                               // until realloc() is needed
    };
    
    /**
     * Computer class.
     **/
    class Computer{
    public:
        /**
         * Computer constructor
         */
        Computer();
        
        /**
         * Gets the computer's move by predicting the player's 
         * move based off a player's move history
         *
         * @param Player's most recent move history
         * @param Player's overall move history
         * @param Number of moves thus far
         * @return The move selected by the computer
         */
        Move processMove(char* history, const int &numMoves);
        
    private:
        /**
         * Decides a move for the computer based off
         * player's tendency to play certain moves
         * in the current situation
         *
         * @param number of times rock was played
         * @param number of times scissors was played
         * @param number of times paper was played
         * @return The move selected by the computer
         */
        Move decideMove(int numR, int numS, int numP);
    };
    
    /**
     * Compares 2 moves to determine the victor
     *
     * @param the first move to be compared
     * @param the second move to be compared
     * @return 1  |  move1 wins
     *         0  |  It's a tie
     *        -1  |  move2 wins
     **/
    int compareMove(Move move1, Move move2);
    
    /**
     * Simple playAgain prompt
     */
    bool playAgain();
    
    Computer computer;     // Computer instance
    Player player;         // Player instance
    int playerScore;       // player score
    int computerScore;     // computer score
    int totalGames;        // total games played
    
};

#endif