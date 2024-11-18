#include <bits/stdc++.h>  

using namespace std;

string palabra_aleatoria(int n){
    string palabra;
    for (int i = 0; i < n; ++i) {
        palabra += 'a' + rand() % 26;
    }
    return palabra;
}

void generacion_data(string tipo){
    ofstream file("dataset_" + tipo + ".txt");

    if (!file.is_open()) {
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }

    if(tipo == "mismo_tamano"){
        for (int i = 0; i < 16; ++i) {
            string s1 = palabra_aleatoria(i);
            string s2 = palabra_aleatoria(i);
            file << s1 << endl << s2 << endl;
        }
    }
    else if(tipo == "s1>s2"){
        for (int i = 0; i < 16; ++i) {
            string s1 = palabra_aleatoria(i + 1);
            string s2 = palabra_aleatoria(i/2);
            file << s1 << endl << s2 << endl;
        }
    }
    else if(tipo == "s1<s2"){
        for (int i = 0; i < 16; ++i) {
            string s1 = palabra_aleatoria(i/2);
            string s2 = palabra_aleatoria(i + 1);
            file << s1 << endl << s2 << endl;
        }
    }
    else if(tipo == "s1_vacia"){
        for (int i = 0; i < 16; ++i) {
            string s1 = "";
            string s2 = palabra_aleatoria(i);
            file << s1 << endl << s2 << endl;
        }
    }
    else if(tipo == "s2_vacia"){
        for (int i = 0; i < 16; ++i) {
            string s1 = palabra_aleatoria(i);
            string s2 = "";
            file << s1 << endl << s2 << endl;
        }
    }
    else if(tipo == "transposicion"){
        for (int i = 0; i < 16; ++i) {
            string s2 = palabra_aleatoria(i + 1);
            string s1 = s2;
            for (string::size_type j = 0; j < s1.size() - 1; j += 2) {
                swap(s1[j], s1[j + 1]);
            }
            file << s1 << endl << s2 << endl;
        }
    }
    else{
        cout << "Tipo de dataset no valido" << endl;
    }
}

int main(){
    srand(time(0));
    string tipo;
    for (int i = 0; i < 6; ++i) {
        if(i == 0) tipo = "mismo_tamano";
        if(i == 1) tipo = "s1>s2";
        if(i == 2) tipo = "s1<s2";
        if(i == 3) tipo = "s1_vacia";
        if(i == 4) tipo = "s2_vacia";
        if(i == 5) tipo = "transposicion";

        generacion_data(tipo);
    }
    

    return 0;
}