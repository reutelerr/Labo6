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
   }
}

string getStringTens(const int& tens) {
   switch(tens){
      case 10 : 
         return "dix";
         break;
      case 20 : 
         return "vingt";
         break;
      case 30: 
         return "trente";
         break;
      case 40 : 
         return "quarante";
         break;
      case 50 : 
         return "cinquante";
         break;
      case 60 : 
         return "soixante";
         break;
      case 70 : 
         return "septante";
         break;
      case 80 : 
         return "huitante";
         break;
      case 90 : 
         return "nonante";
         break;
   }
}

string getStringHundreds(const int& hundreds) {
   string result = "cent";
   if (hundreds > 1) {
      result = getStringUnits(hundreds) + " " + result;
   }
   return result;
}

/*void displayDigit(const int& num, const int& digitIndex)*/

string getStringEntierPart(unsigned number) {
   string result = "";
   unsigned units;
   string strUnits;
   unsigned tens;
   string strTens;
   unsigned hundreds;
   string strHundreds;
   unsigned temp;
   
   unsigned i = 0;
   while (number) {
      temp = number;
      
      units = temp % 10;
      strUnits = getStringUnits(units);
      temp /= 10;
      
      
      tens = (temp % 10) * 10;
      strTens = getStringTens(tens);
      temp /= 10;
      
      hundreds = temp % 10;
      strHundreds = getStringHundreds(hundreds);
      temp /= 10;
      
      result = strUnits + " " + result;
      result = strTens + " " + result;
      result = strHundreds + " " + result;
      
      number /= 1000;

   }
   
   return result;
}

void displayDecimalPart(const int& num) {

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
   int entierPart = (int) montant;
   double decimalPart = montant - entierPart;

   return getStringEntierPart(entierPart);
}

int main() {

   double d;

   while (cin >> d) {
      cout << montantEnVaudois(d) << endl;
   }

   return 0;
}
