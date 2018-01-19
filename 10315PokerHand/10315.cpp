#include<iostream>
#include<vector>
#include<sstream>
#include<unordered_map>
#include<string>
#include<bitset>
#include<algorithm>
using namespace std;

#ifdef DEBUG // turn on by g++ -std=c++11  -g  10315.cpp -o 10315 -DDEBUG
#define Debug(x) std::cout << x 
#else
#define Debug(x)
#endif

unordered_map<char, int> suits = {
    {'C',0},
    {'H',1},
    {'D',2},
    {'S',3}
};

struct card{
    int val;
    int suit;
    card(char _val, char _suit){
        //cout << "reading in " << _val << " and " << _suit << endl;
        if(_val == 'J'){
            val = 11;
        }else if(_val == 'Q'){
            val = 12;
        }else if(_val == 'K') {
            val = 13;
        }else if(_val == 'A') {
            val = 14;
        }else if(_val == 'T'){
            val = 10;
        }else{
            val = (_val - '0');
        }
        suit = suits[_suit];
    }
    //used to compare two cards by value
    //https://stackoverflow.com/questions/4892680/sorting-a-vector-of-structs
    bool operator<(const card& c2) const{
        return val < c2.val;
    }
};

const int MAXBIT = 40; // size of the bitset.

struct hand{
    vector<card> cards;    
    bitset<MAXBIT> handValue;
 };

void setHighCardBit(hand* hand, int val){
    // this function is used by hasFourKind and hasTriple and has Full House. Because these hands are ranked by their 4s, and 3s respectively
    // at this point, the hand might have bits activate in the pairs range (between 13-25), this function will clear it, and set this instead. 
    for(int i = 13; i<26; i++) hand->handValue.reset(i); 
    hand->handValue.set(val+13); 
}

void clearAllBit(hand* hand, int start, int end){
    for (int i = start; i<end; i++) hand->handValue.reset(i);
}

bool hasFlush(hand* hand){
    int currentSuit = hand -> cards[0].suit;
    for(int x = 0; x < hand -> cards.size(); x++){
        if(currentSuit != hand -> cards[x].suit){
            return false;
        }
    }
    return true;
}

bool hasStraight(hand* hand){
    vector<card> tmp = hand ->cards;
    sort(tmp.begin(), tmp.end());
    for(int i = 1;i<tmp.size();i++){
        if(tmp[i].val - tmp[i-1].val != 1){
            return false;
        }
    }
    //hand ->topNumber = tmp[4].val; // the last card is the high card of the straight, define it for high card later on
    return true;
}

bool hasFourKind(hand* hand){
    int maxDiff = 2;
    unordered_map<int, int> countOfFour;
    for(int x = 0; x < hand -> cards.size(); x++){
        int val = hand -> cards[x].val;
        if(countOfFour[val] == 0){
            maxDiff --;
            if (maxDiff == -1) return false;
        }
        countOfFour[val] ++;
        if(countOfFour[val] == 4){
            clearAllBit(hand, 0, 13); //clear all high card bits
            setHighCardBit(hand, val);
            //hand -> topNumber = hand->cards[x].val;
            return true;
        }
    }
    return false;
}

int numberOfPairs(hand* hand){
    // get number of pairs 
    //unordered_map<int, int> countOfPairs;
    int countOfPairs[15] = {0};
    //int maxDifference = 2;
    int numPairs = 0;
    for(int x = 0; x < hand -> cards.size(); x++){
        int val = hand -> cards[x].val;
        if(countOfPairs[val] == 1){
            hand->handValue.set(val+13); // the pair bits have to increment 
            numPairs ++;
        }
        countOfPairs[val] ++;
    }
    return numPairs;
}

bool hasTriples(hand* hand){
    int maxDiff = 3;
    unordered_map<int, int> countOfTrips;
    for(int x = 0; x < hand -> cards.size(); x++){
        int val = hand -> cards[x].val;
        if(countOfTrips[val] == 0){
            maxDiff --;
            if (maxDiff == -1) return false;
        }        
        countOfTrips[val] ++;
        if(countOfTrips[val] == 3){
            //hand -> topNumber = hand->cards[x].val;
            clearAllBit(hand, 0, 13); //clear all high card bits
            setHighCardBit(hand, val);
            return true;
        }
    }
    return false;
}

void checkBestHand(hand* hand){
    /**/
    bool isFlush    = hasFlush(hand);
    bool isStraight = hasStraight(hand);

    // from strongest hand to weakest
    if(isStraight && isFlush){
        //Debug("straight flush of " << endl);
        hand->handValue.set(MAXBIT-1);
        return;
    }else if(isFlush){
        Debug("flush" << endl);
        clearAllBit(hand, 13, 26); // only using high card rule
        hand->handValue.set(MAXBIT-4);
        return;
    }else if(isStraight){
        Debug("straight" << endl);
        hand->handValue.set(MAXBIT-5);
        return;
    }
    
    // isTriple, is4Kind and numberofPairs set the bits within the function
    // thats why we have to break them out from the earlier three functions. 
    int pairs       = numberOfPairs(hand);  
    bool isTriple   = hasTriples(hand);  
    bool is4Kind    = hasFourKind(hand);
    if(is4Kind){
        Debug("4 kind " << endl);
        hand->handValue.set(MAXBIT-2);
    }else if(isTriple && pairs == 2){
        Debug("full house " << endl);
        clearAllBit(hand, 0, 13); // clear highcard bits, keep the triple bits;
        hand->handValue.set(MAXBIT-3);
    }else if(isTriple){
        Debug("3Kind" << endl);
        hand->handValue.set(MAXBIT-6);
    }else if(pairs == 2){
        Debug("2 pairs" << endl);
        hand->handValue.set(MAXBIT-7);
    }else if(pairs == 1){
        Debug("pair" << endl);
        hand->handValue.set(MAXBIT-8);
    }else{
        Debug("high card" << endl);
        hand->handValue.set(MAXBIT-9);
    }
}

int main(){
    //freopen("input.txt","r", stdin);
    string str;
    while(getline(cin, str) && str.length() > 0){
    
        stringstream ss(str);
        string substring;
        //read first 5 cards for black
        hand black, white;
        for(int i = 0; i < 5; i++){
            getline(ss, substring, ' ');
            card newCard(substring.front(), substring.back());
            black.cards.push_back(newCard);
            black.handValue.set(newCard.val); // activate the bit on the card value 
        }
        for(int i = 0; i<5; i++){   // same for the white hand.
            getline(ss, substring, ' ');
            card newCard(substring.front(), substring.back());
            white.cards.push_back(newCard); 
            white.handValue.set(newCard.val); // activate the bit on the card value           
        }
        Debug("black has ... ");
        checkBestHand(&black);
        Debug("white has ... ");
        checkBestHand(&white);
        unsigned long long blackValue = (long long)(black.handValue.to_ulong());
        unsigned long long whiteValue = (long long)(white.handValue.to_ulong());
        if(blackValue > whiteValue){
            puts("Black wins.");
        }else if(blackValue < whiteValue){
            puts("White wins.");
        }else{
            puts("Tie.");
        }
    }
    return 0;
}