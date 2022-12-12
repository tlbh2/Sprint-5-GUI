
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>
using namespace std;

class write
{
private:
    ofstream ofs; 
public:
    write(string const& FileName);
    ~write();
    void save(const string& s);
};

write::write(string const& FileName)
    : ofs(FileName.c_str(), ios::out) // construct the object
{
}

write::~write()
{
    ofs.close();
}

void write::save(const string& s)
{
    ofs << s << endl;
}

class read
{
private:
    ifstream ifs;
public:
    string line, substrings, id, name, x, y, label;
    read(string const& FileName);
    void outPut();
};

read::read(string const& FileName)
    : ifs(FileName.c_str(), ios::out) // construct the object
{
}

void read::outPut()
{
    while (getline(ifs, line))
    {
        cout << line << endl;
    }
}

int main()
{
    // Create and open a text file
    ofstream MyFile("filename.txt");
    // Write to the file
    MyFile << "Files can be tricky, but it is fun enough!" << endl;
    MyFile << "Files can be tricky, but it is fun enough!" << endl;
    MyFile << "Files can be tricky, but it is fun enough!" << endl;
    // Close the file
    MyFile.close();

    fstream file("replay.txt");
    string line, substrings, id , name , x , y , label;
    const char delim = ' ';

    //identify recorded SOS placement in text file

    if (file.good())
    {
        while (getline(file, line))
        {
            stringstream X(line);

            while (X >> id >> name >> x >> y >> label)
            {
                if (id == "-")
                {
                    cout << name << x << y << label << endl;
                    Sleep(200); //slow down the loop
                }
            }

        }
        file.close();
    }
    
    /*
    if (file.good()) //preferred method
    {
        while (file >> id >> name >> x >> y >> label)
        {
            if (id == "-")
            {
                cout << name << x << y << label << endl;
            }
        }
        file.close();
    }
    */

    write* w = new write("replayy.txt");
    read* r = new read("replayy.txt");
   
    w->save("This is a test!");
    //r->outPut();

    return 0;
}
