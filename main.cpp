/* ---------------------------
 Laboratoire : 4
 Fichier : main.cpp
 Auteur(s) :
 Date : 01.11.2018

 But :         Mise en oeuvre d'opérations arithmétiques simples
 (+,-,*) sur des entiers positifs longs représentés
 sous forme de chaines de caractères en notation
 décimale

 Remarque(s) :

 Compilateur :
 --------------------------- */

#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

/**
 Addition

 @param lhs entier >=0 représenté en notation décimale
 @param rhs entier >=0 représenté en notation décimale

 @return somme des 2 entiers représentée en notation décimale
 */
string add(string lhs, string rhs) {
  string resultat;

  // A COMPLETER

  return resultat;
}


/**
 Multiplication

 @param lhs entier >=0 représenté en notation décimale
 @param rhs entier >=0 représenté en notation décimale

 @return produit des 2 entiers représenté en notation décimale
 */
string multiply(string lhs, string rhs) {
  string resultat;

  // A COMPLETER

  return resultat;
}

/**
 Factorielle

 @param n entier >=0

 @return n!, la factorielle de n représentée en notation décimale
 */
string factorial(int n) {
  string resultat;

  // A COMPLETER

  return resultat;
}

/**
 Soustraction

 @param lhs entier >=0 représenté en notation décimale
 @param rhs entier >=0 représenté en notation décimale

 @return différence (lhs - rhs) des 2 entiers représentée en notation décimale
 */
string subtract(string lhs, string rhs) {
  string resultat;

  // A COMPLETER

  return resultat;
}


/**
 Fonction principale

 @return Mise en oeuvre d'opérations arithmétiques simples
 (+,-,*) sur des entiers positifs longs représentés
 sous forme de chaines de caractères en notation
 décimale
 */
int main() {

  cout << "Entrez deux entiers >= 0 \n";
  string i1, i2;
  cin >> i1 >> i2;

  cout << i1 << " + " << i2 << " = " << add(i1,i2) << endl;
  cout << i1 << " * " << i2 << " = " << multiply(i1,i2) << endl;
  cout << i1 << " - " << i2 << " = " << subtract(i1,i2) << endl;

  cout << "\nEntrez un entier >= 0 \n";
  int i3;
  cin >> i3;
  cout << "Factoriel(" << i3 << ") = " << factorial(i3) << endl;

  return EXIT_SUCCESS;
}
