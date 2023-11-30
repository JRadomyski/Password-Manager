#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include <algorithm>

using namespace std;

const int MAX_KEY_SIZE = 100;
const int MAX_RESULT_SIZE = 1000;

string crypt(const string& input, const string& key, const string& mode) {
    int master_key[MAX_KEY_SIZE];
    int key_length = 0;
    for (char c : key) {
        master_key[key_length++] = int(c);
    }

    int result[MAX_RESULT_SIZE];
    int result_length = 0;

    if (mode == "encrypt") {
        size_t i = 0;
        for (char ch : input) {
            result[result_length++] = int(ch) + master_key[i++ % key_length];
        }
    } else if (mode == "decrypt") {
        stringstream ss(input);
        string token;
        size_t i = 0;
        while (getline(ss, token, ',')) {
            int value = stoi(token);
            result[result_length++] = (value - master_key[i % key_length] < 0) ? 0 : value - master_key[i % key_length];
            i++;
            i %= key_length;
        }
    }

    string result_str;
    for (int i = 0; i < result_length; i++) {
        result_str += to_string(result[i]) + ',';
    }
    result_str.pop_back();

    return result_str;
}

string generate_password(int n_numbers, int n_letters, int n_special_chars) {
    string numbers = "0123456789";
    string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string special_chars = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

    random_device rd;
    mt19937 generator(rd());

    string password;
    for (int i = 0; i < n_numbers; i++)
        password.push_back(numbers[generator() % numbers.size()]);
    for (int i = 0; i < n_letters; i++)
        password.push_back(letters[generator() % letters.size()]);
    for (int i = 0; i < n_special_chars; i++)
        password.push_back(special_chars[generator() % special_chars.size()]);

    shuffle(password.begin(), password.end(), generator);

    return password;
}

void store_password(const string& master_key) {
    string platform, login, password;

    cout << "\nProvide platform, login and password you want to store." << endl;
    cin >> platform >> login >> password;

    string encrypted_platform = crypt(platform, master_key, "encrypt");
    string encrypted_login = crypt(login, master_key, "encrypt");
    string encrypted_password = crypt(password, master_key, "encrypt");

    ofstream file("vault.txt", ios::app);
    if (file.is_open()) {
        file << encrypted_platform << " " << encrypted_login << " " << encrypted_password << "\n";
        file.close();
    }

    cout << "Record was added to the Vault!" << endl;
}

int main() {
    string master_key;
    cout << "\nGreetings Master! Please provide the Master Key to proceed! -> ";
    cin >> master_key;

    string choice;
    while (true) {
        cout << "\nChoose one of the options below:" << endl;
        cout << "1. Generate Password" << endl;
        cout << "2. Store Password" << endl;
        cout << "3. Exit" << endl;

        cin >> choice;

        if (choice == "1") {
            int n_numbers, n_letters, n_special_chars;
            cout << "\nEnter the number of numbers, letters and special characters for the password to be generated." << endl;
            cin >> n_numbers >> n_letters >> n_special_chars;

            string password = generate_password(n_numbers, n_letters, n_special_chars);
            cout << "\nGenerated password: " << password << endl;
        }
        else if (choice == "2") {
            store_password(master_key);
        }
        else if (choice == "3") {
            break;
        }
        else {
            cout << "\nInvalid choice. Please try again." << endl;
        }
    }

    return 0;
}
