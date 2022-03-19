/*
 * Name: Aidan Calenda
 * Assignment: Lab 6
 * Section: 3
 */
#include <iostream> // input output
#include <string> // string capability
#include <cstdlib> // some standard functions (random number)
#include "vector"
#include <fstream> // to read files
#include <algorithm>
using namespace std;

static const int NUMBER_OF_SENSORS = 14;
/**
 * Returns a vector of strings by splitting on a delimiter
 * @param s the string you want to split
 * @param delimiter the delimiter (for e.g. ,)
 * @return the split strings as a vector
 */
vector<string> split (const string& s, const string& delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

/**
 * Converts a time string (HH mm ss) into seconds
 * @return seconds
 */
int getSeconds(const string& time) {
    int h, m, s= 0;

    if (sscanf_s(time.c_str(), "%d %d %d", &h, &m, &s) >= 2){
        int secs = h *3600 + m*60 + s;
        return secs;
    }
    return 0;
}

/**
 * Converts seconds into 24 hour time (HH mm ss)
 */
string secondsToTimeString(int seconds) {
    int h = seconds / 3600.0;
    int m = (seconds - h*3600)/60.0;
    int s = (seconds - (h*3600) - (m*60));
    string res = to_string(h) + " " + to_string(m) + " " + to_string(s);
    return res;
}

vector<int> generatePlayerBibs(int numberOfPlayers) {
    vector<int> runnerBibs(numberOfPlayers);

    for (int i=0; i<numberOfPlayers;i++) {
        // generate unique number
        int bib = rand() % 500;
        while (find(runnerBibs.begin(), runnerBibs.end(), bib) != runnerBibs.end()) {
            bib = rand() % 500;
        }
        runnerBibs.at(i) = bib;
    }
    return runnerBibs;
}

void generateTimesFile(const string& fileName) {
    ofstream file(fileName);
    if (file.is_open()) {
        srand(time(nullptr));
        // write the gun time
        file << "08 00 00\n";
        int seconds = getSeconds("08 00 00");
        const int numberOfPlayers = 20;
        vector<int> runnerBibs = generatePlayerBibs(numberOfPlayers);
        
        for (int i=0;i<=NUMBER_OF_SENSORS;i++) {
            vector<int> tempRunners(runnerBibs);// deep copy
            for (int player=0;player < numberOfPlayers;player++) {
                int runner = rand() % tempRunners.size();
                int runnerBib = tempRunners.at(runner);
                tempRunners.erase(tempRunners.begin() + runner);

                seconds += rand() % 120;
                file << to_string(i) << ", " << to_string(player) << ", "
                << to_string(runnerBib) << ", " << secondsToTimeString(seconds) << "\n";
            }
            if (i < NUMBER_OF_SENSORS - 1) {
            seconds += rand() % 900 + 600; // add atleast between 6-10 mins
            } else {
                seconds += rand() % 120 + 60;
            }
        }
        file.close();
    }
}

vector<string> readFile(const string& fileName) {
    vector<string> times;
        ifstream file(fileName);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                printf("%s\n", line.c_str());
                // write code to put the lines in the vector
            }
            file.close();
        }
    return times;
}




int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        throw runtime_error("Missing file information/Generate command");
    }

     if (string(argv[1]) =="g") { // generate the times.txt file
        generateTimesFile("times.txt");
    } else {
        const string fileName = argv[1];
        auto times = readFile(fileName);
    


    // implement your code
    }

 
    
    return 0;
}
