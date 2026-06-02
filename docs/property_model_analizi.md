# Property (Özellik) Modül Yapısı ve Detaylı Analizi

Bu dokümanda, projedeki nesnelere dinamik nitelikler kazandıran `property.c` kaynak kod dosyasındaki fonksiyonların mimari analizi, işlevleri ve zaman/alan karmaşıklıkları incelenmiştir.

---

## 1. Sistematik Özet: Projede Ne İşe Yarar?

C dili yapısı gereği statik bir dildir ve çalışma zamanında (runtime) bir nesneye yeni alanlar eklenmesine izin vererek esnemez. Projedeki `Property` yapısı, bu kısıtlamayı aşmak için kurulmuş bir **Dinamik Key-Value (Anahtar-Değer) Hafıza Yönetimi** modülüdür.

* **Esnek Nesne Modeli:** Bir `Node` (Düğüm) oluşturulduğunda tipi "User" ise altına `addProperty` ile `name` ve `age` özellikleri eklenir. Eğer düğüm tipi "Photo" ise yine aynı struct kullanılarak altına `resolution` veya `file_size` özellikleri bağlanabilir. Kod hiçbir yapısal değişikliğe uğramadan her veriyi esnekçe saklar.
* **Bağlı Liste Mimarisi (Linked List):** Özellikler hafızada ardışık olarak değil, tek yönlü bağlı liste mantığıyla saklanır. Her özellik hücresi (`Property`), kendisinden sonraki özellik hüresinin bellek adresini (`next` pointer) işaret eder.

---

## 2. Fonksiyonların Zaman ve Alan Karmaşıklığı Analizi

Modülün kaynak kodunda yer alan çekirdek algoritmaların Big-O analizleri şu şekildedir ($K$: Bir düğüme bağlı toplam özellik sayısı):

### `addProperty` (Özellik Ekleme)
* **Kaynak Kod Mantığı:** Yeni bir özellik hücresi için bellekten yer ayırır (`malloc`), anahtar ve değer verilerini kopyalar (`strcpy`), ardından bu hücreyi listenin başına ekler:
  ```c
  newProp->next = *head;
  *head = newProp;
