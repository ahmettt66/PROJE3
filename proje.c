#include <stdio.h>
#include <stdlib.h>

// Fonksiyon: Dosyada sayı var mı kontrol
int dosyada_var_mi(long long sayi, FILE *dosya) {
    rewind(dosya);  // Dosyanın başına git
    long long mevcut_sayi;

    // Dosyayı satır satır oku
    while (fscanf(dosya, "%lld", &mevcut_sayi) != EOF) {
        if (mevcut_sayi == sayi) {
            return 1;
        }
    }

    return 0;
}

// Kontrol ve dosya yazma fonksiyonu
void kontrol(long long sayi, FILE *dosya, FILE *casus) {
    int uzunluk = 0;
    long long temp_sayi = sayi;

    // Sayı uzunluğunu hesaplamama
    if (temp_sayi == 0) {
        uzunluk = 1;
    } else {
        while (temp_sayi != 0) {
            temp_sayi /= 10;
            uzunluk++;
        }
    }

    printf("Girilen sayinin karakter uzunlugu: %d\n", uzunluk);

    if (uzunluk != 11) {
        printf("Lutfen 11 haneli bir sayi giriniz.\n");
    } else {
        if (dosyada_var_mi(sayi, dosya)) {
            // Sayı zaten varsa, casus.txt dosyasına yaz
            printf("Bu sayi zaten dosyada var. Casus dosyasina yaziliyor...\n");
            if (fprintf(casus, "%lld\n", sayi) < 0) {
                printf("Casus dosyasına yazarken bir hata oluştu.\n");
            } else {
                fflush(casus);  // Yazma işlemi tamamlandıktan sonra dosyayı temizle
                printf("Sayi basariyla casus dosyasina yazildi.\n");
            }
        } else {
            // Sayı yoksa, dosya.txt dosyasına yaz
            if (fprintf(dosya, "%lld\n", sayi) < 0) {
                printf("Dosyaya yazarken bir hata oluştu.\n");
            } else {
                fflush(dosya);  // Yazma işlemi tamamlandıktan sonra dosyayı temizle
                printf("Sayi basariyla dosyaya yazildi.\n");
            }
        }
    }
}

int main() {
    FILE *dosya = fopen("dosya.txt", "a+");  // Dosyayı okuma ve yazma modunda aç
    if (dosya == NULL) {
        printf("Dosya açılamadı.\n");
        return 1;
    }

    FILE *casus = fopen("casus.txt", "a");  // Casus dosyasını ekleme modunda aç
    if (casus == NULL) {
        printf("Casus dosyası açılamadı.\n");
        fclose(dosya);
        return 1;
    }

    long long sayi = 0;

    // Kullanıcıdan sayı alma
    while (1) {
        printf("Bir sayi girin (-1 ile cikis): ");
        scanf("%lld", &sayi);

        if (sayi == -1) {
            printf("Program sonlandiriliyor...\n");
            break;
        }

        kontrol(sayi, dosya, casus);  // Sayıyı kontrol et ve uygun dosyaya yaz
    }

    fclose(dosya);
    fclose(casus);
    return 0;
}