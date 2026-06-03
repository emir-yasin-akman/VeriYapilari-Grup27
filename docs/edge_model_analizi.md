# Edge (Kenar/İlişki) Model Yapısı ve Bellek Analizi

Bu dokümanda, graf yapısının bağlantı mekanizmasını oluşturan `models/edge.h` başlık dosyasındaki `Edge` yapısının mimari analizi ve bellek (space) tüketimi incelenmiştir.

---

## 1. Yapısal Mimari Analizi: Projede Ne İşe Yarar?

`Edge` yapısı, Graf Kuramında (Graph Theory) düğümleri birbirine bağlayan "Kenar" (İlişki) kavramını temsil eder. Projenizde yönlendirilmiş graf (directed graph) mimarisine uygun olarak, bir düğümden diğerine giden köprüleri saklar. İçerisindeki alanların görevleri şu şekildedir:

* **`int target_id`:** İlişkinin yöneldiği hedef düğümün benzersiz kimlik (ID) numarasıdır. Örneğin; Ahmet kullanıcısının `edges` listesindeki bir edge'in `target_id` değeri 105 ise, bu Ahmet'ten 105 ID'li nesneye (başka bir kullanıcıya veya etkinliğe) doğru bir ok çıktığını gösterir.
* **`char relation[20]`:** İlişkinin semantik tipini belirler. Sosyal ağ simülasyonundaki esnekliği sağlayan en önemli alanlardan biridir. Bu alanda `"FRIEND"`, `"ATTENDS"`, `"HAS_PHOTO"` veya `"LIKES"` gibi metinler saklanarak aynı struct yapısıyla çok farklı ilişkiler modellenebilir.
* **`char date[20]`:** İlişkinin sisteme işlendiği tam tarihi (`GG-AA-YYYY`) tutar. Zaman tabanlı veya kronolojik sorgulamalar yapılırken (örneğin: son 1 ayda eklenen arkadaşlar) filtreleme amacıyla kullanılır.
* **`struct Edge* next`:** Graf yapısının "Komşuluk Listesi" (Adjacency List) modelini uygulamak için kullanılan işaretçidir. Bir düğüme bağlı birden fazla ilişki varsa, bu ilişkiler tek yönlü bağlı liste (singly linked list) mantığıyla bu `next` pointer'ı üzerinden birbirine zincirlenir.

---

## 2. Bellek (Space) Karmaşıklığı Analizi

Bu başlık dosyası statik veya dinamik bir döngü içermediğinden doğrudan bir zaman karmaşıklığı barındırmaz. Ancak bellek yönetimi açısından analiz edildiğinde:

* **Tek Bir Kenarın Sabit Bellek Boyutu:**
  * `int target_id` (4 byte) + `char relation[20]` (20 byte) + `char date[20]` (20 byte) + 1 adet İşaretçi/Pointer (Sistem mimarisine göre 4 veya 8 byte).
  * Her bir ilişki köprüsü kurulduğunda hafızada sabit bir yer tahsis edilir ($O(1)$ space).
* **Genel Sistem Karmaşıklığı:**
  * Projede oluşturulan toplam ilişki/kenar sayısı $E$ (Edge) olmak üzere, tüm kenar yapılarının hafızada kapladığı alan **$O(E)$** düzeyindedir.
  * Komşuluk listesi (Adjacency List) modeli tercih edildiği için, kullanılmayan boş ilişkiler için bellek harcanmaz (Komşuluk matrisindeki $O(V^2)$ bellek israfının önüne geçilmiştir). Sistem sadece mevcut arkadaşlık ve etkileşim sayısı ($E$) kadar bellek tüketir.
