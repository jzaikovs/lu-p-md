/*
H10. Doti divi binari faili f1 un f2, kuru komponentes ir ieraksts ar strukturu: atslega (int), vertiba (neparsniedz 30 simbolus).
Failu komponentes sakartotas pec atslegam dilstosa seciba.
Uzrakstit programmu, kas apvieno failus f1 un f2 faila f3 ta, lai ari f3 komponentes butu dilstosa seciba
(failos nedrikst paradities divas komponentes ar vienadu atslegu vertibu).
Uzrakstit ari paligprogrammas, kas lauj izveidot failus f1 un f2 un izdruka uz ekrana faila saturu.

risinājuma autors: @jzaikovs
*/

#include <fstream>
#include <vector>

using namespace std;

struct elem {
    int key;
    char value[30];

    elem() {
        this->key = 0;
    }

    elem(int key, const char * value) {
        this->key = key;
        bool cpy = true;

        for (int i = 0; i < 30; i++) {
            this->value[i] = '\0';
            if (cpy) {
                if (value[i] == '\0')
                    cpy = false;
                else
                    this->value[i] = value[i];
            }
        }
    }

    void print() {
        printf("[%d]%s\n", key, value);
    }
};

vector<elem> read(const char * fileName) {
    vector<elem> all;

    fstream file;
    file.open(fileName, ios::in | ios::binary);
    while (file.good()) {
        elem e;
        file.read((char*)&e, sizeof(elem));
        if (file.good()) {
            all.push_back(e);
        }
    }

    return all;
}

void write(const char * fileName, vector<elem> elements) {

    fstream file;
    file.open(fileName, ios::out | ios::binary | ios::trunc );
    for (int i = 0; i < elements.size(); i++) {
        elem e = elements[i];
        file.write((char*)&e, sizeof(elem));
    }
}

void print_elements(vector<elem> elements) {
    for (int i = 0; i < elements.size(); i++) {
        elements[i].print();
    }
}

vector<elem> merge(vector<elem> a, vector<elem> b) {

    // apvienojam divus masīvus vienā - a
    for (int i = 0; i < b.size(); i++) {

        bool exists = false;
        // jā pārbauda vai 'a' saraksts jau nesatur tādu elementu b[i]
        for (int j = 0; j < b.size(); j++) {
            if (a[j].key == b[i].key) {
                exists = true;
                break;
            }
        }

        if (exists == false) { // elements neeksistē
            a.push_back(b[i]);
        }
    }
    return a;
}

vector<elem> sort(vector<elem> a) {
    // burbuļu kārtošanas algoritms
    for (int i = 0; i < a.size(); i++) {
        for (int j = i+1; j < a.size(); j++) {
            elem _a = a[i], _b = a[j];
            if (_b.key > _a.key) {
                a[i] = _b;
                a[j] = _a;
            }
        }
    }
    return a;
}

void _test_create_f1_f2() {
    vector<elem> v;

    v.push_back(elem(0, "apple"));
    v.push_back(elem(1, "microsoft"));
    v.push_back(elem(3, "google"));
    write("f1.in", v);

    v.clear();
    v.push_back(elem(1, "microsoft"));
    v.push_back(elem(5, "facebook"));
    write("f2.in", v);
}

int main() {

    _test_create_f1_f2();

    vector<elem> a = read("f1.in");
    vector<elem> b = read("f2.in");

    vector<elem> c = sort(merge(a, b));

    //print_elements(c);
    write("f3.out", c);

    return 0;
}