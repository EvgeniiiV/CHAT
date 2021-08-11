#include<iostream>
using namespace std;
#include<string>
#include "CHAT.cpp"
#define MaxUserCount 10//limit of Users
#define MaxGroupCount 100//limit of contacts (groups of users) 
#define MaxMessageCount 200//limit of messages in one group 
//detection of memory leaks
#define __CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW


int main()
{
    try
    {
        User<string>* user = new User<string>[MaxUserCount];
        Group<string>* group = new Group<string>[MaxGroupCount];
        Message<string>* mess = new Message<string>[MaxMessageCount];
        Temp<string> temp;
        size_t num_users = 0;//overall number of Users
        size_t numOf_groups = 0;//overall number of groups (MESSAGE[])
        size_t user_ind = 0;//to keep current index of AUTHORIZED USER
        size_t gr_ind = 0;//to keep current index of a GROUP    
        string name, login, password;//current user
        string contact_name;//current contact
        string message;
        size_t choice = 1;//switch
        bool ch(true);//while    
        bool n;//cycles   
        size_t num_of_contact;//to chose the contact in case 4
        size_t presence = 0;//number of groups where this user lists

        cout << "REGISTRATION" << endl;
        while (ch)
        {
            switch (choice)
            {


            case 1:
                name.clear();
                n = true;
                while (n)
                {
                    cout << "Enter your NAME" << endl;
                    while (name.empty())
                    {
                        getline(cin, name);
                    }
                    for (size_t k = 0; k < num_users; k++)
                    {
                        if (user[k].get_name() == name)
                        {
                            n = false;
                            break;
                        }
                    }
                    if (!n)
                    {
                        cout << "This name is already used. Choose another name" << endl;
                        name.clear();
                        n = true;
                    }
                    else n = false;
                }
                n = true;
                while (n)
                {
                    login.clear(); password.clear();
                    cout << "Enter LOGIN" << endl;
                    while (login.empty())
                    {
                        getline(cin, login);
                    }
                    cout << "Enter PASSWORD" << endl;
                    while (password.empty())
                    {
                        getline(cin, password);
                    }
                    for (size_t k = 0; k < num_users; k++)
                    {
                        if (compare_LP <string>(user[k].get_log_pas(), login, password))
                        {
                            n = false;
                            break;
                        }
                    }
                    if (!n)
                    {
                        cout << "Change the login and try again" << endl;
                        login.clear(); password.clear();
                        n = true;
                    }
                    else  n = false;

                }
                choice = request <string, size_t>("to continue REGISTRATION press key 1, for AUTHORIZATION press key 2", 1, 2, num_users);
                user[num_users] = { User<string>(name, login, password) };
                num_users++;

                cout << "REGISTERED USERS:" << endl;
                for (size_t i = 0; i < num_users; i++)
                    cout << i + 1 << ". " << user[i].get_name() << endl;
                break;

            case 2:
                cout << "AUTHORIZATION" << endl;
                n = true;
                while (n)
                {
                    name.clear(); login.clear(); password.clear();
                    cout << "Enter LOGIN" << endl;
                    cin.clear();
                    while (login.empty())
                    {
                        getline(cin, login);

                    }
                    cout << "Enter PASSWORD" << endl;
                    while (password.empty())
                    {
                        getline(cin, password);

                    }
                    for (size_t k = 0; k < num_users; k++)
                    {
                        if (compare_LP <string>(user[k].get_log_pas(), login, password))
                        {
                            user_ind = k;
                            n = false;
                            break;
                        }
                    }
                    if (n)
                    {
                        cout << "Invalid password or login. Try again" << endl;
                        login.clear(); password.clear();
                        n = true;
                    }
                    else n = false;
                }
                name = user[user_ind].get_name();
                cout << "HELLO " << /*user[user_ind].get_name()*/name << "!" << endl << endl;

                choice = request <string, size_t>("ADD a CONTACT: press key 3, CHOOSE a CONTACT: press key 4", 3, 4, num_users);

                //check if this USER has contacts (if choice == 4 && numOf_groups = 0)
                if (choice == 4 && numOf_groups == 0)
                {
                    cout << "You don't have contacts yet" << endl; choice = 3;
                }
                n = true;
                //check if this USER has contacts (if choice == 4 && numOf_groups = 0)
                if (choice == 4 && numOf_groups > 0)
                {
                    for (size_t i = 0; i < numOf_groups; i++)
                    {
                        for (size_t j = 0; j < group[i].get_size_group(); j++)
                        {
                            if (group[i].get_group(j) == user[user_ind].get_name())
                            {
                                n = false;
                                break;
                            }
                        }if (n == false) break;
                    }

                    if (n)
                    {
                        cout << "You don't have contacts yet" << endl;
                        choice = 3;
                        break;
                    }
                }

                break;

            case 3:
                
                //to prevent entry to case 3 if the user already lists in all groups                  
                presence = 0;//number of groups where this user lists
                for (size_t i = 0; i < numOf_groups; i++)
                    for (size_t j = 0; j < group[i].get_size_group(); j++)
                        if (group[i].get_group(j) == name)
                        {
                            presence++;
                        }

                if (presence >= Presence(num_users))
                {
                    cout << user[user_ind].get_name() << ", you are already in touch with all possible contacts" << endl;
                    choice = 4;
                }
                n = true;
                if (choice != 4)
                {
                    while (n)//crearing of contacts
                    {
                        cout << "CREATE a CONTACT" << endl;
                        contact_name.clear();
                        cout << "Enter the NAME of CONTACT" << endl;
                        while (contact_name.empty())
                        {
                            getline(cin, contact_name);
                        }
                        //Chat with yourself is impossible
                        if (user[user_ind].get_name() == contact_name)
                        {
                            cout << "Chat with yourself is impossible" << endl;
                            continue;
                        }
                        //  the name is among of the registered
                        for (size_t i = 0; i < num_users; i++)
                        {
                            if (user[i].get_name() == contact_name)
                            {
                                n = false;
                                break;
                            }
                        }
                        //UNREGISTERED user
                        if (n)
                        {
                            cout << "UNREGISTERED user. Try again" << endl;
                            contact_name.clear();
                        }
                        else n = false;

                        //if This USER has already been ADDED to this group
                        if (temp.get_gr_size() != 0)
                        for (size_t i = 0; i < temp.get_gr_size(); i++)
                            if (temp.get_name(i) == contact_name)
                            {
                                cout << "This USER has already been ADDED to this group." << endl;
                                n = true;
                                break;
                            }
                    }
                    name = user[user_ind].get_name();
                    if (temp.get_gr_size() == 0)
                        temp.insert_name(name);//authorized user's name -> TEMP
                    temp.insert_name(contact_name);//contact name -> TEMP
                    cout << contact_name << " was ADDED" << endl;
                    choice = request <string, size_t>("ADD a CONTACT to THIS group: press key 3, CHOOSE a CONTACT: press key 4", 3, 4, num_users);
                    //if ALL the USERS have already been ADDED to this group and numOf_groups == 0

                    if ((choice == 3 || choice == 4) && temp.get_gr_size() >= num_users && numOf_groups == 0)
                    {
                        //Temp -> Group
                        group[gr_ind].approp ( temp.get_groups(), temp.get_gr_size());
                        cout << "Your new group:" << endl;
                        for (size_t s = 0; s < group[gr_ind].get_size_group(); s++)
                            cout << s + 1 << ". " << group[gr_ind].get_group(s) << endl;
                        cout << "All registred USERS are in this group" << endl;
                        gr_ind++;
                        numOf_groups++;
                        choice = 4;
                        temp.temp_clear();
                        break;
                    }
                    //if ALL the USERS have already been ADDED to this group and there are number of groups more than 0

                    if ((choice == 3 || choice == 4) && temp.get_gr_size() >= num_users && numOf_groups > 0)
                    {
                        n = true;
                        for (size_t i = 0; i < numOf_groups; i++)//check if This Group is already exists
                            if (compare(temp.get_groups(), temp.get_gr_size(), group[i].get_group(), group[i].get_size_group()))
                            {
                                cout << "This Group is already exists, it's NUMBER is " << i << endl;
                                cout << "All registred USERS are in this group" << endl;
                                choice = 4;
                                temp.temp_clear();
                                n = false;
                                break;
                            }
                        if (n)
                        {   //Temp::array -> Message::group
                            group[gr_ind].approp(temp.get_groups(), temp.get_gr_size());                        
                            cout << "Your new group:" << endl;
                            for (size_t s = 0; s < group[gr_ind].get_size_group(); s++)
                                cout << s + 1 << ". " << group[gr_ind].get_group(s) << endl;
                            cout << "All registred USERS are in this group" << endl;
                            gr_ind++;
                            numOf_groups++;
                            choice = 4;
                            temp.temp_clear();
                            break;
                        }
                    }
                    //If NOT all users were involved in the group and user goes to choose next contact                          
                    else if ((choice == 4) && (temp.get_gr_size() < num_users) && (numOf_groups > 0))
                    {
                        //check if This Group is already exists
                        n = true;
                        for (size_t i = 0; i < numOf_groups; i++)
                            //if there is the same group
                            if (compare(temp.get_groups(), temp.get_gr_size(), group[i].get_group(), group[i].get_size_group()))
                            {
                                cout << "This Group is already exists, it's NUMBER is" << i << endl;
                                n = false;
                                temp.temp_clear();
                                break;
                            }

                        if (n)
                        {     //Temp::array -> Message::group
                            group[gr_ind].approp(temp.get_groups(), temp.get_gr_size());
                            cout << "Your new group:" << endl;
                            for (size_t s = 0; s < group[gr_ind].get_size_group(); s++)
                                cout << s + 1 << ". " << group[gr_ind].get_group(s) << endl;
                            gr_ind++;
                            numOf_groups++;
                            temp.temp_clear();
                            break;
                        }
                    }
                    //if the group in temp was created but number Of_groups == 0 
                    else if ((choice == 4) && (temp.get_gr_size() < num_users) && (numOf_groups == 0))
                    {     //Temp::array -> Message::group
                        group[gr_ind].approp(temp.get_groups(), temp.get_gr_size());
                        cout << "Your new group:" << endl;
                        for (size_t s = 0; s < group[gr_ind].get_size_group(); s++)
                            cout << s + 1 << ". " << group[gr_ind].get_group(s) << endl;
                        gr_ind++;
                        numOf_groups++;
                        temp.temp_clear();
                        break;
                    }
                    //If we return in 3 to add a contact in this group and NOT all users were involved in this group 
                    else if (choice == 3 && temp.get_gr_size() < num_users)
                    {
                        cout << "Your group:" << endl;
                        for (size_t s = 0; s < temp.get_gr_size(); s++)
                            cout << s + 1 << ". " << temp.get_name(s) << endl;
                        n = true;
                    }
                }
                break;

            case 4://choose a contact      

                choice = request <string, size_t>("CHAT with your contacts: press key 4, MESSAGE for everyone: press key 6", 4, 6, num_users);
                if (choice == 6) break;

                cout << "Your contacts (groups):" << endl;
                for (size_t i = 0; i < numOf_groups; i++)
                    for (size_t j = 0; j < group[i].get_size_group(); j++)
                        if (group[i].get_group(j) == user[user_ind].get_name())
                        {
                            cout << '\n' << i << ". ";
                            for (size_t k = 0; k < group[i].get_size_group(); k++)
                                cout << group[i].get_group(k) << " ";
                            cout << endl;
                        }cout << endl;

                do
                {
                    cout << "Choose NUMBER of CONTACT (or GROUP)" << endl;
                    do
                    {
                        cin.clear();
                        streamsize L = cin.rdbuf()->in_avail();
                        cin.ignore(L);
                        cin >> num_of_contact;
                        if (!cin)
                            cout << "ENTER a DIGIT" << endl;
                    } while (!cin);
                    //obviously wrong input
                    if (num_of_contact >= numOf_groups || num_of_contact < 0)
                    {
                        cin.clear(); cin.ignore();
                        cout << "Error: INVALID number of CONTACT" << endl;
                    }
                } while (num_of_contact >= numOf_groups || num_of_contact < 0);
                //check if this USER belong to this contact
                if (num_of_contact < numOf_groups)
                {
                    n = true;
                    for (size_t j = 0; j < group[num_of_contact].get_size_group(); j++)
                        if (group[num_of_contact].get_group(j) == user[user_ind].get_name())
                        {
                            choice = 5;
                            n = false;
                            break;
                        }

                    if (n)
                    {
                        cout << "It is NOT YOUR GROUP. Try again" << endl;
                        choice = 4;
                    }
                }

                break;

            case 5:
                for (size_t i = 0; i < mess[num_of_contact].get_size_mes(); i++)
                {
                    cout << num_of_contact << ". ";
                    cout << mess[num_of_contact].get_mess(i) << endl;
                }
                cout << "\nTEXT your message" << endl;
                cin.clear(); cin.ignore();
                getline(cin, message);
                mess[num_of_contact].insert_mess(user[user_ind].get_name() + ": " + message);//message -> Messge::mes               
                choice = next_request<size_t>();
                if (choice == 7) ch = false;
                break;

            case 6:
                cout << "\nTEXT your message" << endl;
                cin.clear(); cin.ignore();
                getline(cin, message);
                for (size_t i = 0; i < numOf_groups; i++)
                    mess[i].insert_mess(user[user_ind].get_name() + ": " + message);//message -> Messge::mes
                choice = next_request<size_t>();
                if (choice == 7) ch = false;
                break;
            }
        }
        delete[]user;
        //delete[]group;
        delete[]mess;

    }
    catch (bad_alloc& exception)
    {
        cout << "Error of NEW" << endl;
    }
    _CrtDumpMemoryLeaks();
    return 0;
}
