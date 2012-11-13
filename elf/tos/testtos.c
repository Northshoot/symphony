#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <iostream>

#define NUM 35000
typedef int (*Fn)(int);

inline long getMilliSecs() {
	timeval t;
	gettimeofday(&t, NULL );
	return t.tv_sec * 1000 + t.tv_usec / 1000;
}

using namespace std;


int main(int argc, char *argv[]) {

	void *g1[NUM];
	void * tmp[NUM];
	long int i = 0;
	long int open = 0;
	int libs = atoi(argv[1]);
	printf("enter main, starting to open %d libraries\n", libs);
	long start_libs = getMilliSecs();
	for (; i < libs; i++) {
		g1[i] = dlmopen(LD_BIND_NOW, "libtostest.so", RTLD_LAZY);
		if (!g1[i]) {
			printf("Cannot open library %ld: %s\n", i, dlerror());
		}
	}


long time_libs = getMilliSecs() - start_libs;

start_libs = getMilliSecs();
char *error = NULL;
for (i=0; i < libs; i++) {
	tmp[i] = dlsym(g1[i], "tickFired");
	if( (error = dlerror()) != NULL) {
		printf("ERROR getting function: %s\n", dlerror());

	}
}
long time_func = getMilliSecs() - start_libs;

start_libs = getMilliSecs();
for(i=0;i<libs;i++) {
	((Fn)tmp[i])(i);
}
long time_exec = getMilliSecs() - start_libs;



//sleep(30);
start_libs = getMilliSecs();
for(i=0;i<libs;i++) {
	dlclose (g1[i]);

}
long time_close = getMilliSecs() - start_libs;

cout<<"Libs: "<< libs <<"\topen time: "<<time_libs<<"\t get func: "<< timefunc<<"\tclose time: "<< time_close<<endl;

return 0;
}
