#include <iostream>
#include <fstream>
#include <string>

class ElemanDugumu {
public:
    int veri;
    ElemanDugumu* sonraki;
};

class BagliListe {
public:
    BagliListe();
    ~BagliListe();
    void ekle(int veri); // Verilen veriyi bagli listenin sonuna yeni bir dUgUm olarak ekler.
    void yazdir(); // Bagli listenin elemanlarini sirayla yazdirir.
    float ortalama(); // Bagli listedeki veri degerlerinin ortalamasini hesaplar ve döndUrUr.
    int dugumSayisi(); // Bagli listedeki dUgUm sayisini döndUrUr.
    int dosyaSatirSayisi(const std::string& dosyaAdi); // Verilen dosyadaki satir sayisini döndUrUr.
    int enFazlaDugumSayisi(BagliListe** listeDizisi, int satirSayisi);
    ElemanDugumu* bas; // Bagli listenin baþini (ilk dUgUmU) gösteren iþaretçi.
};

BagliListe::BagliListe() {
    bas = nullptr;
}

BagliListe::~BagliListe() {
    ElemanDugumu* suanki = bas;
    while (suanki != nullptr) {
        ElemanDugumu* sonraki = suanki->sonraki;
        delete suanki;
        suanki = sonraki;
    }
}

void BagliListe::ekle(int veri) {
    ElemanDugumu* yeniDugum = new ElemanDugumu();
    yeniDugum->veri = veri;
    yeniDugum->sonraki = nullptr;

    if (bas == nullptr) {
        bas = yeniDugum;
    }
    else {
        ElemanDugumu* suanki = bas;
        while (suanki->sonraki != nullptr) {
            suanki = suanki->sonraki;
        }
        suanki->sonraki = yeniDugum;
    }
}

void BagliListe::yazdir() {
    ElemanDugumu* suanki = bas;
    while (suanki != nullptr) {
        std::cout << suanki->veri << " -> ";
        suanki = suanki->sonraki;
    }
    std::cout << "SON" << std::endl;
}

float BagliListe::ortalama() {
    float toplam = 0.0;
    int sayac = 0;

    ElemanDugumu* suanki = bas;
    while (suanki != nullptr) {
        toplam += suanki->veri;
        sayac++;
        suanki = suanki->sonraki;
    }

    if (sayac > 0) {
        return static_cast<float>(toplam) / sayac;
    }
    else {
        return 0.0f;
    }
}

int BagliListe::dugumSayisi() {
    int sayac = 0;
    ElemanDugumu* suanki = bas;

    while (suanki != nullptr) {
        sayac++;
        suanki = suanki->sonraki;
    }

    return sayac;
}

int dosyaSatirSayisi(const std::string& dosyaAdi) {
    std::ifstream dosya(dosyaAdi);
    if (!dosya) {
        std::cerr << "Dosya açilamiyor." << std::endl;
        return -1;
    }

    int satirSayisi = 0;
    std::string satir;
    while (std::getline(dosya, satir)) {
        satirSayisi++;
    }

    dosya.close();

    return satirSayisi;
}

int enFazlaDugumSayisi(BagliListe** listeDizisi, int satirSayisi) {
    int enFazlaDugumSayisi = 0;

    for (int i = 0; i < satirSayisi; i++) {
        int suankiSayi = listeDizisi[i]->dugumSayisi();
        if (suankiSayi > enFazlaDugumSayisi) {
            enFazlaDugumSayisi = suankiSayi;
        }
    }

    return enFazlaDugumSayisi;
}

int main() {
    std::ifstream dosya("veriler.txt");
    std::string dosyaAdi = "veriler.txt";
    int satirSayisi = dosyaSatirSayisi(dosyaAdi);
    if (satirSayisi == -1) {
        return 1;
    }
    std::string satir;

    BagliListe** ustListeler = new BagliListe * [satirSayisi];
    BagliListe** altListeler = new BagliListe * [satirSayisi];

    int satirIndeks = 0;
    while (std::getline(dosya, satir)) {
        BagliListe* ustListe = new BagliListe();
        BagliListe* altListe = new BagliListe();

        int i = 0;
        while (i < satir.length()) {
            if (isdigit(satir[i]) && i + 1 < satir.length() && isdigit(satir[i + 1])) {
                int rakam1 = satir[i] - '0';
                int rakam2 = satir[i + 1] - '0';
                int sayi = rakam1 * 10 + rakam2;

                ustListe->ekle(rakam1);
                altListe->ekle(rakam2);

                i += 2;
            }
            else {
                i++;
            }
        }

        ustListeler[satirIndeks] = ustListe;
        altListeler[satirIndeks] = altListe;

        satirIndeks++;
    }
    dosya.close();


    std::cout << std::endl;
    for (int i = 0; i < satirSayisi; i++) {
        std::cout << "Ust Bagli Liste[" << i << "]: ";
        ustListeler[i]->yazdir();
    }
    std::cout << std::endl;

    for (int i = 0; i < satirSayisi; i++) {
        std::cout << "Alt Bagli Liste[" << i << "]: ";
        altListeler[i]->yazdir();
    }

    int KonumA, KonumB;
    std::cout << "\nKonum A: ";
    std::cin >> KonumA;
    std::cout << "Konum B: ";
    std::cin >> KonumB;

    if (KonumA >= 0 && KonumA < satirSayisi && KonumB >= 0 && KonumB < satirSayisi) {
        BagliListe* geciciUst = ustListeler[KonumA];
        BagliListe* geciciAlt = altListeler[KonumB];

        ustListeler[KonumA] = geciciAlt;
        altListeler[KonumB] = geciciUst;
    }
    else {
        std::cout << "Geçersiz Konumlar. LUtfen geçerli Konumlar girin." << std::endl;
    }

    std::cout << "\nTakas Yapildiktan Sonraki Yeni Listeler:\n";
    std::cout << std::endl;
    for (int i = 0; i < satirSayisi; i++) {
        std::cout << "Ust Bagli Liste[" << i << "]: ";
        ustListeler[i]->yazdir();
    }

    std::cout << std::endl;

    for (int i = 0; i < satirSayisi; i++) {
        std::cout << "Alt Bagli Liste[" << i << "]: ";
        altListeler[i]->yazdir();
    }

    std::cout << std::endl;

    int enFazlaDugumUst = enFazlaDugumSayisi(ustListeler, satirSayisi);
    double* dugumOrtalamalariUstListeler = new double[enFazlaDugumUst]();
    int* dugumElemanSayilariUstListeler = new int[enFazlaDugumUst]();
    for (int i = 0; i < enFazlaDugumUst; i++) {
        dugumOrtalamalariUstListeler[i] = 0.0;
        dugumElemanSayilariUstListeler[i] = 0;
    }

    for (int i = 0; i < satirSayisi; i++) {
        ElemanDugumu* suanki = ustListeler[i]->bas;
        int dugumIndeks = 0;
        int elemanSayisi = 0;
        while (suanki) {
            dugumOrtalamalariUstListeler[dugumIndeks] += suanki->veri;
            dugumElemanSayilariUstListeler[dugumIndeks] += 1;
            suanki = suanki->sonraki;
            dugumIndeks++;
        }
    }

    int indeks = 0;
    int toplamListe = 0;
    for (int i = 0; i < enFazlaDugumUst; i++) {
        toplamListe = dugumElemanSayilariUstListeler[i];
        dugumOrtalamalariUstListeler[i] /= toplamListe;
    }

    double toplamOrtalamalarUstListeler = 0.0;
    for (int i = 0; i < enFazlaDugumUst; i++) {
        toplamOrtalamalarUstListeler += dugumOrtalamalariUstListeler[i];
    }

    std::cout << "Ust: " << toplamOrtalamalarUstListeler << std::endl;

    int enFazlaDugumAlt = enFazlaDugumSayisi(altListeler, satirSayisi);
    double* dugumOrtalamalariAltListeler = new double[enFazlaDugumAlt]();
    int* dugumElemanSayilariAltListeler = new int[enFazlaDugumAlt]();
    for (int i = 0; i < enFazlaDugumAlt; i++) {
        dugumOrtalamalariAltListeler[i] = 0;
        dugumElemanSayilariAltListeler[i] = 0;
    }
    for (int i = 0; i < satirSayisi; i++) {
        ElemanDugumu* suanki = altListeler[i]->bas;
        int dugumIndeks = 0;
        int elemanSayisi = 0;
        while (suanki) {
            dugumOrtalamalariAltListeler[dugumIndeks] += suanki->veri;
            dugumElemanSayilariAltListeler[dugumIndeks] += 1;
            suanki = suanki->sonraki;
            dugumIndeks++;
        }
    }

    indeks = 0;
    toplamListe = 0;
    for (int i = 0; i < enFazlaDugumAlt; i++) {
        toplamListe = dugumElemanSayilariAltListeler[i];
        dugumOrtalamalariAltListeler[i] /= toplamListe;
    }

    double toplamOrtalamalarAltListeler = 0.0;
    for (int i = 0; i < enFazlaDugumAlt; i++) {
        toplamOrtalamalarAltListeler += dugumOrtalamalariAltListeler[i];
    }

    std::cout << "Alt: " << toplamOrtalamalarAltListeler << std::endl;

    for (int i = 0; i < satirSayisi; i++) {
        delete ustListeler[i];
        delete altListeler[i];
    }
    delete[] ustListeler;
    delete[] altListeler;
    delete[] dugumOrtalamalariUstListeler;
    delete[] dugumElemanSayilariUstListeler;
    delete[] dugumOrtalamalariAltListeler;
    delete[] dugumElemanSayilariAltListeler;

    return 0;
}
