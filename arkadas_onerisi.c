#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_USERS 100

// Basit bir graf yapısı için komşuluk matrisi (veya listesi kullanılabilir)
typedef struct {
    int numUsers;
    bool adjacencyMatrix[MAX_USERS][MAX_USERS];
    char* usernames[MAX_USERS];
} SocialGraph;

// İki kullanıcı arasında arkadaşlık (kenar) ekleme
void addFriendship(SocialGraph* graph, int user1, int user2) {
    graph->adjacencyMatrix[user1][user2] = true;
    graph->adjacencyMatrix[user2][user1] = true;
}

// İki kullanıcının zaten arkadaş olup olmadığını kontrol etme
bool isFriend(SocialGraph* graph, int user1, int user2) {
    return graph->adjacencyMatrix[user1][user2];
}

// Triadic Closure: Arkadaş önerisi algoritması
void suggestFriends(SocialGraph* graph, int userId) {
    int suggestions[MAX_USERS] = {0}; // Her kullanıcı için ortak arkadaş sayısını tutar
    bool foundAny = false;

    printf("\n--- %s icin Arkadas Onerileri ---\n", graph->usernames[userId]);

    // 1. Adım: Kullanıcının arkadaşlarına (B) bak
    for (int b = 0; b < graph->numUsers; b++) {
        if (isFriend(graph, userId, b)) {
            
            // 2. Adım: Arkadaşının arkadaşlarına (C) bak
            for (int c = 0; c < graph->numUsers; c++) {
                // Öneri kriterleri:
                // - C, kullanıcının kendisi olmamalı
                // - C, kullanıcının zaten arkadaşı olmamalı
                // - B ve C arkadaş olmalı
                if (c != userId && !isFriend(graph, userId, c) && isFriend(graph, b, c)) {
                    suggestions[c]++;
                    foundAny = true;
                }
            }
        }
    }

    if (!foundAny) {
        printf("Su an icin yeni bir oneri bulunamadı.\n");
        return;
    }

    // Sonuçları yazdır (Ortak arkadaş sayısına göre)
    for (int i = 0; i < graph->numUsers; i++) {
        if (suggestions[i] > 0) {
            printf("Oneri: %s (%d ortak arkadas)\n", graph->usernames[i], suggestions[i]);
        }
    }
}

int main() {
    SocialGraph myNetwork = {0};
    myNetwork.numUsers = 5;

    // Kullanıcı isimlerini ata
    myNetwork.usernames[0] = "User_A";
    myNetwork.usernames[1] = "User_B";
    myNetwork.usernames[2] = "User_C";
    myNetwork.usernames[3] = "User_D";
    myNetwork.usernames[4] = "User_E";

    // Arkadaşlık ilişkilerini kur (Kenarlar)
    addFriendship(&myNetwork, 0, 1); // A - B arkadaş
    addFriendship(&myNetwork, 0, 2); // A - C arkadaş
    addFriendship(&myNetwork, 1, 3); // B - D arkadaş (D, A'ya önerilmeli)
    addFriendship(&myNetwork, 2, 3); // C - D arkadaş (D'nin A ile 2 ortak arkadaşı oldu)
    addFriendship(&myNetwork, 2, 4); // C - E arkadaş (E, A'ya önerilmeli)

    // A kullanıcısı için arkadaş önerilerini getir
    suggestFriends(&myNetwork, 0);

    return 0;
}