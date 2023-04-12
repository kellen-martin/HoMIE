#include "loop_header.hpp"

using namespace std;

vector<command> loadCommands()
{
    vector<command> list;
    string line;
    string word;
    ifstream file(commandFile);

    if(file.is_open())
    {
        while(getline(file, line))
        {
            stringstream ss(line);
            command load;

            if(ss >> word)
            {
                if(word == "SETTINGS"){
                    load.type = SETTINGS;

                }else if(word == "CAPTURE"){
                    load.type = CAPTURE;
                    ss >> word;
                    load.captureFrames = stoi(word);
                    ss >> word;

                    if(word == "DIFF_FRAME"){
                        load.detect = DIFF_FRAME;
                        ss >> word;
                        load.frame1 = stoi(word);
                        ss >> word;
                        load.frame2 = stoi(word);
                    }else if(word == "DIFF_STACK"){
                        load.detect = DIFF_STACK;
                        ss >> word;
                        load.frame1 = stoi(word);
                        ss >> word;
                        load.frame2 = stoi(word);
                    }else if(word == "SINGLE_FRAME"){
                        load.detect = SINGLE_FRAME;
                    }

                    ss >> word;
                    load.sampleID = word;



                }else if(word == "DETECT"){
                    load.type = DETECT;
                    ss >> word;
                    load.sampleID = word;
                    ss >> word;
                    
                    if(word == "DIFF_FRAME"){
                        load.detect = DIFF_FRAME;
                        ss >> word;
                        load.frame1 = stoi(word);
                        ss >> word;
                        load.frame2 = stoi(word);
                    }else if(word == "DIFF_STACK"){
                        load.detect = DIFF_STACK;
                        ss >> word;
                        load.frame1 = stoi(word);
                        ss >> word;
                        load.frame2 = stoi(word);
                    }else if(word == "SINGLE_FRAME"){
                        load.detect = SINGLE_FRAME;
                    }
                    

                }else if(word == "DATA"){
                    load.type = DATA;

                }
            }



        }
        file.close();
    }else{
        cout << "Cannot open file '" << commandFile << "'." << endl;
    }

    return list;
}
