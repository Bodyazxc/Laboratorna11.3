#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <windows.h>

using namespace std;

struct Room
{
    int phone_number;
    int room_number;
    string employees[4];
    int employee_count;
};

void AddRoomToFile(const string& file_name);
void DeleteRoomFromFile(const string& file_name);
void EditRoomInFile(const string& file_name);
void PrintAllRooms(const string& file_name);
void PrintByPhoneNumber(const string& file_name);
void PrintByRoomNumber(const string& file_name);
void PrintByEmployee(const string& file_name);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string file_name;
    cout << "Введіть ім'я файлу: ";
    cin >> file_name;

    int MenuItem;

    while (true)
    {
        cout << endl << "Оберіть дію:" << endl;
        cout << "1 - Додати приміщення" << endl;
        cout << "2 - Видалити приміщення" << endl;
        cout << "3 - Редагувати приміщення" << endl;
        cout << "4 - Вивести всі приміщення" << endl;
        cout << "5 - Пошук за номером телефону" << endl;
        cout << "6 - Пошук за номером приміщення" << endl;
        cout << "7 - Пошук за прізвищем службовця" << endl;
        cout << "0 - Завершити роботу програми" << endl;
        cout << "Введіть: ";
        cin >> MenuItem;

        switch (MenuItem)
        {
        case 1:
            AddRoomToFile(file_name);
            break;
        case 2:
            DeleteRoomFromFile(file_name);
            break;
        case 3:
            EditRoomInFile(file_name);
            break;
        case 4:
            PrintAllRooms(file_name);
            break;
        case 5:
            PrintByPhoneNumber(file_name);
            break;
        case 6:
            PrintByRoomNumber(file_name);
            break;
        case 7:
            PrintByEmployee(file_name);
            break;
        case 0:
            return 0;
        }
    }
}

void AddRoomToFile(const string& file_name)
{
    ofstream file(file_name, ios::app);

    if (!file.is_open())
    {
        cout << "Не вдалося відкрити файл для запису!" << endl;
        return;
    }

    Room room;
    cout << "Введіть номер телефону (2 цифри): ";
    cin >> room.phone_number;

    cout << "Введіть номер приміщення: ";
    cin >> room.room_number;

    cout << "Введіть кількість службовців (від 1 до 4): ";
    cin >> room.employee_count;

    if (room.employee_count < 1 || room.employee_count > 4)
    {
        cout << "Кількість службовців має бути в межах від 1 до 4!" << endl;
        return;
    }

    cin.ignore();
    for (int i = 0; i < room.employee_count; ++i)
    {
        cout << "Введіть прізвище службовця №" << i + 1 << ": ";
        getline(cin, room.employees[i]);
    }

    file << room.phone_number << " " << room.room_number << " " << room.employee_count << endl;
    for (int i = 0; i < room.employee_count; ++i)
    {
        file << room.employees[i] << endl;
    }

    cout << "Приміщення додано!" << endl;
}

void DeleteRoomFromFile(const string& file_name)
{
    ifstream file(file_name);
    ofstream temp_file("temp.txt");

    if (!file.is_open() || !temp_file.is_open())
    {
        cout << "Не вдалося відкрити файли!" << endl;
        return;
    }

    int phone;
    cout << "Введіть номер телефону приміщення для видалення: ";
    cin >> phone;

    Room room;
    bool found = false;
    while (file >> room.phone_number >> room.room_number >> room.employee_count)
    {
        file.ignore();
        bool delete_room = room.phone_number == phone;

        if (delete_room)
        {
            found = true;
            string employee;
            for (int i = 0; i < room.employee_count; ++i)
            {
                getline(file, employee);  // зчитуємо прізвище службовця
            }
        }
        else
        {
            temp_file << room.phone_number << " " << room.room_number << " " << room.employee_count << endl;
            for (int i = 0; i < room.employee_count; ++i)
            {
                string employee;
                getline(file, employee);
                temp_file << employee << endl;
            }
        }
    }

    file.close();
    temp_file.close();

    remove(file_name.c_str());
    rename("temp.txt", file_name.c_str());

    if (found)
        cout << "Приміщення видалено!" << endl;
    else
        cout << "Приміщення з таким номером телефону не знайдено!" << endl;
}

void EditRoomInFile(const string& file_name)
{
    ifstream file(file_name);
    ofstream temp_file("temp.txt");

    if (!file.is_open() || !temp_file.is_open())
    {
        cout << "Не вдалося відкрити файли!" << endl;
        return;
    }

    int phone;
    cout << "Введіть номер телефону приміщення для редагування: ";
    cin >> phone;

    Room room;
    bool found = false;
    while (file >> room.phone_number >> room.room_number >> room.employee_count)
    {
        file.ignore();
        if (room.phone_number == phone)
        {
            found = true;
            cout << "Редагуємо приміщення з номером телефону " << room.phone_number << endl;
            cout << "Введіть новий номер приміщення: ";
            cin >> room.room_number;

            cout << "Введіть кількість службовців (від 1 до 4): ";
            cin >> room.employee_count;

            if (room.employee_count < 1 || room.employee_count > 4)
            {
                cout << "Кількість службовців має бути в межах від 1 до 4!" << endl;
                return;
            }

            cin.ignore();
            for (int i = 0; i < room.employee_count; ++i)
            {
                cout << "Введіть прізвище службовця №" << i + 1 << ": ";
                getline(cin, room.employees[i]);
            }

            temp_file << room.phone_number << " " << room.room_number << " " << room.employee_count << endl;
            for (int i = 0; i < room.employee_count; ++i)
            {
                temp_file << room.employees[i] << endl;
            }
        }
        else
        {
            temp_file << room.phone_number << " " << room.room_number << " " << room.employee_count << endl;
            for (int i = 0; i < room.employee_count; ++i)
            {
                string employee;
                getline(file, employee);
                temp_file << employee << endl;
            }
        }
    }

    file.close();
    temp_file.close();

    remove(file_name.c_str());
    rename("temp.txt", file_name.c_str());

    if (found)
        cout << "Приміщення оновлено!" << endl;
    else
        cout << "Приміщення з таким номером телефону не знайдено!" << endl;
}

void PrintAllRooms(const string& file_name)
{
    ifstream file(file_name);

    if (!file.is_open())
    {
        cout << "Не вдалося відкрити файл!" << endl;
        return;
    }

    Room room;
    cout << "=====================================================================" << endl;
    cout << "|  Телефон  | Приміщення | Службовці                                |" << endl;
    cout << "---------------------------------------------------------------------" << endl;

    while (file >> room.phone_number >> room.room_number >> room.employee_count)
    {
        file.ignore(); 

        cout << "| " << setw(9) << room.phone_number
            << " | " << setw(10) << room.room_number
            << " | ";

        
        for (int i = 0; i < room.employee_count; ++i)
        {
            string employee;
            getline(file, employee);  
            cout << employee;
            if (i < room.employee_count - 1)
                cout << ", "; 
        }
        cout << " |" << endl;
    }

    cout << "=====================================================================" << endl;
}

void PrintByPhoneNumber(const string& file_name)
{
    ifstream file(file_name);

    if (!file.is_open())
    {
        cout << "Не вдалося відкрити файл!" << endl;
        return;
    }

    int phone;
    cout << "Введіть номер телефону для пошуку: ";
    cin >> phone;

    Room room;
    bool found = false;

    while (file >> room.phone_number >> room.room_number >> room.employee_count)
    {
        file.ignore();
        if (room.phone_number == phone)
        {
            found = true;
            cout << "Номер приміщення: " << room.room_number << endl;
            cout << "Номер телефону: " << room.phone_number << endl;
            cout << "Кількість службовців: " << room.employee_count << endl;
            for (int i = 0; i < room.employee_count; ++i)
            {
                cout << "Службовець: " << room.employees[i] << endl;
            }
            break;
        }
    }

    if (!found)
        cout << "Приміщення з таким номером телефону не знайдено!" << endl;
}

void PrintByRoomNumber(const string& file_name)
{
    ifstream file(file_name);

    if (!file.is_open())
    {
        cout << "Не вдалося відкрити файл!" << endl;
        return;
    }

    int room_number;
    cout << "Введіть номер приміщення для пошуку: ";
    cin >> room_number;

    Room room;
    bool found = false;

    while (file >> room.phone_number >> room.room_number >> room.employee_count)
    {
        file.ignore();
        if (room.room_number == room_number)
        {
            found = true;
            cout << "Номер приміщення: " << room.room_number << endl;
            cout << "Номер телефону: " << room.phone_number << endl;
            cout << "Кількість службовців: " << room.employee_count << endl;
            for (int i = 0; i < room.employee_count; ++i)
            {
                cout << "Службовець: " << room.employees[i] << endl;
            }
            break;
        }
    }

    if (!found)
        cout << "Приміщення з таким номером не знайдено!" << endl;
}

void PrintByEmployee(const string& file_name)
{
    ifstream file(file_name);

    if (!file.is_open())
    {
        cout << "Не вдалося відкрити файл!" << endl;
        return;
    }

    string employee_name;
    cout << "Введіть прізвище службовця для пошуку: ";
    cin.ignore(); 
    getline(cin, employee_name);

    Room room;
    bool found = false;

    while (file >> room.phone_number >> room.room_number >> room.employee_count)
    {
        file.ignore();

        bool employee_found = false;

        
        for (int i = 0; i < room.employee_count; ++i)
        {
            getline(file, room.employees[i]);
            if (room.employees[i] == employee_name)
            {
                employee_found = true;
                break;
            }
        }

        if (employee_found)
        {
            found = true;
            cout << "Номер приміщення: " << room.room_number << endl;
            cout << "Номер телефону: " << room.phone_number << endl;
            cout << "Службовець: " << employee_name << endl;
            break; 
        }
    }

    if (!found)
        cout << "Приміщення для цього службовця не знайдено!" << endl;
}

