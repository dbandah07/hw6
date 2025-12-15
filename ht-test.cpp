#include "ht.h"
#include "hash.h"
#include <unordered_map>
#include <iostream>
#include <utility>
#include <string>
#include <sstream>
#include <functional>
using namespace std;
int main()
{
    DoubleHashProber<std::string, MyStringHash > dh;
    HashTable<
        std::string, 
        int, 
        DoubleHashProber<std::string, MyStringHash >, 
        std::hash<std::string>, 
        std::equal_to<std::string> > ht(0.7, dh);

    // This is just arbitrary code. Change it to test whatever you like about your 
    // hash table implementation.
    cout << "SANITY: TEST 1: Inserting 15 items..." << endl;
    for(size_t i = 0; i < 15; i++){
        std::stringstream ss;
        ss << "hi" << i;
        ht.insert({ss.str(), i});
    }
    cout << "SANITY: size after implementation " << ht.size() << endl;

    cout << "SANIT: finding hi5 and incrementing" << endl;
    if( ht.find("hi5") != nullptr ){
        cout << "Found hi1 with val: " << ht["hi5"] << endl;
        ht["hi5"] += 10;
        cout << "Incremented hi1's value to: " << ht["hi5"] << endl;
    }

    cout << "SANITY: searching for missing key" << endl;
    if( ht.find("doesnotexist") == nullptr ){
        cout << "CORRECTLY did NOT find: doesnotexist" << endl;
    }

    cout << "SANITY: before removal of hi7 and hi9" << endl;
    cout << "HT size: " << ht.size() << endl;
    ht.remove("hi7");
    ht.remove("hi9");
    cout << "SANITY: size after removal" << ht.size() << endl;

    cout << "HT size: " << ht.size() << endl;

    if( ht.find("hi9") != nullptr ){
        cout << "Found hi9" << endl;
    }
    else {
        cout << "CORRECTLY did not find hi9" << endl;
    }
    ht.insert({"hi7",17});
    cout << "size: " << ht.size() << endl;


    cout << "SANITY: reinserting hi7 w new value" << endl;
    ht.insert({"hi7", 777});
    cout << "hi7 value after reinserting: " << ht["hi7"] << endl;
    cout << "new size: " << ht.size() << endl;


    cout << "SANITY: stress test to trigger resize" << endl;
    for (size_t i = 100; i < 200; i++) {
      stringstream ss;
      ss << "key" << i;
      ht.insert({ss.str(), i});
    } 

    cout << "SANITY: size after stress insert: " << ht.size() << endl;
    cout << "SANITY: total probes performed: " << ht.totalProbes() << endl;

    cout << "Verifying keys after resize: " << endl;

    cout << "hi0 = " << ht["hi0"] << endl;

    cout << "hi0 = " << ht.at("hi0") << endl;

    if (ht.find("key150") == nullptr) {
      cout << "key150 is MISSING from the table" << endl;
    }
    else {
      cout << "key150 EXISTS, value = " << ht.at("key150") << endl;
    }

    // cout << "key500 = " << ht["key500"] << endl;
    cout << "hi7 = " << ht["hi7"] << endl;

    cout << "Final table: " << endl;
    ht.reportAll(cout); 

    return 0;
}
