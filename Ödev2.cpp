/****************************************************************************************
**
**
**                       SAKARYA ÜNİVERSİTESİ                                 
**              BİLGİSAYAR VE BİLİŞİM BİLİMLERİ FAKÜLTESİ                    
**                   BİLGİSAYAR MÜHENDİSLİĞİ BÖLÜMÜ                          
**                      PROGRAMLAMAYA GİRİŞ DERSİ                             
**                                                                       
**           ÖDEV NUMARASI    : 2                                    
**           ÖĞRENCİ ADI      : Özgür Demir                         
**           ÖĞRENCİ NUMARASI : B221210017                       
**           DERS GRUBU       : C                                     
**
**                                                                      
*****************************************************************************************/


#define _CRT_SECURE_NO_WARNINGS  // Güncel tarihi alırken sistem güvenlik uyarısı verdiği için bu çözüme başvurdum.
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <iomanip>

using namespace std;

struct date
{
    int day = 0;
    int month = 0;
    int year = 0;
};

class Kripto
{
private:

    double hesapBakiye;
    double kriptoAdet;
    double kriptoValue;

public:

    double tempKriptoValue = kriptoValue;
    unsigned int genelHesapId;
    unsigned int ozelHesapId;
    //unsigned int tempGenelHesapId = genelHesapId;
    //unsigned int tempOzelHesapId = ozelHesapId;
    Kripto() : genelHesapId(0), ozelHesapId(0),hesapBakiye(0), kriptoAdet(0), kriptoValue(1)
    {}
    //Kripto(int id, int bky) : hesapId(id), hesapBakiye(bky), kriptoValue(0.5)
    //{}

    // Bakiyeyi paylaşan fonksiyon
    double bakiyeSharer() const
    {
        double tempBakiye = hesapBakiye;
        return tempBakiye;
    }
    // Genel hesap oluşturan fonksiyon
    void genelHesapOlustur()
    {
        static int id = 0;
        id++;
        genelHesapId = id;

        cout << "Genel hesabınız oluşturuldu. Genel hesap id'niz: " << setw(5) << setfill('0') << genelHesapId << endl;

    }
    // Özel hesap oluşturan fonksiyon
    void ozelHesapOlustur()
    {
        static int id = 0;
        id++;
        ozelHesapId = id;

        cout << "Özel hesabınız oluşturuldu. Özel hesap id'niz: " << setw(5) << setfill('0') << ozelHesapId << endl;
    }
    //Bakiye ekleyen fonksiyon
    void bakiyeEkle(double lira)
    {
        char answer = 'h';
        do      // Kullanıcı işlem yapmaktan vazgeçerse diye döngü
        {
            cout << "Para yatırmadan önceki hesap bakiyeniz: " << hesapBakiye << "\nİşleme devam etmek istiyor musunuz(e/h)" << endl;
            cin >> answer;
            if (answer == 'h')   // Çıkış yapmak için koşul
            {
                cout << "Çıkış yapıldı.\n";
                break;
            }
        } while (answer != 'e' && answer != 'h');
        if (answer == 'e') // Onay koşulu
        {
            hesapBakiye += lira;
            cout << "Güncel bakiyeniz: " << hesapBakiye << endl;
        }
    }
    // Hızlı bir şekilde bakiye eklemesi yapan fonksiyon
    void bakiyeDirektEkle(double lira)
    {
        cout << "Bakiye ekleme başarılı, şimdi tekrar kripto satın almayı deneyebilirsiniz." << endl;
        hesapBakiye += lira;
        cout << "Güncel bakiyeniz: " << hesapBakiye << endl;
    }
    // Kripto satın almak için fonksiyon 
    void kriptoAl(double adet)
    {
        char answer = 'h';
        cout << "Anlık 1 adet kripto değeri, " << kriptoValue << "TL" << "\nYinede işlemi onaylıyor musunuz?(e/h) " << endl;
        cin >> answer;
        if (answer == 'e' || answer == 'E')     // Onay koşulu
        {
            double maliyet = adet * kriptoValue;
            if (maliyet > hesapBakiye) // Yapılmak istenen işlem için bakiye yeterli mi diye kontrol eden koşul
            {
                answer = 'h';
                cout << "Hesap bakiyeniz yetersiz. Bakiyeniz: " << hesapBakiye << "TL\nYapmak istediğiniz işlem maliyeti: " << maliyet << "TL" << endl;
                cout << "Bakiye eklemek ister misiniz?(e/h)" << endl; cin >> answer;
                double eklenecek = 0;
                if (answer == 'e' || answer == 'E')   // Onay koşulu
                {
                    do      // Hatalı girişi engelleyen döngü
                    {
                    cout << "Eklemek istediğiniz tutarı giriniz. " << endl; cin >> eklenecek;
                    } while (eklenecek <= 0);
                    bakiyeDirektEkle(eklenecek);       
                }
            }
            else
            {
                hesapBakiye -= maliyet;
                kriptoAdet += adet;
                cout << "Satın alma işlemi başarılı.\nGüncel bakiyeniz: " << hesapBakiye << "\nGüncel kripto miktarınız: " << kriptoAdet << endl;
            }
        }
        else cout << "Devam etmemeyi seçtiniz. Yine bekleriz." << endl;
    }
    // Kripto satmak için fonksiyon
    void kriptoSat(double adet)
    {
        char answer = 'h';
        cout << "Anlık 1 adet kripto değeri, " << kriptoValue << "TL" << "\nYinede işlemi onaylıyor musunuz?(e) " << endl;
        cin >> answer;
        if (answer == 'e' || answer == 'E')   // Onay koşulu
        {
            if (adet > kriptoAdet) // İşlem için kripto sahipliği yeterliliğini kontrol eden koşul
            {
                cout << "Hesabınızda yeterli kripto bulunmuyor. Sahip olduğunuz kripto adedi: " << kriptoAdet << "\nSatmak istediğiniz kripto adedi: " << adet << endl;
            }
            else
            {
                double gelir = adet * kriptoValue;
                hesapBakiye += gelir;
                kriptoAdet -= adet;
                cout << "Satış işlemi başarılı.\nGüncel bakiyeniz: " << hesapBakiye << "\nGüncel kripto mülkünüz: " << kriptoAdet << endl;
            }
        }
        else cout << "Devam etmemeyi seçtiniz. Yine bekleriz." << endl;
    }
    // Para çekme fonksiyonu
    void direktParaCek(int tutar)
    {
        hesapBakiye -= tutar;
        cout << "İşlem başarılı.\nPara çekimi sonrası bakiyeniz: " << hesapBakiye << endl;
    }
    // Genel hesap sorgulama fonksiyonu
    void genelHesapSorgu() const
    {
        cout << "Genel hesap bilgileriniz:\n" << "Hesap id: " << setw(5)<< setfill('0') << genelHesapId << "\nHesap bakiye: " << hesapBakiye << "\nKripto adediniz: " << kriptoAdet << endl;
    }
    // Özel hesap sorgulama fonksiyonu
    void ozelHesapSorgu() const
    {
        cout << "Özel hesap bilgileriniz: \n" << "Hesap id: " << setw(5) << setfill('0') << ozelHesapId << "\nHesap bakiye: " << hesapBakiye << "\nKripto adediniz: " << kriptoAdet << endl;
    }
    // Seçime göre genel veya özel hesap için kârı hesaplayan fonksiyon
    void kar()
    {
        if (kriptoAdet <= 0)    // Hesapta kripto bulunmuyorsa çıkış yapan koşul
        {
            cout << "Hiç kriptonuz bulunmadığı için kârınız da bulunmuyor.\nHemen şimdi kripto satın alarak kripto dünyasına en iyi elden giriş yapabilirsiniz.\n";
            return;
        }

        int cevap = 0;
        do  // Hangi hesap türüyle işlem yapılacağını seçmek için döngü
        {
            cout << "Hangi hesabınızla işlem yapmak istiyorsunuz. Genel hesap için 1'i, özel hesap için 2'yi tuşlayınız.\nFor english please press nine.\n";
            cin >> cevap;
        } while (cevap != 1 && cevap != 2 && cevap != 9);

        if (cevap == 1)     // Seçim genel hesap ise
        {
            if (genelHesapId == 0) // Hesap var mı yok mu  kontrol
            {
                cout << "Genel hesabınız bulunmadığı için devam edilemiyor. Hemen şimdi bir hesap oluşturabilirsiniz.\n";
                return;
            }
            cout << "Genel hesabınız ile işlem yapılıyor\n\n";

            int gun = 0;
            double gelir = 0.0;
            date tarih;
            time_t t = time(0);
            struct tm date = *gmtime(&t);
            cout << "Hesap açma tarihiniz: " << date.tm_mday << "/" << date.tm_mon + 1 << "/" << date.tm_year + 1900 << endl;
            
            do  // Kullanıcıdan doğru tarih bilgisi almak için döngü
            {
                cout << "Hangi tarihte işlem yaptığınızı giriniz veya hesap açma tarihinizden sonra herhangi bir günün tam tarihini giriniz.\n";
                cout << "Gün: "; cin >> tarih.day;
                cout << "Ay: "; cin >> tarih.month;
                cout << "Yıl: "; cin >> tarih.year;
            } while (tarih.day <= 0 || tarih.month <= 0 || tarih.year <= 0);
            cout << "Belirttiğiniz güncel tarih: " << tarih.day << "/" << tarih.month << "/" << tarih.year << endl;
            
            if ((tarih.day - date.tm_mday) < 0)   // Tarih hesabı için kontrol
            {
                tarih.month -= 1;
                tarih.day += 31;
            }
            gun += tarih.day - date.tm_mday;
            
            if ((tarih.month - date.tm_mon - 1) < 0) // Tarih hesabı için kontrol
            {
                tarih.year -= 1;
                tarih.month += 12;
            }
            gun += (tarih.month - date.tm_mon - 1) * 31;
            
            if ((tarih.year - date.tm_year - 1900) < 0) // Tarih hesabı için kontrol
            {
                cout << "Geçmiş bir tarih girdiniz veya hatalı tuşlama yaptınız. Tekrar deneyiniz.\n";
                return;
            }
            gun += (tarih.year - date.tm_year - 1900) * 365;
            
            if (gun < 0) // Tarih hesabı için kontrol
            {
                cout << "Geçmiş bir tarih girdiniz veya hatalı tuşlama yaptınız. Tekrar deneyiniz.\n";
                return;
            }
            
            if (gun == 0) // Tarih hesabı için kontrol
            {
                cout << "Aynı tarihte kârınız bulunmuyor.\n";
                return;
            }
            
            cout << "Sonuç olarak geçmiş gün sayısı: " << gun << endl;
            for (int i = 1; i <= gun; i++)   // Geçen gün sayısı için her gün ayrı ayrı kurallara göre kârı hesaplayan döngü
            {
                if (i % 15 == 0) // 15. gün için koşul
                {
                    kriptoValue = (kriptoValue * 95) / 100;
                }
                else
                {
                    kriptoValue = (kriptoValue * 101) / 100;
                }
            }
            gelir = kriptoAdet * kriptoValue;
            hesapBakiye += gelir;
            cout << "Genel hesap kurallarına göre kârınız: " << gelir << "TL'dir." << endl;
            cout << "Toplam hesap bakiyeniz:" << hesapBakiye << "TL" << endl;
        }

        if (cevap == 2)   // Seçim özel hesap ise
        {
            if (ozelHesapId == 0) // Hesap var mı yok mu kontrol
            {
                cout << "Özel hesabınız bulunmadığı için devam edilemiyor. Hemen şimdi bir hesap oluşturabilirsiniz.\n";
                return;
            }
            cout << "Özel hesabınız ile işlem yapılıyor\n\n";

            srand(time(0));
            int gunler[3] = { 0 };
            for (int i = 0; i < 3; i++)   // Bir ay içinden rastgele 3 günü seçmek için koşul
            {
                int rastgele = rand() % 1 + 30;
                gunler[i] = rastgele;
            }
            int gun = 0;
            double gelir = 0.0;
            date tarih;
            time_t t = time(0);
            struct tm date = *gmtime(&t);
            cout << "Hesap açma tarihiniz: " << date.tm_mday << "/" << date.tm_mon + 1 << "/" << date.tm_year + 1900 << endl;
            do  // Kullanıcıdan doğru tarih bilgisi almak için döngü
            {
                cout << "Hangi tarihte işlem yaptığınızı giriniz veya hesap açma tarihinizden sonra herhangi bir günün tam tarihini giriniz.\n";
                cout << "Gün: "; cin >> tarih.day;
                cout << "Ay: "; cin >> tarih.month;
                cout << "Yıl: "; cin >> tarih.year;
            } while (tarih.day <= 0 || tarih.month <= 0 || tarih.year <= 0);
            cout << "Belirttiğiniz güncel tarih: " << tarih.day << "/" << tarih.month << "/" << tarih.year << endl;
            
            if ((tarih.day - date.tm_mday) < 0)   // Tarih hesabı için kontrol
            {
                tarih.month -= 1;
                tarih.day += 31;
            }
            gun += tarih.day - date.tm_mday;
            
            if ((tarih.month - date.tm_mon - 1) < 0) // Tarih hesabı için kontrol
            {
                tarih.year -= 1;
                tarih.month += 12;
            }
            gun += (tarih.month - date.tm_mon - 1) * 31;
            
            if ((tarih.year - date.tm_year - 1900) < 0) // Tarih hesabı için kontrol
            {
                cout << "Geçmiş bir tarih girdiniz veya hatalı tuşlama yaptınız. Tekrar deneyiniz.\n";
                return;
            }
            gun += (tarih.year - date.tm_year - 1900) * 365;
            
            if (gun < 0) // Tarih hesabı için kontrol
            {
                cout << "Geçmiş bir tarih girdiniz veya hatalı tuşlama yaptınız. Tekrar deneyiniz.\n";
                return;
            }
            
            if (gun == 0) // Tarih hesabı için kontrol
            {
                cout << "Aynı tarihte kârınız bulunmuyor.\n";
                return;
            }
            cout << "Sonuç olarak geçmiş gün sayısı: " << gun << endl;

            for (int i = 1; i <= gun; i++)  // Özel hesap kurallarına göre kâr hesabı için döngü
            {
                if (i == gunler[0])   // Belirlenmiş 3 günden biri denk gelirse diye tespit etme koşulu
                {
                    kriptoValue = (kriptoValue * 90) / 100;
                }
                else if (i == gunler[1])    // Belirlenmiş 3 günden biri denk gelirse diye tespit etme koşulu
                {
                    kriptoValue = (kriptoValue * 90) / 100;
                }
                else if (i == gunler[2])    // Belirlenmiş 3 günden biri denk gelirse diye tespit etme koşulu
                {
                    kriptoValue = (kriptoValue * 90) / 100;
                }
                else
                {
                    kriptoValue = (kriptoValue * 105) / 100;
                }
            }
            gelir = kriptoAdet * kriptoValue;
            hesapBakiye += gelir;
            cout << "Genel hesap kurallarına göre karınız: " << gelir << "TL'dir." << endl;
            cout << "Toplam hesap bakiyeniz:" << hesapBakiye << "TL" << endl;
        }
        if (cevap == 9) // The condition to continue in english
        {
            cout << "There is actually no English here, it was just a joke. We don't prefer english here.\n";
            return;
        }
    }

};


int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "turkish");
    Kripto deneme1;
    int answer = 111;
    int a = 1;
    do      // Menü için döngü
    {
        cout << "\n---------------------------------" << endl;
        cout << "\t KRİPTO MERKEZİ \t" << endl;
        cout << "---------------------------------" << endl << endl;
        cout << "Kripto Merkezine hoş geldiniz." << endl << endl;
        cout << "\t     ***-MENÜ-***" << endl << endl;
        cout << "\t1-Genel Hesap OLuşturma:" << endl;
        cout << "\t2-Özel Hesap Oluşturma:" << endl;
        cout << "\t3-Genel Hesap Sorgulama:" << endl;
        cout << "\t4-Özel Hesap Sorgulama:" << endl;
        cout << "\t5-Kripto Alış:" << endl;
        cout << "\t6-Kripto Satış:" << endl;
        cout << "\t7-Para yatır:" << endl;
        cout << "\t8-Para çek:" << endl;
        cout << "\t9-Kazancını görüntüle:" << endl << endl;
        cout << "\t0-Çıkış:" << endl;
        time_t t = time(0);
        struct tm date = *gmtime(&t);
        cout << "Güncel tarih: " << date.tm_mday << "/" << date.tm_mon + 1 << "/" << date.tm_year + 1900 << endl << endl;
        cout << " Menüden yapmak istediğiniz işlemi seçiniz(1, 2, 3, vs)." << endl << endl;
        cin >> answer;
        double adet1 = 0.0;
        double adet2 = 0.0;
        int tutar = 0;
        int miktar = 0;
        switch (answer)     // Seçime göre işlem için switch yapısı
        {
        case 0:
            cout << "Kriptonun tek adresi \'Kripto Merkezi\'. Yine bekleriz." << endl;
            a = 0;
            break;
        case 1:
            deneme1.genelHesapOlustur();
            break;
        case 2:
            deneme1.ozelHesapOlustur();
            break;
        case 3:
            if (deneme1.genelHesapId == 0) // Hesap var mı yok mu kontrol
            {
                cout << "Hesabınızı sorgulamak için önce hesap oluşturmalısınız.\n";
                break;
            }
            deneme1.genelHesapSorgu();
            break;
        case 4:
            if (deneme1.ozelHesapId == 0)   // Hesap var mı yok mu kontrol
            {
                cout << "Hesabınızı sorgulamak için önce hesap oluşturmalısınız.\n";
                break;
            }
            deneme1.ozelHesapSorgu();
            break;
        case 5:
            if (deneme1.ozelHesapId == 0 && deneme1.genelHesapId == 0) // Kullanıcı hesap oluşturmuş mu kontrol koşulu
            {
                cout << "Kripto satın alabilmek için önce hesap oluşturmalısınız.\n";
                break;
            }
            do      // Hatalı girişi engellemek için döngü
            {
                cout << "Satın almak istediğiniz kripto adedini giriniz." << endl;
                cin >> adet1;
                char answer0 = 'a';
                if (adet1 <= 0) // Giriş hatalı ise
                {
                    cout << "Sıfır ve sıfırdan daha düşük miktarda alım yapılamaz, tekrar deneyiniz.\n" << "Çıkmak için 'x' tuşunu, devam etmek için herhangi bir tuşu giriniz.\n" ;
                    cin >> answer;
                    if (answer == 'x' || answer == 'X') break;  // Çıkış için koşul
                }
            } while (adet1 <= 0);
            deneme1.kriptoAl(adet1);
            break;
        case 6:
            if (deneme1.genelHesapId == 0 && deneme1.ozelHesapId == 0) // Kullanıcı hesap oluşturmuş mu kontrol koşulu
            {
                cout << "Kripto satabilmek için önce hesap oluşturmalısınız.\n";
                break;
            }
            do
            {
                cout << "Satmak istediğiniz kripto adedini giriniz." << endl;
                cin >> adet2;
                char answer = 'a';
                if (adet2 <= 0) // Giriş hatalı ise
                {
                    cout << "Sıfır ve sıfırdan daha düşük miktarda satım yapılamaz, tekrar deneyiniz.\n" << "Çıkmak için 'x' tuşunu, devam etmek için herhangi bir tuşu giriniz." << endl;
                    cin >> answer;
                    if (answer == 'x' || answer == 'X') break;  // Çıkış için koşul
                }
            } while (adet2 <= 0);
            deneme1.kriptoSat(adet2);
            break;
        case 7:
            if (deneme1.genelHesapId == 0 && deneme1.ozelHesapId == 0)  // Kullanıcı hesap oluşturmuş mu kontrol koşulu
            {
                cout << "Para yatırabilmek için önce hesap oluşturmalısınız.\n";
                break;
            }
            do  // Yatırılmak istenen tutarı doğru girmek için döngü
            {
                cout << "Yatırmak istediğiniz tutarı giriniz.(TL)\n";
                cin >> tutar;
                if (tutar <= 0)   // Giriş hatalı ise
                {
                    cout << "Eksik ya da hatalı tuşlama yaptınız. Tekrar deneyiniz.\n";
                }
                else
                {
                    deneme1.bakiyeEkle(tutar);
                    break;
                }
            } while (tutar <= 0);
            break;
        case 8:
            if (deneme1.genelHesapId == 0 && deneme1.ozelHesapId == 0)   // Kullanıcı hesap oluşturmuş mu kontrol koşulu
            {
                cout << "Para çekebilmek için önce hesap oluşturmalısınız.\n";
                break;
            }
            do  // Çekilmek istenen para bilgisinin doğru girilmesi için döngü
            {
                cout << "Güncel hesap bakiyeniz: " << deneme1.bakiyeSharer() << endl;
                if (deneme1.bakiyeSharer() <= 0)   // Bakiye yeterliliği kontrolü
                {
                    cout << "Bakiyeniz yetersiz. İşlem yapılamıyor.\n";
                    break;
                }
                else
                {
                    cout << "Çekmek istediğiniz tutarı giriniz.\n";
                    cin >> miktar;
                    if (miktar <= 0)  // Hatalı tuşlama kontrolü
                    {
                        cout << "Eksik ya da hatalı tuşlama yaptınız. Tekrar deneyiniz.\n";
                    }
                    else
                    {
                        deneme1.direktParaCek(miktar);
                    }
                }

            } while (miktar <= 0);
            break;
        case 9:
            if (deneme1.genelHesapId == 0 && deneme1.ozelHesapId == 0) // Kullanıcı hesap oluşturmuş mu kontrol koşulu
            {
                cout << "Kazanç görüntülemek için önce hesap oluşturmalısınız\n";
                break;
            }
            deneme1.kar();
            break;
        default:
            cout << "Sadece menüde bulunan seçeneklerden birini seçebilirsiniz.\n";
            break;
        }
    } while (a != 0);
}
