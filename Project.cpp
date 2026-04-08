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
    outputfile.open(fileName, ::ios::app);
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

    for (const auto &s : vec)
    {
        vecContent << s;
    }

    write(vecContent.str());
    vec.clear();
}

bool isValidName(const string &name)
{
    if (name.empty()) return false;
    for (char c : name)
        if (!isalpha(c)) return false;
    return true;
}

bool isValidPassword(const string &password)
{
    return password.length() >= 6;
}

bool isValidFilmIndustry(const string &industry)
{
    string upper = industry;
    toUpperCase(upper);
    return (upper == "HOLLYWOOD" || upper == "BOLLYWOOD");
}

int login_cred_new()
{
    string name;
    string password;
    cout << "Hey there! Welcome!" << endl;

    // Validate name
    while (true)
    {
        cout << "Enter name (letters only): ";
        cin >> name;
        if (isValidName(name))
            break;
        cout << "Invalid name. Please use letters only (no spaces or numbers)." << endl;
    }
    toUpperCase(name);
    user_in(name);

    // Validate password
    while (true)
    {
        cout << "Enter Password (min 6 characters): ";
        cin >> password;
        if (isValidPassword(password))
            break;
        cout << "Password too short. Must be at least 6 characters." << endl;
    }
    user_in(password);

    finalise_user_in();

    return 0;
}

int searchLineByData(const string &fileName, const string &searchString, const string &name)
{
    ifstream file(fileName);
    string line;
    int lineNumber = 0;
    bool found = false;

    if (!file.is_open())
    {
        cout << "User doesn't exist. Would you like to register? (Y/N): ";
        char ch;

        // Validate Y/N input
        while (true)
        {
            cin >> ch;
            ch = toupper(ch);
            if (ch == 'Y' || ch == 'N') break;
            cout << "Invalid input. Please enter Y or N: ";
        }

        if (ch == 'Y')
        {
            login_cred_new();
        }
        return -1;
    }

    while (getline(file, line))
    {
        lineNumber++;
        if (line.find(searchString) != string::npos)
        {
            if (!found)
            {
                found = true;
                cout << "Welcome Again, " << name << "!" << endl;
            }
            else
            {
                cout << line << endl;
            }
        }
    }

    file.close();

    if (!found)
    {
        cout << "Data not found in the file." << endl;
        return -1;
    }
    return lineNumber;
}

int login_cred_existing()
{
    string name;
    string password;

    // Validate name
    while (true)
    {
        cout << "Enter name (letters only): ";
        cin >> name;
        if (isValidName(name))
            break;
        cout << "Invalid name. Please use letters only (no spaces or numbers)." << endl;
    }

    // Validate password
    while (true)
    {
        cout << "Enter Password (min 6 characters): ";
        cin >> password;
        if (isValidPassword(password))
            break;
        cout << "Password too short. Must be at least 6 characters." << endl;
    }

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
    // Validate that the user entered something non-empty
    while (true)
    {
        cout << "Enter your choice: ";
        cin >> choiceStr;
        if (!choiceStr.empty()) break;
        cout << "Input cannot be empty. Please try again." << endl;
    }
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
    string filmindustry;

    // Validate film industry input
    while (true)
    {
        cout << "Choose the film industry you want movies of (Hollywood / Bollywood): ";
        cin >> filmindustry;
        if (isValidFilmIndustry(filmindustry))
            break;
        cout << "Invalid choice. Please enter 'Hollywood' or 'Bollywood'." << endl;
    }
    user_in(filmindustry);
    toUpperCase(filmindustry);

    int a;
    // Validate preference menu choice (1-4)
    while (true)
    {
        cout << "Enter Preference Number from below list:" << endl;
        cout << "1. Genre\n2. Actor\n3. Director\n4. Releaseyear" << endl;
        if (cin >> a && a >= 1 && a <= 4)
            break;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
    }
    user_in(a);
    open(a, filmindustry);
}

class ExistingUser : public User
{
public:
    void login() override
    {
        login_cred_existing();
    }

    void input() override
    {
        getUserInput();
    }
};

class NewUser : public User
{
public:
    void login() override
    {
        login_cred_new();
    }

    void input() override
    {
        getUserInput();
    }
};

int main()
{
    int ch;

    // Validate main menu choice (1-2)
    while (true)
    {
        cout << "Are you a:" << endl;
        cout << "1. Existing User?" << endl;
        cout << "2. New User?" << endl;
        cout << "Type '1' for Existing user and '2' for New user: ";
        if (cin >> ch && (ch == 1 || ch == 2))
            break;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid option. Please enter 1 or 2." << endl;
    }

    User *user = nullptr;

    switch (ch)
    {
    case 1:
        user = new ExistingUser();
        break;
    case 2:
        user = new NewUser();
        break;
    }

    user->login();
    user->input();

    delete user;
    return 0;
}
