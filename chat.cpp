#include "chat.h"
#include "iostream"
#include "string.h"

Chat::Chat() {
    data_count = 0;
    data = new AuthData[SIZE];
    // Инициализация хеш-таблицы
    hash_table = new AuthData * [table_size];
    for (int i = 0; i < table_size; ++i) {
        hash_table[i] = nullptr;
    }
}

int Chat::hash_function(const char _login[LOGINLENGTH]) {
    int hash = 0;
    for (int i = 0; i < LOGINLENGTH; ++i) {
        hash = (hash * 31 + _login[i]) % table_size;
    }
    return hash;
}

int Chat::quadratic_probe(int hash_value, int attempt) {
    return (hash_value + attempt * attempt) % table_size;
}

void Chat::insert_to_table(const char _login[LOGINLENGTH], uint* sh1) {
    int hash_value = hash_function(_login);
    int index = hash_value;

    int attempt = 1;
    while (hash_table[index] != nullptr) {
        index = quadratic_probe(hash_value, attempt);
        ++attempt;
    }

    hash_table[index] = new AuthData(_login, sh1);
}

uint* Chat::find_in_table(const char _login[LOGINLENGTH]) {
    int hash_value = hash_function(_login);
    int index = hash_value;

    int attempt = 1;
    while (hash_table[index] != nullptr && strcmp(hash_table[index]->login, _login) != 0) {
        index = quadratic_probe(hash_value, attempt);
        ++attempt;
    }

    if (hash_table[index] != nullptr && strcmp(hash_table[index]->login, _login) == 0) {
        return hash_table[index]->pass_sha1_hash;
    }

    return nullptr;
}

void Chat::reg(const char _login[LOGINLENGTH], const char _pass[], int pass_length) {
    uint* digest = sha1(_pass, static_cast<uint>(pass_length));
    insert_to_table(_login, digest);
    data_count++;
}

bool Chat::login(const char _login[LOGINLENGTH], const char _pass[], int pass_length) {
    uint* stored_hash = find_in_table(_login);

    if (stored_hash == nullptr) {
        return false;  // Логин не найден
    }

    uint* input_hash = sha1(_pass, static_cast<uint>(pass_length));
    bool cmpHashes = !memcmp(stored_hash, input_hash, SHA1HASHLENGTHBYTES);

    delete[] input_hash;

    return cmpHashes;
}

Chat::~Chat() {
    delete[] data;
    for (int i = 0; i < table_size; ++i) {
        delete hash_table[i];
    }
    delete[] hash_table;
}






