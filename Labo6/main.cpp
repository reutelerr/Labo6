/* ---------------------------
 Laboratoire : 6
 Fichier :     main.cpp
 Auteur(s) :
 Date :        28.11.2018
 
 But :
 
 Remarque(s) :
 
 Compilateur : GNU GCC Compiler
 --------------------------- */

#include <iostream>

using namespace std;

void displayUnits(const int& num)
{
    
}

void displayTens(const int& num)
{
    
}

void displayHundreds(const int& num)
{
    if (num > 1)
    {
        displayUnits(num);
        
    }
}

/*void displayDigit(const int& num, const int& digitIndex)*/

void displayIntPart(const int& num)
{
    unsigned int i=0;
    while (num)
    {
        displayUnits(<#const int &num#>)
        displayTens(<#const int &num#>)
        displayHundreds(<#const int &num#>)
        
        
        num /= 1000;
        
    }
}

void displayDecimalPart(const int& num)
{
    
}


int main() {

    
    return 0;
}
