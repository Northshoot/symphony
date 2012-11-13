#!/bin/bash
#original timer was published in
#http://www.linuxjournal.com/content/use-date-command-measure-elapsed-time
#by Mitch Frazier
function timer()
{
	if [[ $# -eq 0 ]]; then
		echo $(date '+%s')
	else
		local  stime=$1
		etime=$(date '+%s')
	        if [[ -z "$stime" ]]; then stime=$etime; fi
	        dt=$((etime - stime))
	        ds=$((dt % 60))
	        dm=$(((dt / 60) % 60))
		dh=$((dt / 3600))
		printf '%d:%02d:%02d' $dh $dm $ds
	fi
}
tmr=$(timer)
INSTALL_DIR="/home/ubuntu/dev/symphony"
#files to install 
APPS="gcc g++ python python-dev mercurial bzr gdb valgrind gsl-bin libgsl0-dev libgsl0ldbl flex bison libfl-dev tcpdum sqlite sqlite3 libsqlite3-dev libxml2 libxml2-dev libgtk2.0-0 libgtk2.0-dev vtun lxc uncrustify doxygen graphviz imagemagick texlive texlive-extra-utils texlive-latex-extra python-sphinx dia python-pygraphviz python-kiwi python-pygoocanvas libgoocanvas-dev libboost-signals-dev libboost-filesystem-dev openmpi-* tinyos-2.1.2"
# update repos
RETVAL=$(sudo apt-get update)
if [ $? -ne 0 ]; then
	echo "Unable to update, reason: $?"
	echo $RETVAL
	exit 1
else
	echo "Successfully updated app repostitory"
fi
#function to handle instaliation 
function make_install(){
	if [ $# == 0 ]; then
	        echo "must give at least one argument"
		exit 1
	fi
	for app in $*
	do
		#we do not care is packet is installed it is success
		RETVAL=$(sudo apt-get install -y $app 2>&1 >/dev/null)
		if [ $? -ne 0 ]; then
			echo "Failure: can't install $app reson: $?"
		        echo $RETVAL
		        echo "Skipping package $app" 
		else
			echo "Succesfully installed $app"
		fi

	done
}

#create directory
if [ ! -d "$INSTALL_DIR" ]; then
	echo "Creating $INSTALL_DIR"
	RET=$(mkdir -p $INSTALL_DIR 2>&1 >/dev/null)
	if [ $? -ne 0 ]; then
		echo "Can not create directory $INSTALL_DIR. Reason: $?"
		echo $RET
		exit 1
	else
		echo "Succesfully created directory $INSTALL_DIR"
	fi
fi
#check if port is open

#install apps
make_install $APPS

cd $INSTALL_DIR
echo "Cloning repo"
RET=$(svn co https://comnet.sm.ltu.se/svn/symphony/trunk/ .)
if [ $? -ne 0 ]; then
	echo "Could not checkout symphony. REASON: $?"
	echo $RET
	exit 1
else
	echo "Check out was successfull"
fi

cd "ns-3.14"
echo "Building standart ns3"
./waf configure --enable-tests
./waf build

printf 'Elapsed time: %s\n' $(timer $tmr) 
echo "Thank you! Enjoy NS3"
