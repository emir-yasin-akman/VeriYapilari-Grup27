# Node (Düğüm) Model Yapısı ve Bellek Analizi

Bu dokümanda, projenin temel yapı taşı olan `models/node.h` başlık dosyasındaki `Node` yapısının mimari analizi ve bellek (space) tüketimi incelenmiştir.

---

## 1. Yapısal Mimari Analizi: Projede Ne İşe Yarar?

`Node` yapısı, sosyal ağ simülasyonundaki her bir somut varlığı (Kullanıcı, Etkinlik, Fotoğraf vb.) temsil eden genel (generic) bir nesne modelidir. İçerisindeki alanların görevleri şu şekildedir:

* **`int id`:** Her düğümün sistemde benzersiz (unique) olarak tanınmasını sağlayan kimlik numarasıdır. Hash tablosunda indis hesaplanırken bu değer baz alınır.
* **`char type[20]`:** Polimorfizm mantığını simüle eder. Düğümün bir `"User"`, `"Event"` veya `"Photo"` mu olduğunu belirterek kodun tek bir struct ile esnek çalışmasını sağlar.
* **`Property* properties`:** Düğümü sabitlemek yerine, dinamik olarak genişletilebilir hale getirir. Örneğin bir kullanıcının adı, bir fotoğrafın uzantısı bu bağlı liste (linked list) modelinde saklanır.
* **`Edge* edges`:** Bu düğümden dışarıya doğru uzanan tüm ilişkileri (Arkadaşlık, Beğeni, Katılım) bir bağlı liste olarak tutar. Graf yapısının "Komşuluk Listesi" (Adjacency List) bu işaretçi üzerinden yürür.
* **`struct Node* next`:** Hash tablosunda çakışma (collision) yaşandığında, aynı indise düşen düğümlerin birbirini kaybetmeden "Separate Chaining" yöntemiyle bağlanmasını sağlayan kritik bir işaretçidir.

---

## 2. Bellek (Space) Karmaşıklığı Analizi

Bu dosya statik veya dinamik bir döngü içermediğinden doğrudan bir zaman karmaşıklığı barındırmaz. Ancak bellek yönetimi açısından analiz edildiğinde:

* **Tek Bir Düğümün Sabit Bellek Boyutu:** * `int id` (4 byte) + `char type[20]` (20 byte) + 3 adet İşaretçi/Pointer (Sistem mimarisine göre $3 \times 4$ veya $3 \times 8$ byte).
  * Bu doğrultuda her bir düğüm ham olarak hafızada sabit bir yer tutar ($O(1)$ space).
* **Genel Sistem Karmaşıklığı:**
  * Projede oluşturulan toplam düğüm sayısı $V$ (Vertex) olmak üzere, tüm düğümlerin hafızada kapladığı alan **$O(V)$** düzeyindedir. 
  * Düğümlere bağlı özellikler ve kenarlar dinamik olarak (`malloc` ile) yönetildiği için bellek israfı sıfıra indirilmiştir; sistem sadece canlanan veri kadar yer kaplar.
