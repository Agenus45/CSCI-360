#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

double english [26] = {
    0.0817, 0.0150, 0.0278, 0.0425, 0.1270, 0.0223, 0.0202, 0.0609,
    0.0697, 0.0015, 0.0077, 0.0403, 0.0241, 0.0675, 0.0751, 0.0193, 0.0010, 0.0599, 0.0633,
     0.0906, 0.0276, 0.0098, 0.0236, 0.0015, 0.0197, 0.0007
}; // Array to store the frequency of each letter in the English language

void rankedLetters (double values[], int order[]) {
    bool used[26] = {false}; // Array to keep track of used letters

    for (int rank = 0 ; rank< 26; rank ++){
        int biggestIndex = -1; // -1 means no letter has been found yet

        for (int i = 0; i < 26; i++) {
            if (!used[i] && (biggestIndex == -1 || values[i] > values[biggestIndex])) {
                biggestIndex = i; // new biggest letter
            }
        }
        order[rank] = biggestIndex; // write it down the leetter
        used[biggestIndex] = true; // Mark the letter as used
    }
}

void addGuesses( string &key, string cipherLetters, string plainLetters){

    for (int i=0; i< cipherLetters.length(); i++){
        char cipherLetter = cipherLetters[i];
        char plainLetter = plainLetters[i];

        for (int j=0; j< 26; j++){
            if (key[j] == plainLetter && j != cipherLetter- 'a'){ // Check if the plain letter is already assigned to a different cipher letter
                 cout<< "CONFLICT" << plainLetter << " is already assigned to " << char(j+'a') << endl;

            }
            }
           key[cipherLetter - 'a'] = plainLetter; // Assign the plain letter to the corresponding cipher letter in the key
        }
    }

void printwithkey(string text, string key){
    int lineLength = 0; // Initialize variable to keep track of the current line length
    for (int i=0; i<text.length(); i++){
        char c= text[i];
        if (c >= 'a' && c <= 'z' && key[c-'a'] != '-') { // Check if character is a lowercase letter and has a corresponding substitution in the key
            cout<< key [c-'a']; // Print the substituted letter
        }else{
            cout<< c; // Print the original character if it is not a lowercase letter or has no substitution in the key
        }
        lineLength++; // Increment the line length
        if (c==' '&& lineLength > 60) { // Check if the character is a space and the line length exceeds 60
            cout<< endl; // Print a newline character to start a new line
            lineLength = 0; // Reset the line length
        }
    }
    cout<< endl; // Print a newline character at the end of the text
}




int main(){

    string ciphertext= "lrvmnir bpr sumvbwvr jx bpr lmiwv yjeryrkbi jx qmbm wi bpr xjvni mkd ymibrut jx irhx wi bpr riirkvr jx ymbinlmtmipw utn qmumbr "
     "dj w ipmhh but bj rhnvwdmbr bpr yjeryrkbi jx bpr qmbm mvvjudwko bj yt wkbrusurbmbwjk lmird jk xjubt trmui jx ibndt wb wi kjb mk rmit bmiq bj rashmwk "
    "rmvp yjeryrkb mkd wbi iwokwxwvmkvr mkd ijyr ynib urymwk nkrashmwkrd bj ower m vjyshrbr rashmkmbwjk jkr cjnhd pmer bj lr fnmhwxwrd mkd wkiswurd bj invp "
    "mk rabrkb bpmb pr vjnhd urmvp bpr ibmbr jx rkhwopbrkrd ywkd vmsmlhr jx urvjokwgwko ijnkdhrii ijnkd mkd ipmsrhrii ipmsr w dj kjb drry ytirhx bpr xwkmh mnbpjuwbt lnb yt "
    "rasruwrkvr cwbp qmbm pmi hrxb kj djnlb bpmb bpr xjhhjcwko wi bpr sujsru msshwvmbwjk mkd wkbrusurbmbwjk w jxxru yt bprjuwri wk bpr pjsr bpmb bpr riirkvr jx jqwkmcmk qmumbr cwhh urymwk wkbmvb ";

    int count [26] = {0}; // Initialize array to store frequency of each letter
    int totalLetters = 0; // Initialize variable to store total number of letters   

    for (int i = 0; i < ciphertext.length(); i++) {
        char c = ciphertext[i];
        if (c >= 'a' && c <= 'z') { // Check if character is a lowercase letter
            count[c - 'a']++; // Increment the count for the corresponding letter
            totalLetters++; // Increment the total number of letters
        }
    }


        double relativeFrequency [26]; // Array to store relative frequency of each letter

        for(int i =0 ;i<26; i++)
        {

            relativeFrequency[i] = (double)count[i] / totalLetters; // Calculate relative frequency
        }

            int cipherOrder[26]; // Array to store the order of letters based on frequency
            int englishOrder[26]; // Array to store the order of letters based on English frequency

            rankedLetters( relativeFrequency, cipherOrder); // Rank letters based on ciphertext frequency
            rankedLetters(english, englishOrder); // Rank letters based on English frequency
            
            cout<< " Total letters: " << totalLetters << endl;
            cout<< "Letter Frequency" << endl;
            cout << fixed << setprecision(4);

            for (int rank = 0; rank < 26; rank++) {
                int c = cipherOrder[rank]; // Get the index of the letter in ciphertext order
                int e = englishOrder[rank]; // Get the index of the letter in English order

                char cipherLetter = 'a' + c; // Convert index to corresponding letter
                char englishLetter = 'a' + e; // Convert index to corresponding letter

                cout << setw(4) << rank + 1 << " | " << cipherLetter << " | " << setw(3) << count[c] << " | Relative Frequency: " << relativeFrequency[c] << " | English Letter: " << englishLetter << endl;
            }


string words [300]; // Array to store words from the ciphertext
int wordCount[300]; // Array to store the count of each word
int numWords = 0; // Initialize variable to store the number of words

string currentWord = ""; // Initialize variable to store the current word being processed

for (int i=0; i< ciphertext.length(); i++) {
    char c = ciphertext[i];
    if (c >= 'a' && c <= 'z') { // Check if character is a lowercase letter
        currentWord += c; // Add the letter to the current word
    
    }else if (currentWord!="") { // Check if the current word is not empty

        bool found = false; // hit a space, so the word is finished.
    
    for (int j =0; j<numWords; j++) {
        if (words[j] == currentWord) { // Check if the current word already exists in the array
            wordCount[j]++; // Increment the count for the existing word
            found = true; // Mark the word as found
            break; // Exit the loop since the word is found
        }
    }
    


    if (!found) { // If the word is not found in the array
        words[numWords] = currentWord; // Add the new word to the array
        wordCount[numWords] = 1; // Initialize the count for the new word
        numWords++; // Increment the number of words
    }
    currentWord = ""; // start the next word
    }
}
    cout << endl<< "repeated words: " << endl;
    for (int times= 20; times>=2    ; times--) { // Loop through the word counts in reverse order
        for (int j = 0; j < numWords; j++) { // Loop through the words array
            if (wordCount[j] == times) { // Check if the word count matches the current count
                cout << words[j] << " | Count: " << wordCount[j] << endl; // Print the word and its count
            }
        }
    }
    for(int length = 1; length <= 3 ; length++) { // Loop through word lengths from 1 to 3
        cout << endl << "Words of length " << length << ":" << endl;
        for (int j = 0; j < numWords; j++) { // Loop through the words array
            if (words[j].length() == length) { // Check if the word length matches the current length
                cout << words[j] << " | Count: " << wordCount[j] << endl; // Print the word and its count
            }
     
        }
        cout<< endl;
    }

    cout<< endl<< "words with the double letters: " << endl;
    for (int j = 0; j < numWords; j++) { // Loop through the words array
        for (int k= 0 ; k< words[j] .length()-1; k++) { // Loop through the characters of the word
            if (words[j][k] == words[j][k+1]) { // Check if the current character is the same as the next character
                cout << words[j] << " | Count: " << wordCount[j] << endl; // Print the word and its count
                break; // Exit the loop since a double letter is found
            }
        }

    }
    string key(26, '-');                          // 26 dashes, one per letter a-z

    cout << endl << "====(stage 1)====" << endl;
    addGuesses(key, "bpr", "THE");
    printwithkey(ciphertext, key);

    cout << endl << "====TESTING(REJECTED): k = O ====" << endl;
    string testkey = key;
    addGuesses(testkey, "mk", "AO");
    printwithkey(ciphertext, testkey);

    cout << endl << "====(stage 2)====" << endl;
    addGuesses(key, "mkdw", "ANDI");
    printwithkey(ciphertext, key);

    cout << endl << "====TESTING(REJECTED): w = A ====" << endl;
    testkey = key;
    addGuesses(testkey, "w", "A");

    cout << endl << "====(stage 3)====" << endl;
    addGuesses(key, "jxiv", "OFSC");
    printwithkey(ciphertext, key);

    cout << endl << "====(stage 4)====" << endl;
    addGuesses(key, "uy", "RM");
    printwithkey(ciphertext, key);

    cout << endl << "====(stage 5)====" << endl;
    addGuesses(key, "lnt", "BUY");
    printwithkey(ciphertext, key);

    cout << endl << "====(stage 6)====" << endl;
    addGuesses(key, "shoeqc", "PLGVKW");
    printwithkey(ciphertext, key);

    cout << endl << "====(stage 7)====" << endl;
    addGuesses(key, "fga", "QZX");
    printwithkey(ciphertext, key);

    cout << endl << "====FINAL KEY====" << endl;
    cout << "Cipher: abcdefghijklmnopqrstuvwxyz" << endl;
    cout << "Plain : " << key << endl;



   return 0;
}