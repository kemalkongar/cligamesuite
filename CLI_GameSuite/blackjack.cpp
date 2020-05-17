#include "blackjack.h"

#include <ctype.h>

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>

using namespace std;

Card::Card(Rank pRank, Suit pSuit) : aRank(pRank), aSuit(pSuit) {}
Card::Card(int pRank, int pSuit) : aRank(pRank), aSuit(pSuit) {}

int Card::getValue() {  // Return normal value unless Jack, Queen, or King.

    if (this->aRank == 11 || this->aRank == 12 || this->aRank == 13) {
        return 10;
    }
    return this->aRank;

}  // Low and High Ace will be handled during playtime.

void Card::displayCard() {
    string Rank;
    char Suit;

    if (this->aSuit == 0) {
        Suit = 'C';
    } else if (this->aSuit == 1) {
        Suit = 'D';
    } else if (this->aSuit == 2) {
        Suit = 'H';
    } else if (this->aSuit == 3) {
        Suit = 'S';
    } else {
        cout << "Suit exception during Card creation. Exiting." << endl;
        exit(1);
    }

    if (this->aRank == 11) {
        Rank = 'J';
    } else if (this->aRank == 12) {
        Rank = 'Q';
    } else if (this->aRank == 13) {
        Rank = 'K';
    } else {
        Rank = to_string(this->aRank);
    }

    cout << Rank << Suit << " ";
}

int Card::getRank() {
    return this->aRank;
}

void Hand::add(Card card) {
    this->aHand.push_back(card);
}

void Hand::clear() {
    this->aHand.clear();
}

int Hand::getTotal() {
    int total = 0;
    if (this->aHand.size() == 0) {
        return total;
    }

    for (vector<Card>::iterator it = this->aHand.begin(); it != this->aHand.end(); it++) {
        Card currentCard = *it;
        total += currentCard.getValue();
    }
    return total;
}

void Hand::printHand() {
    if (this->aHand.size() == 0) {
        cout << "This hand holds no cards" << endl;
    } else {
        for (vector<Card>::iterator it = this->aHand.begin(); it != this->aHand.end(); it++) {
            Card currentCard = *it;
            currentCard.displayCard();
        }
    }
    if (this->hasAce() && (this->getTotal() + 10 == 21)) {
        cout << " [" << this->getTotal() + 10 << "] with a High Ace" << endl;
        return;
    }
    cout << "[" << this->getTotal() << "]";
    if (this->hasAce() && (this->getTotal() + 10 < 21)) {
        cout << " [" << this->getTotal() + 10 << "] with a High Ace" << endl;
    } else {
        cout << endl;
    }
}

bool Hand::hasAce() {
    for (vector<Card>::iterator it = this->aHand.begin(); it != this->aHand.end(); it++) {
        Card currentCard = *it;
        if (currentCard.getRank() == 1) {
            return true;
        }
    }
    return false;
}

void Deck::populate() {
    vector<Card> createDeck;

    for (int i = 1; i < 14; i++) {
        for (int j = 0; j < 4; ++j) {
            Card newCard(i, j);
            createDeck.push_back(newCard);
        }
    }

    this->thisDeck = createDeck;
}

void Deck::shuffle() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    auto gen = std::default_random_engine(seed);

    std::shuffle(this->thisDeck.begin(), this->thisDeck.end(), gen);

    // Based on the C++ reference.
}

void Deck::deal(Hand &targetHand) {
    targetHand.add(this->thisDeck.back());
    this->thisDeck.pop_back();
}

void Deck::print() {
    for (vector<Card>::iterator it = this->thisDeck.begin(); it != this->thisDeck.end(); it++) {
        Card currentCard = *it;
        currentCard.displayCard();
    }
}

void Deck::getSize() {
    cout << "Number of cards in this deck: " << this->thisDeck.size() << endl;
}

bool AbstractPlayer::isBusted() {
    if (this->aHand.getTotal() > 21) {
        return true;
    }
    return false;
}

bool HumanPlayer::isDrawing() {
    cout << "Would you like to draw another card? (y/n)" << endl;
    char c;
    cin >> c;
    c = tolower(c);
    if (c == 'y') {
        return true;
    } else if (c == 'n') {
        return false;
    } else {
        cout << "Input not recognized. Assuming 'n'." << endl;
        return false;
    }
}

int HumanPlayer::announce() {
    if (this->isBusted()) {
        return 1;
    }
    int playerLowAce = this->aHand.getTotal();
    int playerHighAce = playerLowAce + 10;

    if (playerLowAce == 21) {
        return 0;
    } else if (this->aHand.hasAce() && playerHighAce == 21) {
        return 0;
    }
    return 99;
}

int HumanPlayer::announce(int casinoTotal) {
    if (this->isBusted()) {
        cout << "Busted! The House wins." << endl;
        return 1;
    }
    if (casinoTotal > 21) {
        cout << "Busted! The Player wins." << endl;
        return 0;
    }
    int playerLowAce = this->aHand.getTotal();
    int playerHighAce = playerLowAce + 10;

    if (playerLowAce == 21) {
        cout << "The Player wins!" << endl;
        return 0;
    } else if (this->aHand.hasAce() && playerHighAce == 21) {
        cout << "The Player wins!" << endl;
        return 0;
    }

    if (this->aHand.hasAce() && playerHighAce < 21) {
        if (playerHighAce > casinoTotal) {
            cout << "The Player wins with the better hand!" << endl;
            return 0;
        } else if (playerHighAce < casinoTotal) {
            cout << "The House wins with the better hand!" << endl;
            return 1;
        } else {
            cout << "The hands are equal. It's a Draw!" << endl;
            return 2;
        }
    }
    if (playerLowAce > casinoTotal) {
        cout << "The Player wins with the better hand!" << endl;
        return 0;
    } else if (playerLowAce < casinoTotal) {
        cout << "The House wins with the better hand!" << endl;
        return 1;
    } else {
        cout << "The hands are equal. It's a Draw!" << endl;
        return 2;
    }
}

bool ComputerPlayer::isDrawing() {
    int cardTotal = this->aHand.getTotal();
    int cardTotalAceHigh = cardTotal;
    if (this->aHand.hasAce()) {
        cardTotalAceHigh += 10;
    }
    if (cardTotalAceHigh < 16) {
        return true;
    }
    if (cardTotal < 16) {
        return true;
    }
    return false;
}

void BlackJackGame::play() {
    m_Deck.populate();
    m_Deck.shuffle();
    m_Casino.aHand.clear();

    HumanPlayer player;

    m_Deck.deal(player.aHand);
    m_Deck.deal(player.aHand);
    m_Deck.deal(m_Casino.aHand);

    cout << "The Player:  ";
    player.aHand.printHand();
    cout << "The House: ";
    m_Casino.aHand.printHand();
    if (player.announce() == 99) {
        while (player.isDrawing()) {
            m_Deck.deal(player.aHand);
            player.aHand.printHand();
            if (player.announce() == 0) {
                cout << "The Player wins!" << endl;
                return;
            }
            if (player.announce() == 1) {
                cout << "The House wins!" << endl;
                return;
            }  // Stated seperately to avoid message repetition.
        }
    }
    while (m_Casino.isDrawing()) {
        cout << "The House is drawing a card." << endl;
        m_Deck.deal(m_Casino.aHand);
        m_Casino.aHand.printHand();
    }
    int casinoTotal = m_Casino.aHand.getTotal();
    if (casinoTotal < 12 && m_Casino.aHand.hasAce()) {
        casinoTotal += 10;
    }
    player.announce(casinoTotal);
}
