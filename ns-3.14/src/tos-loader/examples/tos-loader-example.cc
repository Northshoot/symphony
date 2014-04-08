/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include <stdio.h>
#include <stdlib.h>
#include "ns3/core-module.h"
#include "ns3/tos-loader.h"
#include <vector>
#define NUM 20
typedef int (*Fn)(int);

using namespace ns3;


int 
main (int argc, char *argv[])
{
//  bool verbose = true;
//
//  CommandLine cmd;
//  cmd.AddValue ("verbose", "Tell application to log if true", verbose);
//
//  cmd.Parse (argc,argv);

  void *g1[NUM];
  void * tmp[NUM];
  std::vector<TosLoader *> m_loaders;
  long int i=0;
  long int open=0;
  int libs = NUM;//atoi(argv[1]);
  printf ("enter main, starting to open %d libraries\n", libs);
  clock_t start = clock();
  for(;i<libs;i++){
	  m_loaders.push_back(new TosLoader());
    g1[i] = m_loaders[i]->getHandler("libtos.so");
    std::cout<<"Openend "<<i<<std::endl;
    if(!g1[i]){
      printf ("Cannot open library \n");
    } else {

      tmp[i]= m_loaders[i]->getFunction("tickFired");
      if(tmp[i])
         printf("got function: %lu %lu\n",i, (long int)tmp[i]);
      else
    	  printf("can't open function\n");
      open++;

    }
  }

printf("Opened %ld libraries, time : %f\n", open, ( (double)clock() - start ) / CLOCKS_PER_SEC );

  start = clock();
  for(i=0;i<libs;i++){
         ((Fn)tmp[i])(i);
  }

printf("Time to execute one function in %ld libraries : %f\n",  open,( (double)clock() - start ) / CLOCKS_PER_SEC );

  //sleep(30);
//start = clock();
//  for(i=0;i<libs;i++){
//  dlclose (g1[i]);
//
//  }
printf("Time to close  %ld libraries : %f\n", open,  ( (double)clock() - start ) / CLOCKS_PER_SEC );

  printf ("dlclose libtos.so completed\n");
  printf ("leave main\n");
  /* ... */

  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}

