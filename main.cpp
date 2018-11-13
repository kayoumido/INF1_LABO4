/* ---------------------------
 Laboratoire : 4
 Fichier : main.cpp
 Auteur(s) : Doran Kayoumi, Robin Demarta, Gabrielle Thurnherr
 Date : 01.11.2018

 But : Mise en oeuvre d'opérations arithmétiques simples
 (+,-,*) sur des entiers positifs longs représentés
 sous forme de chaines de caractères en notation
 décimale

 Remarque(s) :

 Compilateur : g++ 6.3.0
 --------------------------- */

#include <cstdlib>
#include <iostream>
#include <string>
#include <cassert>
#include <algorithm>
#include <limits>

using namespace std;

const char ZERO = '0';
const char NEGATIVE_SIGN = '-';
const short ZERO_INT_VALUE = ZERO;
const short CARRY_LIMIT = 10;
const short WORKING_BASE = 10;

/**
 * Convertit un entier en char
 *
 * @param x entier à convertir
 *
 * @return entier converti
 */
char integerToChar(int x) {
  return char(x + ZERO_INT_VALUE);
}

/**
 * Convertit un char en entier
 *
 * @param c char à convertir
 *
 * @return entier converti
 */
short charToInteger(char c) {
  return c - ZERO_INT_VALUE;
}

/**
 * Convertit une string en int
 *
 * @param toConvert entier valeur a convertir
 *
 * @return l'entier convertit en string
 */
string integerToString(int toConvert) {
  string converted;

  if(toConvert == 0) {
    converted = ZERO;
  }

  while (toConvert > 0) {
    converted = integerToChar(toConvert % WORKING_BASE) + converted;
    toConvert = toConvert / WORKING_BASE;
  }
  return converted;
}

/**
 * Rallonge la string la plus courte à la même longueur
 * que l'autre en y ajoutant des zéros
 *
 * @param s1 string de la plus grande longueur
 * @param s2 string a rallonger
 *
 * @return la string de la meme longueur que la premiere
 */
string equaliseLength(const string& s1, string s2) {
  unsigned long long difference = s1.length() - s2.length();
  for (unsigned long long i = difference; i > 0; i--) {
    s2 = ZERO + s2;
  }
  return s2;
}

/**
 * Retire les éventuels premier zéros d'une string
 * @param value string à traiter
 * @return le string sans les premiers zéros
 */
string removeZeros(string value) {
  string result;
  bool building = false;
  int valueLength = value.length();
  
  for(int i = 0; i < valueLength; ++i) {
    if(value[i] != ZERO || building) {
      building = true;
      result += value[i];
    }
  }
  
  if(!building) {
    result = ZERO;
  }
  
  return result;
}

/**
 * Vérifie si le nombre produit un carry et met à jour les valeurs
 *
 * @param value
 * @param carryContainer
 */
void checkForCarry(short& value, short& carryContainer) {
  if (value >= CARRY_LIMIT) {
    carryContainer = value / CARRY_LIMIT;
    value -= carryContainer * CARRY_LIMIT;
  } else {
    carryContainer = 0;
  }
}

/**
 * Intervertit deux variables string
 *
 * @param s1 string à inverser
 * @param s2 string à inverser  
 */
void swap(string& s1, string& s2) {
  string tmp = s1;
  s1 = s2;
  s2 = tmp;
}

/**
 * Addition
 *
 * @param lhs entier >=0 représenté en notation décimale
 * @param rhs entier >=0 représenté en notation décimale
 *
 * @return somme des 2 entiers représentée en notation décimale
 */
string add(string lhs, string rhs) {
  string result;
  short n1;
  short n2;
  short total;
  short carry = 0;

  // Rajoute un zero au début du string
  lhs = ZERO + lhs;
  rhs = ZERO + rhs;

   // Controle quelle est la string la plus longue et la plus courte en rajoutant des zeros
  if (lhs.length() > rhs.length()) {
    rhs = equaliseLength(lhs, rhs);
  } else if (rhs.length() > lhs.length()) {
    lhs = equaliseLength(rhs, lhs);
  }

  // Prend le dernier caractere des strings et les additionne
  for (int i = (int)lhs.length() - 1; i >= 0; i--) {
    n1 = charToInteger(lhs[i]);
    n2 = charToInteger(rhs[i]);

    // Permet de controler le cas limite, et de ne pas ajouter un zero au debut du resultat
    if (i == 0 and carry == 0) {
      continue;
    } else {
      total = n1 + n2 + carry;
    }
    checkForCarry(total, carry);
    result = integerToChar(total) + result;
  }

  return result;
}

/**
 * Multiplication
 *
 * @param lhs entier >=0 représenté en notation décimale
 * @param rhs entier >=0 représenté en notation décimale
 *
 * @return produit des 2 entiers représenté en notation décimale
 */
string multiply(string lhs, string rhs) {
  string result;

  short i1Digit;
  short i2Digit;
  short carry = 0;
  short multiplicationDigit = 0;
  string multiplication;
  string zeros;

  // Parcourir premier nombre
  for (int i = (int)lhs.length() - 1; i >= 0; --i) {
    i1Digit = charToInteger(lhs[i]);
    carry = 0;
    multiplication = zeros;

    // Parcourir deuxième nombre et multiplier chaque digit
    for (int j = (int)rhs.length() - 1; j >= 0; --j) {
      i2Digit = charToInteger(rhs[j]);

      multiplicationDigit = (i1Digit * i2Digit) + carry;
      checkForCarry(multiplicationDigit, carry);

      multiplication = integerToChar(multiplicationDigit) + multiplication;
    }

    // Ajouter le dernier carry s'il y en a un
    if (carry != 0) {
      multiplication = integerToChar(carry) + multiplication;
    }

    zeros += ZERO; // Prochain chiffre -> ajouter un zéro au début du résultat intermédiaire
    result = add(result, multiplication);
  }

  return removeZeros(result);
}

/**
 * Factorielle
 *
 * @param n entier >=0
 *
 * @return n! la factorielle de n représentée en notation décimale
 */
string factorial(int n) {
  string result = "1";

  string value = integerToString(n);
  string multiplier = "0";

  while (multiplier != value) {
    multiplier = add(multiplier, "1");
    result = multiply(multiplier, result);
  }

  return result;
}

/**
 * Soustraction
 *
 * @param lhs entier >=0 représenté en notation décimale
 * @param rhs entier >=0 représenté en notation décimale
 *
 * @return différence (lhs - rhs) des 2 entiers représentée en notation décimale
 */
string subtract(string lhs, string rhs) {
  string result;
  bool negative = false;

  // Recherche de la valeur la plus grande.
  //  Si la valeur `rhs` est plus grande que `lhs`,
  //    alors elles sont inversées afin d'avoir la plus grande a gauche du calcul.
  //  Si les valeurs on été inversé, le résultat de la soustraction sera donc négative.
  if (lhs.length() < rhs.length()) {
    swap(lhs, rhs);
    negative = true;
  }
  // Dans le cas ou les valeurs font la même longueur,
  //   on vérifie, chaque caractère des valeurs afin de trouver la plus grande des deux.
  if (lhs.length() == rhs.length() and charToInteger(lhs[0]) <= charToInteger(rhs[0])) {
    for (int i = (int) lhs.length() - 1; i >= 0; --i) {
      if (charToInteger(lhs[i]) < charToInteger(rhs[i])) {
        swap(lhs, rhs);
        negative = true;
        break;
      }
    }
  }

  rhs = equaliseLength(lhs,rhs);

  int lhsLength = (int)lhs.length();
  for (int i = lhsLength - 1; i >= 0; --i) {
    short difference = charToInteger(lhs[i]) - charToInteger(rhs[i]);

    if (difference < 0) {
      lhs[i - 1] = integerToChar(charToInteger(lhs[i - 1]) - 1);
      difference += CARRY_LIMIT;
    }

    result = integerToChar(difference) + result;
  }

  if (negative) result = NEGATIVE_SIGN + result;

  return removeZeros(result);
}

/**
 * Fonction principale
 *
 * @return Mise en oeuvre d'opérations arithmétiques simples
 * (+,-,*) sur des entiers positifs longs représentés
 * sous forme de chaines de caractères en notation
 * décimale
 */
int main() {

  cout << "Entrez deux entiers >= 0 \n";
  string i1, i2;
  cin >> i1 >> i2;

  cout << i1 << " + " << i2 << " = " << add(i1, i2) << endl;
  cout << i1 << " * " << i2 << " = " << multiply(i1, i2) << endl;
  cout << i1 << " - " << i2 << " = " << subtract(i1, i2) << endl;

  cout << "\nEntrez un entier >= 0 \n";
  int i3;
  cin >> i3;
  cout << "Factoriel(" << i3 << ") = " << factorial(i3) << endl;

  return EXIT_SUCCESS;
}
