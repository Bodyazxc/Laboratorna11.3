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
    cout << "������ ��'� �����: ";
    cin >> file_name;

    int MenuItem;

    while (true)
    {
        cout << endl << "������ ��:" << endl;
        cout << "1 - ������ ���������" << endl;
        cout << "2 - �������� ���������" << endl;
        cout << "3 - ���������� ���������" << endl;
        cout << "4 - ������� �� ���������" << endl;
        cout << "5 - ����� �� ������� ��������" << endl;
        cout << "6 - ����� �� ������� ���������" << endl;
        cout << "7 - ����� �� �������� ���������" << endl;
        cout << "0 - ��������� ������ ��������" << endl;
        cout << "������: ";
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
        cout << "�� ������� ������� ���� ��� ������!" << endl;
        return;
    }

    Room room;
    cout << "������ ����� �������� (2 �����): ";
    cin >> room.phone_number;

    cout << "������ ����� ���������: ";
    cin >> room.room_number;

    cout << "������ ������� ���������� (�� 1 �� 4): ";
    cin >> room.employee_count;

    if (room.employee_count < 1 || room.employee_count > 4)
    {
        cout << "ʳ������ ���������� �� ���� � ����� �� 1 �� 4!" << endl;
        return;
    }

    cin.ignore();
    for (int i = 0; i < room.employee_count; ++i)
    {
        cout << "������ ������� ��������� �" << i + 1 << ": ";
        getline(cin, room.employees[i]);
    }

    file << room.phone_number << " " << room.room_number << " " << room.employee_count << endl;
    for (int i = 0; i < room.employee_count; ++i)
    {
        file << room.employees[i] << endl;
    }

    cout << "��������� ������!" << endl;
}

void DeleteRoomFromFile(const string& file_name)
{
    ifstream file(file_name);
    ofstream temp_file("temp.txt");

    if (!file.is_open() || !temp_file.is_open())
    {
        cout << "�� ������� ������� �����!" << endl;
        return;
    }

    int phone;
    cout << "������ ����� �������� ��������� ��� ���������: ";
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
                getline(file, employee);  // ������� ������� ���������
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
        cout << "��������� ��������!" << endl;
    else
        cout << "��������� � ����� ������� �������� �� ��������!" << endl;
}

void EditRoomInFile(const string& file_name)
{
    ifstream file(file_name);
    ofstream temp_file("temp.txt");

    if (!file.is_open() || !temp_file.is_open())
    {
        cout << "�� ������� ������� �����!" << endl;
        return;
    }

    int phone;
    cout << "������ ����� �������� ��������� ��� �����������: ";
    cin >> phone;

    Room room;
    bool found = false;
    while (file >> room.phone_number >> room.room_number >> room.employee_count)
    {
        file.ignore();
        if (room.phone_number == phone)
        {
            found = true;
            cout << "�������� ��������� � ������� �������� " << room.phone_number << endl;
            cout << "������ ����� ����� ���������: ";
            cin >> room.room_number;

            cout << "������ ������� ���������� (�� 1 �� 4): ";
            cin >> room.employee_count;

            if (room.employee_count < 1 || room.employee_count > 4)
            {
                cout << "ʳ������ ���������� �� ���� � ����� �� 1 �� 4!" << endl;
                return;
            }

            cin.ignore();
            for (int i = 0; i < room.employee_count; ++i)
            {
                cout << "������ ������� ��������� �" << i + 1 << ": ";
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
        cout << "��������� ��������!" << endl;
    else
        cout << "��������� � ����� ������� �������� �� ��������!" << endl;
}

void PrintAllRooms(const string& file_name)
{
    ifstream file(file_name);

    if (!file.is_open())
    {
        cout << "�� ������� ������� ����!" << endl;
        return;
    }

    Room room;
    cout << "=====================================================================" << endl;
    cout << "|  �������  | ��������� | ���������                                |" << endl;
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
        cout << "�� ������� ������� ����!" << endl;
        return;
    }

    int phone;
    cout << "������ ����� �������� ��� ������: ";
    cin >> phone;

    Room room;
    bool found = false;

    while (file >> room.phone_number >> room.room_number >> room.employee_count)
    {
        file.ignore();
        if (room.phone_number == phone)
        {
            found = true;
            cout << "����� ���������: " << room.room_number << endl;
            cout << "����� ��������: " << room.phone_number << endl;
            cout << "ʳ������ ����������: " << room.employee_count << endl;
            for (int i = 0; i < room.employee_count; ++i)
            {
                cout << "����������: " << room.employees[i] << endl;
            }
            break;
        }
    }

    if (!found)
        cout << "��������� � ����� ������� �������� �� ��������!" << endl;
}

void PrintByRoomNumber(const string& file_name)
{
    ifstream file(file_name);

    if (!file.is_open())
    {
        cout << "�� ������� ������� ����!" << endl;
        return;
    }

    int room_number;
    cout << "������ ����� ��������� ��� ������: ";
    cin >> room_number;

    Room room;
    bool found = false;

    while (file >> room.phone_number >> room.room_number >> room.employee_count)
    {
        file.ignore();
        if (room.room_number == room_number)
        {
            found = true;
            cout << "����� ���������: " << room.room_number << endl;
            cout << "����� ��������: " << room.phone_number << endl;
            cout << "ʳ������ ����������: " << room.employee_count << endl;
            for (int i = 0; i < room.employee_count; ++i)
            {
                cout << "����������: " << room.employees[i] << endl;
            }
            break;
        }
    }

    if (!found)
        cout << "��������� � ����� ������� �� ��������!" << endl;
}

void PrintByEmployee(const string& file_name)
{
    ifstream file(file_name);

    if (!file.is_open())
    {
        cout << "�� ������� ������� ����!" << endl;
        return;
    }

    string employee_name;
    cout << "������ ������� ��������� ��� ������: ";
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
            cout << "����� ���������: " << room.room_number << endl;
            cout << "����� ��������: " << room.phone_number << endl;
            cout << "����������: " << employee_name << endl;
            break; 
        }
    }

    if (!found)
        cout << "��������� ��� ����� ��������� �� ��������!" << endl;
}

