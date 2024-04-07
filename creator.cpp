#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


int main()
{
    int i;
    std::string line;
    std::ifstream instream;
    
    for (i=2; i<=59; i++)
    {
        if (i<10)
        {
            instream.open("ue23c0101.sub");
            std::stringstream ss;
            ss << i;
            std::string s;
            ss >> s;
            getline(instream, line);
            std::ofstream outstream;
            outstream.open("ue23c010"+ s + ".sub");
            while(instream)
            {
                outstream << line;
                if (line != "CSC-251")
                    outstream << '\n';
                getline(instream, line);
            }
            outstream.close();
            instream.close();
        }
        else
        {
            instream.open("ue23c0101.sub");
            std::stringstream ss;
            ss << i;
            std::string s;
            ss >> s;
            getline(instream, line);
            std::ofstream outstream;
            outstream.open("ue23c01"+ s + ".sub");
            while(instream)
            {
                outstream << line;
                if (line != "CSC-251")
                    outstream << '\n';
                getline(instream, line);
            }
            outstream.close();
            instream.close();
        }
    }
    std::cout <<"All done";
    return 0;
}