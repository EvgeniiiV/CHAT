#include<iostream>
using namespace std;
#include<string>
#include <streambuf>
#include "CHAT.h"

template<typename T>User<T>::User() = default;
template<typename T>User<T>::User(T name, T login, T pass) : _name(name), _login(login), _pass(pass) {}
template<typename T> T User<T>::get_name() const { return _name; }
template<typename T> T User<T>::get_log_pas() const { return _login + _pass; }

template <typename T>Temp<T>::Temp()
{
    allocedSize = 1;
    size = 0;
    try
    {
        array = new T[allocedSize];
    }
    catch (bad_alloc& ba)
    {
        cout << ba.what() << endl;
    }
}
template<typename T>void Temp<T>::insert_name(T newval)
{
    if (size == allocedSize)
    {
        try
        {
            T* newMem = new T[allocedSize * 2];
            for (size_t i = 0; i < size; i++)
                newMem[i] = array[i];
            allocedSize *= 2;
            delete[] array;
            array = newMem;
        }
        catch (bad_alloc& ba)
        {
            cout << ba.what() << endl;
        }
    }
    //sorting of names for the group
    array[size++] = newval;
    for (size_t startIndex = 0; startIndex < size; ++startIndex)
    {
        size_t smallestIndex = startIndex;
        for (size_t currentIndex = startIndex + 1; currentIndex < size; ++currentIndex)
        {
            if (array[currentIndex] < array[smallestIndex])
                smallestIndex = currentIndex;
        }
        std::swap(array[startIndex], array[smallestIndex]);
    }
}

template <typename T>size_t Temp<T>::get_gr_size() const { return size; }
template <typename T>T* Temp<T>::get_groups()const { return array; }
template <typename T>T Temp<T>::get_name(size_t i)const { return array[i]; }
template <typename T>void Temp<T>::temp_clear()//to clear temp
{
    for (size_t i = 0; i < size; i++)
        array[i] = "";
    size = 0;
}


template <typename T> Message<T>::Message()
{
    size_group = 0;
    alloc_mess = 1;
    size_mess = 0;
    try
    {
        mess = new string[alloc_mess];
    }
    catch (bad_alloc& ba)
    {
        cout << ba.what() << endl;
    }
}

template <typename T> void Message<T>::insert_mess(T newval)
{
    try
    {
        if (size_mess == alloc_mess)
        {
            T* newmess = new T[alloc_mess * 2];

            for (size_t i = 0; i < size_mess; i++)
                newmess[i] = mess[i];
            alloc_mess *= 2;
            delete[] mess;
            mess = newmess;
        }
        mess[size_mess++] = newval;
    }
    catch (bad_alloc& ba)
    {
        cout << ba.what() << endl;
    }
}

template <typename T>T* Message<T>::get_group()const { return group; }
template <typename T>T Message<T>::get_group(size_t i)const { return group[i]; }
template <typename T>size_t Message<T>::get_size_group() const { return size_group; }
template <typename T>size_t Message<T>::get_size_mes() const { return size_mess; }
template <typename T>T Message<T>::get_mess(size_t i)const { return mess[i]; }
template <typename T>void Message<T>::approp(string * g, size_t size)//Temp->Message::group 
{
    size_group = size;
    group = new string[size_group];
    for (size_t i = 0; i < size_group; i++)
        group[i] = g[i];
}

template <typename T1, typename T2 > bool compare(T1 * user, T2 u, T1 * group, T2 g)// compares Temp::array[i] and Message::group[i]
{
    if (u != g) return false;
    for (size_t i = 0; i < u; i++)
        if (user[i] != group[i]) return false;
    return true;
}

template <typename T> bool compare_LP(T LP, T L, T P)//compares login and password
{
    if (LP == L + P) return true;
    return false;
}

template <typename T1, typename T2> T2 request(T1 rst, T2 a, T2 b, T2 first)
{
    T2 choice = 0;
    if (!first)
    {
        cout << "REGISTRATION of next USER: press key 1" << endl;//for registrarion
        do//to prevent invalid input
        {
            cin.clear();
            streamsize L = cin.rdbuf()->in_avail();
            cin.ignore(L);     
            cin >> choice;          
            if (!cin)
                cout << "ENTER a DIGIT" << endl;
            if (choice != a)
                cout << "ENTER " << a << endl;            
        } while ((choice != a) || !cin);
    }
    if (first)
    {
        do//to prevent invalid input during 
        {
            cout << rst << endl;
            cin.clear();
            streamsize L = cin.rdbuf()->in_avail();
            cin.ignore(L);
            cin >> choice;
            if (!cin)
                cout << "ENTER a DIGIT" << endl;
            if (choice != a && choice != b)
                cout << "ENTER " << a << " or " << b << endl;
        } while ((choice != a && choice != b) || !cin);
    }
    return choice;
}

template <typename T> T next_request()//case 5, 6
{
    size_t choice = 0;
    do
    {
        cout << "\nLogout and Registration: press key 1" << endl;
        cout << "Logout and Authorization: press key 2" << endl;
        cout << "Create new contact: press key 3" << endl;
        cout << "Chose another contact: press key 4" << endl;
        cout << "Next message to this: press key contact 5" << endl;
        cout << "Message for everyone: press key 6" << endl;
        cout << "Quit: press key 7" << endl;
        cin.clear();
        streamsize L = cin.rdbuf()->in_avail();
        cin.ignore(L);
        cin >> choice;
        if (!cin)
            cout << "ENTER a DIGIT" << endl;
        if (choice < 1 || choice > 7)
            cout << "ENTER 1 - 7" << endl;
    } while (choice < 1 || choice > 7 || !cin);
    return choice;
}


