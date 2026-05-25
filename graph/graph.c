#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "graph.h"
#include "../queue/queue.h"

// Geliştirilmiş İlişki Ekleme Fonksiyonu (Otomatik Çift Yön Desteği)
void addEdge(HashTable* ht, int src, int dest, char* relation) {
    Node* source = getNode(ht, src);
    Node* destination = getNode(ht, dest);

    if (!source || !destination) return;

    // Veri tekrarını önleme kontrolü (Aynı ilişki zaten var mı?)
    Edge* check = source->edges;
    while (check != NULL) {
        if (check->target_id == dest && strcmp(check->relation, relation) == 0) {
            return; // Zaten ekli, tekrar ekleme
        }
        check = check->next;
    }

    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    if (!newEdge) return;

    newEdge->target_id = dest;
    strcpy(newEdge->relation, relation);

    // Sistem tarihini ekle
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(newEdge->date, sizeof(newEdge->date), "%02d-%02d-%04d",
             tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    newEdge->next = source->edges;
    source->edges = newEdge;

    // KESİN ÇÖZÜM: Eğer ilişki FRIEND (Arkadaşlık) ise otomatik olarak tersini de ekle (Yönsüz Graf Mantığı)
    if (strcmp(relation, "FRIEND") == 0) {
        Edge* backCheck = destination->edges;
        int hasBackEdge = 0;
        while (backCheck != NULL) {
            if (backCheck->target_id == src && strcmp(backCheck->relation, "FRIEND") == 0) {
                hasBackEdge = 1;
                break;
            }
            backCheck = backCheck->next;
        }
        if (!hasBackEdge) {
            Edge* backEdge = (Edge*)malloc(sizeof(Edge));
            if (backEdge) {
                backEdge->target_id = src;
                strcpy(backEdge->relation, "FRIEND");
                strcpy(backEdge->date, newEdge->date);
                backEdge->next = destination->edges;
                destination->edges = backEdge;
            }
        }
    }
}

// ---------- BFS (Genişlik Öncelikli Arama) ----------
void BFS(HashTable* ht, int start_id) {
    int* visited = (int*)calloc(TABLE_SIZE, sizeof(int));
    if (!visited) return;

    Queue* q = createQueue();
    Node* startNode = getNode(ht, start_id);

    if (!startNode) {
        freeQueue(q);
        free(visited);
        return;
    }

    enqueue(q, startNode);
    visited[hash(start_id)] = 1;

    printf("Dugum %d uzerinden BFS baslatiliyor:\n", start_id);

    while (!isEmpty(q)) {
        Node* current = dequeue(q);
        printf("Ziyaret Edilen Dugum: %d (Tur: %s)\n", current->id, current->type);

        Edge* edge = current->edges;
        while (edge != NULL) {
            if (!visited[hash(edge->target_id)]) {
                Node* neighbor = getNode(ht, edge->target_id);
                if (neighbor) {
                    visited[hash(edge->target_id)] = 1;
                    enqueue(q, neighbor);
                }
            }
            edge = edge->next;
        }
    }

    freeQueue(q);
    free(visited);
}

// Filtrelenmiş BFS Algoritması
void filteredBFS(HashTable* ht, int start_id, const char* relation_filter) {
    int* visited = (int*)calloc(TABLE_SIZE, sizeof(int));
    if (!visited) return;

    Queue* q = createQueue();
    Node* startNode = getNode(ht, start_id);

    if (!startNode) {
        freeQueue(q);
        free(visited);
        return;
    }

    enqueue(q, startNode);
    visited[hash(start_id)] = 1;

    printf("Dugum %d uzerinden Filtrelenmis BFS baslatiliyor (Filtre: '%s'):\n", start_id, relation_filter);

    while (!isEmpty(q)) {
        Node* current = dequeue(q);
        printf("Ziyaret Edilen Dugum: %d (Tur: %s)\n", current->id, current->type);

        Edge* edge = current->edges;
        while (edge != NULL) {
            if (strcmp(edge->relation, relation_filter) == 0) {
                if (!visited[hash(edge->target_id)]) {
                    Node* neighbor = getNode(ht, edge->target_id);
                    if (neighbor) {
                        visited[hash(edge->target_id)] = 1;
                        enqueue(q, neighbor);
                    }
                }
            }
            edge = edge->next;
        }
    }
    freeQueue(q);
    free(visited);
}

// İki düğüm arasında bağlantı var mı kontrolü
static int areConnected(HashTable* ht, int src_id, int dest_id) {
    Node* src = getNode(ht, src_id);
    if (!src) return 0;

    Edge* edge = src->edges;
    while (edge != NULL) {
        if (edge->target_id == dest_id)
            return 1;
        edge = edge->next;
    }
    return 0;
}

// DFS Yardımcı Fonksiyonu
static void dfsUtil(HashTable* ht, Node* node, int* visited) {
    if (!node || !visited) return;

    printf("Ziyaret Edilen Dugum: %d (Tur: %s)\n", node->id, node->type);
    visited[hash(node->id)] = 1;

    Edge* edge = node->edges;
    while (edge != NULL) {
        Node* neighbor = getNode(ht, edge->target_id);
        if (neighbor && !visited[hash(neighbor->id)]) {
            dfsUtil(ht, neighbor, visited);
        }
        edge = edge->next;
    }
}

// ---------- DFS (Derinlik Öncelikli Arama) ----------
void DFS(HashTable* ht, int start_id) {
    int* visited = (int*)calloc(TABLE_SIZE, sizeof(int));
    if (!visited) return;

    Node* startNode = getNode(ht, start_id);
    if (!startNode) {
        free(visited);
        return;
    }

    printf("Dugum %d uzerinden DFS baslatiliyor:\n", start_id);
    dfsUtil(ht, startNode, visited);

    free(visited);
}

typedef struct {
    int node_id;
    int mutual_count;
} Recommendation;

// Arkadaş Önerisi Algoritması (Ortak Arkadaş Sayısına Göre)
void recommendFriends(HashTable* ht, int node_id, int minMutualFriends) {
    Node* node = getNode(ht, node_id);
    if (!node) return;

    Recommendation recommendations[TABLE_SIZE];
    int recCount = 0;

    Edge* edge = node->edges;
    while (edge != NULL) {
        Node* friendNode = getNode(ht, edge->target_id);
        if (friendNode) {
            Edge* fofEdge = friendNode->edges;
            while (fofEdge != NULL) {
                int candidateId = fofEdge->target_id;
                Node* candidateNode = getNode(ht, candidateId);
                if (!candidateNode || strcmp(candidateNode->type, "User") != 0) {
                    fofEdge = fofEdge->next;
                    continue;
                }

                if (candidateId != node_id && !areConnected(ht, node_id, candidateId)) {
                    int found = 0;
                    for (int i = 0; i < recCount; i++) {
                        if (recommendations[i].node_id == candidateId) {
                            recommendations[i].mutual_count += 1;
                            found = 1;
                            break;
                        }
                    }
                    if (!found && recCount < TABLE_SIZE) {
                        recommendations[recCount].node_id = candidateId;
                        recommendations[recCount].mutual_count = 1;
                        recCount++;
                    }
                }
                fofEdge = fofEdge->next;
            }
        }
        edge = edge->next;
    }

    printf("Dugum %d icin arkadas onerileri:\n", node_id);
    if (recCount == 0) {
        printf("  Ortak arkadasa sahip oneri bulunamadi.\n");
        return;
    }

    for (int i = 0; i < recCount; i++) {
        if (recommendations[i].mutual_count >= minMutualFriends) {
            Node* candidate = getNode(ht, recommendations[i].node_id);
            char* name = candidate ? getProperty(candidate->properties, "name") : NULL;
            if (name) {
                printf("  - Dugum %d (%s): %d ortak arkadas\n",
                       recommendations[i].node_id,
                       name,
                       recommendations[i].mutual_count);
            } else {
                printf("  - Dugum %d: %d ortak arkadas\n",
                       recommendations[i].node_id,
                       recommendations[i].mutual_count);
            }
        }
    }
}

// Giriş bağlantılarını sayma fonksiyonu
static int countIncomingEdges(HashTable* ht, int node_id) {
    int count = 0;
    if (!ht) return count;

    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* temp = ht->table[i];
        while (temp != NULL) {
            Edge* edge = temp->edges;
            while (edge != NULL) {
                if (edge->target_id == node_id) {
                    count++;
                }
                edge = edge->next;
            }
            temp = temp->next;
        }
    }
    return count;
}

// Derece Merkeziliği (Popülerlik) Hesaplama
int getDegreeCentrality(HashTable* ht, int node_id) {
    Node* node = getNode(ht, node_id);
    if (!node) return -1;

    int outDegree = 0;
    Edge* edge = node->edges;
    while (edge != NULL) {
        outDegree++;
        edge = edge->next;
    }

    int inDegree = countIncomingEdges(ht, node_id);
    return outDegree + inDegree;
}

// Tüm düğümlerin popülerlik derecesini yazdırma
void printNodeCentrality(HashTable* ht) {
    if (!ht) return;

    printf("\nDugum onem dereceleri (Derece Merkeziligi):\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = ht->table[i];
        while (current != NULL) {
            int centrality = getDegreeCentrality(ht, current->id);
            char* name = getProperty(current->properties, "name");
            if (name) {
                printf("  - Dugum %d (%s) [Tur: %s]: Derece merkeziligi = %d\n",
                       current->id,
                       name,
                       current->type,
                       centrality);
            } else {
                printf("  - Dugum %d [Tur: %s]: Derece merkeziligi = %d\n",
                       current->id,
                       current->type,
                       centrality);
            }
            current = current->next;
        }
    }
}

// Faz 2: Çok Adımlı Sorgu (Kullanıcı -> Arkadaşlar -> Etkinlikler -> Fotoğraflar)
void findPhotosOfFriendsEvents(HashTable* ht, int start_user_id) {
    Node* startUser = getNode(ht, start_user_id);
    if (!startUser) {
        printf("Hata: Baslangic kullanicisi (ID: %d) bulunamadi.\n", start_user_id);
        return;
    }

    char* userName = getProperty(startUser->properties, "name");
    if (!userName) {
        printf("Hata: Baslangic kullanici adi bulunamadi.\n");
        return;
    }

    printf("\n[Cok Adimli Sorgu]: Cok adimli arama basladi.\n");
    printf("Baslangic: %s (ID: %d, Tur: %s)\n\n", userName, start_user_id, startUser->type);

    Edge* friendEdge = startUser->edges;
    while (friendEdge != NULL) {
        if (strcmp(friendEdge->relation, "FRIEND") == 0) {
            Node* friendNode = getNode(ht, friendEdge->target_id);
            if (friendNode && strcmp(friendNode->type, "User") == 0) {
                char* friendName = getProperty(friendNode->properties, "name");
                if (friendName) {
                    printf("%s -(FRIEND)-> Arkadasi: %s", userName, friendName);
                    printf(" (Baglanti Tarihi: %s)\n", friendEdge->date);

                    Edge* attendsEdge = friendNode->edges;
                    while (attendsEdge != NULL) {
                        if (strcmp(attendsEdge->relation, "ATTENDS") == 0) {
                            Node* eventNode = getNode(ht, attendsEdge->target_id);
                            if (eventNode && strcmp(eventNode->type, "Event") == 0) {
                                char* eventName = getProperty(eventNode->properties, "name");
                                if (eventName) {
                                    printf("    -(ATTENDS)-> Etkinlik: %s", eventName);
                                    printf(" (Katilim Tarihi: %s)\n", attendsEdge->date);

                                    Edge* photoEdge = eventNode->edges;
                                    while (photoEdge != NULL) {
                                        if (strcmp(photoEdge->relation, "HAS_PHOTO") == 0) {
                                            Node* photoNode = getNode(ht, photoEdge->target_id);
                                            if (photoNode && strcmp(photoNode->type, "Photo") == 0) {
                                                char* photoName = getProperty(photoNode->properties, "name");
                                                if (photoName) {
                                                    printf("        -(HAS_PHOTO)-> Fotograf: %s", photoName);
                                                    printf(" (Kayit Tarihi: %s)\n", photoEdge->date);
                                                }
                                            }
                                        }
                                        photoEdge = photoEdge->next;
                                    }
                                }
                            }
                        }
                        attendsEdge = attendsEdge->next;
                    }
                }
            }
        }
        friendEdge = friendEdge->next;
    }
    printf("\n[Cok Adimli Sorgu]: Sorgu tamamlandi.\n\n");
}

// Rastgele Sentetik Veri Üretici ve Stress Testi Analizi
void generateSyntheticData(HashTable* ht, int userCount, int eventCount, int photoCount, int edgeCount) {
    char* userNames[] = {"Mert", "Asiye", "Doruk", "Melis", "Volkan", "Ceren", "Oguz", "Dilek", "Arda", "Begum", "Kaan", "Sude"};
    char* eventNames[] = {"Yapay Zeka Hackathonu", "Siber Guvenlik Zirvesi", "C Programlama Kampi", "Veri Bilimi Semineri"};
    char* photoNames[] = {"profil_resmi.jpg", "kod_ekrani.png", "etkinlik_hatirasi.jpg", "kampus_hayati.png"};

    int userPoolSize = sizeof(userNames) / sizeof(userNames[0]);
    int eventPoolSize = sizeof(eventNames) / sizeof(eventNames[0]);
    int photoPoolSize = sizeof(photoNames) / sizeof(photoNames[0]);

    int startId = 100;
    int currentId = startId;

    for (int i = 0; i < userCount; i++) {
        Node* newUser = (Node*)malloc(sizeof(Node));
        newUser->id = currentId;
        strcpy(newUser->type, "User");
        newUser->edges = NULL;
        newUser->properties = NULL;
        char customName[50];
        snprintf(customName, sizeof(customName), "%s_%d", userNames[rand() % userPoolSize], currentId);
        addProperty(&newUser->properties, "name", customName);
        insertNode(ht, newUser);
        currentId++;
    }

    for (int i = 0; i < eventCount; i++) {
        Node* newEvent = (Node*)malloc(sizeof(Node));
        newEvent->id = currentId;
        strcpy(newEvent->type, "Event");
        newEvent->edges = NULL;
        newEvent->properties = NULL;
        char customEvent[100];
        snprintf(customEvent, sizeof(customEvent), "%s (%d)", eventNames[rand() % eventPoolSize], currentId);
        addProperty(&newEvent->properties, "name", customEvent);
        insertNode(ht, newEvent);
        currentId++;
    }

    for (int i = 0; i < photoCount; i++) {
        Node* newPhoto = (Node*)malloc(sizeof(Node));
        newPhoto->id = currentId;
        strcpy(newPhoto->type, "Photo");
        newPhoto->edges = NULL;
        newPhoto->properties = NULL;
        char customPhoto[50];
        snprintf(customPhoto, sizeof(customPhoto), "%s_id_%d", photoNames[rand() % photoPoolSize], currentId);
        addProperty(&newPhoto->properties, "name", customPhoto);
        insertNode(ht, newPhoto);
        currentId++;
    }

    int totalNodesCreated = userCount + eventCount + photoCount;
    int edgesAdded = 0;

    for (int eId = startId + userCount; eId < startId + userCount + eventCount; eId++) {
        int randomUserId = startId + (rand() % userCount);
        addEdge(ht, randomUserId, eId, "ATTENDS");
        edgesAdded++;
    }

    for (int pId = startId + userCount + eventCount; pId < startId + totalNodesCreated; pId++) {
        int randomEventId = startId + userCount + (rand() % eventCount);
        addEdge(ht, randomEventId, pId, "HAS_PHOTO");
        edgesAdded++;
    }

    int maxAttempts = edgeCount * 5;
    int attempts = 0;

    while (edgesAdded < edgeCount && attempts < maxAttempts) {
        attempts++;
        int srcId = startId + (rand() % totalNodesCreated);
        int destId = startId + (rand() % totalNodesCreated);

        if (srcId == destId) continue;

        Node* srcNode = getNode(ht, srcId);
        Node* destNode = getNode(ht, destId);

        if (!srcNode || !destNode) continue;

        if (strcmp(srcNode->type, "User") == 0 && strcmp(destNode->type, "User") == 0) {
            addEdge(ht, srcId, destId, "FRIEND");
            edgesAdded++;
        } 
        else if (strcmp(srcNode->type, "User") == 0 && strcmp(destNode->type, "Event") == 0) {
            addEdge(ht, srcId, destId, "ATTENDS");
            edgesAdded++;
        } 
        else if (strcmp(srcNode->type, "Event") == 0 && strcmp(destNode->type, "Photo") == 0) {
            addEdge(ht, srcId, destId, "HAS_PHOTO");
            edgesAdded++;
        }
        else if (strcmp(srcNode->type, "User") == 0 && strcmp(destNode->type, "Photo") == 0) {
            addEdge(ht, srcId, destId, "LIKES");
            edgesAdded++;
        }
    }

    clock_t start = clock();
    for (int id = startId; id < currentId; id++) {
        getDegreeCentrality(ht, id);
    }
    clock_t end = clock();
    double timeSpent = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

    printf("\n==================================================\n");
    printf("DINAMIK SENTETIK VERI ENJEKSIYONU VE PERFORMANS RAPORU\n");
    printf("==================================================\n");
    printf("Uretilen Kullanici (User) Sayisi : %d\n", userCount);
    printf("Uretilen Etkinlik (Event) Sayisi : %d\n", eventCount);
    printf("Uretilen Fotograf (Photo) Sayisi : %d\n", photoCount);
    printf("Graf Yapisina Eklenen Yeni Kenar  : %d\n", edgesAdded);
    printf("Toplam Canli Sentetik Dugum      : %d\n", totalNodesCreated);
    printf("Algoritma Stress Analiz Suresi   : %.4f ms\n", timeSpent);
    printf("==================================================\n");
}

// Faz 3: Graf Verilerini JSON Olarak Dışa Aktarma
void exportGraphToJSON(HashTable* ht, const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        printf("Hata: JSON dosyasi olusturulamadi!\n");
        return;
    }

    fprintf(fp, "{\n  \"nodes\": [\n");
    int firstNode = 1;

    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = ht->table[i];
        while (current != NULL) {
            if (!firstNode) fprintf(fp, ",\n");
            char* name = getProperty(current->properties, "name");
            char safeName[100] = "Unknown";
            if (name) snprintf(safeName, sizeof(safeName), "%s", name);

            fprintf(fp, "    {\"id\": %d, \"label\": \"%s\", \"group\": \"%s\"}", 
                    current->id, safeName, current->type);
            firstNode = 0;
            current = current->next;
        }
    }
    fprintf(fp, "\n  ],\n  \"edges\": [\n");

    int firstEdge = 1;
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = ht->table[i];
        while (current != NULL) {
            Edge* edge = current->edges;
            while (edge != NULL) {
                if (!firstEdge) fprintf(fp, ",\n");
                fprintf(fp, "    {\"from\": %d, \"to\": %d, \"label\": \"%s\", \"date\": \"%s\"}", 
                        current->id, edge->target_id, edge->relation, edge->date);
                firstEdge = 0;
                edge = edge->next;
            }
            current = current->next;
        }
    }
    fprintf(fp, "\n  ]\n}\n");
    fclose(fp);
    printf("\n>>> Basarili: Graf verileri '%s' dosyasina aktarildi.\n", filename);
}

// Graf Bellek Temizliği
void freeGraph(HashTable* ht) {
    if (!ht) return;
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = ht->table[i];
        while (current != NULL) {
            Node* nextNode = current->next;
            Property* prop = current->properties;
            while (prop != NULL) {
                Property* nextProp = prop->next;
                free(prop);
                prop = nextProp;
            }
            Edge* edge = current->edges;
            while (edge != NULL) {
                Edge* nextEdge = edge->next;
                free(edge);
                edge = nextEdge;
            }
            free(current);
            current = nextNode;
        }
        ht->table[i] = NULL;
    }
}

void generateSyntheticData(HashTable* ht, int userCount, int eventCount, int photoCount, int edgeCount) {
    char* userNames[] = {"Mert", "Asiye", "Doruk", "Melis", "Volkan", "Ceren", "Oguz", "Dilek", "Arda", "Begum", "Kaan", "Sude"};
    char* eventNames[] = {"Yapay Zeka Hackathonu", "Siber Guvenlik Zirvesi", "C Programlama Kampi", "Veri Bilimi Semineri"};
    char* photoNames[] = {"profil_resmi.jpg", "kod_ekrani.png", "etkinlik_hatirasi.jpg", "kampus_hayati.png"};

    int userPoolSize = sizeof(userNames) / sizeof(userNames[0]);
    int eventPoolSize = sizeof(eventNames) / sizeof(eventNames[0]);
    int photoPoolSize = sizeof(photoNames) / sizeof(photoNames[0]);

    int startId = 100;
    int currentId = startId;

    // 1. Programatik Dugum Uretimi (Havuzdan rastgele isim atayarak)
    for (int i = 0; i < userCount; i++) {
        Node* newUser = (Node*)malloc(sizeof(Node));
        newUser->id = currentId;
        strcpy(newUser->type, "User");
        newUser->edges = NULL;
        newUser->properties = NULL;
        
        char customName[50];
        snprintf(customName, sizeof(customName), "%s_%d", userNames[rand() % userPoolSize], currentId);
        addProperty(&newUser->properties, "name", customName);
        
        insertNode(ht, newUser);
        currentId++;
    }

    for (int i = 0; i < eventCount; i++) {
        Node* newEvent = (Node*)malloc(sizeof(Node));
        newEvent->id = currentId;
        strcpy(newEvent->type, "Event");
        newEvent->edges = NULL;
        newEvent->properties = NULL;
        
        char customEvent[100];
        snprintf(customEvent, sizeof(customEvent), "%s (%d)", eventNames[rand() % eventPoolSize], currentId);
        addProperty(&newEvent->properties, "name", customEvent);
        
        insertNode(ht, newEvent);
        currentId++;
    }

    for (int i = 0; i < photoCount; i++) {
        Node* newPhoto = (Node*)malloc(sizeof(Node));
        newPhoto->id = currentId;
        strcpy(newPhoto->type, "Photo");
        newPhoto->edges = NULL;
        newPhoto->properties = NULL;
        
        char customPhoto[50];
        snprintf(customPhoto, sizeof(customPhoto), "%s_id_%d", photoNames[rand() % photoPoolSize], currentId);
        addProperty(&newPhoto->properties, "name", customPhoto);
        
        insertNode(ht, newPhoto);
        currentId++;
    }

    int totalNodesCreated = userCount + eventCount + photoCount;

    // 2. Programatik ve Akilli Kenar (Ilişki) Uretimi
    int edgesAdded = 0;
    
    // 2a. Her etkinliğe en az 1 rastgele kullanıcı katılsın (ATTENDS)
    for (int eId = startId + userCount; eId < startId + userCount + eventCount; eId++) {
        int randomUserId = startId + (rand() % userCount);
        addEdge(ht, randomUserId, eId, "ATTENDS");
        edgesAdded++;
    }

    // 2b. Her fotoğraf en az 1 rastgele etkinliğe ait olsun (HAS_PHOTO)
    for (int pId = startId + userCount + eventCount; pId < startId + totalNodesCreated; pId++) {
        int randomEventId = startId + userCount + (rand() % eventCount);
        addEdge(ht, randomEventId, pId, "HAS_PHOTO");
        edgesAdded++;
    }
    int maxAttempts = edgeCount * 5;
    int attempts = 0;

    while (edgesAdded < edgeCount && attempts < maxAttempts) {
        attempts++;
        int srcId = startId + (rand() % totalNodesCreated);
        int destId = startId + (rand() % totalNodesCreated);

        if (srcId == destId) continue;

        Node* srcNode = getNode(ht, srcId);
        Node* destNode = getNode(ht, destId);

        if (!srcNode || !destNode) continue;

        // Mantiksal Graf Topolojisi Kontrolu
        if (strcmp(srcNode->type, "User") == 0 && strcmp(destNode->type, "User") == 0) {
            addEdge(ht, srcId, destId, "FRIEND");
            edgesAdded++;
        } 
        else if (strcmp(srcNode->type, "User") == 0 && strcmp(destNode->type, "Event") == 0) {
            addEdge(ht, srcId, destId, "ATTENDS");
            edgesAdded++;
        } 
        else if (strcmp(srcNode->type, "Event") == 0 && strcmp(destNode->type, "Photo") == 0) {
            addEdge(ht, srcId, destId, "HAS_PHOTO");
            edgesAdded++;
        }
        else if (strcmp(srcNode->type, "User") == 0 && strcmp(destNode->type, "Photo") == 0) {
            addEdge(ht, srcId, destId, "LIKES");
            edgesAdded++;
        }
    }

    // 3. Performans ve Stress Testi Olcumu
    clock_t start = clock();
    for (int id = startId; id < currentId; id++) {
        getDegreeCentrality(ht, id);
    }
    clock_t end = clock();
    double timeSpent = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

    // Sonuclarin Terminal Raporu Olarak Basilmasi
    printf("\n==================================================\n");
    printf("DINAMIK SENTETIK VERI ENJEKSIYONU VE PERFORMANS RAPORU\n");
    printf("==================================================\n");
    printf("Uretilen Kullanici (User) Sayisi : %d\n", userCount);
    printf("Uretilen Etkinlik (Event) Sayisi : %d\n", eventCount);
    printf("Uretilen Fotograf (Photo) Sayisi : %d\n", photoCount);
    printf("Graf Yapisina Eklenen Yeni Kenar  : %d\n", edgesAdded);
    printf("Toplam Canli Sentetik Dugum      : %d\n", totalNodesCreated);
    printf("Algoritma Stress Analiz Suresi   : %.4f ms\n", timeSpent);
    printf("==================================================\n");
}

// JSON Dişa Aktarma Fonksiyonu - Faz 3 İçin
void exportGraphToJSON(HashTable* ht, const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        printf("Hata: JSON dosyasi olusturulamadi!\n");
        return;
    }

    fprintf(fp, "{\n  \"nodes\": [\n");
    int firstNode = 1;

    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = ht->table[i];
        while (current != NULL) {
            if (!firstNode) fprintf(fp, ",\n");
            
            char* name = getProperty(current->properties, "name");
            char safeName[100] = "Unknown";
            if (name) {
                // Basit bir escape islemi (JSON kirilmamasi icin)
                snprintf(safeName, sizeof(safeName), "%s", name);
            }

            fprintf(fp, "    {\"id\": %d, \"label\": \"%s\", \"group\": \"%s\"}", 
                    current->id, safeName, current->type);
            
            firstNode = 0;
            current = current->next;
        }
    }
    fprintf(fp, "\n  ],\n  \"edges\": [\n");

    int firstEdge = 1;
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = ht->table[i];
        while (current != NULL) {
            Edge* edge = current->edges;
            while (edge != NULL) {
                if (!firstEdge) fprintf(fp, ",\n");
                
                fprintf(fp, "    {\"from\": %d, \"to\": %d, \"label\": \"%s\", \"date\": \"%s\"}", 
                        current->id, edge->target_id, edge->relation, edge->date);
                
                firstEdge = 0;
                edge = edge->next;
            }
            current = current->next;
        }
    }
    fprintf(fp, "\n  ]\n}\n");

    fclose(fp);
    printf("\n>>> Basarili: Graf verileri '%s' dosyasina aktarildi.\n", filename);
}
