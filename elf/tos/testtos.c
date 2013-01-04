#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif


#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <iostream>

#define NUM 35000
typedef long int (*Fn)(int);


//CLOCK_REALTIME, a system-wide realtime clock.
//CLOCK_PROCESS_CPUTIME_ID, high-resolution timer provided by the CPU for each process.
//CLOCK_THREAD_CPUTIME_ID, high-resolution timer provided by the CPU for each of the threads.

#define CLOCK_TYPE CLOCK_REALTIME

inline long getMilliSecs() {
	timeval t;
	gettimeofday(&t, NULL );
	return t.tv_sec * 1000 + t.tv_usec / 1000;
}

timespec diff(timespec start, timespec end)
{
	timespec temp;
	if ((end.tv_nsec-start.tv_nsec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}


int main(int argc, char *argv[]) {

	timespec time1, time2;

	long int i = 0;
	long int open = 0;
	int libs = atoi(argv[1]);
	void *g1[libs];
	void * tmp[libs];
	clock_gettime(CLOCK_TYPE, &time1);
	for (; i < libs; i++) {
		g1[i] = dlmopen(LM_ID_NEWLM, "libtosblink.so", RTLD_LAZY);
		if (!g1[i]) {
			printf("Cannot open library %ld: %s\n", i, dlerror());
		} else {

			open++;
		}
	}
	clock_gettime(CLOCK_TYPE, &time2);
	timespec time_open = diff(time1,time2);


	clock_gettime(CLOCK_TYPE, &time1);
for (i=0; i < open; i++) {
	tmp[i] = dlsym(g1[i], "tickFired");
	if(!tmp[i]) {
		printf("ERROR getting function: %s\n", dlerror());

	}
}
clock_gettime(CLOCK_TYPE, &time2);
timespec time_func = diff(time1,time2);

clock_gettime(CLOCK_TYPE, &time1);
long int ret;
for(i=0;i<libs;i++) {
	ret=((Fn)tmp[i])(i);
	//if(!(ret == i))
		//printf("error in return value got %ld expect %ld\n",ret, i);
}
clock_gettime(CLOCK_TYPE, &time2);
timespec time_exec = diff(time1,time2);



clock_gettime(CLOCK_TYPE, &time1);
for(i=0;i<libs;i++) {
	dlclose (g1[i]);

}
clock_gettime(CLOCK_TYPE, &time2);
timespec time_close =  diff(time1,time2);
//
//std::cout<<"Libs: "<< libs <<"\topen time: "<<time_libs<<"\t get func: "<<
//			time_func<<"\texec_time: "<< time_exec<< "\tclose time: "<<time_close<<std::endl;


std::cout<<libs <<"\t"<<
			time_open.tv_sec<<"\t"<<time_open.tv_nsec<<"\t"<<
			time_func.tv_sec<<"\t"<< time_func.tv_nsec<<"\t"<<
			time_exec.tv_sec<< "\t"<<time_exec.tv_nsec<< "\t"<<
			time_close.tv_sec<<"\t"<<time_close.tv_nsec<<std::endl;
return 0;
}
