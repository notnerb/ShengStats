#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;

#include <cstring>

#include <vector>

const int MAX_CHARS_PER_LINE = 512;
const int MAX_TOKENS_PER_LINE = 20;
const char* const DELIMITER = " ";

int main()
{
  //prepare output
  std::ofstream file;
  file.open("storms.rtf");
  // create a file-reading object
  ifstream fin;
  fin.open("traj_1981.txt"); // open a file
  if (!fin.good()) 
    return 1; // exit if file not found

  //create output buffer to hold inter-header contents when searching them
  std::vector<std::string> lineBuffer;
  
  // read each line of the file
  while (!fin.eof()){
    // read an entire line into memory
    char buf[MAX_CHARS_PER_LINE];
    fin.getline(buf, MAX_CHARS_PER_LINE);
   
    // parse the line into blank-delimited tokens
    int n = 0; // a for-loop index
    bool inDomain;
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
        double lon = 360 - std::stod(token[0]);

        
        if(lat > 25 && lat < 27 && lon > 79 && lon < 81) 
        {
          //
          cout << header <<endl;
          inDomain = true;
        }
       

        
      }
      //pop lineBuffer out to output file
      if(inDomain){
        file << header << "\n";
        for(unsigned int i=0; i<lineBuffer.size(); i++)
        {
          
          file << lineBuffer[i] << "\n";
          
        }
        lineBuffer.clear();
        inDomain = false;
      } 
      lineBuffer.clear();
    }
  }
  file.close();

    // process (print) the tokens
    
  
}