# STM32 ADC-DMA-PWM Kontrol Sistemi 🚀
**Öğrenci:** Gökhan Beyaz  
**No:** 25221304003

## 📝 Proje Tanıtımı
Bu çalışma, **STM32F030F4Px** mikrodenetleyicisi üzerinde ADC, DMA ve PWM birimlerinin entegre çalışmasını sergilemektedir. Sistem, potansiyometreden aldığı analog sinyali işleyerek PWM aracılığıyla LED parlaklığına dönüştürmektedir.

## 🛠 Teknik Konfigürasyon
| Birim | Pin | Görev |
| :--- | :--- | :--- |
| **ADC** | PA0 | Potansiyometre Girişi (12-bit okuma) |
| **PWM** | PA9 | LED Parlaklık Kontrolü (TIM1_CH2) |
| **EXTI** | PA1 | Sistem Kesme (Interrupt) Butonu |
| **UART** | PA2/PA3 | Log Bilgisi (9600 Baud) |

## 🕹 Canlı Simülasyon (Wokwi)
Projeyi tüm devre elemanlarıyla (potansiyometre, LED, direnç) canlı test etmek için tıklayınız:  
👉 [Wokwi Üzerinde Çalıştır](https://wokwi.com/projects/461394785041268737)

> **Önemli Not:** Wokwi simülasyonu `diagram.json` dosyası üzerinden tüm devre bağlantılarını otomatik olarak yüklemektedir. Eğer bir yükleme sorunu yaşanırsa, aşağıdaki görsel şemayı referans alınız.

## 📸 Simülasyon Test Çıktısı
Aşağıdaki görselde sistemin hatasız çalıştığı ve LED kontrolünün sağlandığı görülmektedir:

![Sistem Testi](image_26d567.png)

## 📂 Dosya Açıklamaları
* `ana.c`: Uygulama algoritması ve çevre birimi konfigürasyonlarını içerir.
* `STM32F030F4PX_FLASH.ld`: Bellek yerleşimi ve Linker Script ayarları.
