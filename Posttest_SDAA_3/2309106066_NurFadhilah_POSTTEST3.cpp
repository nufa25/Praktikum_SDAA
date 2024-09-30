#include <iostream>

using namespace std;

struct draft_node {
    string title, writer, genre, status;
    int total_pages;
    draft_node* next;
};

draft_node* head = nullptr;

void select_status(string& status) {
    int select_status = 0;
    while (select_status < 1 || select_status > 3){
        cout << "Status Naskah:\n";
        cout << "1. Dalam Proses Review\n";
        cout << "2. Lolos Penerbitan\n";
        cout << "3. Ditolak\n";
        cout << "Pilih Status: ";
        cin >> select_status;
        if (select_status == 1){
            status = "Dalam Proses Review";
        }
        else if (select_status == 2){
            status = "Lolos Penerbitan";
        }
        else if (select_status == 3){
            status = "Ditolak";
        }
        else{
            cout << "Input tidak valid!" << endl;
        }
    }
}

void add_draft(draft_node*& head) {
    draft_node* new_draft = new draft_node;

    cout << "\n=== Menambahkan Naskah ===\n";
    
    cout << "Judul: ";
    cin.ignore();
    getline(cin, new_draft->title);

    cout << "Penulis: ";
    getline(cin, new_draft->writer);

    cout << "Genre: ";
    getline(cin, new_draft->genre);

    cout << "Jumlah Halaman: ";
    cin >> new_draft->total_pages;

    select_status(new_draft->status);

    new_draft->next = head;
    head = new_draft;

    cout << "\nNaskah baru telah ditambahkan." << endl;
}

void read_draft(draft_node*& head) {
    if (head == nullptr) {
        cout << "\nNaskah tidak tersedia.\n";
        return;
    }

    cout << "\n=== Daftar Naskah ===\n";
    draft_node* temp = head;
    int i = 1;
    while (temp != nullptr) {
        cout << i << ". " << temp->title << endl;
        temp = temp->next;
        i++;
    }
}

void detail_draft(draft_node*& head) {
    read_draft(head);
    if (head == nullptr) return;

    int select;
    cout << "\nPilih Naskah (masukkan nomor): ";
    cin >> select;

    draft_node* temp = head;
    int i = 1;
    while (temp != nullptr && i < select) {
        temp = temp->next;
        i++;
    }

    if (temp != nullptr) {
        cout << "\n=== Detail Naskah ===\n";
        cout << "Judul: " << temp->title << endl;
        cout << "Penulis: " << temp->writer << endl;
        cout << "Genre: " << temp->genre << endl;
        cout << "Jumlah Halaman: " << temp->total_pages << endl;
        cout << "Status Naskah: " << temp->status << endl;
    } else {
        cout << "Pilihan tidak valid!\n";
    }
}

void edit_draft(draft_node*& head) {
    read_draft(head);
    if (head == nullptr) return;

    int select;
    cout << "\nPilih naskah yang ingin diedit: ";
    cin >> select;

    draft_node* temp = head;
    int i = 1;
    while (temp != nullptr && i < select) {
        temp = temp->next;
        i++;
    }

    if (temp != nullptr) {
        cin.ignore();
        cout << "\n=== Edit Naskah ===\n";

        cout << "Masukkan judul baru: ";
        getline(cin, temp->title);

        cout << "Masukkan penulis baru: ";
        getline(cin, temp->writer);

        cout << "Masukkan genre baru: ";
        getline(cin, temp->genre);

        cout << "Masukkan jumlah halaman baru: ";
        cin >> temp->total_pages;

        select_status(temp->status);

        cout << "\nNaskah telah diedit.\n";
    } else {
        cout << "Pilihan tidak valid!\n";
    }
}

void delete_draft(draft_node*& head) {
    read_draft(head);
    if (head == nullptr) return;

    int select;
    cout << "\nPilih naskah yang ingin dihapus: ";
    cin >> select;

    if (select == 1) {
        draft_node* temp = head;
        head = head->next;
        delete temp;
        cout << "\nNaskah telah dihapus.\n";
    } else {
        draft_node* temp = head;
        int i = 1;
        while (temp != nullptr && i < select - 1) {
            temp = temp->next;
            i++;
        }

        if (temp != nullptr && temp->next != nullptr) {
            draft_node* temp_delete = temp->next;
            temp->next = temp->next->next;
            delete temp_delete;
            cout << "\nNaskah berhasil dihapus!\n";
        } else {
            cout << "Pilihan tidak valid!\n";
        }
    }
}

int main() {
    string password;
    string password_login = "nufa25";
    bool login = false;

    while (!login) {
        cout << "\n";
        cout << "=== Selamat Datang ===\n\n";
        cout << "Silahkan Masukkan Password: ";
        cin >> password;

        if (password == password_login) {
            cout << "\n\n=== Manajemen Draft Penerbitan ===\n";

            int select = 0;
            while (select != 5) {
                cout << "\nMenu:\n";
                cout << "1. Lihat Daftar Draft\n";
                cout << "2. Tambahkan Draft Baru\n";
                cout << "3. Edit Draft\n";
                cout << "4. Hapus Draft\n";
                cout << "5. Keluar\n";
                cout << "Pilih menu: ";
                cin >> select;

                switch (select) {
                    case 1:
                        detail_draft(head);
                        break;
                    case 2:
                        add_draft(head);
                        break;
                    case 3:
                        edit_draft(head);
                        break;
                    case 4:
                        delete_draft(head);
                        break;
                    case 5:
                        cout << "Anda Memilih Keluar.\n";
                        return 0;
                    default:
                        cout << "Pilihan tidak tersedia. Silakan coba lagi.\n";
                        break;
                }
            }
            login = true;
        } else {
            cout << "Password Salah! Silahkan coba lagi.\n";
        }
    }

    return 0;
}
