#include <stdio.h>
#include <string.h>

#define KEY_SIZE 4
#define MAX_PHRASE_SIZE 200

const char ALPHABET[] = {   '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
                            'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
                            'U', 'V', 'W', 'X', 'Y', 'Z', '.', ',', '?', ' '    };
const size_t ALPHABET_SIZE = sizeof(ALPHABET)/sizeof(ALPHABET[0]);    //alphabetSize/alphabetElementSize = S_SIZE
int main(){
    int key[KEY_SIZE];      //The key have KEY_SIZE elements between 0 and 9;
    char strkey[KEY_SIZE];  //To usage, the user input the key as a string. 
    char phrase[MAX_PHRASE_SIZE]; 

    gets(strkey);           //Get the key from the user

    for(int i = 0; i < KEY_SIZE; i++){
        key[i] = strkey[i] - '0';   //To see more about ASCII Table check the following link: https://pt.wikipedia.org/wiki/ASCII
    }

    scanf("%[^\n]s", phrase);
    int phraseSize = strlen(phrase);
    // //ENCRYPTIING
    // int pos = 0;
    // int invalidChar = 1;
    // for(int i = 0; i < phraseSize; i++){
    //     pos = 0;
    //     invalidChar = 1;

    //     for( int j = 0; j < ALPHABET_SIZE; j++){
    //         if(phrase[i] == ALPHABET[j]){
    //             pos = j;
    //             invalidChar = 0;
    //             break;
    //         }
    //     }

    //     if (invalidChar == 1) break;
    //     phrase[i] = ALPHABET[(pos + key[i % KEY_SIZE]) % ALPHABET_SIZE];             
    // }
    
    // if (invalidChar == 1) printf("Invalid character in position %i\n", pos);
    // else printf("%s\n", phrase);
    
    //ENCRYPTIING
    char *p = NULL;
    for (int i = 0; i < phraseSize; i++){ 
        p = strchr(ALPHABET, phrase[i]);    /*! *Search for the character in the string and return a pointer
                                                *to the first occurrence of the character.
                                                *If the character is not found, the function returns a null pointer.    */

        if (p == NULL)  break;   //If the character is not in ALPHABET, break the loop

        ptrdiff_t pos = p - ALPHABET;   /*! *Character (numeric) position in the ALPHABET
                                            *The ptrdiff_t is a data type that represents the difference between two pointers,
                                            *that is An unsigned long int with a nicer name.
                                            *p is a pointer that is within the range of the ALPHABET, that is: *ALPHABET[0] <= p <= *S[ALPHABET_SIZE]
                                            *Then p - ALPHABET represents the distance from ALPHABET (the "origin" of the vector) to p  */

        int k = i % KEY_SIZE;   //The key index
        size_t encryptoPos = (pos + key[k]) % ALPHABET_SIZE; //The position of the encrypted character in the ALPHABET
        phrase[i] = ALPHABET[encryptoPos];    // Replace the character in the phrase by the encrypted character
    }
    
    if (p == NULL) printf("Invalid character found");
    else printf("%s\n", phrase);
} 