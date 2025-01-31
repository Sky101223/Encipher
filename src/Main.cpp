#include <iostream>
#include <stdint.h>
#include <fstream>
#include <sstream>
#include <sys/stat.h>

static size_t GetFileSize(const char* _filename)
{
    if (_filename == NULL)
        std::cerr << "Error: The file name cannot be empty!\n";

    struct stat statBuffer;

    stat(_filename, &statBuffer);

    size_t filesize = statBuffer.st_size;

    return filesize;
}

int main(void)
{
    std::string content;

    {
        std::fstream input("Input.in", std::ios::in);
        std::fstream original("ResultFiles/Original.out", std::ios::out);
        if (!input.is_open())
        {
            std::cerr << "Error: File opening error! Please check if the file path is correct.\n";
        }

        std::cout << "The size of file is " << GetFileSize("Input.in") << " bytes." << std::endl;

        std::stringstream temp;
        temp << input.rdbuf();
        content = temp.str();

        for (std::string::iterator i_character = content.begin();
            i_character != content.end(); ++i_character)
        {
            if (*i_character == ' ')
                content.erase(i_character);
        }

        original.seekp(0);
        original << content;

        input.close();
        original.close();
    }


    {
        std::fstream ascllOut("ResultFiles/ASCLL.out", std::ios::out);
        ascllOut.seekp(0);
        for (char& character : content)
        {
            ascllOut << static_cast<int32_t>(character);
        }
        ascllOut.close();

        std::fstream ascllIn("ResultFiles/ASCLL.out", std::ios::in);
        ascllIn.seekg(0);

        std::fstream morseCodeOut("ResultFiles/MorseCode.out", std::ios::out);
        std::stringstream temp;
        temp << ascllIn.rdbuf();
        morseCodeOut.seekp(0);
        for (char& number : temp.str())
        {
            switch (number)
            {
            case '0':   morseCodeOut << "-----"; break;
            case '1':   morseCodeOut << ".----"; break;
            case '2':   morseCodeOut << "..---"; break;
            case '3':   morseCodeOut << "...--"; break;
            case '4':   morseCodeOut << "....-"; break;
            case '5':   morseCodeOut << "....."; break;
            case '6':   morseCodeOut << "-...."; break;
            case '7':   morseCodeOut << "--..."; break;
            case '8':   morseCodeOut << "---.."; break;
            case '9':   morseCodeOut << "----."; break;
            default:    continue;
            }
        }
        ascllIn.close();
        morseCodeOut.close();

        std::fstream morseCodeIn("ResultFiles/MorseCode.out", std::ios::in);
        morseCodeIn.seekg(0);
        std::fstream result("ResultFiles/Result.out", std::ios::out);
        std::stringstream resultTemp;
        result.seekp(0);
        resultTemp << morseCodeIn.rdbuf();
        for (char& character : resultTemp.str())
        {
            result << std::to_string(static_cast<int32_t>(character));
        }

        morseCodeIn.close();
        result.close();

        std::cout << "Okay, you can find Result.\nout in the ResultFiles folder, which is the encrypted result." << std::endl;
    }

    return 0;
}