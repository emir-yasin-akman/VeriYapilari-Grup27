#ifndef TRIADIC_H
#define TRIADIC_H

#include "graph.h"

// verilen kullanıcı için arkadaş önerisi yapan fonksiyon
// (ortak arkadaşlara bakarak öneri üretir)
void suggest_friends(HashTable* ht, int user_id);

#endif