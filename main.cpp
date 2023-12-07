#include <iostream>
#include "chat.h"

int main() {
    Chat chat;

    chat.reg("user1", "password1", 9);
    chat.reg("user2", "password2", 9);

    if (chat.login("user1", "password1", 9)) {
        std::cout << "Login successful for user1.\n";
    }
    else {
        std::cout << "Login failed for user1.\n";
    }

    if (chat.login("user2", "wrong_password", 14)) {
        std::cout << "Login successful for user2.\n";
    }
    else {
        std::cout << "Login failed for user2.\n";
    }

    return 0;
}


