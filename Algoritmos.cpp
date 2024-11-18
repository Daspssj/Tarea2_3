#include <bits/stdc++.h>

using namespace std;

vector<int> costo_insercion(26);
vector<int> costo_eliminacion(26);
vector<vector<int>> costo_sustitucion(26, vector<int>(26));
vector<vector<int>> costo_transposicion(26, vector<int>(26));

void load_costos(){
    
    ifstream file;

    file.open("cost_insert.txt");
    for (int i = 0; i < 26; ++i) {
        file >> costo_insercion[i];
    }
    file.close();

    file.open("cost_delete.txt");
    for (int i = 0; i < 26; ++i) {
        file >> costo_eliminacion[i];
    }
    file.close();

    file.open("cost_replace.txt");
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
            file >> costo_sustitucion[i][j];
        }
    }
    file.close();
    
    file.open("cost_transpose.txt");
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
            file >> costo_transposicion[i][j];
        }
    }
    file.close();
}

int costo_sust(char a, char b) {
    return costo_sustitucion[a - 'a'][b - 'a'];
}

int costo_inser(char a) {
    return costo_insercion[a - 'a'];
}

int costo_elim(char a) {
    return costo_eliminacion[a - 'a'];
}

int costo_transpos(char a, char b) {
    return costo_transposicion[a - 'a'][b - 'a'];
}

int brute_force(string s1, string s2){
    int i = s1.length();
    int j = s2.length();

    if (i == 0) return j * costo_inser(s2[j - 1]);
    if (j == 0) return i * costo_elim(s1[i - 1]);

    int costo = costo_sust(s1[i - 1],s2[j - 1]);
    int minimo_costo = brute_force(s1.substr(0, i - 1), s2.substr(0, j - 1)) + costo;

    minimo_costo = min(minimo_costo, brute_force(s1.substr(0, i - 1), s2) + costo_elim(s1[i - 1]));
    minimo_costo = min(minimo_costo, brute_force(s1, s2.substr(0, j - 1)) + costo_inser(s2[j - 1]));

    if (i > 1 && j > 1 && s1[i] == s2[j - 1] && s1[i - 1] == s2[j]) {
        costo = costo_transpos(s1[i],s2[j]);
        minimo_costo = min(minimo_costo, brute_force(s1.substr(0, i - 1), s2.substr(0, j - 1)) + costo);
    }

    return minimo_costo;
}

int dynamic_progra(string& s1, string& s2){
    int n = s1.length();
    int m = s2.length();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1));

    for (int i = 0; i <= n; ++i) {
        dp[i][0] = i * costo_elim(s1[i - 1]);
    }

    for (int j = 0; j <= m; ++j) {
        dp[0][j] = j * costo_inser(s2[j - 1]);
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            
            int insertar = dp[i][j - 1] + costo_inser(s2[j - 1]);

            int eliminar = dp[i - 1][j] + costo_elim(s1[i - 1]);

            int sustituir = dp[i - 1][j - 1] + costo_sust(s1[i - 1], s2[j - 1]);

            int transponer = INT_MAX;   
            if (i > 1 && j > 1 && s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1]) {
                transponer = dp[i - 2][j - 2] + costo_transpos(s1[i - 1], s2[j - 1]);
            }

            dp[i][j] = min({insertar, eliminar, sustituir, transponer});
        } 
    }
    return dp[n][m];   
}

int main(){
    load_costos();
    
    int opcion;
    string archivo;

    cout << "Elija el archivo: \n1- Mismo tamanio\n2- S1 vacio\n3- S2 vacio\n4- S1 Mayor que S2\n5- S2 Mayor que S1\n6- Transpuesto" << endl;
    cin >> opcion;

    if(opcion == 1){
        archivo = "dataset_mismo_tamano.txt";
    }
    else if(opcion == 2){
        archivo = "dataset_s1_vacia.txt";
    }
    else if(opcion == 3){
        archivo = "dataset_s2_vacia.txt";
    }
    else if(opcion == 4){
        archivo = "dataset_s1>s2.txt";
    }
    else if(opcion == 5){
        archivo = "dataset_s1<s2.txt";
    }
    else if(opcion == 6){
        archivo = "dataset_transposicion.txt";
    }
    else{
        cout << "Opcion invalida" << endl;
        return 1;
    }

    ifstream file(archivo);
    if (!file.is_open()) {
        cout << "No se pudo abrir el archivo" << endl;
        return 1;
    }

    string s1, s2;
    
    while (getline(file, s1) && getline(file, s2)) {
        auto inicio1 = chrono::high_resolution_clock::now();
        cout << "Costo de edicion de fuerza bruta: " << brute_force(s1, s2) << endl;
        auto fin1 = chrono::high_resolution_clock::now();
        auto duraccion1 = chrono::duration_cast<chrono::microseconds>(fin1 - inicio1);
        cout << "Tiempo de ejecucion: " << duraccion1.count() << " microsegundos" << " / "<< duraccion1.count()/1000000 << " segundos" << endl;

        auto inicio2 = chrono::high_resolution_clock::now();
        cout << "Costo de edicion de programacion dinamica: " << dynamic_progra(s1, s2) << endl;
        auto fin2 = chrono::high_resolution_clock::now();
        auto duraccion2 = chrono::duration_cast<chrono::microseconds>(fin2 - inicio2);
        cout << "Tiempo de ejecucion: " << duraccion2.count() << " microsegundos" << " / "<< duraccion2.count()/1000000 << " segundos" << endl;
        
        cout << endl;
    }

    file.close();

    return 0;
}