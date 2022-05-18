#include<iostream>
#include<fstream>
#include<string.h>
#include <iomanip>
#include <vector>
#include<windows.h>
using namespace std;

void login();
void registr();
void forgot();

class Item
{	
private:  
	string _text;
	bool _done;
public:
	Item();	
	Item(string);
	~Item();

	string text();
	void done();
	bool is_done();
};

Item::Item()
{
	_text = "";
	_done = false;
}

Item::Item(string item)
{
	int startf = item.find("false");
	int startt = item.find("true");
	string str;

	if (startf > -1 && startt == -1) 
	{
		str = item.substr(0, startf - 1);
		_done = false;
	} else if (startt > -1 && startf == -1) { 
		str = item.substr(0, startt - 1);
		_done = true;
	} else if (startf == -1 && startt == -1) {
		str = item;
		_done = false;
	}
	_text = str;
}

Item::~Item()
{
}

string Item::text()
{
	return _text;
}

void Item::done()
{
	_done = true;
}

bool Item::is_done()
{
	return _done;
}

class TodoList 
{
private:
	const char* filename;
	vector<Item> list;
public:
	TodoList();
	TodoList(const char*);
	~TodoList();
	void read();
	void display();
	void create();
	void save();
	void add();
	void clear();
	void check();
	int get_count();
};

TodoList::TodoList()
{
	filename = nullptr;
}

TodoList::TodoList(const char* filename)
{
	this->filename = filename;
}

TodoList::~TodoList()
{
}

void TodoList::read()
{
	fstream fs(filename, fstream::in);
	string line;
	list.clear();
	while(getline(fs, line))
	{
		if (line == "") continue;
		Item item(line);
		list.push_back(item);
	}
	fs.close();
}

void TodoList::display()
{
	cout << "Your todo list: " << endl << endl;
	const int W = 40;	
	cout << "   " << setw(W) << left << "TASK" << "DONE" << endl;
	cout << "   " << setw(W) << left << "----" << "----" << endl;
	for (int i = 0; i < list.size(); ++i)
		cout << i + 1 << ") " << setw(W) << left << list[i].text() << (list[i].is_done() ? "Done" : "" ) << endl;	
}

void TodoList::create()
{
	bool is_finished = false;
	int count = 1;
	string task;
	list.clear();
	while(!is_finished)
	{	
		cout << count << ": ";
		getline(cin, task);
		if (task == "") is_finished = true;
		Item item(task);
		list.push_back(item);
		count++;
	}
}

void TodoList::save()
{
	fstream fs(filename, fstream::out);
	for (Item item : list) 
	{
		if (item.text().empty()) continue;
		fs << item.text() << " " << (item.is_done() ? "true" : "false") << endl;
	}
	fs.close();
}

int TodoList::get_count()
{
	return list.size();
}

void TodoList::add()
{
	int index = list.size();
	while (true)
	{
		cout << ++index << ": ";
		string task;
		getline(cin, task);
		if (task == "") break;
		Item item(task);
		list.push_back(item);
	}
	save();
}

void TodoList::clear()
{
	list.clear();
	remove(filename);
}	

void TodoList::check()
{
	cout << "Enter number of task: ";
	string choice;
	getline(cin, choice);
	if (choice.empty()) return;
	for (char c : choice) if (isalpha(c)) return;
	int index = stoi(choice) - 1;
	if (index > list.size()) return;
	list[index].done();
	save();
}

void SetColor(int ForgC)
{
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}

int main()
{
	//system("Color 51");
	while(1){
		SetColor(14);
        int choice;
        cout<<"***********************************************************************\n\n\n";
        cout<<"                      Welcome to login page                               \n\n";
        cout<<"*******************        MENU        *******************************\n\n";
        cout<<"1.LOGIN"<<endl;
        cout<<"2.REGISTER"<<endl;
        cout<<"3.FORGOT PASSWORD (or) USERNAME"<<endl;
        cout<<"4.Exit"<<endl;
        cout<<"\nEnter your choice :";
        cin>>choice; 
        cout<<endl;
        switch(choice)
        {
                case 1:
                        login();
                        break;
                case 2:
                        registr();
                        break;
                case 3:
                        forgot();
                        break;
                case 4:
                        return 0;
                default:
                        system("cls");
                        cout<<"You've made a mistake , give it a try again\n"<<endl; 
                        
        }
	}
}

void login()
{
	SetColor(9);
        int count;
        string user,pass,u,p;
        system("cls");
        cout<<"please enter the following details"<<endl;
        cout<<"USERNAME :";
        cin>>user;
        cout<<"PASSWORD :";
        cin>>pass;
        ifstream input("database.txt");
        while(input>>u>>p)
        {
            if(u==user && p==pass)
            {
                count=1;
                system("cls");
            }
        }
        input.close();
        if(count==1)
        {
        	SetColor(2);
            cout<<"\nHello "<<user<<"\nLOGIN SUCESS\nThanks for logging in\n";
            cin.get();
            TodoList tasks("todolist.txt");
	while(true)
	{
		SetColor(12);
		tasks.read();
		if (tasks.get_count() > 0)
		{
			tasks.display();
			cout << endl;
			cout << "1) Add" << endl;
			cout << "2) Clear" << endl;
			cout << "3) Check" << endl;
			cout << "Choice: ";
			string choice;
			getline(cin, choice);
			if (choice == "1")
			{
				tasks.add();
			} else if (choice == "2") {
				tasks.clear();
			} else if (choice == "3") {
				tasks.check();
			} else {
				break;
			}
		} else {
			cout << "Created a new list .." << endl;
			tasks.create();
			cout << endl; 
			tasks.display();
			tasks.save();
				}
			}       
        }
        else
        {
        	SetColor(4);
            cout<<"\nLOGIN ERROR\nPlease check your username and password\n";  
        }
}

void registr()
{
        SetColor(11);
        string reguser,regpass,ru,rp;
        system("cls");
        cout<<"Enter the username :";
        cin>>reguser;
        cout<<"\nEnter the password :";
        cin>>regpass;
        ofstream reg("database.txt",ios::app);
        reg<<reguser<<' '<<regpass<<endl;
        system("cls");
        SetColor(10);
        cout<<"\nRegistration Sucessful\n";      
}

void forgot()
{
	SetColor(6);
        int ch;
        system("cls");
        cout<<"Forgotten ? We're here for help\n";
        cout<<"1.Search your id by username"<<endl;
        cout<<"2.Search your id by password"<<endl;
        cout<<"3.Main menu"<<endl;
        cout<<"Enter your choice :";
        cin>>ch;
        switch(ch)
        {
                case 1:
                {
                        int count=0;
                        string searchuser,su,sp;
                        cout<<"\nEnter your remembered username :";
                        cin>>searchuser;
                        ifstream searchu("database.txt");
                        while(searchu>>su>>sp)
                        {
                                if(su==searchuser)
                                {
                                        count=1;
                                }
                        }
                        searchu.close();
                        if(count==1)
                        {
                                cout<<"\n\nHurray, account found\n";
                                cout<<"\nYour password is "<<sp;
                                cin.get();
                                cin.get();
                                system("cls");   
                        }
                        else
                        {
                                cout<<"\nSorry, Your userID is not found in our database\n";
                                cout<<"\nPlease kindly contact your system administrator for more details \n";
                                cin.get();
                                cin.get();
                        }
                        break;
                }
                case 2:
                {
                        int count=0;
                        string searchpass,su2,sp2;
                        cout<<"\nEnter the remembered password :";
                        cin>>searchpass;
                        ifstream searchp("database.txt");
                        while(searchp>>su2>>sp2)
                        {
                                if(sp2==searchpass)
                                {
                                        count=1;
                                }       
                        }
                        searchp.close();
                        if(count==1)
                        {
                                cout<<"\nYour password is found in the database \n";
                                cout<<"\nYour Id is : "<<su2;
                                cin.get();
                                cin.get();
                                system("cls");    
                        }
                        else
                        {
                                cout<<"Sorry, We cannot found your password in our database \n";
                                cout<<"\nkindly contact your administrator for more information\n";
                                cin.get();
                                cin.get();
                        }
                        break;
                }
                case 3:
                {
                        cin.get();
                        main();
                }
                default:
                        cout<<"Sorry, You entered wrong choice. Kindly try again"<<endl;
                        forgot();
        }
}
