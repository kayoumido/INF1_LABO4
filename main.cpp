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

const int ZERO_INT_VALUE = '0';

/**
 * convertit un char en int
 * @param  c [char a convertir]
 * @return   [int convertit]
 */
int charToInt(char c) {
  return (int)c - ZERO_INT_VALUE;
}

/**
 * convertit un int en char
 * @param  c [int a convertir]
 * @return   [char convertit]
 */
char intToChar(int value) {
  return (char)(value + ZERO_INT_VALUE);
}


/**
 * Vérifie si le nombre produit un carry et met à jour les valeurs
 * @param value
 * @param carryContainer
 */
void checkForCarry(int& value, int& carryContainer) {
  if(value >= 10) {
    carryContainer = value / 10;
    value -= carryContainer * 10;
  }
}

/**
 Addition

 @param lhs entier >=0 représenté en notation décimale
 @param rhs entier >=0 représenté en notation décimale

 @return somme des 2 entiers représentée en notation décimale
 */
string add(string lhs, string rhs) {
  string resultat;

  // A COMPLETER
  
  //La taille de lhs doit être >= à celle de rhs
  if(lhs.length() < rhs.length()) {
    string temp = lhs;
    lhs = rhs;
    rhs = temp;
  }
  
  int lhsLength = lhs.length();
  int rhsLength = rhs.length();
  int addition;
  int carry = 0;
  int deltaLength = lhsLength - rhsLength;
  
  //Compenser la taille de rhs par des zéros au début
  for(int i = 0; i < deltaLength; ++i) {
    rhs = '0' + rhs;
  }
  
  for(int i = lhsLength - 1; i >= 0; --i) {
    int i1Digit = charToInt(lhs[i]);
    int i2Digit = charToInt(rhs[i]);
    
    addition = i1Digit + i2Digit + carry;
    carry = 0;
    checkForCarry(addition, carry);
    
    resultat = intToChar(addition) + resultat;
  }
  
  //Ajouter le dernier carry s'il y en a un
  if(carry != 0) {
    resultat = intToChar(carry) + resultat;    
  }
  
  //LORSQU'IL Y A UN DERNIER CARRY (DEJA PRIS DANS LA DERNIERE ADDITION) IL EST RAJOUTE ENCORE A LA FIN -> FAUX
  
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
  int i1Digit;
  int i2Digit;
  int carry = 0;
  int multiplicationDigit = 0;
  string multiplication;
  string zeros;
  
  //Parcourir premier nombre
  for(int i = lhs.length() - 1; i >= 0; --i) {
    i1Digit = charToInt(lhs[i]);
    carry = 0;
    multiplication = zeros;
    
    //Parcourir deuxième nombre et multiplier chaque digit
    for(int j = rhs.length() - 1; j >= 0; --j) {
      i2Digit = charToInt(rhs[j]);
            
      multiplicationDigit = (i1Digit * i2Digit) + carry;
      carry = 0;
      checkForCarry(multiplicationDigit, carry);
      
      multiplication = intToChar(multiplicationDigit) + multiplication;
    }
    
    //Ajouter le dernier carry s'il y en a un
    if(carry != 0) {
      multiplication = intToChar(carry) + multiplication;    
    }
    
    zeros += "0"; //Prochain chiffre -> ajouter un zéro au début du résultat intermédiaire    
    resultat = add(resultat, multiplication);    
    
    //cout << endl << multiplication + (i > 0 ? " + " : " = ") << endl; //TEST
    
  }
  
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
  bool negative = false;

  // check if left hand side value is smaller thant the right one
  if (lhs.length() < rhs.length()) {
    string tmp = lhs;
    lhs = rhs;
    rhs = tmp;
    negative = true;
  }

  if (lhs.length() == rhs.length() and charToInt(lhs[0]) < charToInt(rhs[0])) {
    for (int i = (int)lhs.length() - 1; i >= 0; --i) {
      if (charToInt(lhs[i]) < charToInt(rhs[i])) {
        string tmp = lhs;
        lhs = rhs;
        rhs = tmp;
        negative = true;
        break;
      }
    }
  }

  int size_difference = (int)lhs.length() - (int)rhs.length();

  // add 0 at the beginning of the rhs
  // so we have two numbers with the same length
  for (int i = 0; i < size_difference; ++i) {
    rhs = "0" + rhs;
  }

  /**
   * for each character (right to left):
    difference = N1.digit[i] - N2.digit[i];
    if (difference < 0)
        N1.digit[i - 1]--;
        difference += 10;
    N3.digit[i] = difference;
   */
  for (int i = (int)lhs.length() - 1; i >= 0; --i) {

    int difference = charToInt(lhs[i]) - charToInt(rhs[i]);

    if (difference < 0) {
      lhs[i - 1] = intToChar( charToInt(lhs[i - 1]) - 1 );
      difference += 10;
    }

    resultat = intToChar(difference) + resultat;
  }

  if (negative) resultat = "-" + resultat;

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

/*
 * 100 - 120
 * 0 - 0 = 0
 * 0 - 2 = -2
 * 1 - 1 = 0
 *
 * 10 - 120
 * 0 - 0 = 0
 * 1 - 2 = 1
 * 0 - 1 = -1
 * 010
 */