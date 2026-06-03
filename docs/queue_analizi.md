# Queue (Kuyruk) Modül Yapısı ve Detaylı Analizi

Bu dokümanda, graf arama algoritmalarının temel işleyiş mekanizmasını sağlayan `queue.c` kaynak kod dosyasındaki fonksiyonların mimari analizi, işlevleri ve zaman/alan karmaşıklıkları incelenmiştir.

---

## 1. Zaman ve Alan Karmaşıklığı (Big-O) Analizi

Modülün kaynak kodunda yer alan çekirdek fonksiyonların karmaşıklık analizleri şu şekildedir ($Q$: Kuyruktaki anlık eleman sayısı):

### `enqueue` (Kuyruğa Eleman Ekleme)
* **Kaynak Kod Mantığı:** Dinamik olarak yeni bir `QueueNode` hücresi oluşturur (`malloc`), veriyi bağlar ve kuyruğun en arka işaretçisini (`q->rear`) güncelleyerek elemanı sona ekler.
* **Zaman Karmaşıklığı:** **$O(1)$**. Kuyrukta kaç eleman olursa olsun, son elemanın adresi `rear` işaretçisinde tutulduğu için arama veya tarama yapmadan doğrudan sona ekleme yapılır.
* **Bellek Karmaşıklığı:** **$O(1)$**. Her ekleme işleminde sadece tek bir düğümlük (Node) yeni alan tahsis edilir.

### `dequeue` (Kuyruktan Eleman Çıkarma)
* **Kaynak Kod Mantığı:** Kuyruğun en başındaki elemanı (`q->front`) okur, öncelik sırasını bir sonraki elemana kaydırır (`q->front->next`) ve işi biten yardımcı taşıyıcı hücreyi bellekten siler (`free(temp)`). Asıl graf düğümünü (Node) ise güvenle geri döndürür.
* **Zaman Karmaşıklığı:** **$O(1)$**. Sadece iki adet pointer yönlendirmesi ve bir adet hafıza serbest bırakma işlemi yapıldığı için sabit zamanda, anında çalışır.

### `freeQueue` (Kuyruk Bellek Temizliği)
* **Kaynak Kod Mantığı:** Bir `while` döngüsü ile kuyruk tamamen boşalana kadar (`!isEmpty(q)`) sürekli `dequeue` fonksiyonunu çağırır.
* **Zaman Karmaşıklığı:** **$O(Q)$**. Kuyrukta kalan tüm elemanları tek tek bellekten silmek zorunda olduğu için, işlem süresi kuyruktaki eleman sayısıyla doğru orantılıdır.

### Yardımcı Fonksiyonlar (`createQueue` ve `isEmpty`)
* **Zaman Karmaşıklığı:** **$O(1)$**. Sadece başlangıç atamaları ve anlık `NULL` kontrolü yaptıkları için sabit zamanda çalışırlar.

---

## 2. Sistematik Özet: Projede Ne İşe Yarar?

`queue.c` modülü, projede veri tutmaktan ziyade **"İşlem Sırası Yöneticisi"** (Task Scheduler) olarak görev yapar.

* **Genişlik Öncelikli Arama (BFS) Motoru:** `graph.c` içerisindeki `BFS` ve `filteredBFS` algoritmalarının kalbidir. Bir kullanıcının sosyal ağdaki komşuları (arkadaşları) taranırken, bu komşular sırayla kuyruğa (`enqueue`) alınır ve ilk eklenen komşu ilk işlenerek (`dequeue`) ağaçta katman katman (level-by-level) genişleme sağlanır.
* **Bellek Sızıntısı Koruması:** `dequeue` fonksiyonundaki `free(temp)` satırı, kuyruk mekanizmasının kendi yarattığı taşıyıcı düğümleri işi bittiğinde anında silmesini sağlar. Ancak bunu yaparken asıl veriyi (`Node* nodeData`) yok etmez. Bu "taşıyıcı-zarf" (wrapper) mantığı, projenin RAM kullanımını stabil tutar.
