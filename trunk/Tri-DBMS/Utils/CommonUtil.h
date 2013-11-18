/*
 * CommonUtil.h
 *
 *  Created on: Nov 18, 2013
 *      Author: ravin
 */

#ifndef COMMONUTIL_H_
#define COMMONUTIL_H_
#include <vector>
#include <iostream>
#include <istream>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <sstream>
using namespace std;
class CommonUtil {
public:


	static vector<string> split(string str, string splitter) {

		vector<string> res;

		for (unsigned int i = 0; i < str.length();) {
			int pos = str.find(splitter, i);
			string split_str = str.substr(i, pos - i);
			if (split_str != "") {
				res.push_back(split_str);
			}
			//cout << "i,pos=" << i << "," << pos << endl;
			//cout << str.substr(i, pos - i) << endl;
			i = pos + splitter.length();
			if (pos < 0) {
				break;
			}
		}

		return res;
	}

	static int string_to_int(std::string var) {

		int res = 0;
		istringstream mystream(var);
		mystream >> res;

		return res;
	}

	static string int_to_string(int var) {
		ostringstream mystream;
		mystream << var;
		return mystream.str();
	}

	static string char_to_string(char *var) {
		string res(var);
		return res;
	}
};


#endif /* COMMONUTIL_H_ */
