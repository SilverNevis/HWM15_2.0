#pragma once

#include "sha1.h"
#include "string.h"

#define SIZE 10
#define LOGINLENGTH 10

class Chat {
public:
    Chat();
    void reg(const char _login[LOGINLENGTH], const char _pass[], int pass_length);
    bool login(const char _login[LOGINLENGTH], const char _pass[], int pass_length);

    friend void test(Chat& c);

    ~Chat();  // Деструктор

private:
    struct AuthData {
        AuthData() :
            login(""),
            pass_sha1_hash(nullptr) {
        }
        ~AuthData() {
            if (pass_sha1_hash != nullptr)
                delete[] pass_sha1_hash;
        }
        AuthData(const char _login[LOGINLENGTH], uint* sh1) {
            strncpy_s(login, _login, _TRUNCATE);
            pass_sha1_hash = sh1;
        }
        AuthData& operator=(const AuthData& other) {
            strncpy_s(login, other.login, _TRUNCATE);

            if (pass_sha1_hash != nullptr)
                delete[] pass_sha1_hash;
            pass_sha1_hash = new uint[SHA1HASHLENGTHUINTS];

            memcpy_s(pass_sha1_hash, SHA1HASHLENGTHBYTES, other.pass_sha1_hash, SHA1HASHLENGTHBYTES);

            return *this;
        }
        char login[LOGINLENGTH];
        uint* pass_sha1_hash;
    };

    AuthData* data;
    int data_count;

    // Хеш-таблица
    static const int table_size = 20;  // Размер хеш-таблицы
    AuthData** hash_table;

    int hash_function(const char _login[LOGINLENGTH]);
    int quadratic_probe(int hash_value, int attempt);

public:
    void insert_to_table(const char _login[LOGINLENGTH], uint* sh1);
    uint* find_in_table(const char _login[LOGINLENGTH]);
};








