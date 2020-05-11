#include <iostream>
#include <string>
using namespace std;

class cards {
private:
    string rank;
    string suit;
    //no need for card rank, 1-10, jack(11), queen(12), king(13), ace(14)
public:
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
        cout << rank << " " << suit;
    }
    cards(string r,string s) {
        rank = r;
        suit = s;
    }
};
class deck {
private:
    const int deckSize = 52;
    cards fullDeck[52];
public:
    deck() {
        string ranks[] = { "ace", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "jack", "queen", "king" };
        string suits[] = { "clubs", "spades", "diamonds", "hearts" };

        int cardNum = 0;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 13; j++) {
                fullDeck[cardNum].setSuit(suits[i]);
                fullDeck[cardNum].setRank(ranks[j]);
                cardNum++;
            }
        }
    }
	//copy constructor make none sense
    deck(const deck &obj) {
      
    }
};


int main() {
    cards userCard("yeet", "man");
    cout << "RANK: " << userCard.getRank() << endl;
    userCard.cardOutput();
    userCard.setRank("ten");

    return 0;
}