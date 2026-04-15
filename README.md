# STM32 ADC-DMA-PWM Kontrol Sistemi 🚀
**Öğrenci:** Gökhan Beyaz  
**No:** 25221304003

## 📝 Proje Tanıtımı
Bu proje, **STM32F030F4Px** mikrodenetleyicisi kullanılarak, analog verinin işlenmesi ve donanım kontrolü üzerine kurgulanmıştır. Sistem, potansiyometreden aldığı analog sinyali işleyerek PWM aracılığıyla LED parlaklığına dönüştürmektedir.

## 🛠 Teknik Konfigürasyon
| Birim | Pin | Görev |
| :--- | :--- | :--- |
| **ADC** | PA0 | Potansiyometre okuma (12-bit) |
| **PWM** | PA9 | LED Parlaklık Kontrolü (TIM1_CH2) |
| **EXTI** | PA1 | Sistem Kesme (Interrupt) Butonu |
| **UART** | PA2/PA3 | Seri Terminal Log Bilgisi (9600 Baud) |

## 🕹 Canlı Simülasyon (Wokwi)
Projeyi tarayıcı üzerinden canlı test etmek için aşağıdaki bağlantıyı kullanabilirsiniz:
👉 [Wokwi Simülasyonu İçin Tıklayınız](https://wokwi.com/projects/367244067477216257)

## 📸 Simülasyon Test Çıktısı
Aşağıdaki görselde sistemin hatasız çalıştığı ve LED kontrolünün sağlandığı görülmektedir:

![Sistem Testi](image_26d567.png)

## 📂 Dosya Açıklamaları
* `ana.c`: Projenin ana algoritması, kesme yapıları ve HAL sürücü konfigürasyonlarını içerir.
* `STM32F030F4PX_FLASH.ld`: Mikrodenetleyici bellek haritası ve linker ayarları.
