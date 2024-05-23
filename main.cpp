#define _CRT_SECURE_NO_WARNINGS

#include "main.h"

using namespace std;

void read_file(const char *file_name, deque<doctor *> &all_doctors) {
    ifstream file(file_name);

    if (!file.is_open()) {
        cout << "Невозможно открыть файл " << file_name << "\n";
        return;
    }

    int n;
    char fam_buff[256];
    char name_buff[256];
    int spec_buff;
    int qual_buff;

    file >> n;

    for (int i = 0; i < n; i++) {
        file >> fam_buff >> name_buff >> spec_buff >> qual_buff;

        SpecType new_spec = static_cast<SpecType>(spec_buff);
        QualType new_qual = static_cast<QualType>(qual_buff);

        auto *doc = new doctor(fam_buff, name_buff, new_spec, new_qual);
        all_doctors.push_back(doc);
    }

    file.close();
}

void save_file(const char *file_name, deque<doctor *> &all_doctors) {
    ofstream file(file_name);

    if (!file.is_open()) {
        cout << "Невозможно открыть файл\n";
        return;
    }

    file << all_doctors.size() << "\n";

    for (auto doc: all_doctors) {
        file << doc->get_fam() << " " << doc->get_name() << " "
             << doc->get_enum_spec() << " " << doc->get_enum_qual()
             << "\n";
    }

    file.close();
    std::cout << "Данные сохранены\n";
}

void print_doctors(deque<doctor *> &all_doctors) {
    if (all_doctors.empty()) {
        std::cout << "Нет записей о докторах в базе\n";
        return;
    }
    std::cout << std::left << std::setw(30) << "Фамилия" << std::setw(30) << "Имя" << std::setw(30) << "Специальность"
              << std::setw(30)
              << "Квалификация" << endl << endl;

    for (auto doc: all_doctors) {
        cout << *doc;
    }
}

void delete_doctor_from_pos(deque<doctor *> &all_doctors) {
    char pos_buff[256];
    while (true) {
        cout << "Введите позицию в очереди, с которой вы хотите убрать доктора: ";
        cin >> pos_buff;
        long pos;
        try {
            pos = check_int(pos_buff);
        }

        catch (int) {
            cout << "Позиция - целое число!\n\n";
            continue;
        }

        pos -= 1;

        if (pos < 0 or pos >= all_doctors.size()) {
            cout << "Выход за пределы очереди!\n\n";
            continue;
        }

        all_doctors.erase(all_doctors.begin() + pos);
        break;
    }
}

bool compare_doctors(doctor *doc1, doctor *doc2) {
    return strcmp(doc1->get_fam(), doc2->get_fam()) < 0;
}

doctor *find_doctor_by_fio(fio &initials, std::deque<doctor *> &all_doctors) {
    for (auto doc: all_doctors) {
        if (initials == *doc) {
            return doc;
        }
    }
    return nullptr;
}

void find_doctors_by_spec(std::deque<doctor *> &all_doctors, std::deque<doctor *> &founded_doctors) {
    char spec_buff[256];
    while (true) {
        cout << "Введите специальность доктора\n"
                "специальность - цифра 1, 2 или 3\n"
                "1 - терапевт\n"
                "2 - кардиолог\n"
                "3 - стоматолог\n";
        cin >> spec_buff;
        long spec;
        try {
            spec = check_spec(spec_buff);
        }

        catch (int) {
            cout << "Специальность - целое число!\n\n";
            continue;
        }
        catch (const char *error) {
            cout << error;
            continue;
        }

        for (auto doc: all_doctors) {
            if (spec == doc->get_enum_spec()) {
                founded_doctors.push_back(doc);
            }
        }
        break;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

//    doctor doc1("fam1", "name1", STO, HIGH);
//    doctor doc2("fam2", "name2", TER, HIGH);
//
//    cout << (doc1 > doc2);

    deque<doctor *> all_doctors;

    read_file("doctors.txt", all_doctors);

    bool condition = true;
    while (condition) {
        cout << "Добавить нового доктора в начало очереди........1\n"
                "Добавить нового доктора в конец очереди.........2\n"
                "Убрать доктора с заданной позиции в очереди.....3\n"
                "Вывести информацию о всех докторах..............4\n"
                "Отсортировать докторов по фамилии...............5\n"
                "Найти доктора по фамилии и имени................6\n"
                "Найти доктора по специальности..................7\n"
                "Завершить программу.............................8\n\n"
                "Введите номер функции: ";
        char input[256];
        long command;

        cin >> input;
        try {
            command = check_int(input);
        }
        catch (int code) {
            cout << "Ошибка. Введите целое число.\n\n";
            continue;
        }
        cout << "\n";

        switch (command) {
            case 1: {
                auto *doc_to_add = new doctor;
                cin >> *doc_to_add;
                all_doctors.push_front(doc_to_add);
                cout << "Доктор добавлен в начало очереди\n\n";
                break;
            }
            case 2: {
                auto *doc_to_add = new doctor;
                cin >> *doc_to_add;
                all_doctors.push_back(doc_to_add);
                cout << "Доктор добавлен в конец очереди\n\n";
                break;
            }
            case 3:
                delete_doctor_from_pos(all_doctors);
                cout << "Запись о докторе удалена\n\n";
                break;
            case 4:
                print_doctors(all_doctors);
                cout << "\n";
                break;
            case 5:
                sort(all_doctors.begin(), all_doctors.end(), compare_doctors);
                cout << "Очередь отсортирована\n\n";
                break;
            case 6: {
                fio initials;
                cin >> initials;
                doctor *founded_doc = find_doctor_by_fio(initials, all_doctors);
                if (!founded_doc) {
                    cout << "Доктор не найден\n\n";
                } else {
                    cout << "Доктор найден:\n\n";
                    cout << founded_doc->get_fam() << " " << founded_doc->get_name() << ", " << founded_doc->get_spec()
                         << ", " << founded_doc->get_qual() << " квалификация" << endl << endl;
                }
                break;
            }
            case 7: {
                deque<doctor *> founded_doctors;
                find_doctors_by_spec(all_doctors, founded_doctors);
                if (founded_doctors.empty()) {
                    cout << "Доктора заданной специальности не найдены\n\n";
                } else {
                    cout << endl << endl;
                    std::cout << std::left << std::setw(30) << "Фамилия" << std::setw(30) << "Имя" << std::setw(30)
                              << "Специальность" << std::setw(30) << "Квалификация" << endl << endl;

                    for (auto doc: founded_doctors) {
                        cout << *doc;
                    }
                }
                cout << "\n";
                break;
            }
            case 8:
                condition = false;
                save_file("doctors.txt", all_doctors);

                for (auto &doc: all_doctors) {
                    delete doc;
                }

                break;
            default:
                cout << "Нет такой команды, введите команду от 1 до 8\n\n";
                break;
        }
    }

    return 0;
}
