#include <iostream>
#include <fstream>

using namespace std;

streampos getFileSize(const string &fileName)
{
    ifstream file(fileName, ios::binary);

    if (!file)
        throw runtime_error("FileReadError: Can not read the file " + fileName);

    file.seekg(0, ios::end);
    streampos fileSize = file.tellg();
    file.close();

    return fileSize;
}

void readBinaryFile(const string &fileName, char *buffer, streampos fileSize)
{
    ifstream file(fileName, ios::binary);

    if (!file)
        throw runtime_error("FileReadError: Can not read the file " + fileName);

    file.read(buffer, fileSize);
    file.close();
}

void writeBinaryFile(const string &fileName, const char *buffer, streampos fileSize)
{
    ofstream file(fileName, ios::binary);

    if (!file)
        throw runtime_error("FileWriteError: Can not Write in the file " + fileName);

    file.write(buffer, fileSize);
    file.close();
}

void copyBinaryFile(const string &fileName, const string &copyName)
{
    streampos fileSize = getFileSize(fileName);
    char *buffer = new char[fileSize];

    try
    {
        readBinaryFile(fileName, buffer, fileSize);
        writeBinaryFile(copyName, buffer, fileSize);
    }
    catch (...)
    {
        delete[] buffer;
        throw;
    }

    delete[] buffer;
}

int main(int argc, char *argv[])
{
    try
    {
        copyBinaryFile("logo.png", "logo2.png");
    }
    catch (const exception &e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}
