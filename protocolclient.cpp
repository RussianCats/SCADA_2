#include "protocolclient.h"

void ProtocolClient::run()
{
    setTerminationEnabled(true);
    ifstream file("settings.txt"); // окрываем файл для чтения
        string value;

        if (file.is_open())
        {
            for (int i = 0; i < 7; i++)
            {

                file >> value;
                string delim = "=";
                vector<string> out;

                size_t start;
                size_t end = 0;

                while ((start = value.find_first_not_of(delim, end)) != std::string::npos)
                {
                    end = value.find(delim, start);
                    out.push_back(value.substr(start, end - start));
                };

                if (out[0] == VALUE_IP)
                    PATH += " " + out[1];

                if (out[0] == VALUE_PORT)
                    PATH += " " + out[1];
            }
        };
        file.close(); // закрываем файл

    system(PATH.c_str());
}

