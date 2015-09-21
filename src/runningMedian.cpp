#include <iostream>     // cout
#include <fstream>      // ofstream/ifstream - input/output files
#include <sstream>      // stringstream - split string into words
#include <queue>        // priority_queue
#include <vector>       // vector
#include <functional>   // greater - for min/max heaps
#include <algorithm>    // sort file names in a-z order
#include <string>       // string
#include <iomanip>      // setprecision for median output
#include <dirent.h>     // dirent - folder/files
#include <string.h>     // strlen/strcmp

class Median {
    std::priority_queue<int> maxHeap;
    std::priority_queue<int, std::vector<int>, std::greater<int> > minHeap;
public:
    void runningMedian() {
        std::string inputDir = "wc_input";
        std::string outputPath = "wc_output/med_result.txt";
        std::ofstream outFile;
        outFile.open(outputPath, std::ofstream::out);
        if (!outFile.is_open()) {
            std::cout << "Error opening file for output!";
            return;
        }
        std::vector<std::string> files = getAllTxts(inputDir);
        std::sort(files.begin(), files.end());   // sort in alphabetical order a-z
        std::cout << "Processing txt files: " << std::endl;
        for (std::string file : files) {
            std::ifstream inFile;
            std::cout << "    " << file << std::endl;
            inFile.open(inputDir + "/" + file, std::ios::in);
            std::string line;
            if (!inFile) return;
            while (getline(inFile, line)) {  // get each line in each file
                int num = countWordsInString1(line);
                addNewNumber(num);
                double m = getMedian();
                outFile << std::setprecision(1) << std::fixed << m << std::endl;
                //std::cout << setprecision(1) << std::fixed << m << std::endl;
            }
            inFile.close();
        }
        outFile.close();
        std::cout << "Done!" << std::endl;
    }
    
    void addNewNumber(int num) {
        /* Note: addNewNumber maintains a condition that 
         * maxHeap.size() >= minHeap.size() */
        if (maxHeap.size() == minHeap.size()) {
            if ((!minHeap.empty()) && (num > minHeap.top())) {
                maxHeap.push(minHeap.top()); minHeap.pop();
                minHeap.push(num);
            }
            else {
                maxHeap.push(num);
            }
        }
        else {
            if (num < maxHeap.top()) {
                minHeap.push(maxHeap.top()); maxHeap.pop();
                maxHeap.push(num);
            }
            else {
                minHeap.push(num);
            }
        }
    }
    
    double getMedian() {
        /* maxHeap is always at least as big as minHeap. 
           so if maxHeap is empty, then minHeap is also. 
           If maxHeap and minHeap are of different sizes, then 
           maxHeap must have one extra element. Return its
           top element. */
        if (maxHeap.empty()) return 0;
        if (maxHeap.size() == minHeap.size())
            return ((double)minHeap.top() + (double)maxHeap.top()) / 2;
        else
            return maxHeap.top();
    }
    
    int countWordsInString1(std::string const& str) {
        /* Use stringstream and >> operator 
           words are separated by arbitrary number
           of spaces and/or tabs */
        std::stringstream  stream(str);
        std::string        oneWord;
        unsigned int  count = 0;

        while (stream >> oneWord) { ++count;}
        return count;
    }
    
    int countWordsInString2(std::string const& str) {
        /* Here we define one word as one segment of consecutive spaces/tabs 
         * in front of one segment of consecutive non-spaces/tabs */
        int len = str.length();
        int count = 0;

        for (int i = 0;;) {
            while (i < len && (str[i] == ' ' || str[i] == '\t')) 
                i++;    // skip spaces or tabs in front of each word
            if (i == len) 
                break;  // end of std::string          
            while (i < len && str[i] != ' ' && str[i] != '\t') 
                i++;    // skip non-spaces or non-tabes
            count++;    // find one word
        }
        return count;
    }

    std::vector<std::string> getAllTxts(std::string path = ".") {
        DIR*   dir;
        struct dirent* pdir;
        std::vector<std::string> files;

        dir = opendir(path.c_str());

        while (pdir = readdir(dir)) {
            int pos = strlen(pdir->d_name) - 4;
            if (pdir->d_type == DT_REG && !strcmp(&pdir->d_name[pos], ".txt"))  // check if it's a file or folder and the extension
                files.push_back(pdir->d_name);
        }

        return files;
    }
};

int main(void) {

    Median median;

    median.runningMedian();

    return 0;
}

