#include <iostream>
#include <string>
using namespace std;

struct Draft {
    string title, writer, genre, status, pembukuan_status;
    int total_pages;
    Draft* next;
};

// Daftar Naskah
struct QueueNode {
    Draft* draft;
    QueueNode* next;
};

// Naskah yang Lolos Penerbitan
struct StackNode {
    Draft* draft;
    StackNode* next;
};

QueueNode* front = nullptr;
QueueNode* rear = nullptr;
StackNode* top = nullptr;

void enqueue(Draft* new_draft) {
    QueueNode* new_node = new QueueNode;
    new_node->draft = new_draft;
    new_node->next = nullptr;
    
    if (rear == nullptr) {
        front = rear = new_node;
    } else {
        rear->next = new_node;
        rear = new_node;
    }
}

Draft* dequeue() {
    if (front == nullptr) return nullptr;

    QueueNode* temp = front;
    front = front->next;

    if (front == nullptr) {
        rear = nullptr;
    }

    Draft* draft = temp->draft;
    delete temp;
    return draft;
}

void push_stack(Draft* new_draft) {
    StackNode* new_node = new StackNode;
    new_node->draft = new_draft;
    new_node->next = top;
    top = new_node;
}

void show_queue() {
    if (front == nullptr) {
        cout << "\nTidak ada naskah dalam daftar.\n";
        return;
    }

    cout << "\n=== Daftar Naskah ===\n";
    QueueNode* temp = front;
    int i = 1;
    while (temp != nullptr) {
        cout << i << ". " << temp->draft->title << endl;
        temp = temp->next;
        i++;
    }
}

void show_stack() {
    if (top == nullptr) {
        cout << "\nTidak ada naskah yang lolos penerbitan.\n";
        return;
    }

    cout << "\n=== Daftar Naskah Lolos Penerbitan ===\n";
    StackNode* temp = top;
    int i = 1;
    while (temp != nullptr) {
        cout << i << ". " << temp->draft->title << endl;
        temp = temp->next;
        i++;
    }
}

void select_pembukuan_status(Draft* draft) {
    int select_pembukuan_status = 0;
    while (select_pembukuan_status < 1 || select_pembukuan_status > 2) {
        cout << "Status Pembukuan:\n";
        cout << "1. Telah Dibukukan\n";
        cout << "2. Dalam Proses Pembukuan\n";
        cout << "Pilih Status: ";
        cin >> select_pembukuan_status;
        if (select_pembukuan_status == 1) {
            draft->pembukuan_status = "Telah Dibukukan";
        } else if (select_pembukuan_status == 2) {
            draft->pembukuan_status = "Dalam Proses Pembukuan";
        } else {
            cout << "Input tidak valid!\n";
        }
    }
}

void add_draft() {
    Draft* new_draft = new Draft;

    cout << "\n=== Tambah Naskah ===\n";
    
    cout << "Judul: ";
    cin.ignore();
    getline(cin, new_draft->title);

    cout << "Penulis: ";
    getline(cin, new_draft->writer);

    cout << "Genre: ";
    getline(cin, new_draft->genre);

    cout << "Jumlah Halaman: ";
    cin >> new_draft->total_pages;

    int select_status = 0;
    while (select_status < 1 || select_status > 2) {
        cout << "Status Naskah:\n";
        cout << "1. Lolos Penerbitan\n";
        cout << "2. Dalam Proses Review\n";
        cout << "3. Ditolak/Revisi\n";
        cout << "Pilih Status: ";
        cin >> select_status;
        if (select_status == 1) {
            new_draft->status = "Lolos Penerbitan";
            select_pembukuan_status(new_draft);
            push_stack(new_draft); // Stack
        } 
        // Queue
        else if (select_status == 2) {
            new_draft->status = "Dalam Proses Review";
            enqueue(new_draft);
        } else if (select_status == 3) {
            new_draft->status = "Ditolak/Revisi";
            enqueue(new_draft); 
        } else {
            cout << "Input tidak valid!\n";
        }
    }
    cout << "\nNaskah telah ditambahkan.\n";
}

//Nampilin Daftar Naskah (Queue)
void detail_draft_queue() {
    show_queue();
    if (front == nullptr) return;

    int select;
    cout << "\nPilih naskah (masukkan nomor): ";
    cin >> select;

    QueueNode* temp = front;
    int i = 1;
    while (temp != nullptr && i < select) {
        temp = temp->next;
        i++;
    }

    if (temp != nullptr) {
        cout << "\n=== Detail Naskah ===\n";
        cout << "Judul: " << temp->draft->title << endl;
        cout << "Penulis: " << temp->draft->writer << endl;
        cout << "Genre: " << temp->draft->genre << endl;
        cout << "Jumlah Halaman: " << temp->draft->total_pages << endl;
        cout << "Status: " << temp->draft->status << endl;
    } else {
        cout << "Pilihan tidak valid!\n";
    }
}

// Nampilin Naskah yang Lolos Penerbitan (Stack)
void detail_draft_stack() {
    show_stack();
    if (top == nullptr) return;

    int select;
    cout << "\nPilih naskah: ";
    cin >> select;

    StackNode* temp = top;
    int i = 1;
    while (temp != nullptr && i < select) {
        temp = temp->next;
        i++;
    }

    if (temp != nullptr) {
        cout << "\n=== Detail Naskah ===\n";
        cout << "Judul: " << temp->draft->title << endl;
        cout << "Penulis: " << temp->draft->writer << endl;
        cout << "Genre: " << temp->draft->genre << endl;
        cout << "Jumlah Halaman: " << temp->draft->total_pages << endl;
        cout << "Status Pembukuan: " << temp->draft->pembukuan_status << endl;
    } else {
        cout << "Pilihan tidak valid!\n";
    }
}

// Ngedit Daftar Naskah (Queue)
void edit_draft() {
    show_queue();
    if (front == nullptr) return;

    int select;
    cout << "\nPilih naskah yang ingin diedit (masukkan nomor): ";
    cin >> select;

    QueueNode* temp = front;
    int i = 1;
    while (temp != nullptr && i < select) {
        temp = temp->next;
        i++;
    }

    if (temp != nullptr) {
        Draft* draft = temp->draft;

        cout << "\n=== Edit Naskah ===\n";
        cout << "Judul Baru: ";
        cin.ignore();
        getline(cin, draft->title);

        cout << "Penulis Baru: ";
        getline(cin, draft->writer);

        cout << "Genre Baru: ";
        getline(cin, draft->genre);

        cout << "Jumlah Halaman Baru: ";
        cin >> draft->total_pages;

        int select_status = 0;
        while (select_status < 1 || select_status > 3) {
            cout << "Status Naskah Baru:\n";
            cout << "1. Lolos Penerbitan\n";
            cout << "2. Dalam Proses Review\n";
            cout << "3. Ditolak/Revisi\n";
            cout << "Pilih Status: ";
            cin >> select_status;
            if (select_status == 1) {
                draft->status = "Lolos Penerbitan";
                select_pembukuan_status(draft);
                push_stack(draft);
                dequeue();
            } else if (select_status == 2) {
                draft->status = "Dalam Proses Review";
            } else if (select_status == 3) {
                draft->status = "Ditolak/Revisi";
            } else {
                cout << "Input tidak valid!\n";
            }
        }
        cout << "\nNaskah telah diedit.\n";
    } else {
        cout << "Pilihan tidak valid!\n";
    }
}


void delete_draft() {
    show_queue();
    if (front == nullptr) return;

    int select;
    cout << "\nPilih naskah yang ingin dihapus: ";
    cin >> select;

    QueueNode* temp = front;
    int i = 1;
    while (temp != nullptr && i < select) {
        temp = temp->next;
        i++;
    }
    if (temp != nullptr) {
        dequeue();
        cout << "Naskah telah dihapus.\n";
    } else {
        cout << "Pilihan tidak valid!\n";
    }
}

void menu() {
    int choice;
    do {
        cout << "\n=== Menu ===\n";
        cout << "1. Tambah Naskah\n";
        cout << "2. Tampilkan Daftar Naskah\n";
        cout << "3. Tampilkan Naskah yang Lolos Penerbitan\n";
        cout << "4. Edit Naskah\n";
        cout << "5. Hapus Naskah\n";
        cout << "6. Keluar\n";
        cout << "Pilih Menu: ";
        cin >> choice;

        switch (choice) {
            case 1: add_draft(); break;
            case 2: detail_draft_queue(); break;
            case 3: detail_draft_stack(); break;
            case 4: edit_draft(); break;
            case 5: delete_draft(); break;
            case 6: cout << "Anda memilih keluar\n"; break;
            default: cout << "Pilihan tidak valid! Silakan coba lagi.\n"; break;
        }
    } while (choice != 6);
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
            menu();
            login = true;
        }else{
            cout << "Password Salah! Silahkan coba lagi.\n";
        }
    }
    return 0;
}
