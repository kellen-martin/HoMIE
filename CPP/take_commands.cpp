#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    string filename = "Commands.txt";
    string line;
    string sampleID;
    char inChar;
    int option;
    int option2;
    int option3;
    int option4;
    int option5;
    int temp;
    ofstream file;
    int maxN = 200;

    file.open(filename);

    // write to file line by line: "file << Line 1\nLine 2\n;"

    while(true)
    {   
        line = "";
        option = 0;
        cout << endl;
        cout << "----------- select command type ----------" << endl;
        cout << "    1:  Image sensor settings" << endl;
        cout << "    2:  Capture images" << endl;
        cout << "    3:  Motion detection" << endl;
        cout << "    4:  Data request" << endl;
        cout << "------------------------------------------" << endl << endl;

        while((option < 1) || (option > 4))
        {
            cout << "(1-4): ";
            cin >> option;
        }

        switch(option)
        {
            case 1: // image sensor settings
                break;

            case 2: // capture images
                line = "CAPTURE";
                option2 = 0;
                cout << "------------- Capture images -------------" << endl;
                cout << "    Enter an ID for this sample: "; cout << endl;
                cout << "ID (no spaces): ";
                cin >> sampleID;
                cout << "    Number of frames to capture: ";
                while((option2 < 1) || option2 > maxN)
                {
                    cin >> option2;
                    if(option2 < 1) cout << "(enter a positive number): ";
                    if(option2 > maxN) cout << "(maximum of " << maxN << " frames): ";
                }

                line += " " + to_string(option2);

                if(option2 > 1)
                {   
                    option3 = 0;
                    cout << "    Select preferred motion detection method:" << endl;
                    cout << "      1:  Difference frame" << endl;
                    cout << "      2:  Difference stack" << endl;
                    while((option3 < 1) || (option3 > 2))
                    {
                        cout << "(1-2): ";
                        cin >> option3;
                    }

                    if(option3 == 1)
                    {   
                        line += " DIFF_FRAME"; 
                        option4 = 0;
                        cout << "Select frame 1: ";
                        while((option4 < 1) || (option4 > option2))
                        {
                            cout << "(1-" << option2 << "): ";
                            cin >> option4;
                        }
                        option5 = 0;
                        cout << "Select frame 2: ";
                        while((option5 < 1) || (option5 > option2) || (option5 == option4))
                        {
                            if(option5 == option4) cout << "Select a different frame ";
                            cout << "(1-" << option2 << "): ";
                            cin >> option5;
                        }

                        line += " " + to_string(option4) + " " + to_string(option5);

                        // save command as new capture with n frames difference frame

                    }else{
                        line += " DIFF_STACK";
                        option4 = 0;
                        cout << "Select stack starting frame: ";
                        while((option4 < 1) || (option4 > option2))
                        {
                            cout << "(1-" << option2 << "): ";
                            cin >> option4;
                        }
                        option5 = 0;
                        cout << "Select stack ending frame: ";
                        while((option5 < 1) || (option5 > option2) || (option5 == option4))
                        {
                            if(option5 == option4) cout << "Select a different frame ";
                            cout << "(1-" << option2 << "): ";
                            cin >> option5;
                        }

                        if(option4 > option5)
                        {
                            temp = option4;
                            option4 = option5;
                            option5 = temp;
                        }

                        line += " " + to_string(option4) + " " + to_string(option5);

                        // save command as new capture with n frames difference stack

                    }

                }else{
                    line += " SINGLE_FRAME";
                    // save command as single frame capture with single frame detect

                }

                line += " " + sampleID;

                cout << "------------------------------------------" << endl;

                break;

            case 3: // motion detection
                line = "DETECT";

                option2 = 0;
                cout << "------------ Motion detection ------------" << endl;
                cout << "    Enter the ID of the sample to process:" << endl;
                cout << "ID (no spaces): "; cin >> sampleID;
                line += " " + sampleID;
                cout << "    Select motion detection method:" << endl;
                cout << "      1:  Difference frame" << endl;
                cout << "      2:  Difference stack" << endl;
                cout << "      3:  Single frame" << endl;
                while((option2 < 1) || (option2 > 3))
                {
                    cout << "(1-3): "; cin >> option2;
                }

                switch(option2)
                {
                    case 1:
                        line += " DIFF_FRAME"; 
                        option4 = 0;
                        cout << "Select frame 1: ";
                        while((option4 < 1))
                        {
                            cout << "(1-nFrames): ";
                            cin >> option4;
                        }
                        option5 = 0;
                        cout << "Select frame 2: ";
                        while((option5 < 1) || (option5 == option4))
                        {
                            if(option5 == option4) cout << "Select a different frame ";
                            cout << "(1-nFrames): ";
                            cin >> option5;
                        }

                        line += " " + to_string(option4) + " " + to_string(option5);

                        break;

                    case 2:
                        line += " DIFF_STACK";
                        option4 = 0;
                        cout << "Select stack starting frame: ";
                        while((option4 < 1))
                        {
                            cout << "(1-nFrames): ";
                            cin >> option4;
                        }
                        option5 = 0;
                        cout << "Select stack ending frame: ";
                        while((option5 < 1) || (option5 == option4))
                        {
                            if(option5 == option4) cout << "Select a different frame ";
                            cout << "(1-nFrames): ";
                            cin >> option5;
                        }

                        if(option4 > option5)
                        {
                            temp = option4;
                            option4 = option5;
                            option5 = temp;
                        }

                        line += " " + to_string(option4) + " " + to_string(option5);
                        break;

                    case 3:
                        line += " SINGLE_FRAME";
                        option4 = 0;
                        cout << "Select a frame ";
                        while(option4 < 1)
                        {
                            cout << "(1-nFrames): "; cin >> option4;
                        }

                        line += " " + to_string(option4);

                        break;

                    default:
                        break;
                }

                
                
                cout << "------------------------------------------" << endl;
                break;

            case 4: // data request
                line = "DATA";
                option2 = 0;
                sampleID = "";
                cout << "-------------- Data request --------------" << endl;
                cout << "Enter a sample ID (no spaces): "; cin >> sampleID;
                line += " " + sampleID;
                cout << "Select a frame type: " << endl;
                cout << "    1:  Reconstructed frame" << endl;
                cout << "    2:  Raw frame" << endl;
                while((option2 < 1) || (option2 > 2))
                {
                    cout << "(1-2): "; cin >> option2;
                }

                if(option2 == 1){
                    // reconstructed frame
                    line += " RECON";

                    option3 = 0;
                    cout << "Select motion detection method:" << endl;
                    cout << "    1:  Difference frame" << endl;
                    cout << "    2:  Difference stack" << endl;
                    cout << "    3:  Single frame" << endl;
                    while((option3 < 1) || (option3 > 3))
                    {
                        cout << "(1-3): "; cin >> option3;
                    }

                    switch(option3)
                    {
                        case 1:
                            line += " DIFF_FRAME"; 
                            option4 = 0;
                            cout << "Select frame 1: ";
                            while((option4 < 1))
                            {
                                cout << "(1-nFrames): ";
                                cin >> option4;
                            }
                            option5 = 0;
                            cout << "Select frame 2: ";
                            while((option5 < 1) || (option5 == option4))
                            {
                                if(option5 == option4) cout << "Select a different frame ";
                                cout << "(1-nFrames): ";
                                cin >> option5;
                            }

                            line += " " + to_string(option4) + " " + to_string(option5);

                            break;

                        case 2:
                            line += " DIFF_STACK";
                            option4 = 0;
                            cout << "Select stack starting frame: ";
                            while((option4 < 1))
                            {
                                cout << "(1-nFrames): ";
                                cin >> option4;
                            }
                            option5 = 0;
                            cout << "Select stack ending frame: ";
                            while((option5 < 1) || (option5 == option4))
                            {
                                if(option5 == option4) cout << "Select a different frame ";
                                cout << "(1-nFrames): ";
                                cin >> option5;
                            }

                            if(option4 > option5)
                            {
                                temp = option4;
                                option4 = option5;
                                option5 = temp;
                            }

                            line += " " + to_string(option4) + " " + to_string(option5);
                            break;

                        case 3:
                            line += " SINGLE_FRAME";
                            option4 = 0;
                            cout << "Select a frame ";
                            while(option4 < 1)
                            {
                                cout << "(1-nFrames): "; cin >> option4;
                            }

                            line += " " + to_string(option4);

                            break;

                        default:
                            break;
                    }

                    option4 = 0;
                    cout << "Select an option for returning data:" << endl;
                    cout << "    1:  Full image" << endl;
                    cout << "    2:  Motion detection flags only" << endl;
                    while((option4 < 1) || (option4 > 2))
                    {
                        cout << "(1-2): "; cin >> option4;
                    }
                    
                    if(option4 == 1){
                        // save full image
                        line += " FULL";
                    }else{
                        // save only detection flags
                        line += " FLAGS";
                    }

                    cout << "------------------------------------------" << endl;
                    break;

                    
                }else{
                    // raw frame
                    line += " RAW";
                }

                





                cout << "------------------------------------------" << endl;
                break;

            default:
                break;
        }

        line += "\n";
        file << line;


        inChar = '0';
        cout << "Enter another command? ";
        while((!(inChar == 'y') && !(inChar == 'Y')) && (!(inChar == 'n') && !(inChar == 'N')))
        {
            cout << "(y/n): ";
            cin >> inChar;
        }

        if((inChar == 'n') || (inChar == 'N')) break;
        
    }

    file.close();

    return 0;
}
