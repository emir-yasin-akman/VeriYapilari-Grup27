# Veri Yapıları Alan (Space) Karmaşıklığı Analizi

Bu dokümanda, projenin çekirdek mekanizmasını oluşturan temel veri yapılarının bellek (space) karmaşıklıkları incelenmiştir.

---

## 1. Hash Tablosu Yapısı (Hash Folder)
Projede kullanıcı verilerinin veya ilişkili anahtarların hızlıca saklanması için bir **Hash Table** yapısı tercih edilmiştir. 
* Çakışma yönetimi (Collision Handling) için dinamik yapılar kullanılmıştır.
* **Alan Karmaşıklığı:** Toplam eleman sayısı $N$ olmak üzere, veriler tablolarda doğrudan veya dinamik listeler halinde tutulduğu için alan karmaşıklığı **$O(N)$** düzeyindedir.

## 2. Graf Yapısı (Graph Folder)
Sosyal ağ simülasyonundaki kullanıcı ilişkilerini modellemek için **Graf (Graph)** veri yapısı kullanılmıştır.
* **Alan Karmaşıklığı:** Graf mimarisinde toplam düğüm (kullanıcı) sayısı $V$ ve kenar (arkadaşlık ilişkisi) sayısı $E$ olmak üzere; eğer komşuluk listesi kullanıldıysa **$O(V + E)$**, komşuluk matrisi tercih edildiyse **$O(V^2)$** yer kaplamaktadır. Projedeki asenkron yapı optimize bir bellek tüketimi sunar.

## 3. Trie Veri Yapısı (Trie Folder)
Kullanıcı arama, kelime veya etiket tamamlama gibi hızlı string eşleştirme süreçleri için **Trie (Önek Ağacı)** veri yapısı entegre edilmiştir.
* **Alan Karmaşıklığı:** Trie yapısında bellek, alfabedeki karakter sayısına ($ALPHABET\_SIZE$) ve eklenen kelimelerin toplam uzunluklarına bağlıdır. En kötü senaryoda alan karmaşıklığı **$O(Kelime\_Sayisi \times Ortalama\_Uzunluk \times ALPHABET\_SIZE)$** olarak hesaplanır.

## 4. Kuyruk Yapısı (Queue Folder)
Simülasyon motorunun asenkron/thread-safe şekilde çalışabilmesi ve isteklerin sırayla işlenmesi için **Dinamik Queue (Kuyruk)** yapısı kurulmuştur.
* **Alan Karmaşıklığı:** Kuyrukta o an işlem bekleyen maksimum görev sayısı $M$ olmak üzere dinamik bellek yönetimi sayesinde alan karmaşıklığı **$O(M)$** ile sınırlıdır.
