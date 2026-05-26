# Property Graph Tabanlı Sosyal Ağ Modelleme

Bu proje, sosyal ağ sistemlerinde kullanılan property graph veri modelinin sadeleştirilmiş bir versiyonu olarak geliştirilmektedir. Projenin temel amacı, ağ üzerindeki varlıklar (düğümler) ve ilişkiler (kenarlar) arasında verimli veri yapıları ve algoritmalar kullanarak çok adımlı sorgular gerçekleştirmektir.

## Faz 1: Mevcut Veri Yapıları ve Gereksinim Uyumluluğu

Faz 1 kapsamında aşağıdaki temel yapılar sıfırdan implemente edilmiş ve başarıyla çalıştırılmıştır:

- Property Graph (Adjacency List): Farklı türde düğümleri (User, Photo, Event) ve özellikli kenarları (FRIEND, LIKES) destekleyen komşuluk listesi yapısı kurulmuştur.

- Karma Tablo (Hash Table): Düğümlere benzersiz ID üzerinden ortalama O(1) sürede erişim sağlanmaktadır.

- Trie (Önek Ağacı): Metin tabanlı arama ve otomatik tamamlama işlemleri için sisteme dahil edilmiştir.

- Kuyruk (Queue): BFS algoritmasının çalışması için dinamik kuyruk yapısı oluşturulmuştur.

- Temel Algoritmalar: BFS ve DFS tarama algoritmaları graf üzerinde aktif olarak çalışmaktadır.

- Bellek Yönetimi: Dinamik bellek kullanımı kontrol altına alınmış, freeGraph ve freeQueue fonksiyonları ile bellek temizliği sağlanmıştır.

- Teknik İyileştirmeler ve Düzeltmeler

- Geliştirme sürecinde tespit edilen aşağıdaki hatalar giderilmiştir:

- Trie arama fonksiyonundaki eksiklik giderilerek searchTrie fonksiyonu eklenmiştir.

- Edge.date bilgisi sabit değerden sistem tarihine dönüştürülmüştür.

- BFS visited dizisi dinamik hale getirilerek bellek kullanımı optimize edilmiştir.

## Gelecek Planları: Faz 2 ve Faz 3

Projenin sonraki aşamalarında aşağıdaki özelliklerin eklenmesi planlanmaktadır:

**Faz 2: Gelişmiş Algoritma ve Sorgu Modeli**

- Çok Adımlı Sorgular: Kullanıcı -> arkadaşlar -> katıldığı etkinlikler gibi ardışık graf traversal işlemleri gerçekleştirilecektir.

- Analitik Ölçümler: Arkadaş önerisi mantığı (Triadic closure) ve basit merkezilik ölçümleri sisteme entegre edilecektir.

- Performans Analizi: Kullanılan algoritmaların zaman ve uzay karmaşıklıkları analiz edilecektir.

**Faz 3: Arayüz ve Görselleştirme**

- Graf Görselleştirme: Sorgu sonuçları 2D node-link diyagramı olarak gösterilecek, düğüm türleri farklı şekil/renklerle temsil edilecektir.

- Etkileşim: Graf üzerindeki bir düğüme tıklandığında, düğümün özellikleri Hash Table üzerinden çekilerek yan panelde sunulacaktır.

- Sentetik Veri: Sistem performansını test etmek amacıyla programatik veya GenAI destekli veri üretimi yapılacaktır.
