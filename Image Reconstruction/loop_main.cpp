#include "loop_defs.cpp" // for global variables
#include "loop_dtypes.cpp" // for data types

#ifndef LOOP_FUNCTIONS
#define LOOP_FUNCTIONS
#include "loadCommands.cpp"
#endif


using namespace std;

int main()
{
    bool verbose = true;

    pid_t child;
    char in = '!';
    cout << "Enter a new set of commands?";
    while(!(in == 'y') && !(in == 'n'))
    {
        cout << "(y/n): "; cin >> in;
    }

    if(in == 'y'){
        child = fork();

        if(child == 0){
            // child process
            vector<const char*> args = {"./take_commands", nullptr};
            execvp(args[0], const_cast<char* const*>(args.data()));
            return 1;
        }else{
            // parent process
            int status;
            pid_t terminated = waitpid(child, &status, 0);
            cout << endl;
        }
    }

    // load commands here
    vector<command> commands = loadCommands();

    int n = commands.size();

    for(int i = 0; i < n; i++)
    {
        // switch on type:
        switch(commands[i].type)
        {
            case NONE:
                // undefined command
                break;


            case SETTINGS:
                // change image sensor settings
                break;


            case CAPTURE:
                // capture images
                // fork and use sdk program to capture n frames
                cout << "Capture " << commands[i].captureFrames << " frames for ID: " << commands[i].sampleID;
                cout << ", reconstruct using method " << commands[i].detect << endl;

                child = fork();

                if(child == 0){
                    // child process (uncomment and call capture program):

                    // vector<const char*> args = {"./take_commands", nullptr};
                    // execvp(args[0], const_cast<char* const*>(args.data()));
                    // return 1;
                    
                    return 0;
                }else{
                    // parent process
                    int status;
                    pid_t terminated = waitpid(child, &status, 0);
                    cout << endl;
                }

                break;


            case DETECT:
                // do motion detection on a reconstruction
                switch(commands[i].detect)
                {
                    case DIFF_FRAME:
                        if(verbose) cout << "Reconstruct sample " << commands[i].sampleID << " and use frames " << commands[i].frame1 << " and " << commands[i].frame2 << " for diff frame motion detection" << endl;
                        child = fork();

                        if(child == 0){
                            // child process (uncomment and call capture program):
                            vector<const char*> args = {"./loop_recon", commands[i].sampleID.c_str(), "DIFF_FRAME", to_string(commands[i].frame1).c_str(), to_string(commands[i].frame2).c_str(), "ALL", nullptr};
                            execvp(args[0], const_cast<char* const*>(args.data()));
                            return 1;
                            
                            return 0;
                        }else{
                            // parent process
                            int status;
                            pid_t terminated = waitpid(child, &status, 0);
                            cout << endl;
                        }

                        break;

                    case DIFF_STACK:
                        if(verbose) cout << "Reconstruct sample " << commands[i].sampleID << " and use frames " << commands[i].frame1 << " to " << commands[i].frame2 << " for diff stack motion detection" << endl;
                        child = fork();

                        if(child == 0){
                            // child process (uncomment and call capture program):
                            vector<const char*> args = {"./loop_recon", commands[i].sampleID.c_str(), "DIFF_STACK", to_string(commands[i].frame1).c_str(), to_string(commands[i].frame2).c_str(), "ALL", nullptr};
                            execvp(args[0], const_cast<char* const*>(args.data()));
                            return 1;
                            
                            return 0;
                        }else{
                            // parent process
                            int status;
                            pid_t terminated = waitpid(child, &status, 0);
                            cout << endl;
                        }

                        break;

                    case SINGLE_FRAME:
                        if(verbose) cout << "Reconstruct sample " << commands[i].sampleID << " and use frame " << commands[i].frame1 << " for single frame motion detection" << endl;
                        child = fork();

                        if(child == 0){
                            // child process (uncomment and call capture program):

                            vector<const char*> args = {"./loop_recon", commands[i].sampleID.c_str(), "SINGLE_FRAME", to_string(commands[i].frame1).c_str(), "ALL", nullptr};
                            execvp(args[0], const_cast<char* const*>(args.data()));
                            return 1;
                            
                            return 0;
                        }else{
                            // parent process
                            int status;
                            pid_t terminated = waitpid(child, &status, 0);
                            cout << endl;
                        }
                        break;

                    default:
                        break;
                }


                break;


            case DATA:

                switch(commands[i].returnType)
                {   
                    case TYPE_RECON:
                        switch(commands[i].detect)
                        {
                            case DIFF_FRAME:
                                cout << "Return diff frame from sample " << commands[i].sampleID << " using frames " << commands[i].frame1 << " and " << commands[i].frame2 << endl;

                                break;

                            case DIFF_STACK:
                                cout << "Return diff stack from sample " << commands[i].sampleID << " using frames " << commands[i].frame1 << " to " << commands[i].frame2 << endl;
                                
                                break;

                            case SINGLE_FRAME:
                                cout << "Return single frame from sample " << commands[i].sampleID << ", frame: " << commands[i].frame1 << endl;
                                
                                break;

                            default:
                                break;
                        }

                        break;

                    case TYPE_RAW:
                        cout << "Return raw frame from sample: " << commands[i].sampleID << endl;
                        break;

                    default:
                        break;
                }

                // send compression data
                break;


            default:
                // unexpected command
                break;
        }
    }

    return 0;
}