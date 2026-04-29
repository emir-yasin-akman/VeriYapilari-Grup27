#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "triadic.h"

// ortak arkadaşlara bakarak arkadaş önerisi yapar
void suggest_friends(HashTable* ht, int user_id) {

    int scores[TABLE_SIZE] = {0};   // önerilen kişiler için skor (kaç ortak arkadaş var)
    int visited[TABLE_SIZE] = {0};  // daha önce aday olarak işaretlendi mi

    Node* user = getNode(ht, user_id);
    if (!user) {
        printf("Kullanici bulunamadi\n");
        return;
    }

    Edge* e = user->edges;

    // kullanıcının arkadaşlarını dolaş
    while (e) {
        if (strcmp(e->relation, "FRIEND") == 0) {

            Node* friend = getNode(ht, e->target_id);
            if (!friend) {
                e = e->next;
                continue;
            }

            Edge* fof = friend->edges; // arkadaşın arkadaşları

            // arkadaşın arkadaşlarını dolaş
            while (fof) {
                if (strcmp(fof->relation, "FRIEND") == 0) {

                    int candidate = fof->target_id;

                    // kendisi değilse ve zaten arkadaş değilse
                    if (candidate != user_id &&
                        !is_friend(ht, user_id, candidate)) {

                        scores[candidate]++;   // ortak arkadaş sayısını artır
                        visited[candidate] = 1; // bu kullanıcıyı aday olarak işaretle
                    }
                }
                fof = fof->next;
            }
        }
        e = e->next;
    }

    printf("%d icin arkadaş onerileri:\n", user_id);

    int found = 0;

    // önerileri yazdır
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (visited[i]) {
            printf("Kullanici %d (ortak arkadas sayisi: %d)\n", i, scores[i]);
            found = 1;
        }
    }

    // hiç öneri yoksa
    if (!found) {
        printf("Hic oneri bulunamadi\n");
    }
}