#include <bits/stdc++.h>
using namespace std;

void toLowerCase(string &str)
{
    transform(str.begin(), str.end(), str.begin(), ::tolower);
}

void toUpperCase(string &str)
{
    transform(str.begin(), str.end(), str.begin(), ::toupper);
}

void write(const string &strrr) 
{
    ofstream outputfile;
    string fileName = "fileName.txt";
    outputfile.open(fileName , ::ios::app);
    if (!outputfile.is_open())
    {
        cout << "Failed to open " << fileName << "." << endl;
        return;
    }

    outputfile << strrr << endl;
    outputfile.close();
    cout << "User data saved successfully." << endl;
}

vector<string> vec; 

template <typename T>
void user_in(const T &inputt)
{
    stringstream ss;
    ss << inputt;  
    vec.push_back(ss.str()); 
}

void finalise_user_in()
{
    stringstream vecContent;

    for (const auto &s : vec) {
        vecContent << s; 
    }

    write(vecContent.str()); 
    vec.clear(); 
}

int login_cred_new()
{
    string name;
    string password;
    cout << "Hey there! Welcome!" << endl;
    cout << "Enter name: ";
    cin >> name;
    user_in(name);
    cout << "Enter Password: ";
    cin >> password;
    user_in(password);

    toUpperCase(name);
    return 0;
}

int searchLineByData(const string &fileName, string searchString, const string &name) {
    toLowerCase(searchString);
    ifstream file(fileName);
    string line;
    int lineNumber = 0;
    bool found = false;
    if (!file.is_open()) {
        cout << "User Doesn't exist, would you like to still search? Y or N: " << endl;
        char ch;
        cin >> ch;
        if (ch == 'Y') {
            login_cred_new();
        }
        return -1;
    }
    while (getline(file, line)) {
        lineNumber++;
        if (line.find(searchString) != string::npos) {
            found = true;
            cout << "Welcome Again, " << name << "!" << endl;
            cout << "Previous searches of user were: \n" << line << endl;
            user_in(searchString);
            break;
        }
    }
    while (getline(file, line))
    {
        lineNumber++;
        if (line.find(searchString) != string::npos)
        {
            found = true;
            cout << line << endl;
        }
    }

    file.close();
    if (!found) {
        cout << "Data not found in the file." << endl;
        return -1;
    }
    return lineNumber;
}


int login_cred_existing()
{
    string name;
    string password;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter Password: ";
    cin >> password;
    

    toUpperCase(name);

    string fileName = "fileName.txt";
    searchLineByData(fileName, name + password, name);
    return 0;
}


class User
{
public:
    virtual void login() = 0; 
    virtual void input() = 0; 
};

int open(int choice, string filmindustry)
{
    ifstream inputfile;
    ifstream inputfile2;

    string filename;
    switch (choice)
    {
    case 1:
        filename = "GENRE";
        break;
    case 2:
        filename = "ACTOR";
        break;
    case 3:
        filename = "DIRECTOR";
        break;
    case 4:
        filename = "RELEASEYEAR";
        break;
    default:
        cout << "Invalid option." << endl;
        return 1;
    }

    string filename1 = filename + filmindustry + ".txt";

    inputfile.open(filename1);
    if (!inputfile.is_open())
    {
        cout << "Failed to open " << filename << endl;
        return 1;
    }

    cout << "Available options are:" << endl;
    string ch;
    while (getline(inputfile, ch))
    {
        cout << ch << endl;
    }
    inputfile.close();

    string choiceStr;
    cout << "Enter your choice: ";
    cin >> choiceStr;
    user_in(choiceStr);
    finalise_user_in();
    
    toUpperCase(choiceStr);
    string movieFilename = choiceStr + filmindustry + ".txt";

    inputfile2.open(movieFilename);
    if (!inputfile2.is_open())
    {
        cout << "Failed to open movie file: " << movieFilename << endl;
        return 1;
    }

    string movie;
    cout << "Movies for the selected option:" << endl;
    while (getline(inputfile2, movie))
    {
        cout << movie << endl;
    }

    inputfile2.close();
    return 0;
}

void getUserInput() 
{
    cout << "Choose the film industry you want movies of: Hollywood or Bollywood" << endl;
    string filmindustry;
    cin >> filmindustry;
    user_in(filmindustry);
    toUpperCase(filmindustry);

    cout << "Enter Preference Number from below list: " << endl;
    cout << "1. Genre\n2. Actor\n3. Director\n4. Releaseyear" << endl;
    int a;
    cin >> a;
    user_in(a);
    open(a,filmindustry);
}

class ExistingUser : public User {
public:
    void login() override {
        login_cred_existing(); 
    }
    
    void input() override {
        getUserInput(); 
    }
};

class NewUser : public User {
public:
    void login() override {
        login_cred_new(); 
    }
    
    void input() override {
        getUserInput(); 
    }
};


int main() {

    int ch;
    cout << "Are you a: " << endl;
    cout << "1. Existing User?" << endl;
    cout << "2. New User?" << endl;
    cout << "Type '1' for Existing user and '2' for New user: ";
    cin >> ch;

    User* user = nullptr;

    switch (ch) {
    case 1:
        user = new ExistingUser();
        break;
    case 2:
        user = new NewUser();
        break;
    default:
        cout << "Invalid option." << endl;
        return 1;
    }

    user->login(); 
    user->input(); 

    delete user; 
    return 0;
}

