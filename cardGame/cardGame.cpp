//written by lucas ritossa
//allows user to manipulate objects inside of the main to output different things
#include <iostream>
#include <string>
#include <time.h>

using namespace std;


class cards {
private:
    string rank;
    string suit;
public:
    //basic input/read write functions
    cards() {
        rank = "Ace";
        suit = "Spades";
    }
    string getRank() {
        return rank;
    }
    void setRank(string a) {
        rank = a;
    }
    string getSuit() {
        return suit;
    }
    void setSuit(string a) {
        suit = a;
    }
    void cardOutput() {
        cout << rank << " " << suit <<endl;
    }
    //constructor
    cards(string r,string s) {
        rank = r;
        suit = s;
    }
};

class deck {
private:
    const int deckSize = 52;
    
public:
    cards fullDeck[52];
    //all card values 
    string ranks[13] = { "ace", "ace", "ace", "ace", "five", "six", "seven", "eight", "nine", "ten", "jack", "queen", "king" };
    string suits[4] = { "clubs", "spades", "diamonds", "hearts" };
    deck() {
        //creates a set of 52 cards, organized by rank and suit
        int cardNum = 0;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 13; j++) {
                fullDeck[cardNum].setSuit(suits[i]);
                fullDeck[cardNum].setRank(ranks[j]);
                cardNum++;
            }
        }
    }
    //mixed entire deck (not tottally mixed as mentioned below), also mixes a set of cards according to the cardIndex paramater, this way all cards are TOTALLY MIXED
    cards mixDeck(int cardIndex) {
        int cardNum = 0;
        int rand1 = 0;
        int rand2 = 0;
        int oldrand1 = 0;
        int oldrand2 = 0;
        /*because of nesting, first random number(suit) is going to generate 13 of the same suit (random rank) cards,
        this can be solved by adding a third nest, then randomizing the whole thing, then outputing the results*/
        for (int i = 0; i < 4; i++) {
            if(i > 0 && rand1 != oldrand1)
                rand1 = rand() % 4;
            else {
                for (int i = 0; i < 100; i++) {
                    if (i < 1 || rand1 != oldrand1)
                        rand1 = rand() % 4;
                    i = 100;
                }
            }
            for (int j = 0; j < 13; j++) {
                if (i < 1 || rand2 != oldrand2)
                    rand2 = rand() % 13;
                else {
                    //this could theoretically pose an error if you somehow were able to get a repeat of a number 100 times in a row
                    for (int i = 0; i < 100; i++) {
                        if (i > 0 && rand1 != oldrand1)
                            rand1 = rand() % 4;
                        i = 100;
                    }
                }
                    fullDeck[cardNum].setSuit(suits[rand1]);
                    fullDeck[cardNum].setRank(ranks[rand2]);
                    //0 if you're looking to mix a hand of cards, not full deck
                    if (cardIndex == 0) {
                        break;
                    }
                cardNum++;
            }
            oldrand1 = rand1;
            oldrand2 = rand2;
        }
        //If card index is 0, only one element is needed, this also results in TRUE randomness, this is because the suit is being re-generated each time
        if (cardIndex == 0) {
            return fullDeck[0];
        }
    }
    //returns top card of the deck
    cards dealCard() {
        return fullDeck[0];
    }
    //returns current deck size (array size)
    int currentSize() {
        int arrSize = (sizeof(fullDeck) / sizeof(*fullDeck));
        return arrSize;
    }
    cards deleteDeck() {
        //class deconstructor?, maybe loop to top of function?
        deck();
    }
    //copy constructor
    deck(const deck& obj) {
    }
};

    class hand {
        //dependencies
    private:
        string suit;
        string rank;
    public:
        cards defaultHand[5];
        deck deckUtility;
        //generates a random start hand
        hand() {
            //sets 5 random cards inside the default hand
            for(int i = 0; i<5; i++)
                defaultHand[i] = deckUtility.mixDeck(0);
        }
        //gets a hard from the deck
        cards dealFrom(int cardIndex) {
            return deckUtility.fullDeck[cardIndex];
        }
        //checks if all suits are the same in a given hand
        bool flushDeck() {
            int totalSame = 0;
            for (int i = 0; i < 5; i++) {
                if (defaultHand[0].getSuit() == defaultHand[i].getSuit()) {
                    totalSame++;
                }
                if (totalSame == 5) {
                    return true;
                }
            }
            return false;
        }
        //checks if four ranks are the same in a given hand
        bool fourKind() {
            int totalSame = 0;
            //nested loop is needed (unless already sorted), pretty heavy, but it works
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++) {
                    //checks first letter (x), to whole string (xyxxx, yxxxx, xxxyx)
                    if (defaultHand[i].getRank() == defaultHand[j].getRank()) {
                        totalSame++;
                    }
                }
                if (totalSame == 4)
                    return true;

                totalSame = 0;
            }
            
            return false;
        }
        //returns highest card value
        cards highCard() {
            int points[5] = { 0, 0, 0, 0, 0 };
            cards returnValue;
            int highestPoint = 0;
            for (int i = 0; i < 5; i++) {
                for (int q = 0; q < 13; q++) {
                    if (defaultHand[i].getRank() == deckUtility.ranks[q]) {
                        points[i] = q;
                    }
                }
            }
            for (int i = 0; i < 5; i++) {
                if (highestPoint < points[i]) {
                    highestPoint = points[i];
                    returnValue = defaultHand[i];
                }
            }
            
            return returnValue;
        }
        //outputs full hand of cards
        void print() {
            for (int i = 0; i < 5; i++) {
                defaultHand[i].cardOutput();
            }
        }
        //copy constructor
        hand(const hand& obj) {
        };
    };
    //main is used for testing out the class objects
int main() {
    srand(time(NULL));

    deck deck1;
    cards userCard("yeet", "man");
    hand hand1;
    cout << "card outputs - \n";
    hand1.print();
    cout << "five suit - \n";
    cout<<hand1.flushDeck()<<endl;
    cout << "four rank - \n";
    cout << hand1.fourKind() << endl;
    //deals a card from the deck, takes a argument to choose index of card
    cout << "user card dealing - \n";
    hand1.dealFrom(1).cardOutput();
    cout << "highest card rank - \n";
    hand1.highCard().cardOutput();

    return 0;
}