#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <set>
#include <ctime>

using namespace std;

string generatePassword(int length) {
    const string lower = "abcdefghijklmnopqrstuvwxyz";
    const string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string digits = "0123456789";
    const string special = "!@#$%^&*()-_=+[]{};:,.<>?";
    const string all = lower + upper + digits + special;

    if (length < 4) {
        throw invalid_argument("Длина пароля должна быть минимум 4");
    }

    static mt19937 rng(static_cast<unsigned>(time(nullptr)));
    uniform_int_distribution<size_t> distAll(0, all.size() - 1);
    uniform_int_distribution<size_t> distLow(0, lower.size() - 1);
    uniform_int_distribution<size_t> distUp(0, upper.size() - 1);
    uniform_int_distribution<size_t> distDig(0, digits.size() - 1);
    uniform_int_distribution<size_t> distSp(0, special.size() - 1);

    string password;
    password += lower[distLow(rng)];
    password += upper[distUp(rng)];
    password += digits[distDig(rng)];
    password += special[distSp(rng)];

    for (int i = 4; i < length; ++i) {
        password += all[distAll(rng)];
    }

    shuffle(password.begin(), password.end(), rng);
    return password;
}

template <typename T>
vector<T> removeDuplicates(const vector<T>& input) {
    vector<T> result;
    set<T> seen;
    for (const auto& item : input) {
        if (seen.insert(item).second) {
            result.push_back(item);
        }
    }
    return result;
}

class Employee {
protected:
    string name;
    double salary;
public:
    Employee(const string& name, double salary) : name(name), salary(salary) {}
    virtual ~Employee() = default;

    virtual double calculateBonus() const {
        return salary * 0.10;
    }

    string getName() const { return name; }
    double getSalary() const { return salary; }

    virtual void printInfo() const {
        cout << "Сотрудник: " << name
            << " | Оклад: " << salary
            << " | Премия: " << calculateBonus() << endl;
    }
};

class Manager : public Employee {
    double bonusPercent;
public:
    Manager(const string& name, double salary, double bonusPercent = 0.25)
        : Employee(name, salary), bonusPercent(bonusPercent) {
    }

    double calculateBonus() const override {
        return salary * bonusPercent;
    }

    void printInfo() const override {
        cout << "Менеджер: " << name
            << " | Оклад: " << salary
            << " | Премия: " << calculateBonus() << endl;
    }
};

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    cout << "=== Пароли ===" << endl;
    cout << generatePassword(8) << endl;
    cout << generatePassword(12) << endl;
    cout << generatePassword(16) << endl;

    cout << "\n=== Удаление дубликатов ===" << endl;
    vector<int> nums = { 1, 2, 2, 3, 4, 4, 5, 1, 6 };
    auto uniqueNums = removeDuplicates(nums);
    cout << "Было:   ";
    for (int n : nums) cout << n << " ";
    cout << "\nСтало:  ";
    for (int n : uniqueNums) cout << n << " ";
    cout << endl;

    vector<string> words = { "apple", "banana", "apple", "cherry", "banana" };
    auto uniqueWords = removeDuplicates(words);
    cout << "Строки: ";
    for (const auto& w : uniqueWords) cout << w << " ";
    cout << endl;

    cout << "\n=== Премии ===" << endl;
    Employee emp("Иван", 50000);
    Manager mgr("Ольга", 80000, 0.30);

    emp.printInfo();
    mgr.printInfo();

    cout << "\n=== Полиморфизм ===" << endl;
    vector<Employee*> staff = { &emp, &mgr };
    for (auto* e : staff) {
        e->printInfo();
    }

    return 0;
}