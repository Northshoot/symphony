#include <memory>
#include "ns3/tos-module.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"

using namespace ns3;
using namespace std;

typedef struct {
	int a;
	int b;
	int c;
}Foo;

void withoutheader(){
	Foo * buf;
	buf = (Foo*) malloc(sizeof(Foo));
	buf->a=1;
	buf->b=2;
	buf->c=3;
	cout << "before inserting"<<endl;
	cout << "a: " << buf->a << "b: " << buf->b << "c: " << buf->c << endl;

	Ptr<Packet> pkt = Create <Packet> (Packet(reinterpret_cast< uint8_t*>(buf),
			sizeof(Foo)));

	Foo * buf1;
	buf1 = (Foo*) malloc(sizeof(Foo));
	pkt->CopyData(reinterpret_cast< uint8_t*>(buf1), sizeof(Foo));
	cout << "After insert inserting"<<endl;
	cout << "a: " << buf1->a << "b: " << buf1->b << "c: " << buf1->c << endl;

	Ptr<Packet> pkt1 = pkt->Copy();
	Foo * buf2;
	buf2 = (Foo*) malloc(sizeof(Foo));
	buf2 = buf1;
	cout << "reasign buffers"<<endl;
		cout << " a: " << buf2->a << " b: " << buf2->b << " c: " << buf2->c << endl;
	pkt1->CopyData(reinterpret_cast< uint8_t*>(buf2), sizeof(Foo));
	cout << "After copy"<<endl;
	cout << "a: " << buf2->a << " b: " << buf2->b << " c: " << buf2->c << endl;

	Ptr<Packet> pkt2 = pkt1->Copy();
	Foo * buf3;
	buf3 = (Foo*) malloc(sizeof(Foo));
	pkt2->CopyData(reinterpret_cast< uint8_t*>(buf3), sizeof(Foo));
	cout << "After copy"<<endl;
	cout << "a: " << buf3->a << " b: " << buf3->b << " c: " << buf3->c << endl;
}

void withHeader(){
	WifiMacHeader hdr;
	hdr.SetTypeData();
	hdr.SetAddr1(Mac48Address::GetBroadcast());
	hdr.SetAddr2 (Mac48Address::GetBroadcast());
	hdr.SetDsNotFrom();
	hdr.SetDsNotTo();

	Foo * buf;
	buf = (Foo*) malloc(sizeof(Foo));
	buf->a=1;
	buf->b=2;
	buf->c=3;
	cout << "before inserting"<<endl;
	cout << "a: " << buf->a << "b: " << buf->b << "c: " << buf->c << endl;

	Ptr<Packet> pkt = Create <Packet> (Packet(reinterpret_cast< uint8_t*>(buf),
			sizeof(Foo)));
	//XXX: here get data destroyed
	pkt->AddHeader(hdr);
	cout<<"Header added, where is data?"<<endl;
	Foo * buf1;
	buf1 = (Foo*) malloc(sizeof(Foo)+sizeof(WifiMacHeader));
	pkt->CopyData(reinterpret_cast< uint8_t*>(buf1), sizeof(Foo)+sizeof(WifiMacHeader));
	cout << "After insert inserting"<<endl;
	cout << "a: " << buf1->a << "b: " << buf1->b << "c: " << buf1->c << endl;

	Ptr<Packet> pkt1 = pkt->Copy();
	Foo * buf2;
	buf2 = (Foo*) malloc(sizeof(Foo));
	buf2 = buf1;
	cout << "reasign buffers"<<endl;
		cout << " a: " << buf2->a << " b: " << buf2->b << " c: " << buf2->c << endl;
		pkt1->RemoveHeader(hdr);
	pkt1->CopyData(reinterpret_cast< uint8_t*>(buf2), sizeof(Foo));
	cout << "After copy"<<endl;
	cout << "a: " << buf2->a << " b: " << buf2->b << " c: " << buf2->c << endl;

	Ptr<Packet> pkt2 = pkt1->Copy();
	Foo * buf3;
	buf3 = (Foo*) malloc(sizeof(Foo));
	pkt2->CopyData(reinterpret_cast< uint8_t*>(buf3), sizeof(Foo));
	cout << "After copy"<<endl;
	cout << "a: " << buf3->a << " b: " << buf3->b << " c: " << buf3->c << endl;
}

int main(void)
{
//	withoutheader();
//	cout << "\n\nNow lets repeat with header...\\"<<endl;
//	withHeader();

	return 0;
}
