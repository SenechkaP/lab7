#define _CRT_SECURE_NO_WARNINGS

#include "doctor.h"

doctor::doctor() : fio() {
    this->spec = TER;
    this->qual = SECOND;
}

doctor::doctor(char *fam, char *name, SpecType spec, QualType qual) : fio(fam, name) {
    this->spec = spec;
    this->qual = qual;
}

doctor::doctor(doctor &doc) {
    this->set_fam(doc.get_fam());
    this->set_name(doc.get_name());
    this->spec = doc.spec;
    this->qual = doc.qual;
}

doctor::~doctor() {
//    std::cout << "Доктор удалён\n";
}

doctor &doctor::operator=(doctor &doc) {
    if (&doc != this) {
        this->set_fam(doc.get_fam());
        this->set_name(doc.get_name());
        this->spec = doc.spec;
        this->qual = doc.qual;
    }
    return *this;
}

bool doctor::operator>(doctor &doc) {
    return this->spec > doc.spec;
}

std::istream &operator>>(std::istream &is, doctor &doc) {
    char spec_buff[256];
    char qual_buff[256];

    fio new_initials;
    is >> new_initials;

    bool condition = true;

    long spec;
    while (condition) {
        std::cout << "Введите специальность нового доктора\n"
                     "специальность - цифра 1, 2 или 3\n"
                     "1 - терапевт\n"
                     "2 - кардиолог\n"
                     "3 - стоматолог\n\n";
        is >> spec_buff;

        try {
            spec = check_spec(spec_buff);
        }

        catch (int code) {
            std::cout << "Специальность - целое число!\n\n";
            continue;
        }
        catch (const char *error) {
            std::cout << error;
            continue;
        }
        condition = false;
    }
    std::cout << std::endl;

    condition = true;

    long qual;
    while (condition) {
        std::cout << "Введите квалификацию нового доктора\n"
                     "квалификация - цифра 0, 1 или 2\n"
                     "0 - высшая\n"
                     "1 - первая\n"
                     "2 - вторая\n";
        is >> qual_buff;

        try {
            qual = check_qual(qual_buff);
        }

        catch (int code) {
            std::cout << "Квалификация - целое число!\n\n";
            continue;
        }
        catch (const char *error) {
            std::cout << error;
            continue;
        }
        condition = false;
    }
    std::cout << std::endl;

    SpecType new_spec = static_cast<SpecType>(spec);
    QualType new_qual = static_cast<QualType>(qual);

    doc.set_fam(new_initials.get_fam());
    doc.set_name(new_initials.get_name());
    doc.set_spec(new_spec);
    doc.set_qual(new_qual);
    return is;
}

std::ostream &operator<<(std::ostream &os, doctor &doc) {
    os << std::left << std::setw(30) << doc.get_fam() << std::setw(30)
       << doc.get_name() << std::setw(30)
       << doc.get_spec() << std::setw(30) << doc.get_qual() << std::endl;
    return os;
}

SpecType doctor::get_enum_spec() {
    return this->spec;
}

const char *doctor::get_spec() {
    return specs[this->spec - 1];
}

void doctor::set_spec(SpecType spec) {
    this->spec = spec;
}

QualType doctor::get_enum_qual() {
    return this->qual;
}

const char *doctor::get_qual() {
    return quals[this->qual];
}

void doctor::set_qual(QualType qual) {
    this->qual = qual;
}
