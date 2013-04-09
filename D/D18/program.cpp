#include <iostream>
#include "program.h"
using namespace std;

Skola::Skola() {} // konstruktors
Skola::~Skola() // destruktors
{
    cout << endl << "Objekts ir izdzeests!" << endl;
}

void Skola::mainit(int indeks,int skaits)
{
    klases[indeks-1]=skaits;
}

void Skola::drukat()
{
    kopaa = 0;
    for(int i=0; i<12; i++)
        cout << i+1 << ".klasee ir " << klases[i] << " skoleenu!" << endl;  // izdrukaajam skoleenu skaitu pa klaseem
    for(int i=0; i<12; i++)
        kopaa+=klases[i];
    cout << endl << "Kopeejais skoleenu skaits: " << kopaa << endl; // izdrukaajam kopeejo skoleenu skaitu
}

void Skola::aprekins()
{
    int min=klases[0], max=klases[0];

    cout << "Skoleenu skaits skolaa: " << kopaa << endl;
    cout << "Videejais skoleenu skaits klasee: " << (double)kopaa/12.0 << endl; // izdrukaajam videejo skoleenu skaitu klasee
    for (int i=0; i<12; i++)
    {
        if (klases[i] < min) min = klases[i]; // atrodam min skoleenu skaitu klasee
        if (klases[i] > max) max = klases[i]; // atrodam max skoleenu skaitu klasee
    }
    cout << "MIN skoleenu skaits klasee: " << min << endl;
    cout << "MAX skoleenu skaits klasee: " << max << endl;
}

