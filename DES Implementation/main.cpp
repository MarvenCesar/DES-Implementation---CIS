//
//  main.cpp
//  DES Implementation
//
//  Created by Marven Cesar on 2/24/24.
//

#include <iostream>
#include <string>
#include <bitset>
#include <random>
using namespace std;
string plaintext;

int PC1[56] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
};

bitset<64>generateRandomKey() {
    // functions from <random> library which helps generate truly random bits which are independent
    random_device rd; // random number generator
    mt19937_64 gen(rd()); // seed for 64-bit Mersenne Twister pseudo-random number generator, initialized with a seed obtained from a non-deterministic random number generator
    uniform_int_distribution<uint64_t> dis; // generate random numbers within a specified range, where each number within the range has an equal probability of being chosen.
    bitset<64> key(dis(gen)); // generate random 64 bits
    
    // set parity bits to ensure odd parity for every 7 bits
  for (int i = 0; i < 64; i += 8) {
      bool parity = 0;
      for (int j = i; j < i+7; ++j ) {
   parity ^= key[j]; // XOR to calculate parity
   }
   key[i + 7] = parity; // Set parity bit to achieve odd parity
   }
    
   return key;
   }

bitset<56> pc1(const bitset<64>& key){
    bitset<56> permutedKey;
    for(int i = 0; i < 56; ++i){
        // PC1[i] - 1 because our table is 1-indexed but bitset is 0-indexed
        permutedKey[55 - i] = key[64-PC1[i]];
    }
    return permutedKey;
}

string plaintextToBinary(const string& plaintext){
    string binaryString;
    for(char c : plaintext){
        bitset<8> bits(c);
        binaryString += bits.to_string();
    }
    return binaryString;
    
}

int main() {
    int bits;
    string binaryString;
    cout <<"Welcome to the Data Encryption Standard Program\n";
    cout <<"Please enter the message you would like to encrypte: ";
    getline(cin, plaintext); // getline allows space in input
    cout <<"Message recieved: " << plaintext<< "\n";
    binaryString = plaintextToBinary(plaintext);
    cout << "Binary representation of text: " << binaryString << "\n ";
    bitset<64>j = generateRandomKey();
    cout << "KEY: " << j;
    bitset<56>k = pc1(j);
    cout << "\nAfter pc-1 KEY: " << k;
    

    
};
