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
   
   
   unsigned i = 0;
   while (number) {
       
       unsigned units;
       string strUnits;
       unsigned tens;
       string strTens;
       unsigned hundreds;
       string strHundreds;
       unsigned temp;
       string strTeens;
       
      temp = number % 1000;
       
       if (i)
       {
           result = "mille " + result;
       }
       
       int tensAndUnits = temp % 100;
      if (10 < tensAndUnits and tensAndUnits < 17)
      {
          strTeens = getStringTeens(tensAndUnits);
          temp /= 100;
          result = strTeens + " " + result;
      }
       else
       {
           units = temp % 10;
           if (units and not((i) and (temp == 1)))//Exclure le cas "un mille"
           {
               strUnits = getStringUnits(units);
               result = strUnits + " " + result;
           }
           temp /= 10;
           
           tens = temp % 10;
           if (tens)
           {
               strTens = getStringTens(tens);
               if(units == 1)
               {
                   strTens += " et ";
               }
               else
               {
                   strTens += "-";
               }
               result = strTens + result;
           }
           temp /= 10;
       }
    
      hundreds = temp % 10;
       if (hundreds)
       {
           strHundreds = getStringHundreds(hundreds);
           result = strHundreds + " " + result;
       }
      temp /= 10;
      number /= 1000;
       ++i;
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
   int decimalPartAsInteger = decimalPart * 100 + 0.05; // Added 0.05 to round in a good way
   
   string entierPartRepresentationAsString = getStringEntierPart(entierPart);
   string decimalRepresentationAsString = getStringEntierPart(decimalPartAsInteger);
   string finalRepresentation;
   
   finalRepresentation = entierPartRepresentationAsString;
   // Add the xy "et" xy "centime(s)" only if we have a decimal part
   if(!decimalRepresentationAsString.empty()){
      // Plurals management
      string centsAsString = (decimalPartAsInteger > 1) ? "centimes" : "centime";
      finalRepresentation = finalRepresentation + "et" + decimalRepresentationAsString + centsAsString;
   }

   return finalRepresentation;
}

int main() {

   double d;

   while (cin >> d) {
      cout << montantEnVaudois(d) << endl;
   }

   return 0;
}
