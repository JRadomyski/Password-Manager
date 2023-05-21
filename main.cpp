#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <random>

std::string crypt(const std::string& input, const std::string& key, const std::string& mode) {
    std::vector<int> master_key;
    std::transform(key.begin(), key.end(), std::back_inserter(master_key), [](char c) { return int(c); });

    std::vector<int> result;

    if (mode == "encrypt") {
        for (const char& ch : input) {
            static size_t i = 0;
            result.push_back(int(ch) + master_key[i++ % master_key.size()]);
        }
    } else if (mode == "decrypt") {
        std::stringstream ss(input);
        std::string token;
        while (std::getline(ss, token, ',')) {
            static size_t i = 0;
            int value = std::stoi(token);
            result.push_back((value - master_key[i++ % master_key.size()] < 0) ? 0 : value - master_key[i++ % master_key.size()]);
        }
    }

    std::string result_str;
    for (const auto& i : result) {
        result_str += std::to_string(i) + ',';
    }
    result_str.pop_back(); // remove the trailing comma

    return result_str;
}

std::string generate_password(int n_numbers, int n_letters, int n_special_chars) {
    std::string numbers = "0123456789";
    std::string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string special_chars = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

    std::random_device rd;
    std::mt19937 generator(rd());

    std::string password;
    for (int i = 0; i < n_numbers; i++)
        password.push_back(numbers[generator() % numbers.size()]);
    for (int i = 0; i < n_letters; i++)
        password.push_back(letters[generator() % letters.size()]);
    for (int i = 0; i < n_special_chars; i++)
        password.push_back(special_chars[generator() % special_chars.size()]);

    std::shuffle(password.begin(), password.end(), generator);

    return password;
}

void store_password(const std::string& master_key) {
    std::string platform, login, password;

    std::cout << "\nProvide platform, login and password you want to store." << std::endl;
    std::cin >> platform >> login >> password;

    std::string encrypted_platform = crypt(platform, master_key, "encrypt");
    std::string encrypted_login = crypt(login, master_key, "encrypt");
    std::string encrypted_password = crypt(password, master_key, "encrypt");

    std::ofstream file("vault.vt", std::ios::app);
    if (file.is_open()) {
        file << encrypted_platform << " " << encrypted_login << " " << encrypted_password << "\n";
        file.close();
    }

    std::cout << "Record was added to the Vault!" << std::endl;
}

int main() {
    std::string master_key;
    std::cout << "\nGreetings Master! Please provide the Master Key to proceed!";
    std::cin >> master_key;

    std::string choice;
    while (true) {
        std::cout << "\nChoose one of the options below:" << std::endl;
        std::cout << "1. Generate Password" << std::endl;
        std::cout << "2. Store Password" << std::endl;
        std::cout << "3. Quit" << std::endl;

        std::cin >> choice;

        if (choice == "1") {
            int n_numbers, n_letters, n_special_chars;
            std::cout << "\nEnter the number of numbers, letters and special characters for the password to be generated." << std::endl;
            std::cin >> n_numbers >> n_letters >> n_special_chars;

            std::string password = generate_password(n_numbers, n_letters, n_special_chars);
            std::cout << "\nGenerated password: " << password << std::endl;
        }
        else if (choice == "2") {
            store_password(master_key);
        }
        else if (choice == "3") {
            break;
        }
        else {
            std::cout << "\nInvalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}