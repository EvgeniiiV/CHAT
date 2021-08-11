#pragma once
#include<iostream>
using namespace std;
#include<string>

template <typename T>class User
{
private:
    T _name, _login, _pass;
public:
    User();
    User(T name, T login, T pass);
    T get_name() const;
    T get_log_pas() const;
};

template <typename T> class Temp
{
public:
    Temp();    
    void insert_name(T newval);
    size_t get_gr_size()const;
    T* get_groups()const;
    T get_name(size_t i)const;
    void temp_clear();//to clear temp  
    ~Temp();

private:
    size_t allocedSize;
    size_t size;
    T* array;
};

template <typename T> class Group
{
public:
    Group();
    ~Group();    
    void insert_name(T newval);
    size_t get_size_group() const;
    T get_group(size_t i)const;
    T* get_group()const;

private:
    size_t alloc_group;
    size_t size_group;
    T* _group;
};

template <typename T> class Message
{
public:
    Message();
    ~Message();    
    void insert_mess(T newval);
    size_t get_size_mes() const;
    T get_mess(size_t i)const;

private:
    size_t alloc_mess;
    size_t size_mess;
    T* _mess;
};

template <typename T1, typename T2 > bool compare(T1* user, T2 u, T1* group, T2 g);// compares Temp::array[i] and Message::group[i]
template <typename T> bool compare_LP(T LP, T L, T P);//compares login and password
template <typename T1, typename T2> T2 request(T1 rst, T2 a, T2 b, T2 first);//for registrarion
template <typename T> T next_request();//case 5, 6
inline size_t Factorial(size_t num);//factorial
inline size_t Presence(size_t num);//to calculate max number of possible groups for one user based on the number of registered users





