#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trie-mtx.h"

Trie createTrie(int maxNode, int alphaSize) {
  Trie newTrie;
  //Allocation de la structure
  newTrie = (Trie) malloc(sizeof(struct _trie));
  if (newTrie == NULL) {
    return NULL;
  }

  //Allocation de la matrice
  newTrie->transition = (int **) malloc(maxNode * sizeof(int *));
  if (newTrie->transition == NULL) {
    return NULL;
  }
  for (int i = 0; i <= maxNode; i++) {
    newTrie->transition[i] = (int *) malloc(alphaSize * sizeof(int));
    if (newTrie->transition[i] == NULL) {
      return NULL;
    }
  }
  
  //Allocation du tableau des états finaux
  newTrie->finite = (char *) malloc(maxNode * sizeof(char));
  if (newTrie->finite == NULL) {
    return NULL;
  }
  newTrie->maxNode = maxNode;
  newTrie->nextNode = 1;
  for (int i = 0; i <= maxNode; i++) {
    for (int j = 0; j < alphaSize; j++) {
      newTrie->transition[i][j] = -1;
    }
    newTrie->finite[i] = 0;
  }
  return newTrie; //Retour du pointeur sur la structure.
}

/**
 * Insert un mot dans un trie.
 * @return L'état final du trie correspondant au mot
 */
int insertInTrie(Trie trie, char *w) {
  size_t length = strlen(w); //Longueure du mot
  int curState = 0; //On démarre de la racine
  for (int i = 0; i < length; i++) { //Pour toutes les lettres du mot
    int next = trie->transition[curState][(int) w[i]];
    if (next > -1) { //Si une transition existe de l'etat courant par la lettre
      curState = next; //On avance sur la branche
    } else { //Sinon
      //Affectation d'un nouveau noeud de l'etat courant par w[i]
      trie->transition[curState][(int) w[i]] = trie->nextNode;
      curState = trie->nextNode; //On avance sur le nouveau noeud
      trie->nextNode++;
    }
  }
  //On etait sur la derniere lettre
  trie->finite[curState] = 1; //On note le dernier état comme final
  if (!isInTrie(trie, w)) {
    fprintf(stderr, "[DEBUG] pas de mot dans le trie apres insert\n");
  }
  return curState;
}

int isInTrie(Trie trie, char *w) {
  size_t length = strlen( w);
  int curState = 0;
  for (int i = 0; i < length; i++) {
    int next = trie->transition[curState][(int) w[i]];
    if (next < 0) {
      return 0;
    } else {
      curState = next;
    }
  }
  return trie->finite[curState];
}
