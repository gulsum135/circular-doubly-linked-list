#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Dugum{
    char harf;
    int index;
    struct Dugum* onceki;
    struct Dugum* sonraki;
}Dugum;
Dugum* Dugum_Ekle(Dugum* ilkdugum, char harf, int index) {
    Dugum* yeni =(Dugum*)malloc(sizeof(Dugum));
    yeni->harf= harf;
    yeni->index= index;

    if(ilkdugum==NULL){
        yeni->sonraki=yeni;
        yeni->onceki=yeni;
        return yeni;
    }
    Dugum* son= ilkdugum->onceki;
    son->sonraki= yeni;
    yeni->onceki= son;
    yeni->sonraki= ilkdugum;
    ilkdugum->onceki= yeni;
    return ilkdugum;
}

void Liste_Yazdir(Dugum* ilkdugum){
    if(ilkdugum==NULL){
        printf("Liste bos.\n");
        return;}
    Dugum* gecici=ilkdugum;
    do{
        printf("[%c,%d] ",gecici->harf,gecici->index);
        gecici=gecici->sonraki;
    }while(gecici!=ilkdugum);
    printf("\n");
}

int Dugum_Sayisi(Dugum* ilkdugum) {
    if(ilkdugum==NULL) return 0;
    int sayac=0;
    Dugum* gecici=ilkdugum;
    do{
    sayac++;
    gecici=gecici->sonraki;
    }while(gecici!=ilkdugum);
    return sayac;
}

Dugum* HareketEt(Dugum* baslangic, int index) {
    Dugum* konum = baslangic;
    int adim=abs(index);
    for(int i=0; i<adim; i++) {
        konum=(index>0) ? konum->sonraki :konum->onceki;
    }
    return konum;
}

Dugum* Dugum_Isle(Dugum* ilkdugum, char* sonrakiHarf) {
    if (ilkdugum == NULL) return NULL;
    Dugum* konum= ilkdugum;

    while (Dugum_Sayisi(ilkdugum)>1) {
        int index = konum->index;

        if (index == 0) {
            int yeniIndex =rand()%9-4;
            printf("\nEklenecek harf ve index: [%c,%d]\n", *sonrakiHarf, yeniIndex);
            ilkdugum = Dugum_Ekle(ilkdugum, *sonrakiHarf, yeniIndex);
            konum= HareketEt(konum, yeniIndex);
            (*sonrakiHarf)++;
            continue;
        }

        Dugum* silinecek=konum;
        konum=HareketEt(konum,index);

        silinecek->onceki->sonraki=silinecek->sonraki;
        silinecek->sonraki->onceki=silinecek->onceki;

        if(silinecek==ilkdugum){
            ilkdugum = silinecek->sonraki;
        }

        printf("\nSilinecek harf ve index:[%c,%d]\n\n",silinecek->harf,silinecek->index);
        free(silinecek);
        Liste_Yazdir(ilkdugum);
    }

    return ilkdugum;
}

int main(){
    Dugum* ilkdugum = NULL;
    char harf = 'A';
    int N= 6;
 srand(time(NULL)); 
 
    for (int i = 0; i <N; i++) {
        int rastgeleIndex=(rand() % 9) - 4;
        ilkdugum=Dugum_Ekle(ilkdugum,harf++,rastgeleIndex);
    }

    printf("liste:\n");
    Liste_Yazdir(ilkdugum);

    ilkdugum=Dugum_Isle(ilkdugum,&harf);

    printf("\nSon kalan dugum:\n");
    Liste_Yazdir(ilkdugum);

    free(ilkdugum); 
    return 0;
}
