/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>

#include "ns3/log.h"
#include "tos-loader.h"
namespace ns3 {
NS_LOG_COMPONENT_DEFINE("TosLoader");

TosLoader::TosLoader() {
	NS_LOG_FUNCTION(this);
}

TosLoader::~TosLoader() {
	NS_LOG_FUNCTION(this);
	dlclose (handler);
}

void *
TosLoader::getHandler(std::string libname) {

	handler = dlmopen(LM_ID_NEWLM, libname.c_str(), RTLD_LAZY);
	if (!handler) {
		std::cerr << handler << "Cannot open library: " << dlerror() << '\n';
		exit(1);
	}

	return handler;
}

void *
TosLoader::getFunction(const char * func_name) {
	char *error = NULL;
	void * tmp = dlsym(handler, func_name);
	if ((error = dlerror()) != NULL) {
		//        std::stringstream sstm;
		//        sstm << "Cannot get function: " << name << "\n" << error;
		//        NS_ASSERT_MSG(false, sstm.str());
		//this is not fail safe, better way for multiple models is neede
		//for now return default function which prints error is the function is not found
		std::string defFunc = "sim_function_not_found";
		std::stringstream sstm;
		sstm << "Function not found: " << func_name
				<< ". Using default TOS function.\n" << error;
		void * tmp = dlsym(handler, defFunc.c_str());
		NS_LOG_ERROR(sstm.str());
		return tmp;
	} else {
		return tmp;
	}
	return NULL;
}

}



