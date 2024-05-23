#define _CRT_SECURE_NO_WARNINGS

#pragma once

#include <iostream>
#include "funcs.h"

class fio {
private:
    char *name;
    char *fam;
public:
    fio();

    fio(char *, char *);

    fio(fio &);

    ~fio();

    fio &operator=(fio &);

    bool operator==(fio &);

    friend std::istream &operator>>(std::istream &, fio &);

    char *get_fam();

    void set_fam(char *);

    char *get_name();

    void set_name(char *);
};