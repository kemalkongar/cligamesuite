#include <vector>
using namespace std;

class Card {
    int aRank;
    int aSuit;

   public:
    enum Rank { ACE = 1,
                TWO,
                THREE,
                FOUR,
                FIVE,
                SIX,
                SEVEN,
                EIGHT,
                NINE,
                TEN,
                JACK,
                QUEEN,
                KING };
    enum Suit { CLUBS,
                DIAMONDS,
                HEARTS,
                SPADES };

    Card(Rank pRank, Suit pSuit);
    Card(int pRank, int pSuit);
    int getValue();      // Just going to return the getRankValue result. Simpler on the eyes.
    void displayCard();  // going to call getValue for the Rank. Going to determine Suit.
    int getRank();
};

class Hand {
    vector<Card> aHand;
    //Uses default constructor. Cards not initialized.
   public:
    void add(Card card);
    void clear();
    int getTotal();
    void printHand();
    bool hasAce();
};

class Deck {
    vector<Card> thisDeck;

   public:
    //Default vonstructor.
    void populate();
    void shuffle();
    void deal(Hand &targetHand);
    void print();
    void getSize();
};

class AbstractPlayer {
   public:
    Hand aHand;
    virtual bool isDrawing() = 0;
    bool isBusted();
};

class HumanPlayer : public AbstractPlayer {
   public:
    bool isDrawing();
    int announce(); // Checks only for the Player
    int announce(int casinoHand); // Called after Casino is done. Final calculation.
};

class ComputerPlayer : public AbstractPlayer {
   public:
    bool isDrawing();
};

class BlackJackGame {
    Deck m_Deck;
    ComputerPlayer m_Casino;

   public:
    void play();
};