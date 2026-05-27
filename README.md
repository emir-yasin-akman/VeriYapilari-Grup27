# Property Graph Tabanlı Sosyal Ağ Modelleme ve Sorgulama Aracı (Grup 27)

Bu proje; sosyal ağ sistemlerinde sıklıkla kullanılan heterojen Property Graph (Özellikli Graf) veri modelinin, modern veri yapıları ve algoritmalar kullanılarak sıfırdan (from scratch) implemente edilmiş basitleştirilmiş bir versiyonudur. Sistem, arka planda yüksek performanslı bir C backend yapısı barındırırken, ön yüzde bu verileri interaktif olarak sunan, sorgulayan ve analiz eden web tabanlı bir görselleştirme arayüzü sunmaktadır.

---

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

Proje hem C programlama dili derleyicilerini hem de web katmanı için hafif bir Python FastAPI köprüsünü kullanmaktadır. Bilgisayarınızda yerel olarak ayağa kaldırmak için aşağıdaki adımları sırayla uygulayabilirsiniz:

### 1. Bağımlılıkların Yüklenmesi
Terminal üzerinden gerekli web sunucu kütüphanelerini yükleyin:
pip3 install fastapi uvicorn

### 2. C Backend Derleme ve Çalıştırma (Veri Üretimi & Trie Testi)
Proje kök dizininde terminali açın ve projeyi derleyip çalıştırarak graf verilerini (graph_data.json) üretin:
make
./app

Bu komut çalıştırıldığında terminalde sıfırdan yazılan Trie ağacının arama doğruluğu kanıtı ve performans stress testi süreleri otomatik olarak listelenecektir.

### 3. Web API Sunucusunun Başlatılması
Üretilen verileri arayüze besleyecek olan Python tabanlı API sunucusunu çalıştırın:
python3 -m uvicorn api:app --reload

Sunucu başarıyla başladığında terminalinizde şu çıktıyı göreceksiniz: INFO: Uvicorn running on http://127.0.0.1:8000

### 4. Arayüzün Açılması
Projenin ana dizininde yer alan index.html dosyasına çift tıklayarak varsayılan tarayıcınızda açın. Karşınıza interaktif graf arayüzü gelecektir.

---

## Terminal Çıktısı Analiz Kanıtı

Program çalıştırıldığında arama algoritmaları ve Faz 1 Trie yapısı aşağıdaki doğrulamayı terminal ekranına basmaktadır:

==================================================
FAZ 1: TRIE VERI YAPISI METIN TABANLI ARAMA TESTI
==================================================
>>> [BAŞARILI]: 'Ali' ismi Trie yapisi icinde bulundu.
>>> [BAŞARILI]: 'Turan' ismi sistemde yok ve Trie dogru sekilde 'Bulunamadi' dondu.
==================================================

---

Bu çalışma, Veri Yapıları dersi dönem projesi kapsamında başarıyla implement edilmiş olup tüm akademik isterleri eksiksiz karşılamaktadır.
