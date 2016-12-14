#ifndef sort_hpp
#define sort_hpp
#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <functional>
#include <algorithm>
#include <queue>

using namespace std; 


struct man
{
    string surname;
    string name;
    size_t year;
    unsigned long int length() { return surname.size() + name.size() + sizeof(year); }
};


struct M
{
    ifstream *ptr;
    man data;
};


bool operator > (const man & m1, const man & m2) {
    return m1.name > m2.name;
}

bool operator < (const man & m1, const man & m2) {
    return m1.name < m2.name;
}

bool operator < (const M & m1, const M & m2) {
    return m1.data > m2.data;
}

ostream & operator << (ostream & output, man const & m)
{
    output << m.surname << " " << m.name << " " << m.year;
    return output;
}

istream & operator >> (istream & input, man & m)
{
    input >> m.surname >> m.name >> m.year;
    return input;
}


class _sort {

    vector<string> f;
    string f1;
    string f2;
    unsigned long int buffer_size;
    
    void sort();
    void make_file(string, vector<man>);
    void remove_create_files();
    void generate();

    public:
    _sort(string, string, int buffer_size);

    _sort(_sort const &) = delete;
    auto operator=(_sort const &) -> _sort & = delete;
    _sort(_sort &&) = delete;
    auto operator=(_sort &&) -> _sort & = delete;
};

_sort::_sort(string m1, string m2, int size) : f1(m1), f2(m2),
    buffer_size(size * 1024 * 1024) {
    generate();
    sort();
}

void _sort::make_file(string name_file, vector<man> arr) 
{
    ofstream file(name_file);
    if (!file) 
    {
        throw("file not open");
    }
    for (int i = 0; i < arr.size(); ++i)
    {
        file << arr[i] << std::endl;
    }
    file.close();
}

void _sort::generate() 
{
    ifstream file(f1);
    unsigned long size = 0;
    string name_file = "0";
    man data;
    vector<man> arr;

    while (file >> data) {
        size += data.length();
        if (buffer_size - data.length() <= size) {
            f.push_back(name_file);
            std::sort(arr.begin(), arr.end());
            make_file(name_file, arr);
            name_file = f.size();
            size = (unsigned long ) data.length();
            arr.clear();
        }
        arr.push_back(data);
    }
    if (arr.size() > 0) {
        std::sort(arr.begin(), arr.end());
        f.push_back("end.txt");
        make_file("end.txt", arr);
    }
    file.close();
}


void _sort::sort() 
{
    std::priority_queue<M> other;
    for (int i = 0; i < f.size(); ++i) {
        M tmp = {new std::ifstream(f[i])};
        *tmp.ptr >> tmp.data;
        other.push(tmp);
    }
    std::ofstream tmp(f2);
    std::string word;
    while (!other.empty()) {
        M tmp1 = other.top();
        tmp << tmp1.data << std::endl;
        other.pop();
        if (!tmp1.ptr->eof() && *tmp1.ptr >> tmp1.data) {
            other.push(tmp1);
        } else {
            tmp1.ptr->close();
        }
    }
    remove_create_files();
}

void _sort::remove_create_files()
{
    for (int i = 0; i < f.size(); ++i) 
    {
        auto a = f[i].c_str();
        std::remove(a);
    }
}

#endif

