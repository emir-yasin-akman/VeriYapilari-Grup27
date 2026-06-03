# Hash Tablosu Yapısı ve Zaman Karmaşıklığı Analizi

Bu dokümanda, `hash.c` dosyası içerisinde yer alan temel Hash (Çırpı) tablosu fonksiyonlarının zaman karmaşıklığı (Big-O) analizleri ve sistem mimarisindeki görevleri detaylandırılmıştır.

---

## 1. Zaman Karmaşıklığı (Big-O) Analizi

### `hash` (İndis Hesaplama)
* **Kaynak Kod Yapısı:** Gelen `id` değerinin mutlak değerini alarak tablo boyutuna (`TABLE_SIZE`) göre mod (`%`) alma işlemi yapar.
* **Zaman Karmaşıklığı:** **$O(1)$**. Hiçbir döngü barındırmaz, doğrudan sabit zamanda çalışan salt matematiksel bir modülo işlemidir.

### `getNode` (Düğüm Arama ve Getirme)
* **Kaynak Kod Yapısı:** Hesaplanmış indise gider ve o indisteki bağlı listeyi (`while (temp != NULL)`) tarayarak doğru düğümü arar.
* **Zaman Karmaşıklığı:**
  * **En İyi ve Ortalama Durum:** **$O(1)$**. Hash fonksiyonu düğümleri tabloya homojen dağıttıysa, aranan eleman doğrudan o indisteki ilk eleman olur ve anında bulunur.
  * **En Kötü Durum:** **$O(N)$** ($N$: Tablodaki eleman sayısı). Çakışmaların (collision) çok fazla olduğu ve tüm düğümlerin aynı indise yığılarak tek bir uzun bağlı liste oluşturduğu durumda, aranan düğümü bulmak için listenin sonuna kadar gitmek gerekir.

### `insertNode` (Düğüm Ekleme)
* **Kaynak Kod Yapısı:** Verinin zaten sistemde olup olmadığını teyit etmek için öncelikle `getNode` çağrısı yapar. Eğer veri yoksa (unique ise), bağlı listenin (chaining) en başına ekleme yapar.
* **Zaman Karmaşıklığı:**
  * **En İyi Durum:** **$O(1)$**. Eğer arama işlemi tek adımda biterse, yeni düğümü listenin başına bağlamak da tek adım ($O(1)$) süreceğinden ekleme çok hızlı gerçekleşir.
  * **En Kötü Durum:** **$O(N)$**. Ekleme işleminin kendisi aslında $O(1)$ sürmesine rağmen, kodun en başındaki `getNode(ht, node->id)` çağrısı benzersizlik kontrolü yaptığı için, arama fonksiyonunun zafiyeti olan $O(N)$ durumu buraya da doğrudan yansır.

---

## 2. Sistematik Özet: Projede Ne İşe Yarar?

`hash.c` kodları, projenin **"Merkezi Veritabanı Motoru"** olarak görev yapmaktadır.

* **Hızlı Veri Erişimi:** Graf yapısında düğümler arası ilişkiler kurulurken, BFS/DFS gibi arama simülasyonları çalıştırılırken veya JSON formatında veriler dışa aktarılırken bir kullanıcıyı, etkinliği ya da fotoğrafı bulmak gerektiğinde tüm grafı baştan sona taramak gerekmez. Bu tablo kullanılarak $O(1)$ hızında doğrudan o verinin bellek adresine ulaşılır.
* **Çakışma Yönetimi (Collision Resolution):** Kodda görüldüğü üzere "Separate Chaining" yöntemi uygulanmıştır. İki farklı veri aynı indise denk gelirse, birbiri üzerine yazılıp silinmek yerine `node->next = ht->table[index]` mantığıyla veriler bir zincir gibi birbirine bağlanarak %100 veri güvenliğiyle saklanır.
* **Veri Bütünlüğü Koruması (Data Integrity):** `insertNode` içerisindeki if bloğu (`getNode` kontrolü) sayesinde, aynı ID numarasına sahip iki farklı kaydın sisteme mükerrer olarak girilmesi engellenmiş ve veri kirliliğinin önüne geçilmiştir.
