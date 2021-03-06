#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <fstream>
using std::ifstream;

#include <numeric>
#include <cstring>
using std::string;

#include <vector>

const int MAX_CHARS_PER_LINE = 512;
const int MAX_TOKENS_PER_LINE = 20;
const char* const DELIMITER = " ";

int textParser(string inFile, std::ofstream& outFile){
	
  //prepare output
  
  // create a file-reading object
  ifstream fin;
  
  fin.open(inFile); // open a file
  if (!fin.good()) 
    return 1; // exit if file not found

  //create output buffer to hold inter-header contents when searching them
  std::vector<std::string> lineBuffer;

  //define relevant points of second domain
  double B[] = {27.6,-82.2};
  double A[] = {25.5,-80.8};
  double C[] = {27,-83.8};
  
  // read each line of the file
  while (!fin.eof()){
    // read an entire line into memory
    char buf[MAX_CHARS_PER_LINE];
    fin.getline(buf, MAX_CHARS_PER_LINE);
   
    // parse the line into blank-delimited tokens
    int n = 0; // a for-loop index
    //bool to track presence in domain
    bool inDomain = false;
    // array to store memory addresses of the tokens in buf
    const char* token[MAX_TOKENS_PER_LINE] = {}; // initialize to 0
    char start[] = "start";
    char header[MAX_CHARS_PER_LINE];
    //store header for output to file

    std::strcpy(header, buf);
    // parse the line
    token[0] = strtok(buf, DELIMITER); // first token

    if (token[0] != 0 && strcmp(start,token[0])==0) // zero if line is blank
    {
      //parse header line into tokens
      for (n = 1; n < MAX_TOKENS_PER_LINE; n++)
      {
        token[n] = strtok(0, DELIMITER); // subsequent tokens
       
        if (!token[n]) break; // no more tokens
      }
      int records = std::stoi(token[1]);
      //cout<< records << ",";

      for (int i = 0; i < records; i++){ // records = # of lines before next start header
        
        fin.getline(buf, MAX_CHARS_PER_LINE);
        //add line to buffer
        std::string Str(buf);
        lineBuffer.push_back(Str);

        token[0] = strtok(buf, DELIMITER);//first token
        for (n = 1; n < MAX_TOKENS_PER_LINE; n++)
        {
        token[n] = strtok(0, DELIMITER); // subsequent tokens
       
        if (!token[n]) break; // no more tokens
        }

        double lat = std::stod(token[1]);
        double lon = (360 - std::stod(token[0]));

        //check first domain


        //check combination of first and second domain, low resolution right now, working on a better solution to represent any rectangle
        if(lat < 27.5 && lat > 24.5 && lon > 79 && lon < 83.5)
        {
          //
          cout << header <<endl;
          inDomain = true;
        }

       

        
      }
      //pop lineBuffer out to output file
      if(inDomain){
        outFile << header << "\n";
        for(unsigned int i=0; i<lineBuffer.size(); i++)
        {
          
          outFile << lineBuffer[i] << "\n";
          
        }
        lineBuffer.clear();
        inDomain = false;
      } 
      lineBuffer.clear();
    }
  }
  
  cout<< "end of file " <<endl;

}

int main()
{
  std::ofstream file;
  file.open("domainStorms.rtf");
	for (int i = 0; i < 20; i++){
		//run the parser on all datafiles from the Sheng dataset.
		int year = 1981 + i;
		std::string titleYear = std::to_string(year);
		std::string inputFile = "traj_" + titleYear + ".txt";
    		textParser(inputFile, file);

	}
  file.close();
}
