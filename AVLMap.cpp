#include "AVLMap.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
using std::map;
using std::make_pair;
using std::cout;
using std::vector;
using std::random_shuffle;
using std::pair;
using std::string;

void testone() {
	AVLMap<int,int> test; 
	pair<int,int> fst = make_pair(1,1); 
	pair<int,int> snd = make_pair(2,2);
	pair<int,int> thrd = make_pair(3,3);
	pair<int,int> fr = make_pair(4,4);
	pair<int,int> fv = make_pair(5,5);
	pair<int,int> sx = make_pair(6,4);
	pair<int,int> svn = make_pair(7,4);
	test.insert(fst);
	test.insert(snd);
	auto x = test.insert(thrd);
	test.insert(fr);
//	test.printPreOrder(test.getroot());
	test.insert(sx);
	test.insert(svn);
//	test.insert(fst);
	test.insert(fv);
	
	if(test[1] != fst.second){
		cout << "Problem with insert or bracket operator\n";
	}
	/*
	cout << test.height(test.getroot()) << "\n"; 
	cout << test.height(test.getroot()->left) << "\n";
	cout << test.height(test.getroot()->right) << "\n";
	*/
	//test.printPreOrder(test.getroot());
	//cout << test[1] << "\n";
	//cout << test[2] << "\n";
	//cout << test[3] << "\n";
	//cout << test.count(1) << "\n";
	//cout << test.count(0) << "\n";
	//cout << "This should be a 1: " << (itrfrst.first == itrfrstfail.first);
	//cout << "\nThis should be a 0: " << (itrfrst.second == itrfrstfail.second);
	
	//cout << "\n"<< test.count(2) << "\n";
	/*
	for(auto x:test){
		cout << "\n" << "Ranged loop";
		cout << x.first << "\n";
	}
	*/
	test.erase(2);
	test.clear();
	test.insert(sx);
	test.insert(fst);
}

bool equalitytest(){
	int test_size = 1000;
	bool testbool = true;
	AVLMap<int,int> test;
	map<int,int> testmap;
	vector<int> RandomThing;
	for(int i = 0; i<test_size; ++i){
		RandomThing.push_back(i);
	}
    random_shuffle(RandomThing.begin(), RandomThing.end());

    for(int i=0;i<test_size;++i){
    	test.insert(make_pair(RandomThing[i],RandomThing[i]));
    	testmap.insert(make_pair(RandomThing[i],RandomThing[i]));
    }

    auto ths = test.begin()++++++++++++;
    auto thsafter = ths;
    thsafter++;
    auto ers = test.erase(ths);
    if(ers != thsafter){
    	testbool = false;
    }
	for(auto bgn = test.begin();bgn != test.end(); ++bgn){
		if((*bgn).second != testmap[(*bgn).first]){
			testbool = false;
		}
	}
	return testbool;
}


void stringtest() {
	AVLMap<int,string> test; 
	pair<int,string> fst;
	fst = make_pair(1,"words"); 
	pair<int,string> snd;
	snd = make_pair(2,"morewords");
	pair<int,string> thrd;
	thrd = make_pair(3,"things");
	auto itrfrst = test.insert(fst);
	auto itrfrstfail = test.insert(fst);
	cout << test[1] << "\n";
	test.insert(snd);
	cout << test[2] << "\n";
	test.insert(thrd);
	cout << test[3] << "\n";
	cout << test.count(1) << "\n";
	cout << test.count(0) << "\n";

	if(itrfrst.first != itrfrstfail.first) cout << "Insert broke on duplicate insertion \n";
	if(itrfrst.second == itrfrstfail.second) cout << "Insert broke on duplicate insertion (the boolean is incorrect)\n";
	auto tmpsz = test.size(); 
	test.erase(2);
	if(tmpsz-1 != test.size()){
		cout << "Erase size failed \n";
	}
	if(test.count(2) != 0){
		cout << "Erase did not remove node \n";
	}
	for(auto x:test){
		cout << "\n" << "Ranged loop  ";
		cout << x.first << ": " << x.second << "\n";
	}

}


bool runAVLTestsForwards(){
	int test_size = 200000;
    AVLMap<int, int> firstbst;
	map<int,int> firstmap;
	
	vector<int> randoms;

	for(int i = 0; i<test_size; ++i){
		randoms.push_back(i);
	}
	//cout << randoms[0] << "\n";
    random_shuffle(randoms.begin(), randoms.end());
	//cout << randoms[0] << "\n";

	auto t1a = std::chrono::high_resolution_clock::now();
	for(int i=0; i<test_size; ++i){
	    firstbst.insert(make_pair(randoms[i],randoms[i]));
		firstmap.insert(make_pair(randoms[i],randoms[i]));
	}
	auto t2a = std::chrono::high_resolution_clock::now();

   std::cout << "inserting " << test_size << " took "
           	  << std::chrono::duration_cast<std::chrono::milliseconds>(t2a-t1a).count()///1000
              << " milliseconds\n";

	random_shuffle(randoms.begin(), randoms.end()--);
	for(int i=0; i<test_size; ++i){
		if(firstbst[randoms[i]]!=firstmap[randoms[i]]){
			cout << "check with map failed\n";
			return false;
		}
	}	
	
	AVLMap<int, int> tsbtsrif(firstbst);
	
	const auto a = tsbtsrif;
	const auto b = firstbst;

	if(a != b){
		cout << "copy construct worked\n";
		return false;
	}

	firstbst[2000000];
	auto x = firstbst.find(2000000);
	auto y = firstbst.insert(make_pair(2000000,1));
	if(x == y.first && ((*x).second) != 1){
		cout << "SUCCESS!\n";
	}
	firstbst.clear();
	random_shuffle(randoms.begin(), randoms.end());
	//cout << randoms[0] << "\n";
	for(int i=0; i<test_size; ++i){
	    firstbst.insert(make_pair(randoms[i],randoms[i]));
		//firstmap.insert(make_pair(randoms[i],randoms[i]));
	}

	firstbst.clear();
	random_shuffle(randoms.begin(), randoms.end());
	//cout << randoms[0] << "\n";
	for(int i=0; i<test_size; ++i){
	    firstbst.insert(make_pair(randoms[i],randoms[i]));
		//firstmap.insert(make_pair(randoms[i],randoms[i]));
	}
	

	return true;	
}




bool runAVLTestsBackwards(){
	int test_size = 2000000;
    AVLMap<int, int> firstbst;
	map<int,int> firstmap;
	
	vector<int> randoms;

	for(int i = test_size; i>0; --i){
		randoms.push_back(i);
	}
	//cout << randoms[0] << "\n";
	//cout << randoms[0] << "\n";

	auto t1a = std::chrono::high_resolution_clock::now();
	for(int i=0; i<test_size; ++i){
	    firstbst.insert(make_pair(randoms[i],randoms[i]));
		firstmap.insert(make_pair(randoms[i],randoms[i]));
	}
	auto t2a = std::chrono::high_resolution_clock::now();

   std::cout << "inserting " << test_size << " took "
           	  << std::chrono::duration_cast<std::chrono::milliseconds>(t2a-t1a).count()///1000
              << " milliseconds\n";

	for(int i=0; i<test_size; ++i){
		if(firstbst[randoms[i]]!=firstmap[randoms[i]]){
			cout << "check with map failed\n";
			return false;
		}
	}	
	cout << firstbst.size() << "\n\n\n";
	for(int i=10; i<test_size/2; ++i){
	    firstbst.erase(i);
	}
	
	return true;	
}

void simpleTest(){
	AVLMap<int, int> st;
	st[1];
	st[2];
	st[3];
	if(st.size()!=3){
		cout << "Problem with bracket and size\n ";
	}
	//st.printPreOrder(st.getroot());
}


int main(){
	testone();
	cout << "\n---------Testone passed---------\n";
	cout << "\n";
	simpleTest();
	auto t1 = std::chrono::high_resolution_clock::now();
    runAVLTestsForwards();
	auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Forwards test function took "
           	  << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count()///1000
              << " milliseconds\n";

	cout << "\n---------RunTests Forwards passed---------\n";
	if(equalitytest()) {cout << "\n---------Equality Test Passed---------\n";}
	else cout << "\n---------Equality Test Failed---------\n";
	stringtest();
	cout << "\n---------StringTests ran---------\n";


	cout << "\n---------RunTests Backwards passed---------\n";
	t1 = std::chrono::high_resolution_clock::now();
    runAVLTestsBackwards();
	t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Backwards test function took "
           	  << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count()///1000
              << " milliseconds\n";

	cout << "\n---------RunTests passed---------\n";
	

	return 0; 	

	cout << "\n";
/*	
*/
}


