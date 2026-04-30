# VeriYapilari-Grup27

# Property Graph Tabanlı Sosyal Ağ Modelleme

## Proje Tanımı
Bu projede, sosyal ağ sistemlerinde kullanılan **property graph veri modeli** sadeleştirilmiş bir versiyon olarak geliştirilmektedir.  
- **Düğümler (Node):** Kullanıcı, Fotoğraf, Etkinlik vb.  
- **Kenarlar (Edge):** Arkadaşlık, Beğeni, Katılım vb. ilişkiler.  
- **Amaç:** Çok adımlı ilişkisel sorguları verimli veri yapıları ve algoritmalarla gerçekleştirmek.

---

## Faz 1 Gereksinimleri ve Uygunluk
- **Property Graph (Adjacency List):** Node ve Edge yapıları implemente edildi.  
- **Hash Table:** Benzersiz ID ile düğümlere O(1) erişim sağlandı.  
- **Trie:** `insertTrie` ve `searchTrie` fonksiyonları eklendi.  
- **Queue:** BFS için dinamik kuyruk yapısı implemente edildi.  
- **BFS & DFS:** Graf üzerinde traversal algoritmaları çalışıyor.  
- **Bellek Yönetimi:** `freeGraph` ve `freeQueue` ile bellek temizliği sağlandı.  

 Faz 1 eksiksiz tamamlandı.

---

## Hata ve Düzeltmeler
- Başlangıçta **Trie arama fonksiyonu eksikti** → `searchTrie` eklendi.  
- **Edge.date sabit “2026” idi** → sistem tarihine çevrildi.  
- **BFS visited dizisi sabit boyutlu idi** → dinamik hale getirildi.  
- **Queue temizliği karmaşıktı** → `freeQueue()` ile sadeleştirildi.  

---

- Gizem Yurtseven: Ara rapor dökümantasyonu, GitHub akış yönetimi ve kod analizi.
- Emir Yasin Akman: Çekirdek veri yapıları ve algoritma implementasyonu.
