# Trie (Önek Ağacı) Yapısı ve Zaman Karmaşıklığı Analizi

Bu dokümanda, projenin metin tabanlı hızlı arama motorunu oluşturan `trie.c` kaynak kod dosyasındaki fonksiyonların mimari analizi, işlevleri ve zaman/alan karmaşıklıkları incelenmiştir.

---

## 1. Zaman ve Alan Karmaşıklığı (Big-O) Analizi

Modülün kaynak kodunda yer alan çekirdek fonksiyonların karmaşıklık analizleri şu şekildedir ($L$: İşlem gören kelimenin karakter uzunluğu, $R$: Alfabe/Karakter boyutu - `TRIE_CHAR_SIZE`):

### `createTrieNode` (Yeni Düğüm Oluşturma)
* **Kaynak Kod Mantığı:** Bellekten bir düğüm yeri ayırır (`malloc`), kelime bitiş işaretini sıfırlar (`isEnd = 0`) ve `for` döngüsüyle tüm çocuk işaretçilerini (`children`) `NULL` yapar.
* **Zaman Karmaşıklığı:** **$O(R)$** veya alfabetik boyut sabit (genellikle 256) olduğu için **$O(1)$**. Alfabe boyutu kadar dönen sabit bir döngü barındırır.
* **Bellek (Space) Karmaşıklığı:** **$O(R)$**. Her bir düğüm oluşturulduğunda hafızada alfabe boyutu kadar (`children[256]`) işaretçi dizisi yeri ayrılır.

### `insertTrie` (Kelime/Kullanıcı Adı Ekleme)
* **Kaynak Kod Mantığı:** Bir `for` döngüsüyle eklenecek kelimenin her bir harfini tek tek döner. Eğer o harfe ait çocuk düğüm yoksa `createTrieNode` ile oluşturur ve aşağı doğru ilerler. Döngü bitiminde `temp->isEnd = 1` yapar.
* **Zaman Karmaşıklığı:** **$O(L)$**. Döngü sadece eklenen kelimenin karakter sayısı ($L$) kadar döndüğü için zaman karmaşıklığı kelimenin uzunluğuna doğrusal olarak bağlıdır. Tablodaki toplam kelime sayısından tamamen bağımsızdır.
* **Bellek (Space) Karmaşıklığı:** **$O(L \times R)$**. En kötü senaryoda, eklenen kelimenin hiçbir harfi ağaçta daha önce yoksa, kelimenin her harfi için yeni bir düğüm açılır.

### `searchTrie` (Kelime/Kullanıcı Adı Arama)
* **Kaynak Kod Mantığı:** Aranan kelimenin harflerini sırayla takip eder. Eğer döngü sırasında aranan harfe ait bir çocuk düğüm (`children[index]`) bulunamazsa doğrudan `0` (bulunamadı) döner. Harfler eksiksiz tamamlanırsa düğümün `isEnd` değerini başarılı arama sonucu olarak döndürür.
* **Zaman Karmaşıklığı:** **$O(L)$**. Tıpkı eklemede olduğu gibi, sistemde milyonlarca kelime olsa dahi arama süresi sadece ve sadece aranan kelimenin karakter uzunluğu ($L$) kadardır.

---

## 2. Sistematik Özet: Projede Ne İşe Yarar?

`trie.c` modülü, sosyal ağ simülasyonunda **"Akıllı Arama ve Otomatik Tamamlama (Autocomplete) Motoru"** olarak görev yapar.

* **Ultra Hızlı Kullanıcı ve Etkinlik Arama:** Klasik yöntemlerde bir kullanıcı adını aramak için tüm diziyi veya grafı baştan sona taramak ($O(N)$) gerekir. Trie yapısı sayesinde arama işlemi kelimenin harf sayısı ($L$) adımda şimşek hızında tamamlanır.
* **Önek (Prefix) Tabanlı Sorgular:** Sosyal medyadaki arama çubuklarında bir harfe basıldığında (örn: "Me" yazıldığında) "Mert", "Melis" gibi isimlerin otomatik listelenmesi mantığı bu yapı sayesinde kurulur. Ortak öneke sahip kelimeler ağaçta aynı kökü paylaştığı için prefix filtrelemeleri çok verimli yapılır.
* **Mükemmel Bellek Optimizasyonu:** Aynı harflerle başlayan kelimeler (Örn: "Ahmet" ve "Ahsen") "Ah" kısmına kadar olan düğümleri ortak kullanırlar. Bu sayede kelime sayısı arttıkça, benzer kelimeler için tekrar tekrar bellek ayrılmasının önüne geçilir ve hafızadan tasarruf sağlanır.
