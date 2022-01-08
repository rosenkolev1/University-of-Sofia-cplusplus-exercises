// Homework 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<cmath>
#include<cstddef>
#include<cstring>
#include<limits>

using namespace std;

//Gets the actual meaningful length of an array of characters
int GetCharArrayLength(char newText[2048])
{
    int counter = 0;
    //Checks if the symbol is contained in the ASCII table(outside of \0). If it is, then the character isn't undefined.
    //The undefined characters in the array have negative values when cast into int, hence they don't belong to the ASCII table)
    while (newText[counter] != '\0' && (int)newText[counter] > 0 && (int)newText[counter] <= 255)
    {
        counter++;
    }
    return counter;
}

//Returns the index at which the contained string starts. Returns -1 if the string isn't found
int ContainsString(char text[2048], int textLength, string stringContained)
{
    int foundStringChar = 0;

    for (int i = 0; i < textLength; i++)
    {
        char textChar = text[i];
        if (textChar == stringContained[foundStringChar])
        {
            foundStringChar++;
        }
        else if (textChar != stringContained[foundStringChar] && foundStringChar > 0)
        {
            foundStringChar = 0;
            i--;
            continue;
        }

        if (foundStringChar == stringContained.length())
        {
            int startIndex = i - foundStringChar + 1;

            //Checks to see if the string is it's own word/phrase
            char preceedingChar = NULL;
            if (startIndex - 1 >= 0) preceedingChar = text[startIndex - 1];

            char succeedingChar = NULL;
            int something = stringContained.length();
            if (startIndex + stringContained.length() < textLength) succeedingChar = text[startIndex + stringContained.length()];

            if (!isalpha(preceedingChar) && !isalpha(succeedingChar)) return startIndex;
            else
            {
                foundStringChar = 0;
            }
        }
    }

    return -1;
}

void ReplaceWithString(char text[2048], int textLength, string replacement, string replacedString, int index)
{
    char newText[2048];

    int startIndex = index;
    int endIndex = index + replacement.length() - 1;

    int differenceInLength = replacement.length() - replacedString.length();

    for (int i = 0; i < index; i++)
    {
        newText[i] = text[i];
    }

    for (int i = index; i < index + replacement.length(); i++)
    {
        newText[i] = replacement[i - index];
    }

    for (int i = index + replacement.length(); i < textLength + differenceInLength; i++)
    {
        newText[i] = text[i - differenceInLength];
    }

    int trueLengthOfText = GetCharArrayLength(text);
    int trueLengthOfNewText = GetCharArrayLength(newText);

    if (differenceInLength <= 0)
    {
        for (int i = 0; i < textLength; i++)
        {
            text[i] = newText[i];
        }
    }
    else if (differenceInLength > 0)
    {
        for (int i = 0; i < textLength + differenceInLength; i++)
        {
            text[i] = newText[i];
        }
    }
}

void SplitByDelimiter(char text[100], char delimiter, string outputArr[2])
{
    outputArr[0] = "";
    outputArr[1] = "";

    int textLength = GetCharArrayLength(text);
    int wordIndex = 0;
    int wordLettersCount = 0;

    for (int i = 0; i < textLength; i++)
    {
        char textChar = text[i];
        if (textChar != delimiter)
        {
            outputArr[wordIndex] += textChar;
            wordLettersCount++;
        }
        if (textChar == delimiter)
        {
            wordIndex++;
            wordLettersCount = 0;
        }
    }
}

void InsertCharAt(char character, char text[2048], int index)
{
    for (int i = 2046; i >= index; i--)
    {
        text[i + 1] = text[i];
    }

    text[index] = character;
}

void OutputCorrectedText(char newText[2048])
{
    int counter = 0;
    while (newText[counter] != '\0' && (int)newText[counter] > 0)
    {
        cout << newText[counter];
        counter++;
    }
}

void CorrectMissingIntervals(char text[2048], int textLength)
{
    int quotesCount = 0;

    //Might need to trim the empty whitespace characters after the text. Can be done by textLength - 1 instead of textLength
    for (int i = 1; i < textLength - 1; i++)
    {
        if (text[i] == '\"')
        {
            quotesCount++;
        }

        //Slagash interval sled ne6toto
        if (text[i] == ',' || text[i] == ';' || text[i] == ')' || text[i] == '-' || text[i] == '.')
        {
            if (text[i + 1] != ' ' && text[i + 1] != '\n')
            {
                InsertCharAt(' ', text, i + 1);
                textLength++;
            }
        }
        //Check if the quotes are closing 
        else if (text[i] == '\"' && quotesCount % 2 == 0)
        {
            if (text[i + 1] != ' ' && text[i + 1] != '\n')
            {
                InsertCharAt(' ', text, i + 1);
                textLength++;
            }
        }

        //Slagash interval predi razni raboti
        if (text[i] == '-' || text[i] == '+'  || text[i] == '/' || text[i] == '*' || text[i] == '%' || text[i] == '(')
        {
            if (text[i - 1] != ' ' && text[i - 1] != '\n')
            {
                InsertCharAt(' ', text, i);
                i++;
                textLength++;
            }
        }
        //Check if the quotes are opening
        else if (text[i] == '\"' && quotesCount % 2 == 1)
        {
            if (text[i - 1] != ' ')
            {
                InsertCharAt(' ', text, i);
                i++;
                textLength++;
            }
        }
    }    
}

void AddMissingFullStops(char text[2048], int textLength)
{
    //Remove trailing whitespaces
    for (int i = textLength - 1; i >= 0; i--)
    {
        if (text[i] == ' ')
        {
            text[i] = -32;
            textLength--;
        }
        else break;
    }

    //Add missing end of sentence full stop ['.']
    char lastCharacterOfText = text[textLength - 1];
    if (lastCharacterOfText == '\"')
    {
        InsertCharAt('.', text, textLength - 1);
        textLength++;
    }
    else if (lastCharacterOfText != '.')
    {
        text[textLength] = '.';
        textLength++;
    }

    //Add other missing full stops
    for (int i = 0; i < textLength; i++)
    {
        if (text[i] == '\n' && text[i - 1] != '.')
        {
            if (text[i - 1] == '\"') 
            {
                InsertCharAt('.', text, i - 1);
                i++;
            }
            else InsertCharAt('.', text, i);
            textLength++;
        }
    }
}

void AutoCorrectWords(char text[2048], int textLength, char dictionary[128][100], int dictionaryEntriesCount)
{
    string dictionaryWrongWords[128], dictionaryCorrectWords[128];

    int currentWord = 0, currentDelim = -1;
    bool increaseWordCount = false, increaseDelimCount = true;

    //Get the wrong and correct words from the dictionary
    for (int i = 0; i < dictionaryEntriesCount; i++)
    {
        string wordsOfEntry[2];
        SplitByDelimiter(dictionary[i], '-', wordsOfEntry);
        dictionaryWrongWords[i] = wordsOfEntry[0];
        dictionaryCorrectWords[i] = wordsOfEntry[1];
    }

    //Replace each of the wrong words and phrases in the text with the correct ones
    for (int i = 0; i < dictionaryEntriesCount; i++)
    {
        string wrongWord = dictionaryWrongWords[i];
        string correctWord = dictionaryCorrectWords[i];
        int indexOfWrongWord = ContainsString(text, textLength, wrongWord);

        while (indexOfWrongWord > 0)
        {
            ReplaceWithString(text, textLength, correctWord, wrongWord, indexOfWrongWord);
            /*textLength = textLength + (correctWord.length() - wrongWord.length());
            OutputCorrectedText(text);*/
            indexOfWrongWord = ContainsString(text, textLength, wrongWord);
            textLength += (correctWord.length() - wrongWord.length());
        }
    }    
}

void AutoCorrect(char text[1024], int textLength, char dictionary[128][100], int dictionaryEntriesCount)
{
    char newText[2048];
    int newTextLength = textLength;

    //Transfer text from the original to the new. I think this function is only available in MSVC. You can use normal strcpy and the result wouldn't change.
    strcpy_s(newText, sizeof(newText), text);

    //Add missing intervals
    CorrectMissingIntervals(newText, textLength);
    //Adjust new text length
    newTextLength = GetCharArrayLength(newText);   

    //Add missing fullstops
    AddMissingFullStops(newText, newTextLength);
    //Adjust new text length
    newTextLength = GetCharArrayLength(newText);

    //TODO: REPLACE THE WRONG WORDS WITH THE CORRECT ONES
    AutoCorrectWords(newText, newTextLength, dictionary, dictionaryEntriesCount);

    //OUTPUT the correct text
    OutputCorrectedText(newText);

}

void ExerciseZero()
{
    //Moyat sobstven tekst. 
    //Lenght = 203
    //Dictionary Entries = 5
    /*
   
Example Input:
203
Tova a test,za zadachata,"koqto mi otne sumati vreme da napravq"misq 4e mi otne okolo 8 chasa da q napravq "be6e mnogo gadno""otvratitelno napravo"
Napravo glavata me zabolq dokato q(napravq)
Kill meeeee
5
stil-still
meeeee-me
za zadachata-Za Zadachkata gadna
misq-mislq
a-e

Example Output:
Tova e test, Za Zadachkata gadna, "koqto mi otne sumati vreme da napravq" mislq 4e mi otne okolo 8 chasa da q napravq "be6e mnogo gadno" (otvratitelno napravo).
Napravo glavata me zabolq dokato q (napravq).
Kill me.
    */

    //TEST INPUT. UNCOMMENT THIS AND COMMENT THE USER INPUT IF YOU WANT TO USE THE TEST TEXT
    //char text[1024] = "Tova a test,za zadachata,\"koqto mi otne sumati vreme da napravq\"misq 4e mi otne okolo 8 chasa da q napravq \"be6e mnogo gadno\"\"otvratitelno napravo\"\nNapravo glavata me zabolq dokato q(napravq)\nKill meeeee";
    //TEST INPUT
    char dictionary[128][100] =
    {
        "meeeee-me",
        "stil-still",
        "za zadachata-Za Zadachkata gadna",
        "misq-mislq",
        "a-e"
    };

    int textLength = 0, dictionaryLength = 0;

    //DEBUG. Can be used to get the length of any text. Useful for testing and debugging purposes. 
    //int trueTextLength = GetCharArrayLength(text);

    //Validate text length
    cin >> textLength;
    while (textLength <= 0 || textLength > 1024)
    {
        cin >> textLength;
    }

    //Input text from console  
    //UNCOMMENT IF YOU WANT TO INPUT A TEXT MANUALLY FROM THE CONSOLE.
    //COMMENT IF YOU WANT THE TEST INPUT INSTEAD
    cin.ignore();
    char text[1024] = "";

    char currentParagraphOfText[1024];
    int counter = 0;
    int currentTextLength = 0;

    while (currentTextLength < textLength)
    {
        cin.getline(currentParagraphOfText, sizeof(currentParagraphOfText));
        int getParagraphLength = GetCharArrayLength(currentParagraphOfText);

        for (int i = 0; i < getParagraphLength; i++)
        {
            text[i + currentTextLength] = currentParagraphOfText[i];
        }

        text[getParagraphLength + currentTextLength] = '\n';
        currentTextLength++;

        currentTextLength = GetCharArrayLength(text);
    }

    //Validate dictionary length
    cin >> dictionaryLength;
    while (dictionaryLength <= 0 || dictionaryLength > 128)
    {
        cin >> dictionaryLength;
    }

    //Input dictionary entries from the console
    
    //UNCOMMENT IF YOU WANT TO INPUT A TEXT MANUALLY FROM THE CONSOLE.
    //COMMENT IF YOU WANT THE TEST INPUT INSTEAD
    cin.ignore();
    for (int i = 0; i < dictionaryLength; i++)
    {
        cin.getline(dictionary[i], 100);
    }
    
    AutoCorrect(text, textLength, dictionary, dictionaryLength);

    return;
}

//--------------------------Functions for exercise 0 -------------------------------------------------------------

void PrintMatrix(int** array, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int y = 0; y < m; y++)
        {
            cout << array[i][y] << " ";
        }
        cout << endl;
    }
}

int** TransformMatrix(int** arrayA, int** arrayB, int& n1, int& m1, int n2, int m2)
{
    if (n2 < n1)
    {
        n1 = n2;

        //Remove rows from the matrix
        for (int i = n1; i > n2; i--)
        {
            delete[] arrayA[i];
        }

        //DEBUG
        /*cout << endl << endl;
        PrintMatrix(arrayA, n1, m1);
        cout << endl << endl;*/
    }
    if (m2 < m1)
    {
        m1 = m2;

        //Remove columns from the matrix
        int** newArrayA = new int* [n1];
        for (int row = 0; row < n1; row++)
        {
            newArrayA[row] = new int[m1];
            for (int col = 0; col < m1; col++)
            {
                newArrayA[row][col] = arrayA[row][col];
            }
        }
        //DEBUG
        /*cout << endl << endl;
        PrintMatrix(newArrayA, n1, m1);
        cout << endl << endl;*/

        //Remove unused memory
        for (int row = 0; row < n1; row++)
        {
            delete [] arrayA[row];
        }
        delete[] arrayA;

        //Transfer pointer of the new array to the old one
        arrayA = newArrayA;

        //DEBUG
        /*cout << endl << endl;
        PrintMatrix(arrayA, n1, m1);
        cout << endl << endl;*/
    }

    for (int row = 0; row < n1; row++)
    {
        for (int col = 0; col < m1; col++)
        {
            if (arrayA[row][col] < arrayB[row][col]) arrayA[row][col] = arrayB[row][col];
            else if (arrayA[row][col] > arrayB[row][col]) arrayA[row][col] *= -1;
        }
    }

    return arrayA;
}

void ExerciseOne()
{
    /* Copy paste input to test the example
    * Example Input:
     3
     5
     2
     4
     
     1  -3   8  10  34
     4   7  13   2   9
     3   0  -4   5   2
     
     1   2   3  -4
     10  19   2   0

     Example Ouput:
     1  2  -8  -10
     10 19  -13   -2 
    */

    int n1, m1, n2, m2;

    //Enter the dimensions for the arrays
    cin >> n1 >> m1 >> n2 >> m2;

    //Initialize arrayA and arrayB
    int** arrayA = new int* [n1];
    int** arrayB = new int* [n2];

    for (int i = 0; i < n1; i++)
    {
        arrayA[i] = new int[m1];
    }

    for (int i = 0; i < n2; i++)
    {
        arrayB[i] = new int[m2];
    }

    //Input the arrays from the console
    for (int i = 0; i < n1; i++)
    {
        for (int y = 0; y < m1; y++)
        {
            cin >> arrayA[i][y];
        }
    }

    for (int i = 0; i < n2; i++)
    {
        for (int y = 0; y < m2; y++)
        {
            cin >> arrayB[i][y];
        }
    }

    cout << endl << "Original Matrix: " << endl << endl;
    PrintMatrix(arrayA, n1, m1);
    cout << endl << endl;

    arrayA = TransformMatrix(arrayA, arrayB, n1, m1, n2, m2);
    
    cout << "Altered Matrix: " << endl << endl;
    PrintMatrix(arrayA, n1, m1);
}

//--------------------------Functions for exercise 1 -------------------------------------------------------------

void PrintMatrix(char** array, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int y = 0; y < m; y++)
        {
            cout << array[i][y];
        }
        cout << endl;
    }
}

int StartMovingFromTile(char** board, int n, int m, int x, int y)
{
    int totalMoves = 0;

    int currentRow = x;
    int currentCol = y;

    int* alreadyVisitedTilesRowCoordinates = new int[n * m];
    int* alreadyVisitedTilesColCoordinates = new int[n * m];

    while (currentRow >= 0 && currentRow < n && currentCol >= 0 && currentCol < m)
    {
        alreadyVisitedTilesRowCoordinates[totalMoves] = currentRow;
        alreadyVisitedTilesColCoordinates[totalMoves] = currentCol;

        char currentTile = board[currentRow][currentCol];
        totalMoves++;

        if (currentTile == 'U') currentRow--;
        else if (currentTile == 'D') currentRow++;
        else if (currentTile == 'L') currentCol--;
        else if (currentTile == 'R') currentCol++;

        bool hasVisitedTheCellAlready = false;
        //Check if the robot has already visited the same square
        for (int i = 0; i < totalMoves; i++)
        {
            int alreadyVisitedTileRowCoord = alreadyVisitedTilesRowCoordinates[i];
            int alreadyVisitedTileColCoord = alreadyVisitedTilesColCoordinates[i];

            //Stop the robot if the tiles has already been visited
            if (alreadyVisitedTileRowCoord == currentRow && alreadyVisitedTileColCoord == currentCol)
            {
                hasVisitedTheCellAlready = true;
                break;
            }
        }

        if (hasVisitedTheCellAlready) break;
    }

    //DEBUG to check if the already visited cells are being recorded correctly
    cout << endl;
    cout << "When starting at coordinates(x y): " << x << " " << y << " Here are the visited cells" << endl;
    for (int i = 0; i < totalMoves; i++)
    {
        int alreadyVisitedTileRowCoord = alreadyVisitedTilesRowCoordinates[i];
        int alreadyVisitedTileColCoord = alreadyVisitedTilesColCoordinates[i];
        cout << "(" << alreadyVisitedTileRowCoord << " " << alreadyVisitedTileColCoord << ")" << " | ";
    }
    cout << "(" << currentRow << " " << currentCol << ")";
    cout << " --- Total Moves: " << totalMoves;
    cout << endl;

    //Delete allocated memory
    delete[] alreadyVisitedTilesRowCoordinates;
    delete[] alreadyVisitedTilesColCoordinates;

    return totalMoves;
}

void GetMaxMovesStartingPoint(char** board, int n, int m, int& xCoordResult, int& yCoordResult)
{
    int mostMovesPerTile = -1;

    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < m; col++)
        {
            int numberOfMovesFromTile = StartMovingFromTile(board, n, m, row, col);
            if (mostMovesPerTile < numberOfMovesFromTile)
            {
                xCoordResult = row;
                yCoordResult = col;
                mostMovesPerTile = numberOfMovesFromTile;
            }
        }
    }
}

void Exercise21()
{
    /* Copy paste input to test the example
        Example Input:
        4 5
        RRRDL
        RUUDU
        URUDL
        ULLRU

        Example Output:
        3 2

        Example Input 2:
        5 4
        RRRD
        RUUD
        URUD
        ULLD
        ULLL

        Example Ouput 2:
        2 1
    */

    int n, m;
    cin >> n >> m;
    char** board = new char* [n];
    for (int i = 0; i < n; i++)
    {
        board[i] = new char[m];
    }

    //Input board from the console
    for (int i = 0; i < n; i++)
    {
        for (int y = 0; y < m; y++)
        {
            cin >> board[i][y];
        }
    }

    //DEBUG
    cout << endl << "Starting board: " << endl;
    PrintMatrix(board, n, m);
    cout << endl;

    int xCoordMaxMoves = -1;
    int yCoordMaxMoves = -1;
    GetMaxMovesStartingPoint(board, n, m, xCoordMaxMoves, yCoordMaxMoves);

    cout << endl;
    cout << "Starting Coordinates(x y) for the most moves are: " << xCoordMaxMoves << " " << yCoordMaxMoves;
}


//--------------------------Functions for exercise 2 -------------------------------------------------------------

int main()
{
    ExerciseZero();
    //ExerciseOne();
    //Exercise21(); Exercise with the robot moving on a board
}

