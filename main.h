#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <iostream>
#include <clocale>
#include <deque>
#include <algorithm>
#include "doctor.h"

void read_file(const char *, std::deque<doctor *> &);

void save_file(const char *, std::deque<doctor *> &);

void print_doctors(std::deque<doctor *> &);

void delete_doctor_from_pos(std::deque<doctor *> &);

bool compare_doctors(doctor*, doctor*);

doctor* find_doctor_by_fio(fio&, std::deque<doctor *> &);

void find_doctors_by_spec(std::deque<doctor *> &, std::deque<doctor *> &);
