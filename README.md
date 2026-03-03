# ♟️ Chess-Analyzer

Bu proje, dinamik olarak oluşturulan bir satranç tahtası üzerinde vezirlerin hareket kabiliyetini ve engellerle olan etkileşimini analiz eden bir C++ uygulamasıdır. Yazılım mühendisliği eğitimim sürecinde; **algoritma kurma**, **dinamik bellek yönetimi** ve **dosya sistemleri (I/O)** konularındaki yetkinliklerimi geliştirmek amacıyla geliştirilmiştir.

## 🚀 Özellikler

* **Dinamik Tahta Üretimi:** Her çalıştırmada 5x5 ile 30x30 arasında rastgele boyutlarda bir tahta oluşturulur.
* **Engel Sistemi:** Tahta üzerine rastgele yerleştirilen engeller (X), vezirlerin hareket yollarını gerçekçi bir şekilde kısıtlar.
* **8 Yönlü Hareket Analizi:** Her bir vezir için yatay, dikey ve çapraz olmak üzere tüm olası kareler taranır.
* **Dosya Tabanlı Raporlama:** * Ham tahta verisi `input.txt` dosyasına kaydedilir.
    * Detaylı analiz sonuçları ve görselleştirilmiş tahta raporu `output.txt` dosyasında sunulur.

## 🛠️ Teknik Detaylar

* **Bellek Yönetimi:** 2D dinamik diziler kullanılmış ve bellek sızıntısını önlemek için uygun `delete[]` işlemleri uygulanmıştır.
* **Veri Yapıları:** Koordinat yönetimi için özel `struct` yapıları kullanılmıştır.
* **Algoritma:** Vezirlerin hareket yollarını engel veya tahta sınırına çarpana kadar izleyen, yön tabanlı bir tarama algoritması geliştirilmiştir.

## 💻 Nasıl Çalıştırılır?

1. Repoyu klonlayın.
2. Projeyi **Visual Studio 2026** ile açın.
3. Projeyi derleyin ve çalıştırın.
4. Menü üzerinden yeni bir tahta oluşturabilir ve analiz sonuçlarını terminal/dosya üzerinden inceleyebilirsiniz.

## 📊 Örnek Çıktı Görünümü

```text
CHESS BOARD
Q - Vezirler
X - Engeller
0 - Boş/Ulaşılamaz Hücre
+ - Hareket Edilebilir Alan
---------------------------
| Q  +  +  X  0 |
| +  +  0  0  0 |
| +  0  +  0  0 |
| X  0  0  Q  + |
| 0  0  0  +  + |
---------------------------
