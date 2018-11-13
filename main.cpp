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

  // A COMPLETER

  return -1;
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

  string res;

  // A COMPLETER

  return res;
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

  string res;

  // A COMPLETER

  return res;

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

  string res;

  // A COMPLETER

  return res;
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

  string res;

  // A COMPLETER

  return res;
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
  cin >> base;

  string i1, i2;
  cout << "Entrez deux entiers >= 0 en base " << base << endl;
  cin >> i1 >> i2;

  cout << i1 << " + " << i2 << " = " << add(i1,i2,base) << endl;
  cout << i1 << " * " << i2 << " = " << multiply(i1,i2,base) << endl;
  cout << i1 << " - " << i2 << " = " << subtract(i1,i2,base) << endl;

  string i3;
  cout << "\nEntrez un entier >= 0 en base " << base << endl;
  cin >> i3;

  cout << "Factoriel(" << i3 << ") = " << factorial(i3,base) << endl;

  return EXIT_SUCCESS;
}
