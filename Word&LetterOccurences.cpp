/*
 * Function: main
 * PURPOSE: TO OUTPUT HOW MANY WORDS ARE IN A FILE AND HOW MANY LETTERS EACH WORD HAS THAT BEGIN WITH A SELECTED CHARACTER
 * Name: Daniel Pellegrino
 * Written: 3/11/2021; Last Modified 3/24/2022
 * Language: C++
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

using namespace std;

int wordCount( ifstream& );
int maxLetter( ifstream&, char );
void countLetter( ifstream&, int[], int, char );

int main( void )
{
    string inputFileName;
    ifstream fileIn;
    int *letters, max, i;
    char letter = 'a';

    cout << "Enter the name of the file of words: ";

    cin >> inputFileName;

    fileIn.open(inputFileName.data());

    assert(fileIn.is_open());

    cout << endl << inputFileName << " - Word Count:" << endl << wordCount( fileIn ) << endl << endl;

    cin.ignore(100,'\n');

    cout << endl << "Please input a single character to get detail about each amount of a letters word count." << endl;
    cout << "If you want to quit please enter @." << endl;

    while (letter!='@') {
        string input = "";

        getline(cin, input);

        if (!input.empty())
            letter = input.at(0);

        if (letter == '@')
            break;

        if (input.size() == 1)
        {
            max = maxLetter( fileIn, letter );

            letters = new (nothrow) int[max + 1];

            if(letters == nullptr){
                cout << "Could not allocate enough memory!" << endl << "Closing file and exiting program...";
            }
            else{
                countLetter( fileIn, letters, max, letter );
                if (max != 0){
                    for(i = 0; i <= max; i++){
                        if (letters[i] != 0){
                            cout << "# of words that have " << i << " letter(s) that begin with " << letter << ": " << letters[i] << " word(s)." << endl;
                        }
                    }
                }
                else {
                    cout << "No words begin with '" << letter << "'!" << endl;
                }
            }
        }

        else {
            cout << std::endl << "Please only enter one character!" << std::endl;
        }
    }

    fileIn.close();

    return 0;
}

int wordCount( ifstream &FILE )
{
    string s;
    int wordCount = 0;

    while (FILE >> s){
        wordCount++;
    }

    FILE.clear();
    FILE.seekg(0);

    return wordCount;
}

int maxLetter( ifstream &FILE, char letter )
{
    string s;
    int i, max = 0;

    while (FILE >> s){
        for(i = 0; i < (int)s.length(); i++){
            if(isupper(s[i])){
                s[i] += 32;
            }

            if(!(s[i] >= 'a' && s[i] <= 'z')){
                s.erase(i, 1);
                i--;
            }
        }

        if(s[0] == letter){
            if((int)s.length() > max){
                max = s.length();
            }
        }
    }

    FILE.clear();
    FILE.seekg(0);

    return max;
}

void countLetter( ifstream &FILE, int letterCount[], int size, char letter )
{
    string s;
    int i;

    for(i = 0; i <= size; i++){
        letterCount[i] = 0;
    }

    while (FILE >> s){
        for(i = 0; i < (int)s.length(); i++){
            if(isupper(s[i])){
                s[i] += 32;
            }

            if(!(s[i] >= 'a' && s[i] <= 'z')){
                s.erase(i, 1);
                i--;
            }
        }

        if(s[0] == letter){
            letterCount[s.length()]++;
        }
    }

    FILE.clear();
    FILE.seekg(0);

    return;
}
