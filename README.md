# Property Graph Tabanlı Sosyal Ağ Modelleme

Bu proje, sosyal ağ sistemlerinde kullanılan "Property Graph" (Özellikli Graf) veri modelinin C programlama dili kullanılarak sıfırdan implemente edilmiş bir versiyonudur. Projenin temel amacı; ağ üzerindeki farklı varlık türleri (Kullanıcı, Fotoğraf, Etkinlik) ve bu varlıkların birbirleriyle olan ilişkileri (Arkadaşlık, Katılım, Beğeni) arasında verimli veri yapıları kullanılarak karmaşık, çok adımlı sorguların ve analitik ölçümlerin gerçekleştirilmesidir.

---

## 1. Proje Mimarisi ve Temel Veri Yapıları

Proje kapsamında, harici bir kütüphane kullanılmaksızın aşağıdaki temel yapılar dinamik bellek yönetimiyle kurulmuştur:

* **Property Graph (Komşuluk Listesi):** Farklı türdeki düğümleri (User, Photo, Event) ve özel niteliklere (tarih bilgisi, ilişki türü) sahip kenarları (FRIEND, LIKES, ATTENDS, HAS_PHOTO) zincirleme yöntemiyle destekler.
* **Karma Tablo (Hash Table):** Çakışmaları zincirleme (chaining) yöntemiyle çözen ve düğümlere benzersiz ID'ler üzerinden ortalama O(1) sürede erişim sağlayan merkezi indeksleme yapısıdır.
* **Trie (Önek Ağacı):** Metin tabanlı arama, kullanıcı adı önek doğrulama ve otomatik tamamlama işlemleri için graf yapısına entegre edilmiştir.
* **Kuyruk (Queue):** BFS algoritmasının ve katmanlı taramaların bellek sızıntısı olmadan çalışması için dinamik bir kuyruk mekanizması içerir.

---

## 2. Gerçekleştirilen Fazlar ve Teknik Özellikler

### Faz 1: Temel Graf ve Metin Arama Motoru
* **Dinamik Tarama Algoritmaları:** Graf yapısı üzerinde tarama gerçekleştiren BFS (Genişlik Öncelikli Arama) ve DFS (Derinlik Öncelikli Arama) algoritmaları entegre edilmiştir.
* **Filtrelenmiş Arama:** Graf üzerinde sadece belirli ilişki türlerini (örneğin sadece ATTENDS ilişkilerini) izleyen filteredBFS fonksiyonu eklenmiştir.
* **Trie Doğrulama:** Metin tabanlı arama süreçleri optimize edilerek searchTrie mekanizması sisteme dahil edilmiştir.

### Faz 2: Gelişmiş Algoritma ve Çok Adımlı Sorgu Modeli
* **Çok Adımlı Graf Traversal (Multi-step Query):** Bir kullanıcının arkadaşlarını, o arkadaşların katıldığı etkinlikleri ve o etkinliklerde çekilen fotoğrafları ardışık olarak listeleyen hiyerarşik sorgu motoru (findPhotosOfFriendsEvents) implemente edilmiştir.
* **Triadic Closure (Arkadaş Önerisi):** Ortak arkadaş sayılarını analiz ederek, aralarında doğrudan bağ olmayan kullanıcılara minimum ortak arkadaş eşiğine göre akıllı arkadaş önerileri sunan recommendFriends algoritması eklenmiştir.
* **Derece Merkeziliği (Degree Centrality):** Düğümlerin giriş ve çıkış kenarlarını hesaplayarak ağ üzerindeki önem derecesini ölçen getDegreeCentrality fonksiyonu sisteme entegre edilmiştir.

### Faz 3: JSON Çıktısı, Görselleştirme Altyapısı ve Stres Testi
* **JSON Dışa Aktarım Motoru:** Graf yapısını, web arayüzünün (FastAPI ve vis.js) doğrudan okuyabileceği standart bir formatta graph_data.json adıyla dışarı aktarır. Örnek çıktı formatı şu şekildedir:
  {
    "nodes": [
      {"id": 1, "label": "Ali", "group": "User"},
      {"id": 11, "label": "Bilgisayar Muhendisligi Hackathonu", "group": "Event"}
    ],
    "edges": [
      {"from": 1, "to": 2, "label": "FRIEND", "date": "25-05-2026"}
    ]
  }
* **Dinamik Sentetik Veri Enjeksiyonu:** Sistemin sınırlarını test etmek amacıyla, çalışma zamanında (runtime) dinamik düğüm ve kenar üreten ve milisaniye hassasiyetinde stress analizi raporu sunan generateSyntheticData motoru eklenmiştir.

---

## 3. Teknik İyileştirmeler ve Kritik Hata Düzeltmeleri

1. **Yönsüz Graf Tutarlılığı (Çift Yönlü Arkadaşlık):** FRIEND ilişkisi eklendiğinde grafın yönsüz yapıya uyması için sistem otomatik olarak ters yönlü kenarı (backEdge) veri tekrarı oluşturmadan ekleyecek şekilde güncellenmiştir.
2. **Dinamik Zaman Yönetimi:** Sabit/statik olarak atanan Edge.date" bilgisi, C dilinin time.h kütüphanesi kullanılarak doğrudan sistemin o anki gerçek tarihiyle (GG-AA-YYYY) güncellenecek hale getirilmiştir.
3. **Bellek Sızıntısı Optimizasyonu:** visited dizileri calloc ile dinamik hale getirilmiş; program sonlandığında grafın tüm düğüm, kenar ve nitelik haritalarını temizleyen freeGraph fonksiyonu entegre edilmiştir.

---

## 4. Çalıştırma Talimatları

Proje standart C derleyicileri (GCC) ile tam uyumludur. Derlemek ve çalıştırma için terminal üzerinden aşağıdaki komutlar uygulanmalıdır:

# Projeyi derleme
gcc main.c hash/hash.c graph/graph.c trie/trie.c queue/queue.c models/property.c -o social_network

# Projeyi çalıştırma
./social_network

Çalıştırma sonrasında konsolda algoritmaların analiz çıktıları raporlanacak ve proje klasöründe arayüz için gerekli olan graph_data.json dosyası otomatik olarak üretilecektir.
