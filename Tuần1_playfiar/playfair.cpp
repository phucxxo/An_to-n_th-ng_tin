#include <iostream>
#include <string>
#include <cctype>

using namespace std;






class Playfair {


private:


    char matrix[5][5];


    void generateMatrix(string key) {
        bool used[26] = {false};
        used['J' - 'A'] = true; 

        int row = 0, col = 0;

        for (char c : key) {
            if (isalpha(c)) {
                c = toupper(c);
                if (c == 'J') c = 'I';
                if (!used[c - 'A']) {
                    matrix[row][col++] = c;
                    used[c - 'A'] = true;
                    if (col == 5) { col = 0; row++; }
                }
            }
        }

        for (char c = 'A'; c <= 'Z'; c++) {
            if (!used[c - 'A']) {
                matrix[row][col++] = c;
                used[c - 'A'] = true;
                if (col == 5) { col = 0; row++; }
            }
        }
    }






    void findPosition(char c, int &row, int &col) {
        if (c == 'J') c = 'I';
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                if (matrix[i][j] == c) {
                    row = i;
                    col = j;
                    return;
                }
    }





public:
    Playfair(string key) {
        generateMatrix(key);
    }

    void printMatrix() {
        cout << "\n--- Ma tran khoa ---\n";
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++)
                cout << matrix[i][j] << " ";
            cout << endl;
        }
    }





    string formatPlaintext(string text) {
        string formatted = "";

        for (char c : text) {
            if (isalpha(c)) {
                c = toupper(c);
                formatted += (c == 'J') ? 'I' : c;
            }
        }

        string digraphs = "";

        for (size_t i = 0; i < formatted.length(); i++) {
            digraphs += formatted[i];

            if (i + 1 < formatted.length()) {
                if (formatted[i] == formatted[i + 1]) {
                    digraphs += 'X';
                } else {
                    digraphs += formatted[i + 1];
                    i++;
                }
            } else {
                digraphs += 'X';
            }
        }

        return digraphs;
    }

    string encrypt(string text) {
        string pt = formatPlaintext(text);
        string ct = "";

        for (size_t i = 0; i < pt.length(); i += 2) {
            int r1, c1, r2, c2;
            findPosition(pt[i], r1, c1);
            findPosition(pt[i + 1], r2, c2);

            if (r1 == r2) { 
                ct += matrix[r1][(c1 + 1) % 5];
                ct += matrix[r2][(c2 + 1) % 5];
            }
            else if (c1 == c2) { 
                ct += matrix[(r1 + 1) % 5][c1];
                ct += matrix[(r2 + 1) % 5][c2];
            }
            else { 
                ct += matrix[r1][c2];
                ct += matrix[r2][c1];
            }

            ct += " "; 
        }

        return ct;
    }
};








int main() {
    string key = "MONARCHY";
    
    string plaintext = "Do you like to study a Cryptography course";

    Playfair cipher(key);

    cipher.printMatrix();

    cout << "\nPlaintext ban dau: " << plaintext << endl;

    string formatted = cipher.formatPlaintext(plaintext);
    cout << "Plaintext da xu ly: " << formatted << endl;

    string ciphertext = cipher.encrypt(plaintext);
    cout << "Ciphertext: " << ciphertext << endl;

    return 0;
}