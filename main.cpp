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
#include <string>

using namespace std;

string getStringUnits(const int& units) {
    switch(units){
        case 1 :
            return "un";
            break;
        case 2 :
            return "deux";
            break;
        case 3:
            return "trois";
            break;
        case 4 :
            return "quatre";
            break;
        case 5:
            return "cinq";
            break;
        case 6:
            return "six";
            break;
        case 7:
            return "sept";
            break;
        case 8:
            return "huit";
            break;
        case 9:
            return "neuf";
            break;
        default :
            return "";
    }
}

string getStringTens(const int& tens) {
    switch(tens){
        case 1 :
            return "dix";
            break;
        case 2 :
            return "vingt";
            break;
        case 3:
            return "trente";
            break;
        case 4 :
            return "quarante";
            break;
        case 5 :
            return "cinquante";
            break;
        case 6 :
            return "soixante";
            break;
        case 7 :
            return "septante";
            break;
        case 8 :
            return "huitante";
            break;
        case 9 :
            return "nonante";
            break;
        default :
            return "";
    }
}

string getStringTeens(const int& teens)
{
    switch(teens){
        case 11 :
            return "onze";
            break;
        case 12 :
            return "douze";
            break;
        case 13 :
            return "treize";
            break;
        case 14 :
            return "quatorze";
            break;
        case 15 :
            return "quinze";
            break;
        case 16 :
            return "seize";
            break;
        default :
            return "";
    }
}

string getStringHundreds(const unsigned& hundreds) {
    string result = "cent";
    if (hundreds > 1) {
        result = getStringUnits(hundreds) + " " + result;
    }
    return result;
}

string getTensAndUnits(int num)
{
    string result = "";
    if (10 < num and num < 17)
    {
        result = getStringTeens(num) + " " + result;
    }
    else
    {
        int units = num % 10;
        if (units)
        {
            result = getStringUnits(units) + " " + result;
        }
        num /= 10;
        
        int tens = num % 10;
        if (tens)
        {
            string strTens = getStringTens(tens);
            if(units == 1)
            {
                strTens += " et ";
            }
            else
            {
                if(units)
                {
                    strTens += "-";
                }
                else
                {
                    strTens += " ";
                }
            }
            result = strTens + result;
        }
    }
    return result;
}

string getStringIntPart(unsigned number) {
    string result = "";
    
    if(not(number))
    {
        result += "zero ";
    }
    else
    {
        bool  thousands = 0;
        unsigned temp = number;
        while (temp) {
            if (thousands)
            {
                result = "mille " + result;
            }
            unsigned tensAndUnits = temp % 100;
            result = getTensAndUnits(tensAndUnits) + result;
            unsigned hundreds;
            
            string strHundreds;
            hundreds = (temp%1000) / 100;
            if (hundreds)
            {
                strHundreds = getStringHundreds(hundreds);
                if (not(tensAndUnits) and not(thousands) and hundreds != 1)
                {
                    strHundreds += "s";
                }
                result = strHundreds + " " + result;
            }
            temp /= 1000;
            thousands = 1;
        }
    }
    number <= 1 ? result += "franc " : result += "francs ";
    return result;
}

string getStringDecimalPart(unsigned number)
{
    string result = getTensAndUnits(number);
    result += number == 1 ? "centime " : "centimes";
    return result;
}



/**
 @brief Traduit des nombres réels en prix exprimés en vaudois
 @param[in] montant un réel compris entre 0 et 999999.99 CHF.
 @return une chaine de caractères indiquant en vaudois le prix
 en francs et centimes.
 @details Exemples:
 12.30  -> "douze francs et trente centimes"
 200.01 -> "deux cents francs et un centime"
 180    -> "cent huitante francs"
 1.80   -> "un franc et huitante centimes"
 0.20   -> "vingt centimes"
 0      -> "zéro franc"
 */
string montantEnVaudois(double montant) {
    /*int intPart = (int) montant;
    double decimalPart = montant - intPart;
    int decimalPartAsInt = decimalPart * 100 + 0.05; // Added 0.05 to round in a good way
    
    string strIntPart = getStringIntPart(intPart);
    string strDecimalPart = getTensAndUnits(decimalPartAsInt);
    string finalRepresentation;
    
    finalRepresentation = strIntPart;
    // Add the xy "et" xy "centime(s)" only if we have a decimal part
    if(!strDecimalPart.empty() || decimalPart != 0){
        finalRepresentation += (intPart > 0) ? "et " : "";
        finalRepresentation += strDecimalPart;
        finalRepresentation += (decimalPartAsInt > 1) ? "centimes" : "centime";
    }
    
    return finalRepresentation;*/
    
    string result = "";
    if(montant)
    {
        int intPart = (int) montant;
        int decimalPart = 100*(montant - intPart)+ 0.05;
        
        result += intPart ? getStringIntPart(intPart) : "";
        result += intPart and decimalPart ? "et " : "";
        result += decimalPart ? getStringDecimalPart(decimalPart) : "";
    }
    else
    {
        result = "zero franc";
    }
    
    return result;
}
