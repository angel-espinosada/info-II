#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void readByCharacter(const string& filename);
void readByLine(const string& filename);

int main()
{
    const string outFile = "ejemplo.txt";

    try {
        // Try to create/overwrite the file first
        fstream outputFile;
        outputFile.open(outFile, ios::out | ios::trunc);
        if (!outputFile)
        {
            throw runtime_error("Failed to create/open file for writing");
        }

        // Write sample content
        outputFile << "This is a sample file.\n";
        outputFile << "It contains multiple lines of text.\n";
        outputFile << "Third line for demonstration purposes.\n";
        outputFile.close();

        string inFile;
        cout << "Ingrese el nombre del archivo a leer: ";
        cin >> inFile;

        // Read the file using different methods
        readByCharacter(inFile);
        readByLine(inFile);

    } catch (const ifstream::failure& e) {
        cerr << "\nI/O Error: " << e.what() << endl;
    } catch (const runtime_error& e) {
        cerr << "\nError: " << e.what() << endl;
    } catch (...) {
        cerr << "\nUnknown error occurred while handling the file." << endl;
    }

    return 0;
}

// Function to read a file character by character
void readByCharacter(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        throw runtime_error("Failed to open file for character-by-character reading");
    }

    char ch;
    cout << "\nReading '" << filename << "' character by character:\n";
    while (file.get(ch))
    {
        cout << ch;
    }
    file.close();
}

// Function to read a file line by line
void readByLine(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        throw runtime_error("Failed to open file for line-by-line reading");
    }

    string line;
    int lineCount = 1;
    cout << "\nReading '" << filename << "' line by line:\n";
    while (getline(file, line))
    {
        cout << "Line " << lineCount++ << ": " << line << endl;
    }
    file.close();
}
