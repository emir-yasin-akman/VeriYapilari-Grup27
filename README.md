# VeriYapilari-Grup27
### (Property Graph Sosyal Ağ (C) )
# <ins>Ek olan (Opsiyonel) Kisim:</ins>
## Triadic Closure (Arkadaş Önerme)
Bu projede arkadaş önerileri triadic closure mantığına göre yapılmaktadır.

Mantık:
Kullanıcı → Arkadaşlar → Arkadaşların Arkadaşları

Eğer iki kullanıcı arasında ortak arkadaş varsa, bu kişiler birbirine önerilir.  
Ortak arkadaş sayısı arttıkça öneri daha güçlü kabul edilir.

## Algoritma Analizi
Algoritma, kullanıcının arkadaşlarını ve onların arkadaşlarını dolaşır.

- k = kullanıcının arkadaş sayısı  
- m = her arkadaşın ortalama arkadaş sayısı  

Zaman karmaşıklığı:

Ortalama Durum = → O(k × m)

En Kötü Durum = → O(n²) -herkes herkesle arkadaşsa (çok yoğun graph)-

Hash table sayesinde node erişimi ortalama O(1) olduğu için arama işlemleri hızlıdır.

## Uzay Karmaşıklığı:

Bu sistemin toplam uzay karmaşıklığı:

O(N + E)

Burada:
- N: Düğüm (node) sayısını temsil eder (kullanıcı, etkinlik vb.)
- E: Kenar (edge) sayısını temsil eder (arkadaşlık, beğeni vb.)

Açıklaması:
- Her düğüm hash tablo içerisinde saklanır → O(N)
- Her ilişki (edge) komşuluk listesi (adjacency list) yapısında tutulur → O(E) 
    - <sub> (Adjacency matrix'e göre daha az bellek kullanılır. 
Adjacency matrix kullanılsaydı uzay karmaşıklığı O(N²) olurdu.) </sub>

- Triadic closure algoritmasında kullanılan yardımcı diziler (scores ve visited) → O(N)
- Her düğüm ve her kenar bellekte bir kez tutulur. Ek olarak algoritmada O(N) yardımcı alan kullanılır.

Bu nedenle toplam uzay karmaşıklığı graf yapısından dolayı O(N + E) olur.
## Çalıştırma:
Projeyi derlemek için:

make

Programı çalıştırmak için:

make run