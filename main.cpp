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
const int A_UPPERCASE_INT_VALUE = 'A';
const int A_LOWERCASE_INT_VALUE = 'a';
const int A_INT_DIGIT_VALUE = 10;
unsigned base;

/**
 * conversion char en entier
 *
 * @param c charactere représentant un chiffre en base entre 2 et 36
 *
 * @return le nombre correspondant au chiffre en entrée si c est un chiffre
 * ou une lettre majuscule ou minuscule. Par exemple, char2int('D')
 * retournera 13.
 * retourne un nombre négatif (à choix) si c n'est pas un caractère
 * alphanumérique.
 */
int char2int(char c) {
  return c - (c >= A_UPPERCASE_INT_VALUE ? (
          c >= A_LOWERCASE_INT_VALUE ?
          A_LOWERCASE_INT_VALUE - A_INT_DIGIT_VALUE :
          A_UPPERCASE_INT_VALUE - A_INT_DIGIT_VALUE
          ) : ZERO_INT_VALUE);

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

 @param number une chaine de caracteres representant un nombre entier positif
 en base donne
 @param base   la base (entre 2 et 36)

 @return vrai si le nombre est valide, faux sinon.
 */
bool isValidPositiveInteger(string number) {
  bool isValid = true;

  for (char c : number) {
    if (char2int(c) >= (int)base or char2int(c) < 0) {
      isValid = false;
      break;
    }
  }

  return isValid;
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

  for (char i : value) {
    if(i != ZERO || building) {
      building = true;
      result += i;
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
  if (value >= (int)base) {
    carryContainer = value / (int)base;
    value -= carryContainer * (int)base;
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
string add(string lhs, string rhs) {

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

  return removeZeros(result);
}


/**
 Multiplication

 @param lhs entier >=0 représenté en notation décimale
 @param rhs entier >=0 représenté en notation décimale
 @param base entier entre 2 et 36

 @return produit des 2 entiers représenté en notation décimale
 */
string multiply(string lhs, string rhs) {

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

    // Prochain chiffre -> ajouter un zéro au début du résultat intermédiaire
    zeros += ZERO;
    result = add(result, multiplication);
  }

  return removeZeros(result);
}

/**
 Factorielle

 @param n entier >=0 représenté en notation décimale
 @param base entier entre 2 et 36

 @return n!, la factorielle de n représentée en notation décimale
 */
string factorial(string n) {

  string result = "1";
  string multiplier = "0";

  while (multiplier != n) {
    multiplier = add(multiplier, "1");
    result = multiply(multiplier, result);
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
  bool borrow = false;
  for (int i = lhsLength - 1; i >= 0; --i) {

    int leftNumber = char2int(lhs[i]);
    int rightNumber = char2int(rhs[i]);

    if (borrow) {
      leftNumber--;
      borrow = false;
    }

    int difference = leftNumber - rightNumber;
    if (difference < 0) {
      difference += base;
      borrow = true;
    }

    result = int2char(difference) + result;
  }

  result = removeZeros(result);
  if (negative) result = NEGATIVE_SIGN + result;

  return result;
}

void cleanCin() {
  if (cin.fail()) {
    std::cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
}

/**
 Fonction principale

 @return Mise en oeuvre d'opérations arithmétiques simples
 (+,-,*) sur des entiers positifs longs représentés
 sous forme de chaines de caractères en notation
 décimale
 */
int main() {

  const int MAX_BASE = 36;
  const int MIN_BASE = 2;

  do {
    cout << "Entrez la base \n";
    cin >> base;

    cleanCin();

  } while (base < MIN_BASE or base > MAX_BASE);

  string i1, i2;
  do {
    cout << "Entrez deux entiers >= 0 en base " << base << endl;
    cin >> i1 >> i2;

  } while (!isValidPositiveInteger(i1) or !isValidPositiveInteger(i2));

  cout << i1 << " + " << i2 << " = " << add(i1, i2) << endl;
  cout << i1 << " * " << i2 << " = " << multiply(i1, i2) << endl;
  cout << i1 << " - " << i2 << " = " << subtract(i1, i2) << endl;

  string i3;
  do {

    cout << "\nEntrez un entier >= 0 en base " << base << endl;
    cin >> i3;

    cleanCin();

  } while (!isValidPositiveInteger(i3));



  cout << "Factoriel(" << i3 << ") = " << factorial(i3) << endl;

  return EXIT_SUCCESS;
}
