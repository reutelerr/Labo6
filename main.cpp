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
   switch (units) {
      case 1:
         return "un";
      case 2:
         return "deux";
      case 3:
         return "trois";
      case 4:
         return "quatre";
      case 5:
         return "cinq";
         break;
      case 6:
         return "six";
      case 7:
         return "sept";
      case 8:
         return "huit";
      case 9:
         return "neuf";
      default:
         return "";
   }
}

string getStringTens(const int& tens) {
   switch (tens) {
      case 1:
         return "dix";
      case 2:
         return "vingt";
      case 3:
         return "trente";
      case 4:
         return "quarante";
      case 5:
         return "cinquante";
      case 6:
         return "soixante";
      case 7:
         return "septante";
      case 8:
         return "huitante";
      case 9:
         return "nonante";
      default:
         return "";
   }
}

string getStringTeens(const int& teens) {
   switch (teens) {
      case 11:
         return "onze";
      case 12:
         return "douze";
      case 13:
         return "treize";
      case 14:
         return "quatorze";
      case 15:
         return "quinze";
      case 16:
         return "seize";
      default:
         return "";
   }
}

string getStringHundreds(const unsigned& hundreds) {
   string result = "cent";
   if (hundreds > 1) {//Pas de "un cent"
      result = getStringUnits(hundreds) + " " + result;
   }
   return result;
}

string getTensAndUnits(int num) {
   string result;
   if (10 < num and num < 17)//Onze, Douze etc.
   {
      result = getStringTeens(num) + " " + result;
   } else {
      int units = num % 10;
      if (units) {
         result = getStringUnits(units) + " " + result; //Unités
      }
      num /= 10;

      int tens = num % 10;
      if (tens) {
         string strTens = getStringTens(tens); //Dizaines
         if (units == 1)//20 et 1 mais pas 20 et 2 par exemple
         {
            strTens += " et ";
         } else {
            if (units)//trente-quatre par exemple
            {
               strTens += "-";
            } else {
               strTens += " ";
            }
         }
         result = strTens + result;
      }
   }
   return result;
}

string getStringIntPart(unsigned number) {
   string result;

   if (not(number)) {
      result += "zero ";
   } else {
      bool thousands = 0; //Somme-nous dans les milliers ?
      unsigned temp = number;
      while (temp) {
         if (thousands) {
            result = "mille " + result;
         }
         unsigned tensAndUnits = temp % 100;
         if (not(thousands and tensAndUnits == 1))//Pas de "un mille"
         {
            result = getTensAndUnits(tensAndUnits) + result; //Gestion des dizaines et unités en bloc
         }

         unsigned hundreds;
         string strHundreds;
         hundreds = (temp % 1000) / 100;
         if (hundreds) {
            strHundreds = getStringHundreds(hundreds);
            if (not(tensAndUnits) and not(thousands) and hundreds != 1)//On accorde uniquement si rien ne suit
            {
               strHundreds += "s"; //Accord du "cent"
            }
            result = strHundreds + " " + result;
         }
         temp /= 1000; //Groupe de 3 chiffres suivant
         thousands = 1; //On passe au milier (à modulariser ?)
      }
   }
   number <= 1 ? result += "franc " : result += "francs "; //Accord pluriel
   return result;
}

string getStringDecimalPart(unsigned number) {
   string result = getTensAndUnits(number);
   result += number == 1 ? "centime " : "centimes"; //Accord pluriel
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
   string result;
   if (montant) {
      int intPart = (int) montant;
      double roundedDecimalPart = 100 * (montant - intPart) + 0.05; //Pour une partie décimale (mantisse) correctement arrondie
      int decimalPart = (int) roundedDecimalPart; //Cast explicite de double à int, pour prévenir les warnings
      result += intPart ? getStringIntPart(intPart) : ""; //Partie entière
      result += (intPart and decimalPart) ? "et " : ""; //Connecteur
      result += decimalPart ? getStringDecimalPart(decimalPart) : ""; //Partie décimale
   } else {
      result = "zero franc"; //Cas du zéro
   }
   return result;
}

int main() {
   double d;

   while (cin >> d) {
      cout << montantEnVaudois(d) << endl;
   }
   return 0;
}
