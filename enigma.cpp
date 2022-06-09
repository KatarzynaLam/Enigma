#include <iostream>
#include <cstdio>
using namespace std;

#define WIRNIK1 0
#define WIRNIK2 1
#define WIRNIK3 2

struct Wirnik { 
        int *wejscie; 
        int *wyjscie;
int *deltaWejscie;
int *deltaWyjscie;
int liczbaPunktowObrotu;
int *punktyObrotu; 
};

struct Reflektor {
        int *definicja;
        int *delta;
};

struct Enigma { 
        int ileWirnikow;
        int *indeksWirnika; 
        int *startPos; 
        int indeksReflektora;

};

struct Wejscie {
        int alfabet;
        int liczbaWirnikow;
        int liczbaReflektorow;
        int liczbaEnigm;
        int wiadomosc;
        int wiadomoscIndeks;
};

struct Wyjscie {
        int szyfr;
};

struct Obrot {
        int poczatekTab;
        int pozycja;
        bool czyObrot;
};

void deklarowanieTabObrot(Obrot *obrot, int indeks) {

        (obrot + indeks)->poczatekTab = 0;
        (obrot + indeks)->czyObrot = false;
        (obrot + indeks)->pozycja = 1;

}

void obrotNaStartPos(Obrot *obrot, int dlugosc, int iloscObr, int indeks) {
        for (int i = 1; i < iloscObr; i++) {
                (obrot + indeks)->poczatekTab = ((obrot + indeks)->poczatekTab + 1) % dlugosc;
                (obrot + indeks)->pozycja = iloscObr;
        }
}

int czyPunktObrotu(Wirnik *wirnik, Obrot *obrot, int indeks, int indeksWirnika, int delta, int dlugosc, int temp) {
        
        for (int i = 0; i < (wirnik+indeksWirnika)->liczbaPunktowObrotu; i++) {
                temp = ((wirnik + indeksWirnika)->punktyObrotu[i]) + delta;
                if (temp == 0) {
                        temp = dlugosc;
                }
                if ((obrot + indeks)->pozycja  == temp){
                        return 1;
                }
        }
        return 0;
}

void obrotJedenWirnik(Obrot *obrot, int dlugosc) {
        (obrot + WIRNIK1)->poczatekTab = ((obrot + WIRNIK1)->poczatekTab + 1) % dlugosc;
        (obrot + WIRNIK1)->pozycja = ((obrot + WIRNIK1)->pozycja) % dlugosc + 1;
        (obrot + WIRNIK1)->czyObrot = true;
}
void obrotDwaWirniki(Obrot *obrot, int dlugosc, Wirnik *wirnik, Enigma *enigma, int temp) {
        if ((obrot + WIRNIK1)->czyObrot == true) { //jesli 1 sie obrocil

                (obrot + WIRNIK1)->poczatekTab = ((obrot + WIRNIK1)->poczatekTab + 1) % dlugosc;                        //OBROT 1
                (obrot + WIRNIK1)->pozycja = ((obrot + WIRNIK1)->pozycja) % dlugosc + 1;

                if ((wirnik + enigma->indeksWirnika[WIRNIK1])->liczbaPunktowObrotu != 0 && czyPunktObrotu(wirnik, obrot, WIRNIK1, enigma->indeksWirnika[WIRNIK1], 0, dlugosc, temp) == 1) {

                        (obrot + WIRNIK2)->poczatekTab = ((obrot + WIRNIK2)->poczatekTab + 1) % dlugosc;                                //^ sprawdzenie czy wirnik 1 jest na p obrotu 
                        (obrot + WIRNIK2)->pozycja = ((obrot + WIRNIK2)->pozycja) % dlugosc + 1;                                                // obroc wirnik 2
                        (obrot + WIRNIK2)->czyObrot = true;
                }
        }

        else { //jesli 1 sie nie obrocil jeszcze to obroc go
                (obrot + WIRNIK1)->poczatekTab = ((obrot + WIRNIK1)->poczatekTab + 1) % dlugosc;
                (obrot + WIRNIK1)->pozycja = ((obrot + WIRNIK1)->pozycja) % dlugosc + 1;
                (obrot + WIRNIK1)->czyObrot = true;
        }
}

void obrotWiecejWirnikow(Obrot *obrot, int dlugosc, Wirnik *wirnik, Enigma *enigma, int temp) {


        if ((obrot + WIRNIK1)->czyObrot == true && (czyPunktObrotu(wirnik, obrot, WIRNIK1, enigma->indeksWirnika[WIRNIK1], (-1),dlugosc, temp) == 1)){

                if ((obrot + WIRNIK2)->czyObrot == true && (czyPunktObrotu(wirnik, obrot, WIRNIK2, enigma->indeksWirnika[WIRNIK2], (-1),dlugosc, temp) == 1)) {

                        (obrot + WIRNIK1)->poczatekTab = ((obrot + WIRNIK1)->poczatekTab + 1) % dlugosc;
                        (obrot + WIRNIK1)->pozycja = ((obrot + WIRNIK1)->pozycja) % dlugosc + 1;
                        (obrot + WIRNIK2)->poczatekTab = ((obrot + WIRNIK2)->poczatekTab + 1) % dlugosc;
                        (obrot + WIRNIK2)->pozycja = ((obrot + WIRNIK2)->pozycja) % dlugosc + 1;
                        (obrot + WIRNIK3)->poczatekTab = ((obrot + WIRNIK3)->poczatekTab + 1) % dlugosc;
                        (obrot + WIRNIK3)->pozycja = ((obrot + WIRNIK3)->pozycja) % dlugosc + 1;
        
                }
                else {
                        (obrot + WIRNIK1)->poczatekTab = ((obrot + WIRNIK1)->poczatekTab + 1) % dlugosc;
                        (obrot + WIRNIK1)->pozycja = ((obrot + WIRNIK1)->pozycja) % dlugosc + 1;
                        (obrot + WIRNIK2)->poczatekTab = ((obrot + WIRNIK2)->poczatekTab + 1) % dlugosc;
                        (obrot + WIRNIK2)->pozycja = ((obrot + WIRNIK2)->pozycja) % dlugosc + 1;
                        (obrot + WIRNIK2)->czyObrot = true;
                }
        
        }
        else if ((czyPunktObrotu(wirnik, obrot, WIRNIK2, enigma->indeksWirnika[WIRNIK2], (-1), dlugosc, temp) == 1)&& ((obrot + WIRNIK1)->czyObrot == true)&& (obrot + WIRNIK2)->czyObrot == true) {
                (obrot + WIRNIK1)->poczatekTab = ((obrot + WIRNIK1)->poczatekTab + 1) % dlugosc;
                (obrot + WIRNIK1)->pozycja = ((obrot + WIRNIK1)->pozycja) % dlugosc + 1;
                (obrot + WIRNIK2)->poczatekTab = ((obrot + WIRNIK2)->poczatekTab + 1) % dlugosc;
                (obrot + WIRNIK2)->pozycja = ((obrot + WIRNIK2)->pozycja) % dlugosc + 1;
                (obrot + WIRNIK3)->poczatekTab = ((obrot + WIRNIK3)->poczatekTab + 1) % dlugosc;
                (obrot + WIRNIK3)->pozycja = ((obrot + WIRNIK3)->pozycja) % dlugosc + 1;
        }
        else {
                obrotJedenWirnik(obrot, dlugosc);
        }
}


void obrotSzyfrowanie(Obrot *obrot, Wirnik *wirnik, Enigma *enigma, int dlugosc, int iloscWirnikow, int temp) {

        if (iloscWirnikow == 1) {                //jesli 1 wirnik
                obrotJedenWirnik(obrot, dlugosc);
        }

        else if (iloscWirnikow == 2) {           // jesli 2 wirniki
                obrotDwaWirniki(obrot, dlugosc, wirnik, enigma, temp);
        }

        else{            //(3 wirniki lub wiecej)
                obrotWiecejWirnikow(obrot, dlugosc, wirnik, enigma, temp);
        }
}

void szyfrowanieWejscieWirnika(int delta, Wejscie *wejscie, Wyjscie *wyjscie) {

        wyjscie->szyfr = (delta + wejscie->wiadomoscIndeks) % wejscie->alfabet + 1;

        if (wyjscie->szyfr < 1) {
                wyjscie->szyfr = (wejscie->alfabet + delta + wejscie->wiadomoscIndeks) % wejscie->alfabet + 1;
        }
}

void szyfrowanieReflektor(int reflektor, Wyjscie *wyjscie) {

        wyjscie->szyfr = reflektor;
}

void szyfrowanieWyjscieWirnika(int delta, Wejscie *wejscie, Wyjscie *wyjscie) {

        wyjscie->szyfr = (delta + wejscie->wiadomoscIndeks) % wejscie->alfabet + 1;

        if (wyjscie->szyfr < 1) {
                wyjscie->szyfr = (wejscie->wiadomoscIndeks + wejscie->alfabet + delta) % wejscie->alfabet + 1;
        }
}

void start(Obrot *obrot, Wyjscie *wyjscie, Wejscie *wejscie,Enigma *enigma, Reflektor *reflektor, Wirnik *wirnik) {

        int temp = 0;

        for (int i = 0; i < enigma->ileWirnikow; i++) {

                deklarowanieTabObrot(obrot, i);
                obrotNaStartPos(obrot, wejscie->alfabet, enigma->startPos[i], i);
        }
        while (1) {
                scanf_s("%d", &wejscie->wiadomosc);
                if (wejscie->wiadomosc != 0) {
                        wyjscie->szyfr = wejscie->wiadomosc;
                        obrotSzyfrowanie(obrot, wirnik, enigma, wejscie->alfabet, enigma->ileWirnikow, temp);

                        for (int i = 0; i < enigma->ileWirnikow; i++) {          //przejscie przez wejscia wirnikow
                                wejscie->wiadomoscIndeks = wyjscie->szyfr - 1;
                                szyfrowanieWejscieWirnika((wirnik + enigma->indeksWirnika[i])->deltaWejscie[((obrot + i)->poczatekTab + wejscie->wiadomoscIndeks) % wejscie->alfabet], wejscie, wyjscie);
                        }

                        wejscie->wiadomoscIndeks = wyjscie->szyfr - 1;
                        szyfrowanieReflektor(((reflektor + enigma->indeksReflektora)->definicja[wejscie->wiadomoscIndeks]), wyjscie);           //przejscie przez reflektor

                        for (int i = (enigma->ileWirnikow - 1); i >= 0; i--) {           //przejscie przez wyjscia wirnikow
                                wejscie->wiadomoscIndeks = wyjscie->szyfr - 1;
                                szyfrowanieWyjscieWirnika((wirnik + enigma->indeksWirnika[i])->deltaWyjscie[(wejscie->wiadomoscIndeks + (obrot + i)->poczatekTab) % wejscie->alfabet], wejscie, wyjscie);
                        }

                        printf("%d ", wyjscie->szyfr);
                }
                else {
                        cout << endl;
                        break;
                }
        }
}

int main()
{
        Wejscie wejscie;
        Wyjscie wyjscie;

        scanf_s("%d", &wejscie.alfabet);

        //------------------------------------------------------------------------------------
        //DEKLAROWANIE WIRNIKOW
        //------------------------------------------------------------------------------------

        scanf_s("%d", &wejscie.liczbaWirnikow);
        Wirnik *wirnik = new Wirnik[wejscie.liczbaWirnikow];
        //deklarowanie tablic wirnikow kolejnych indeksow
        for (int i = 0; i < wejscie.liczbaWirnikow; i++) {
                (wirnik + i)->wejscie = new int[wejscie.alfabet];
                (wirnik + i)->wyjscie = new int[wejscie.alfabet];
                (wirnik + i)->deltaWejscie = new int[wejscie.alfabet];
                (wirnik + i)->deltaWyjscie = new int[wejscie.alfabet];
                //przypisywanie definicji wirnikow;
                for (int j = 0; j < wejscie.alfabet; j++) {
                        scanf_s("%d", &(wirnik + i)->wejscie[j]);
                }
                for (int j = 0; j < wejscie.alfabet; j++) {
                        (wirnik + i)->wyjscie[(wirnik + i)->wejscie[j] - 1] = (j + 1);                                  

                }
                for (int j = 0; j < wejscie.alfabet; j++) {
                        (wirnik + i)->deltaWejscie[j] = (wirnik + i)->wejscie[j] - (j + 1);
                        (wirnik + i)->deltaWyjscie[j] = (wirnik + i)->wyjscie[j] - (j + 1);
                }

                //deklarowanie punktow obrotu
                scanf_s("%d", &(wirnik + i)->liczbaPunktowObrotu); //ile punktow obrotu
                (wirnik + i)->punktyObrotu = new int[(wirnik + i)->liczbaPunktowObrotu];
                for (int j = 0; j < (wirnik + i)->liczbaPunktowObrotu; j++) {
                        scanf_s("%d", &(wirnik + i)->punktyObrotu[j]);
                }
        }

        //----------------------------------------------------------------------------------------------------------
        //DEKLAROWANIE REFLEKTOROW
        //----------------------------------------------------------------------------------------------------------

        scanf_s("%d", &wejscie.liczbaReflektorow);
        Reflektor *reflektor = new Reflektor[wejscie.liczbaReflektorow];

        for (int i = 0; i < wejscie.liczbaReflektorow; i++) { //tworzenie tablicy
                (reflektor + i)->definicja = new int[wejscie.alfabet];
                (reflektor + i)->delta = new int[wejscie.alfabet];
                for (int j = 0; j < wejscie.alfabet; j++) { //przypisanie wartosci
                        scanf_s("%d", &(reflektor + i)->definicja[j]);
                        (reflektor + i)->delta[j] = (reflektor + i)->definicja[j] - (j + 1);
                }
        }

        //----------------------------------------------------------------------------------------------------------
        //DEKLAROWANIE ENIGM
        //----------------------------------------------------------------------------------------------------------

        scanf_s("%d", &wejscie.liczbaEnigm);
        Enigma enigma;

        for (int i = 0; i < wejscie.liczbaEnigm; i++) {//petla - ile ma być wczytanych szyfrów
                scanf_s("%d", &enigma.ileWirnikow);
                enigma.indeksWirnika = new int[enigma.ileWirnikow];
                enigma.startPos = new int[enigma.ileWirnikow];
                Obrot *obrot = new Obrot[enigma.ileWirnikow];

                for (int j = 0; j < enigma.ileWirnikow; j++) {
                        scanf_s("%d", &enigma.indeksWirnika[j]); //przypisuje indeks wirnika w enigmie
                        scanf_s("%d", &enigma.startPos[j]); //przypisuje startowa pozycje dla wirnikow poszczegolnych
                }
                scanf_s("%d", &enigma.indeksReflektora); //indeks reflektora

                start(obrot, &wyjscie, &wejscie, &enigma, reflektor, wirnik);
                delete[] enigma.indeksWirnika;
                delete[] enigma.startPos;
                delete[] obrot;
        
        }
        for (int i = 0; i < wejscie.liczbaWirnikow; i++) {

                delete[](wirnik + i)->punktyObrotu;
                delete[](wirnik + i)->wejscie;
                delete[](wirnik + i)->wyjscie;
                delete[](wirnik + i)->deltaWejscie;
                delete[](wirnik + i)->deltaWyjscie;
        }
        delete[] wirnik;
        delete[] reflektor;
        
        return 0;
}
