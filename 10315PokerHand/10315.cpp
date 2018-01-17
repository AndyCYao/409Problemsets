#include<iostream>
#include<vector>
#include<sstream>
#include<unordered_map>
#include<string>
using namespace std;

unordered_map<char, int> suits = {
    {'C',0},
    {'H',1},
    {'D',2},
    {'S',3}
};

struct card{
    int val;
    int suit;
    card(string _val, char _suit){
        //cout << "reading in " << _val << " and " << _suit << endl;
        if(_val == "J"){
            val = 11;
        }else if(_val == "Q"){
            val = 12;
        }else if(_val == "K") {
            val = 13;
        }else if(_val == "A") {
            val = 14;
        }else{
            val = stoi(_val);
        }
        suit = suits[_suit];
    }
    //used to compare two cards by value
    //https://stackoverflow.com/questions/4892680/sorting-a-vector-of-structs
    bool operator<(const card& c2) const{
        return val < c2.val;
    }
};


struct hand{
    vector<card> cards;    
    //stores hands from strongest to weakest in integer topHand;
    unsigned short int handValue;
    int topNumber; // if both hands have same topHand, then the topNumber will decide
};

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
    int sum = tmp[4].val + tmp[0].val ;
    if(tmp[3].val + tmp[1].val == sum && tmp[2].val == sum/2) {
        hand ->topNumber = tmp[4].val; // the last card is the high card of the straight
        return true;
    }
    hand ->topNumber = tmp[4].val; // the last card is the high card of the straight, define it for high card later on
    return false;
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
            hand -> topNumber = hand->cards[x].val;
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
            hand -> topNumber = hand->cards[x].val;
            return true;
        }
    }
    return false;
}

void checkBestHand(hand* hand){
    /**/
    bool is4Kind    = hasFourKind(hand);
    bool isFlush    = hasFlush(hand);
    bool isTriple   = hasTriples(hand);
    bool isStraight = hasStraight(hand);
    int pairs       = numberOfPairs(hand);
    // from strongest hand to weakest
    if(isStraight && isFlush){
        cout << "straight flush of " << hand->topNumber << endl;
        hand->handValue = (1 << 9);
    }else if(is4Kind){
        cout << "4 kind " << hand->topNumber << endl;
        hand->handValue = (1 << 8);
    }else if(isTriple && pairs == 2){
        cout << "full house " << hand->topNumber << endl;
        hand->handValue = (1 << 7);
    }else if(isFlush){
        cout << "flush" << endl;
        hand->handValue = (1 << 6);
    }else if(isStraight){
        cout << "straight" << hand->topNumber << endl;
        hand->handValue = (1 << 5);
    }else if(isTriple){
        cout << "3Kind" << hand->topNumber << endl;
        hand->handValue = (1 << 4);
    }else if(pairs == 2){
        cout << "2 pairs" << hand->topNumber << endl;
        hand->handValue = (1 << 3);
    }else if(pairs == 1){
        cout << "pair" << hand->topNumber << endl;
        hand->handValue = (1 << 2);
    }else{
        cout << "high card" << hand->topNumber << endl;
        hand->handValue = (1 << 1);
    }
}

int main(){
    freopen("input.txt","r", stdin);
    string str;
    while(getline(cin, str) && str.length() > 0){
    
        stringstream ss(str);
        string substring;
        //read first 5 cards for black
        hand black, white;
        for(int i = 0; i < 5; i++){
            getline(ss, substring, ' ');
            card newCard(substring.substr(0, substring.size()-1), substring.back());
            black.cards.push_back(newCard);
        }
        for(int i = 0; i<5; i++){
            getline(ss, substring, ' ');
            card newCard(substring.substr(0, substring.size()-1), substring.back());
            white.cards.push_back(newCard);            
        }
        cout << "black has ... " ;
        checkBestHand(&black);
        cout << "white has ... " ;
        checkBestHand(&white);
        if(black.handValue > white.handValue){
            printf("Black wins.\n");
        }else if(black.handValue < white.handValue){
            printf("White wins.\n");
        }else if(black.topNumber > white.topNumber){
            printf("Black wins.\n");
        }else{
            printf("White wins.\n");
        }
    }
    return 0;
}