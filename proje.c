#include <stdio.h>
#include <stdlib.h>

//Dosyada sayı var mı kontrolü
int dosyada_var_mi(long long sayi, FILE *giris) {
    rewind(giris);  // giris dosyasının başına git
    long long mevcut_sayi;

    // Dosyayı satır satır oku
    while (fscanf(giris, "%lld", &mevcut_sayi) != EOF) {
        if (mevcut_sayi == sayi) {
            return 1;
        }
    }

    return 0;
}

// Kontrol ve dosya yazma fonksiyonu
void kontrol(long long sayi, FILE *giris, FILE *casus) {
    int uzunluk = 0;
    long long yedek_sayi = sayi;

    // Sayı uzunluğunu hesaplamama
    if (yedek_sayi == 0) {
        uzunluk = 1;
    } else {
        while (yedek_sayi != 0) {
            yedek_sayi /= 10;
            uzunluk++;
        }
    }

    if (uzunluk != 11) {
        printf("Lutfen 11 haneli bir kimlik numarasi giriniz.\n");
    } else {
        if (dosyada_var_mi(sayi, giris)) {
            // Kimlik numarası zaten varsa, casus.txt dosyasına yaz
            printf("Bu kimlik numarasi zaten giris dosyasinda var. Casus dosyasina yaziliyor...\n");
            fprintf(casus, "%lld\n", sayi);
            fflush(casus);  // Yazma işlemi tamamlandıktan sonra dosyayı temizle
        } else {
            // Kimlik numarası yoksa, dosya.txt dosyasına yaz
            fprintf(giris, "%lld\n", sayi);
            fflush(giris);  // Yazma işlemi tamamlandıktan sonra dosyayı temizle
            printf("Kimlik numarasi basariyla giris dosyasina yazildi.\n");
        }
    }
}

int main() {
    FILE *giris = fopen("giris.txt", "a+");  // Dosyayı okuma ve yazma modunda aç
    if (giris == NULL) {
        printf("Giris dosyasi acilamadi.\n");
        return 1;
    }

    FILE *casus = fopen("casus.txt", "a");  // Casus dosyasını ekleme modunda aç
    if (casus == NULL) {
        printf("Casus dosyasi acilamadi.\n");
        fclose(giris);
        return 1;
    }

    long long sayi = 0;

    // Kullanıcıdan kimlik numarası alma
    while (1) {
        printf("11 Haneli bir kimlik numarasi girin (-1 ile cikis): ");
        scanf("%lld", &sayi);

        if (sayi == -1) {
            printf("Program sonlandiriliyor...\n");
            break;
        }

        kontrol(sayi, giris, casus);  // Kimlik numarasını kontrol et ve uygun dosyaya yaz
    }

    fclose(giris);
    fclose(casus);
    return 0;
}