/* ---------------------------
 Laboratoire : 4b
 Fichier :     main.cpp
 Auteur(s) :
 Date :

 But :         Mise en oeuvre d'opérations arithmétiques simples
 (+,-,*) sur des entiers positifs longs représentés
 sous forme de chaines de caractères en base entre 2 et 36

 Remarque(s) :

 Compilateur :
 --------------------------- */

#include <cstdlib>
#include <iostream>
#include <string>
#include <cassert>
#include <algorithm>
#include <limits>
using namespace std;

const string DIGITS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char ZERO = '0';
const char NEGATIVE_SIGN = '-';
const int ZERO_INT_VALUE = ZERO;
unsigned basis;

/**
 conversion char en entier

 @param c charactere représentant un chiffre en base entre 2 et 36

 @return le nombre correspondant au chiffre en entrée si c est un chiffre
 ou une lettre majuscule ou minuscule. Par exemple, char2int('D')
 retournera 13.
 retourne un nombre négatif (à choix) si c n'est pas un caractère
 alphanumérique.
 */
int char2int(char c) {
  int x = c - ZERO_INT_VALUE;

  if(x >= 17) {
    x -= 7;
  }

  return x;
}

/**
 * Convertit un entier en char
 *
 * @param x entier à convertir
 *
 * @return entier converti
 */
char int2char(int x) {
  return DIGITS[x];
}

/**
 verification de validite d'un nombre en base donnee

 @param nombre une chaine de caracteres representant un nombre entier positif
 en base donne
 @param base   la base (entre 2 et 36)

 @return vrai si le nombre est valide, faux sinon.
 */
bool isValidPositiveInteger(string nombre, unsigned base) {
  assert(base >= 2 and base <= 36);

  // A COMPLETER

  return true;
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
  int valueLength = (int)value.length();

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
void checkForCarry(int& value, int& carryContainer) {
  if (value >= basis) {
    carryContainer = value / basis;
    value -= carryContainer * basis;
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
 Addition

 @param lhs entier >=0 représenté en notation décimale
 @param rhs entier >=0 représenté en notation décimale
 @param base entier entre 2 et 36

 @return somme des 2 entiers représentée en notation décimale
 */
string add(string lhs, string rhs, unsigned base) {
  assert(base >= 2 and base <= 36);
  assert(isValidPositiveInteger(lhs, base));
  assert(isValidPositiveInteger(rhs, base));

  string result;
  int n1;
  int n2;
  int total;
  int carry = 0;

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
    n1 = char2int(lhs[i]);
    n2 = char2int(rhs[i]);

    // Permet de controler le cas limite, et de ne pas ajouter un zero au debut du resultat
    if (i == 0 and carry == 0) {
      continue;
    } else {
      total = n1 + n2 + carry;
    }
    checkForCarry(total, carry);
    result = int2char(total) + result;
  }

  return result;
}


/**
 Multiplication

 @param lhs entier >=0 représenté en notation décimale
 @param rhs entier >=0 représenté en notation décimale
 @param base entier entre 2 et 36

 @return produit des 2 entiers représenté en notation décimale
 */
string multiply(string lhs, string rhs, unsigned base) {
  assert(base >= 2 and base <= 36);
  assert(isValidPositiveInteger(lhs, base));
  assert(isValidPositiveInteger(rhs, base));

  string result;

  int i1Digit;
  int i2Digit;
  int carry = 0;
  int multiplicationDigit = 0;
  string multiplication;
  string zeros;

  // Parcourir premier nombre
  for (int i = (int)lhs.length() - 1; i >= 0; --i) {
    i1Digit = char2int(lhs[i]);
    carry = 0;
    multiplication = zeros;

    // Parcourir deuxième nombre et multiplier chaque digit
    for (int j = (int)rhs.length() - 1; j >= 0; --j) {
      i2Digit = char2int(rhs[j]);

      multiplicationDigit = (i1Digit * i2Digit) + carry;
      checkForCarry(multiplicationDigit, carry);

      multiplication = int2char(multiplicationDigit) + multiplication;
    }

    // Ajouter le dernier carry s'il y en a un
    if (carry != 0) {
      multiplication = int2char(carry) + multiplication;
    }

    zeros += ZERO; // Prochain chiffre -> ajouter un zéro au début du résultat intermédiaire
    result = add(result, multiplication, base);
  }

  return removeZeros(result);
}

/**
 Factorielle

 @param n entier >=0 représenté en notation décimale
 @param base entier entre 2 et 36

 @return n!, la factorielle de n représentée en notation décimale
 */
string factorial(string n, unsigned base) {
  assert(base >= 2 and base <= 36);
  assert(isValidPositiveInteger(n, base));

  string result = "1";
  string multiplier = "0";

  while (multiplier != n) {
    multiplier = add(multiplier, "1", base);
    result = multiply(multiplier, result, base);
  }

  return result;
}

/**
 Soustraction

 @param lhs entier >=0 représenté en notation décimale
 @param rhs entier >=0 représenté en notation décimale
 @param base entier entre 2 et 36

 @return différence (lhs - rhs) des 2 entiers représentée en notation décimale
 */
string subtract(string lhs, string rhs, unsigned base) {
  assert(base >= 2 and base <= 36);
  assert(isValidPositiveInteger(lhs, base));
  assert(isValidPositiveInteger(rhs, base));

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
  if (lhs.length() == rhs.length() and char2int(lhs[0]) <= char2int(rhs[0])) {
    for (int i = (int) lhs.length() - 1; i >= 0; --i) {
      if (char2int(lhs[i]) < char2int(rhs[i])) {
        swap(lhs, rhs);
        negative = true;
        break;
      }
    }
  }

  rhs = equaliseLength(lhs,rhs);

  int lhsLength = (int)lhs.length();
  for (int i = lhsLength - 1; i >= 0; --i) {
    int difference = char2int(lhs[i]) - char2int(rhs[i]);

    if (difference < 0) {
      lhs[i - 1] = int2char(char2int(lhs[i - 1]) - 1);
      difference += basis;
    }

    result = int2char(difference) + result;
  }

  if (negative) result = NEGATIVE_SIGN + result;

  return removeZeros(result);
}


/**
 Fonction principale

 @return Mise en oeuvre d'opérations arithmétiques simples
 (+,-,*) sur des entiers positifs longs représentés
 sous forme de chaines de caractères en notation
 décimale
 */
int main() {

  unsigned base;
  cout << "Entrez la base \n";
  cin >> basis;

  string i1, i2;
  cout << "Entrez deux entiers >= 0 en base " << basis << endl;
  cin >> i1 >> i2;

  cout << i1 << " + " << i2 << " = " << add(i1,i2,basis) << endl;
  cout << i1 << " * " << i2 << " = " << multiply(i1,i2,basis) << endl;
  cout << i1 << " - " << i2 << " = " << subtract(i1,i2,basis) << endl;

  string i3;
  cout << "\nEntrez un entier >= 0 en base " << basis << endl;
  cin >> i3;

  cout << "Factoriel(" << i3 << ") = " << factorial(i3,basis) << endl;

  return EXIT_SUCCESS;
}
