# Graf Yapısı ve Algoritmaları Zaman Karmaşıklığı Analizi

Bu dokümanda, `graph.c` dosyası içerisinde yer alan temel fonksiyonların, arama algoritmalarının ve yardımcı simülasyon fonksiyonlarının kaynak kod tabanlı zaman karmaşıklığı (Big-O) analizleri yapılmıştır.

---

## 1. Temel Graf Algoritmaları Analizi

### `addEdge` (İlişki Ekleme)
* **Zaman Karmaşıklığı:** **$O(1)$** (Ortalama Durum). `getNode` fonksiyonu Hash tablosu kullandığı için düğümü bulmak sabit zaman alır. Hedef düğümü bağlı listenin başına eklemek de $O(1)$'dir.

### Genişlik Öncelikli Arama (`BFS` & `filteredBFS`)
* **Zaman Karmaşıklığı:** **$O(V + E)$** ($V$: Düğüm Sayısı, $E$: Kenar Sayısı). Her düğüm kuyruğa tam olarak bir kez girer ve her kenar (ilişki) tam olarak bir kez kontrol edilir. `strcmp` filtresi genel doğrusal karmaşıklığı bozmaz.

### Derinlik Öncelikli Arama (`DFS`)
* **Zaman Karmaşıklığı:** **$O(V + E)$**. Özyinelemeli `dfsUtil` fonksiyonu, ziyaret edilmemiş komşuları çağırır; her düğüm ve ona bağlı her kenar bir kez işlenir.

### `recommendFriends` (Arkadaş Önerisi - Triadic Closure)
* **Zaman Karmaşıklığı:** **$O(d^3)$** veya tüm graf düşünüldüğünde en kötü senaryoda **$O(V^3)$** ($d$: Ortalama düğüm derecesi). Bir düğümün arkadaşlarını, ardından arkadaşlarının arkadaşlarını (FoF) tarayan üçlü bir iç içe döngü barındırır. Her adımda `areConnected` çağrılır.

---

## 2. Gelişmiş Fonksiyonların Big-O Analizi

### `getDegreeCentrality` (Merkezilik Ölçümü)
* **Zaman Karmaşıklığı:** **$O(V + E)$**. Fonksiyon, gelen kenarları saymak için `countIncomingEdges` metodunu çağırır. Bu metot tüm hash tablosunu (Boyut: $N$) ve her düğümün bağlı kenarlarını ($E$) tamamen gezdiği için doğrusal zamanda çalışır.

### `findPhotosOfFriendsEvents` (Çok Adımlı Sorgu Gezinmesi)
* **Zaman Karmaşıklığı:** **$O(F \times A \times P)$** ($F$: Ortalama arkadaş sayısı, $A$: Ortalama katılım sayısı, $P$: Ortalama fotoğraf sayısı). İç içe üç `while` döngüsü kullanılarak "Arkadaş $\rightarrow$ Etkinlik $\rightarrow$ Fotoğraf" (FRIEND $\rightarrow$ ATTENDS $\rightarrow$ HAS_PHOTO) yolu graf üzerinde adım adım taranır.

### `freeGraph` (Bellek Temizliği)
* **Zaman Karmaşıklığı:** **$O(V + E + P)$** ($P$: Toplam Özellik/Property Sayısı). Tüm hash tablosu baştan sona taranarak düğümler, bu düğümlere ait özellikler (properties) ve kenarlar (edges) tek tek hafızadan `free` ile temizlenir.

---

## 3. Yardımcı Fonksiyonların Görev Özeti

Kodu analiz edilen ancak zaman karmaşıklığından ziyade projenin yapısal bütünlüğünü sağlayan diğer yardımcı fonksiyonlar:

* **`generateSyntheticData`:** Sisteme rastgele kullanıcılar, etkinlikler ve fotoğraflar ekleyerek stres testi (stress test) yapan ve programatik olarak rastgele ilişkiler (kenarlar) oluşturan simülasyon aracıdır.
* **`exportGraphToJSON`:** Grafın tüm verilerini ve ilişkilerini, UI (Kullanıcı Arayüzü) veya Frontend tarafında görselleştirilebilmesi amacıyla `JSON` formatında (`nodes` ve `edges` olarak) dışa aktarır.
