#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
       
			 // Add your code here 
			unsigned long long wVal[5] = {0, 0, 0, 0, 0}; 
			wValue(k, wVal);
			
			unsigned long long h = 0; 
			for(int i = 0; i < 5; i++){
				h += wVal[i] * rValues[i]; 
			}
			return h; 
		}



		void wValue(const std::string k, unsigned long long (&wVal)[5]) const {

			std::string sub = k;
			int w = 4; 
			int start, end;
			while (sub.length() > 0) {
				
				end = sub.length();
				start = std::max(end - 6,0);

				std::string curr = sub.substr(start,end); // get the substring at the end
				sub = sub.substr(0, start); // set sub equal to shorter substring

				unsigned long long total = 0; 
				for (int i = 0; i < curr.length(); i++) {
					total *= 36;
					total += letterDigitToNumber(curr[i]);
    		}
				wVal[w] = total; 
				w--;
			}
		}
			

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
			letter = std::tolower(letter);

			if(letter >= 'a' && letter <= 'z'){
				return letter - 'a'; 
			}
			else{
				return 26 + (letter - '0'); 
			}
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
