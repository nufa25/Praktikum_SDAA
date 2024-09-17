#include <iostream>
using namespace std;

int pascal(int baris, int kolom) {
    if (kolom == 0 || kolom == baris) {
        return 1;
    }
    return pascal(baris - 1, kolom - 1) + pascal(baris - 1, kolom);
}

void segitiga(int tingkat) {
    for (int i = 0; i < tingkat; i++) {
        for (int j = 0; j <= i; j++) {
            cout << pascal(i, j) << " ";
        }
        cout << endl;
    }
}

int main() {
    segitiga(5);
    return 0;
}
