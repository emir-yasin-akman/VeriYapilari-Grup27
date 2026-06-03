# Property Graph Tabanlı Sosyal Ağ Modelleme ve Sorgulama Aracı (Grup 27)

Bu proje; sosyal ağ sistemlerinde sıklıkla kullanılan heterojen Property Graph (Özellikli Graf) veri modelinin, modern veri yapıları ve algoritmalar kullanılarak sıfırdan (from scratch) implemente edilmiş basitleştirilmiş bir versiyonudur. Sistem, arka planda yüksek performanslı bir C backend yapısı barındırırken, ön yüzde bu verileri interaktif olarak sunan, sorgulayan ve analiz eden web tabanlı bir görselleştirme arayüzü sunmaktadır.

---
## Eşzamanlılık ve Mikroservis Yaklaşımı
Proje mimarisi, ekip büyüklüğü ve sistem bileşenlerinin modülerliği göz önüne alınarak monolitik bir yapı yerine ayrı servisler (microservices) mimarisiyle tasarlanmıştır. Yapay zeka simülasyon ve veri motorunu barındıran çekirdek C programı, verileri işleyip bellekten bağımsız bir şekilde JSON formatında dışa aktarırken; asenkron çalışan Python FastAPI sunucusu bu veriyi bağımsız bir servis olarak web arayüzüne sunmaktadır. Bu tasarım, grafik simülasyon süreçleri ile kullanıcı etkileşimlerinin ana bellek seviyesinde birbirinden bağımsız/asenkron çalışmasını sağlayarak veri kilitlenmelerinin önüne geçmektedir.
## Proje Mimari Yapısı ve Fazları

Proje, hocanın belirlediği 3 ana fazın gereksinimlerini ve tüm opsiyonel isterleri karşılamaktadır:

### Faz 1: Zorunlu Veri Yapıları (Sıfırdan Implementasyon)
* Heterojen Property Graph: User, Photo ve Event gibi farklı türde düğümleri (Vertex) ve bu düğümler arasındaki ilişkileri (FRIEND, ATTENDS, HAS_PHOTO) yönlü/yönsüz olarak tutan, Komşuluk Listesi (Adjacency List) tabanlı graf yapısı. Kenarlar üzerinde tarih gibi ek özellikler (properties) taşınmaktadır.
* Hızlı Erişim Karma Tablosu (Hash Table): Graf üzerindeki yüzlerce düğüme benzersiz ID'leri üzerinden ortalama O(1) zaman karmaşıklığında erişim sağlayan özel hash tablosu implementasyonu.
* Metin Tabanlı Önek Ağacı (Trie): Sosyal ağ içerisindeki kullanıcı isimleri üzerinden hızlı arama ve otomatik tamamlama (autocomplete) işlemlerini gerçekleştiren Trie yapısı.
* Kuyruk Yapısı (Queue): Graf üzerinde Genişlik Öncelikli Arama (BFS) algoritmalarının veri akışını yönetmek için sıfırdan yazılmış FIFO kuyruk yapısı.

### Faz 2: Gelişmiş Algoritmalar ve Sorgu Modeli
* Graf Traversal (BFS & DFS): Ağ üzerindeki katmanlı tarama, bağlantı dereceleri hesaplama ve derinlik öncelikli analizler için optimize edilmiş temel arama algoritmaları.
* Çok Adımlı İlişkisel Sorgu Akışı: Sistem, ardışık graf traversal işlemleri gerçekleştirerek karmaşık ilişkileri zincirleme olarak sorgulayabilir:
  Kullanıcı -> arkadaşlar -> katıldığı etkinlikler -> bu etkinliklerdeki fotoğraflar
* Sosyal Ağ Analiz Ölçümleri (Bonus):
  * Triadic Closure: Ortak arkadaş sayılarını analiz ederek kullanıcılara dinamik arkadaş önerilerinde bulunan öneri algoritması.
  * Degree Centrality: Düğümlerin bağlantı yoğunluklarını hesaplayarak ağ içerisindeki en önemli ve popüler aktörleri listeleyen merkezilik ölçümü.
* Dinamik Sentetik Veri Enjeksiyonu (Stress Test): Sistem davranışını, performans sınırlarını ve zaman karmaşıklıklarını ölçmek amacıyla programatik olarak yüzlerce sentetik düğüm ve kenar üreten stress testi motoru.

### Faz 3: Spesifik Arayüz ve İnteraktif Görselleştirme
* 2D Node-Link Diyagramı: Web arayüzünde vis.js kütüphanesi kullanılarak tüm düğüm türleri farklı renk ve görsel hiyerarşilerle (Kullanıcılar mavi, Etkinlikler yeşil, Fotoğraflar turuncu vb.) dinamik olarak canlandırılır.
* Hash Table Entegreli Yan Panel: Graf üzerinde herhangi bir düğüme tıklandığı an, o düğümün tüm özellikleri (properties) ve mevcut bağlantıları arka plandaki Hash Table üzerinden O(1) hızında çekilerek detay panelinde listelenir.
* Arama ve Çok Adımlı Sorgu Modülleri: Metin tabanlı Trie aramasını tetikleyen üst arama barı ve ID tabanlı çok adımlı ilişkisel sorgu akışını canlı tetikleyen interaktif yönetim modülü.

---

## Kurulum ve Çalıştırma Talimatları

Sistemin frontend, backend ve API servislerinin bağımlılık sorunu yaşamadan, işletim sisteminden bağımsız olarak çalışabilmesi için Docker konfigürasyonları hazırlanmıştır.  

__Yöntem 1__: Tek Komutla Otomatik Kurulum (Önerilen - Docker)   Tüm sistem bileşenlerinin otomatik olarak derlenmesi, sentetik verilerin üretilmesi ve servislerin ayağa kaldırılması için aşağıdaki adımları takip etmeniz yeterlidir:  

1-Projeyi bilgisayarınıza klonlayın ve ana dizine gidin:
```
git clone <repository-url>
cd <repository-folder>
```

2-Docker Compose komutu yardımıyla tüm sistemi tek adımda başlatın:
```
docker-compose up --build
```

3-Servisler başarıyla ayağa kalktığında tarayıcınızdan http://localhost adresine giderek interaktif görselleştirme arayüzüne erişebilirsiniz.
Not: Backend API servisi http://localhost:8000 portu üzerinden canlı olarak hizmet verecektir.

__Yöntem 2__: Manuel Geliştirici Kurulumu (Lokal Çalıştırma)
Sistemi Docker kullanmadan yerel ortamda test etmek isterseniz:

1-Gerekli Python paketlerini yükleyin:
```
pip3 install fastapi uvicorn
```

2-C backend motorunu derleyip çalıştırarak graph_data.json verisini üretin:
```
make
./app
```

3-Verileri arayüze besleyecek olan Python tabanlı API sunucusunu başlatın:
```
python3 -m uvicorn api:app --reload
```

4-Ana dizininde yer alan index.html dosyasını tarayıcınızda açarak arayüze erişin.

## Proje Klasör Yapısı ve Belgeler

Proje, modüler ve temiz kod prensiplerine uygun olarak katmanlı bir klasör hiyerarşisiyle organize edilmiştir. Sistem bileşenleri işlevlerine ve veri yapılarına göre alt dizinlere ayrıştırılmıştır.

**graph Klasörü**: Standart ve filtreli graf traversal algoritmaları (BFS, DFS), sosyal ağ analiz ölçümleri (Degree Centrality, Triadic Closure), dinamik sentetik veri üretimi ve grafı arayüzün okuyabileceği formata dönüştüren JSON dışa aktarım motorunu barındırır.

**hash Klasörü**: Graf üzerindeki düğümlere benzersiz ID'leri üzerinden ortalama O(1) zaman karmaşıklığında anlık erişim sağlayan, çakışma çözümlerinde zincirleme tekniği kullanan Hash Table mekanizmasını barındırır.

**trie Klasörü**: Sosyal ağ içindeki kullanıcı isimlerinin metin tabanlı olarak hızlıca indekslenmesini, aranmasını ve otomatik tamamlanmasını sağlayan Önek Ağacı yapısını barındırır.

**queue Klasörü**: BFS katmanlı arama ve çevre analiz algoritmalarında FIFO veri akış mimarisini yöneten dinamik kuyruk yapısını barındırır.

**models Klasörü**: Grafın heterojen ve özellikli yapısını oluşturan temel nesne şablonlarını; Node (Düğüm), Edge (Kenar) ve Property (Özellik) yapılarının C dili mimarisindeki pointer ve struct tanımlamalarını barındırır.

**Kök Dizin**: Çekirdek veri simülasyonunu başlatan main.c, verileri web katmanına taşıyan api.py FastAPI sunucusu, vis.js tabanlı index.html görsel arayüzü ile sistemin tek komutla izole derlenmesini sağlayan Dockerfile, docker-compose.yml ve Makefile yapılandırmalarını içerir.

**docs Klasörü İçeriği**: Gerekli tüm akademik rapor ve ek belgelere bu klasör üzerinden erişilebilir. Klasör içerisinde veri yapılarının mimari açıklamalarını, UML diyagramlarını ve AI API'sine gönderilen prompt'ların dökümünü içeren kapsamlı Proje Raporu, yazılan tüm çekirdek algoritmaların teorik karmaşıklık analiz tablolarını içeren Big-O Zaman ve Uzay Karmaşıklığı Analizleri, tanıtım videosunun adresi yer almaktadır.

## Takım Üyeleri ve Görev Dağılımı

### Emir Yasin AKMAN - 032490105

__Zorunlu Veri Yapıları (Faz 1) Çekirdek İmplementasyonu:__

* Heterojen Property Graph Tasarımı: Farklı türdeki varlıkların (User, Photo, Event) düğüm ; arkadaşlık, katılım veya beğeni gibi ilişkilerin ise kenar olarak modellendiği graf yapısının sıfırdan yazılması. Düğümlerin benzersiz ID ve tür bilgisi (type) , kenarların ise yönlü/yönsüz durumları ile tarih gibi ek nitelikleri (properties) taşıyabilmesi için gerekli veri yapılarının kodlanması.
* Komşuluk Listesi (Adjacency List) Altyapısı: Dinamik bellek yönetimini optimize etmek amacıyla graf yapısının tamamen komşuluk listesi tabanlı olarak sıfırdan implemente edilmesi.
* Hızlı Erişim Karma Tablosu (Hash Table): Tüm düğümlerin benzersiz ID ile saklanmasını sağlayan , çakışma çözümlerinde (collision) zincirleme (chaining) yöntemini kullanan ve düğümlere ortalama $O(1)$ zaman karmaşıklığında erişim sunan karma tablonun geliştirilmesi.
* Kuyruk (Queue) Yapısı: Graf üzerinde Genişlik Öncelikli Arama (BFS) algoritmasının uygulanması , bağlantı derecesi (degrees of separation) hesaplama , ağı katmanlı şekilde tarama ve ağırlıksız en kısa yol bulma işlemlerinin yönetilmesi için FIFO Queue yapısının sıfırdan yazılması.

__Teslim Edilecekler Süreci:__
* Demo Videosu

### Murat Yılmaz ÇARIKCI - 11600797528 - RuthlessAzazel

__Algoritmalar ve Yardımcı AI Kullanımı (Faz 2) Geliştirmesi:__

* Graf Traversal Motoru: Graf yapısı üzerinde kapsamlı tarama ve analiz yapabilmeyi sağlayan core BFS ve DFS algoritmalarının sıfırdan implementasyonu.
* Filtreli Graf Traversal Algoritmaları: Çok adımlı sorguların gerçekleştirilebilmesi amacıyla düğüm ve ilişki bazlı spesifik arama işlemlerini filtreleyerek yürüten algoritmik yapının kurulması.
* Düğüm ve İlişki Bazlı Arama Testleri: Filtreli BFS mimarisinin ve etkinlik katılım ilişkilerinin (Event/ATTENDS testleri) doğruluğunu test eden senaryoların backend seviyesinde kodlanması.

__Teslim Edilecekler Süreci:__
* Docker Konfigürasyonları: Tüm sistemin (Frontend, Backend) bağımlılık sorunu yaşamadan tek bir docker-compose up komutuyla çalışmasını sağlayan Dockerfile ve docker-compose.yml dosyalarının asenkron/mikroservis yaklaşımına uygun olarak yapılandırılması.

### Göktuğ YAZÇAYIR - 032490104 - apex11-dev

__Algoritmalar ve Veri Üretimi (Faz 2) Geliştirmesi:__

* Sosyal Ağ Analiz Ölçümleri: Ortak arkadaşlık bağlarını inceleyerek çalışan Triadic Closure (arkadaş önerisi mantığı) ve düğümlerin ağ genelindeki popülerliğini hesaplayan basit merkezilik ölçümlerinin (degree centrality) koda dökülmesi.
* Ardışık Çok Adımlı Sorgu Modeli: Projenin temel amaçlarından biri olan Kullanıcı -> Arkadaşlar -> Katıldığı Etkinlikler -> Bu Etkinliklerdeki Fotoğraflar örnek sorgu akışının, ardışık graf traversal işlemleriyle çalışacak şekilde kodlanması.
* Dinamik Sentetik Veri Üretimi: Küçük ve orta ölçekli graflar (yüzlerce düğüm) üzerinde sistem davranışını gözlemlemek, performans ve doğruluk testleri yapmak amacıyla programatik olarak rastgele düğüm ve kenar üreten stres testi motorunun tasarlanması.

__Spesifik Arayüz Gereksinimleri (Faz 3) Geliştirmesi:__

* 2D Node-Link Diyagramı Görselleştirmesi: Sorgu sonuçlarının vis.js kullanılarak 2D node-link diyagramı olarak gösterilmesi; Kullanıcıların daire, Fotoğrafların kare ve Etkinliklerin yıldız gibi farklı renk ve şekillerle temsil edilmesi altyapısının kurulması.
* Hash Table Entegreli Etkileşim Paneli: Graf üzerinde herhangi bir düğüme tıklandığında , o düğümün özelliklerinin yan panelde gösterilmesi ve bu bilgilerin arka plandaki Hash Table üzerinden hızlı erişimle elde edilmesini sağlayan API veri bağlantısının yapılması.

__Teslim Edilecekler Süreci:__
* UML Diyagramları

### Gizem YURTSEVEN - 0325900901

__Zorunlu Veri Yapıları (Faz 1) Entegrasyonu__

* Metin Tabanlı Önek Ağacı (Trie): Sosyal ağ içerisindeki metin tabanlı otomatik tamamlama (autocomplete) ve arama işlemlerini gerçekleştiren Trie yapısının main.c mimarisine entegre edilmesi.
* Dinamik Kayıt ve Terminal Doğrulaması: Kullanıcı düğümleri oluşturulurken isim mülkiyetlerinin insertTrie ile veri yapısına kaydedilmesi ve searchTrie fonksiyonunun arama doğruluğunun terminal test senaryoları ile jüriye kanıtlanması.

__Spesifik Arayüz Gereksinimleri (Faz 3) Modülleri:__

* İnteraktif Sorgu Çalıştırma Arayüzü: Kullanıcının belirli bir sorguyu çalıştırabilmesi için index.html üzerinde ID giriş alanlarını ve ardışık graf traversal sorgu akışını canlı olarak tetikleyecek Çok Adımlı Sorgu Modülü butonlarının tasarlanması.

__Teslim Edilecekler Süreci__

* AI API'sine gönderilen prompt'ların dökümünü de içeren kapsamlı proje raporunun uygun olarak hazırlanması.

### Selim KILIÇOĞLU - 032490103 - slmbinary

__Algoritmalar ve Veri üretimi (Faz 2) Testleri:__

* Algoritmik İşlevsellik Doğrulamaları: Sosyal ağ analiz modüllerinin, merkezilik ölçümlerinin ve arkadaş öneri mekanizmalarının sınır testlerinin yapılması ve çıktılarının kontrol edilmesi.

__Teslim Edilecekler Süreci__

* Zaman ve Uzay Karmaşıklığı Analizi: Projede sıfırdan yazılan tüm veri yapılarının ve arama/tarama algoritmalarının zaman ve uzay karmaşıklığı (Big-O) analiz dökümlerinin hazırlanarak teknik rapora aktarılması.
