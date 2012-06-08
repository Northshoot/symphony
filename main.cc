#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <list>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdexcept>
#include "symphony-xml.h"
#include "hardware-model.h"

using namespace std;

int main()
{
   string configFile="advance.xml"; // stat file. Get ambiguous segfault otherwise.

   try {
	   SymphonyXML sym;
	   sym.readConfigFile(configFile);

	   HardwareModel*  radioModel = sym.getRadioModel("radio");
	   //cout << "model name: " <<radioModel.getModelName() << endl;
	   cout<<"about to print"<<endl;
	   radioModel->printModel();
	   vector<string> str_v = sym.getTosFunctions();

} catch (...) {
	cerr << "Unknown exception encountered when creating Symphony" << endl;
}

   //


//   cout << "Application option A="  << sym.getOptionA()  << endl;
//   cout << "Application option B="  << sym.getOptionB()  << endl;
;


   return 0;
}
