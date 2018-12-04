/* ---------------------------
 Laboratoire   : Labo 6
 Fichier       : main.cpp
 Auteur(s)     : Dessaules Loïc, Reuteler Robin, Pande Rochana
 Date          : 04.12.18
 But           : L'utilisateur entre un nombre entre [0-9999.99] et le programme 
                 retourne une chaine de caractères au format string contenant
                 "en vaudois" le montant correspondant exprimé en francs et centimes.
                 Donc septante, huitante et nonante pour 70, 80 et 90.
 Remarque(s)   : Si l'utilisateur entre des centimes qui sont plus précis que le centième
                 (ex: 73.429) nous arrondissons au centime le plus proche
 Compilateur   : MinGW-g++ 6.3.0
 --------------------------- */

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

/**
 * @brief Retourne la correspondance en lettre, de l'unité (chiffre) passé en paramètre
 * 
 * @param[in] units L'unité en chiffre pour lequelle il faut une conversion en string
 * @return L'unité voulu en lettre
 * @details Dans le chiffre 324, l'unité est 4 et nous allons retourner "quatre"
 */
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

/**
 * @brief Retourne la correspondance en lettre, de la dizaine (chiffre) passé en paramètre
 * 
 * @param[in] tens La dizaine en chiffre pour lequelle il faut une conversion en string
 * @return La dizaine voulu en lettre
 * @details Dans le chiffre 324, la dzaine est 2 et nous allons retourner "vingt"
 */
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

/**
 * @brief Retourne la correspondance en lettre, des chiffres de 11 à 16 passés en paramètre
 * 
 * @param[in] teens Les chiffres (11 à 16) pour lequelle il faut une conversion en string
 * @return Le chiffre de 11 à 16 voulu en lettre
 * @details Les chiffres de 11 à 16 sont "spéciaux", ils ne s'écrivent pas de la même
 * manière que les autres (22 = vingt deux). 16 d'écrira donc comme "seize" et non
 * "dix six", ceci est du aux règles de notre langue.
 */
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

/**
 @brief Récupère un chiffre et l'exprime comme un nombre de centaines
 @param[in] hundreds un entier compris entre 1 et 9.
 @return une chaine de caractères exprimant le chiffre en centaines.
 @details Exemples:
 3  -> "trois cent"
 1 -> "cent"
 */
string getStringHundreds(const unsigned& hundreds) {
    string result = "cent";
    if (hundreds > 1) {//Pas de "un cent"
        result = getStringUnits(hundreds) + " " + result;
    }
    return result;
}

/**
 @brief Récupère deux chiffres et les exprime comme dizaines et unités en vaudois
 @param[in] num un entier compris entre 0 et 99.
 @return une chaine de caractères exprimant le nombre en vaudois.
 @details Exemples:
 30  -> "trente"
 1 -> "un"
 21 -> "vingt et un"
 45 -> "quarante cinq"
 13 -> "treize"
 */
string getTensAndUnits(unsigned num) {
    string result;
    if (10 < num and num < 17)//Onze, Douze etc.
    {
        result = getStringTeens(num) + " " + result;
    } else {
        unsigned units = num % 10;
        if (units) {
            result = getStringUnits(units) + " " + result; //Unités
        }
        num /= 10;
        
        unsigned tens = num % 10;
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

/**
 @brief Récupère la partie entière et l'exprime en "Vaudois"
 @param[in] number un entier compris entre 0 et 999'999.
 @return une chaine de caractères exprimant en vaudois le nombre de francs.
 @details Exemples:
 30  -> "trente francs"
 100 -> "cent francs"
 300000 -> "trois cent mille francs"
*/
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

/**
 @brief Récupère la partie décimale et l'exprime en "Vaudois"
 @param[in] number un entier compris entre 0 et 0 et 99.
 @return une chaine de caractères indiquant en vaudois le nombre de centimes.
 @details Exemples:
 30  -> "trente centimes"
 1 -> "un centime"
*/
string getStringDecimalPart(unsigned number) {
    string result = getTensAndUnits(number);
    result += number == 1 ? "centime" : "centimes"; //Accord pluriel
    return result;
}

/**
 @brief Traduit des nombres réels en prix exprimés en vaudois
 @param[in] montant un réel compris entre 0 et 999999.99 CHF.
 @return une chaine de caractères indiquant en vaudois le prix
 en francs et centimes.
 @details Les décimales après la deuxième sont arrondies au centime le plus proche
 Exemples:
 12.30  -> "douze francs et trente centimes"
 200.01 -> "deux cents francs et un centime"
 180    -> "cent huitante francs"
 1.80   -> "un franc et huitante centimes"
 0.20   -> "vingt centimes"
 231.456 -> "deux cent trente et un francs et quarante cinq centimes"
 0      -> "zéro franc"
 */
string montantEnVaudois(double montant) {
    montant = round(montant*100)/100;
    const double MONTANT_MIN = 0;
    const double MONTANT_MAX = 999999.99;
    if (montant < MONTANT_MIN or montant > MONTANT_MAX)
    {
        return "Montant invalide ! ";
    }
    string result;
    if (montant) {
        unsigned intPart = (unsigned) montant;
        double roundedDecimalPart = round((montant - intPart)*100); //Pour une partie décimale (mantisse) correctement arrondie
        unsigned decimalPart = (int) roundedDecimalPart; //Cast explicite de double à int, pour prévenir les warnings
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
