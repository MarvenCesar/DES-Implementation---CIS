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
#include <vector>
#include <iomanip>
#include <sstream>
#include <bitset>

using namespace std;
string plaintext;

int IP[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};


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

int PC2[48] = {
    14, 17, 11, 24, 1, 5, 3, 28,
    15, 6, 21, 10, 23, 19, 12, 4,
    26, 8, 16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55, 30, 40,
    51, 45, 33, 48, 44, 49, 39, 56,
    34, 53, 46, 42, 50, 36, 29, 32
};

int shiftsPerRound[16] = {
    1, 1, 2, 2, 2, 2, 2, 2,
    1, 2, 2, 2, 2, 2, 2, 1
};

int E[48] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
};

int P[32] = {
    16, 7, 20, 21,
    29, 12, 28, 17,
    1, 15, 23, 26,
    5, 18, 31, 10,
    2, 8, 24, 14,
    32, 27, 3, 9,
    19, 13, 30, 6,
    22, 11, 4, 25,
};

int FP[64] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};

const int S[8][4][16] = {
    { // S1
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
    },
    { // S2
        {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
        {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
        {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
        {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
    },
    { // S3
        {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
        {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
        {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
        {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
    },
    { // S4
        {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
        {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
        {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
        {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
    },
    { // S5
        {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
        {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
        {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
        {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
    },
    { // S6
        {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
        {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
        {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
        {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
    },
    { // S7
        {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
        {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
        {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
        {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
    },
    { // S8
        {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
        {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
        {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
        {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
    }
};

int inverse_permutation[64]= {
    40,8,48,16,56,24,64,32,
    39,7,47,15,55,23,63,31,
    38,6,46,14,54,22,62,30,
    37,5,45,13,53,21,61,29,
    36,4,44,12,52,20,60,28,
    35,3,43,11,51,19,59,27,
    34,2,42,10,50,18,58,26,
    33,1,41,9,49,17,57,25
    };



bitset<64> initialPermutation(const bitset<64>& block) {
    // Initial Permutation (IP) table is assumed to be defined
    bitset<64> permutedBlock;
    for (int i = 0; i < 64; ++i) {
        permutedBlock[63 - i] = block[64 - IP[i]];
    }
    return permutedBlock;
}

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
// key reduction
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

// Function to pad the plaintext according to PKCS#7
string applyPKCS7Padding(const string& binaryPlaintext, size_t blockSize) {
    size_t byteLength = binaryPlaintext.length() / 8; // Find the byte length
    size_t paddingNeeded = blockSize - (byteLength % blockSize);
    char paddingValue = static_cast<char>(paddingNeeded);
    
    string paddingBinaryString = "";
    for (size_t i = 0; i < paddingNeeded; ++i) {
        bitset<8> paddingBits(paddingValue);
        paddingBinaryString += paddingBits.to_string();
    }
    
    return binaryPlaintext + paddingBinaryString;
}

bitset<28> leftRotate(bitset<28> k, int shifts) {
    bitset<28> temp = k;
    for (int i = 27; i >= 0; --i) {
        int shiftPos = (i - shifts) < 0 ? (28 - shifts + i) : (i - shifts);
        temp[i] = k[shiftPos];
    }
    return temp;
}


vector<bitset<48>> generateKeySchedule(bitset<56> key) {
    vector<bitset<48>> roundKeys(16);
    bitset<28> left, right;
    bitset<48> compressedKey;

    // Splitting the key into two halves
    for (int i = 0; i < 28; ++i) left[i] = key[i + 28];
    for (int i = 0; i < 28; ++i) right[i] = key[i];

    // Generating 16 subkeys
    for (int round = 0; round < 16; ++round) {
        // Left shifts
        left = leftRotate(left, shiftsPerRound[round]);
        right = leftRotate(right, shiftsPerRound[round]);

        // Combining halves and applying PC-2
        for (int i = 0; i < 48; ++i) compressedKey[i] = (PC2[i] <= 28) ? left[PC2[i] - 1] : right[PC2[i] - 29];
        roundKeys[round] = compressedKey;
    }
    
    return roundKeys;
}

vector<bitset<64>> convertStringToBitsetVector(const string& str) {
    vector<bitset<64>> blocks;
    for (size_t i = 0; i < str.length(); i += 64) {
        bitset<64> block;
        string blockStr = str.substr(i, 64);
        for (size_t j = 0; j < blockStr.length(); ++j) {
            block[63 - j] = blockStr[j] == '1' ? 1 : 0;
        }
        blocks.push_back(block);
    }
    return blocks;
}

bitset<48> expand(bitset<32> right) {
    bitset<48> expandedRight;
    for (int i = 0; i < 48; ++i) {
        // The E-table is 1-indexed, and bitset is 0-indexed
        expandedRight[i] = right[E[i] - 1];
    }
    return expandedRight;
}

bitset<32> permute(bitset<32> substituted) {
    bitset<32> permuted;
    for (int i = 0; i < 32; ++i) {
        // The P-table is 1-indexed, and bitset is 0-indexed
        permuted[i] = substituted[P[i] - 1];
    }
    return permuted;
}

bitset<64> combine(bitset<32> left, bitset<32> right) {
    string combinedString = left.to_string() + right.to_string();
    bitset<64> combined(combinedString);
    return combined;
}

bitset<64> finalPermute(bitset<64> combined) {
    bitset<64> finalPermuted;
    for (int i = 0; i < 64; ++i) {
        // The FP table is 1-indexed, and bitset is 0-indexed
        finalPermuted[i] = combined[FP[i] - 1];
    }
    return finalPermuted;
}

bitset<32> substitute(const bitset<48>& expandedRight) {
    bitset<32> output;
    for (int i = 0; i < 8; ++i) {
        // Extract 6 bits for the current segment
        int segment = (expandedRight >> (42 - 6 * i)).to_ulong() & 0x3F;
        
        // Determine row and column for S-box lookup
        int row = ((segment & 0x20) >> 4) | (segment & 0x01);
        int col = (segment >> 1) & 0x0F;
        
        // Lookup the value in the appropriate S-box
        int sBoxValue = S[i][row][col];
        
        // Convert S-box value to 4-bit and add to output
        bitset<4> fourBits(sBoxValue);
        for (int j = 0; j < 4; ++j) {
            output[(i * 4) + 3 - j] = fourBits[j];
        }
    }
    return output;
}

int main() {
    int bits;
    string binaryString, paddedBinaryString;
    
    
    cout <<"Welcome to the Data Encryption Standard Program\n";
    cout <<"Please enter the message you would like to encrypte: ";
    getline(cin, plaintext); // getline allows space in input
    cout <<"Message recieved: " << plaintext<< "\n";
    binaryString = plaintextToBinary(plaintext);
    paddedBinaryString = applyPKCS7Padding(binaryString, 8);
    cout << "Binary representation of text: " << binaryString << "\n ";
    cout << "Padded Binary representation: " << paddedBinaryString << "\n ";    
    vector<bitset<64>> blocks = convertStringToBitsetVector(paddedBinaryString);
    bitset<64>j = generateRandomKey();
    cout << "KEY: " << j;
    bitset<56>k = pc1(j);
    cout << "\nAfter pc-1 KEY: " << k;
    
    
    // Generate the key schedule
    vector<bitset<48>> roundKeys = generateKeySchedule(k);
    
    // Print each of the 16 subkeys
    for (int i = 0; i < 16; i++) {
        cout << "\nRound " << (i + 1) << " key: " << roundKeys[i].to_ulong() << " (binary: " << roundKeys[i] << ")" << endl;
    }
}

    

