// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, SPRING 2018

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds four public fields
class Data {
public:
    unsigned int val1;
    unsigned int val2;
    char val3;
    string val4;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename) {

    ifstream input(filename.c_str());
    if (!input) {
        cerr << "Error: could not open " << filename << endl;
        exit(1);
    }

    // The first line indicates the size
    string line;
    getline(input, line);
    stringstream ss(line);
    int size;
    ss >> size;

    // Load the data
    for (int i = 0; i < size; i++) {
        getline(input, line);
        stringstream ss2(line);
        Data *pData = new Data();
        ss2 >> pData->val1 >> pData->val2 >> pData->val3 >> pData->val4;
        l.push_back(pData);
    }

    input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename) {

    ofstream output(filename.c_str());
    if (!output) {
        cerr << "Error: could not open " << filename << endl;
        exit(1);
    }

    // Write the size first
    int size = l.size();
    output << size << endl;

    // Write the data
    for (list<Data *>::const_iterator ipD = l.begin(); ipD != l.end(); ipD++) {
        output << (*ipD)->val1 << " "
               << (*ipD)->val2 << " "
               << (*ipD)->val3 << " "
               << (*ipD)->val4 << endl;
    }

    output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data *> &, int field);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
    string filename;
    cout << "Enter name of input file: ";
//    cin >> filename;
    filename = "./sample.txt";
    list<Data *> theList;
    loadDataList(theList, filename);

    cout << "Data loaded.  Executing sort..." << endl;

    int field = 0;
    cout << "Enter an integer from 1 - 4, representing field to sort: ";
    try {
        cin >> field;
        if (field < 1 || field > 4) {
            cerr << "Error: invalid field" << endl;
            exit(1);
        }
    }
    catch (...) {
        cerr << "Error: invalid field" << endl;
        exit(1);
    }

    clock_t t1 = clock();
    sortDataList(theList, field);
    clock_t t2 = clock();
    double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

    cout << "Sort finished. CPU time was " << timeDiff << " seconds." << endl;

    cout << "Enter name of output file: ";
    cin >> filename;
    writeDataList(theList, filename);

    return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.
void pprint(list<Data *> &l, list<Data *>::iterator stop) {
    for (auto it = l.begin(); it != stop; it++) {
        cout << (*it)->val1 << " ";
    }
    cout << endl;
}

void timSort(list<Data *> &l) {
}

//void insertionSort(list<Data *> &l) {
//    auto pList = l.begin();
//    auto head = l.end();
//    while (pList != l.end()) {
//        auto current = pList;
//        pList++;
//        pprint(l, pList);
//        if (head == l.end() || (*current)->val1 < (*head)->val1) {
//            current._M_node->_M_next = head._M_node;
//            head = current;
//        } else {
//            auto p = head;
//            auto pNext = p++;
//            while (p != l.end()) {
//                if (pNext == l.end() || (*current)->val1 < (*pNext)->val1) {
//                    current._M_node->_M_next = pNext._M_node;
//                    pNext._M_node = current._M_node;
//                    break;
//                }
//            }
//            p = ++p;
//        }
//    }
//}

//void insert(list<Data *> &l, list<Data *>::iterator &sorted, list<Data *>::iterator &current) {
//    if (sorted == l.end() || (*sorted)->val1 >= (*current)->val1) {
//        current._M_node->_M_next = sorted._M_node;
//        sorted = current;
//    } else {
//        auto it = sorted;
//        auto itNext = ++sorted;
//        sorted--;
//        while (itNext != l.end() && (*itNext)->val1 < (*current)->val1) {
//            it++;
//            itNext++;
//        }
//        current._M_node->_M_next = it._M_node->_M_next;
//        it._M_node->_M_next = current._M_node;
//    }
//}
//
//void insertionSort(list<Data *> &l) {
//    auto sorted = l.end();
//    auto current = l.begin();
//    while (current != l.end()) {
//        auto next = ++current;
//        current--;
//        insert(l, sorted, current);
//        current = next;
//    }
//    l.begin() = sorted;
//}

//
//void insertionSort(list<Data *> &l) {
//    auto a = l.begin();
//    auto b = l.end();
//    for (auto it = a; it != b; ++it) {
//        rotate(upper_bound(a, it, (*it)->val1, cmp), it, next(it));
//    }
//}

inline bool cmp(unsigned int target, Data *tmp1) {
    return tmp1->val1 > target;
}

void insertionSort(list<Data *> &l) {
    vector<Data *> ll;
    ll.reserve(l.size());
    auto it = l.begin();
    for (int i = 0; i < l.size(); i++) { ll[i] = (*it++); }

    for (auto jt = ll.begin(); jt != ll.end(); ++jt) {
        rotate(upper_bound(ll.begin(), jt, (*jt)->val1, cmp), jt, next(jt));
    }

    it = l.begin();
    for (auto &i : ll) { (*it++) = i; }
}

const int RUN = 32;

void insertionSort(vector<Data *> &vec, int left, int right) {
    for (auto jt = vec.begin() + left; jt != vec.begin() + right + 1; ++jt) {
        rotate(upper_bound(vec.begin() + left, jt, (*jt)->val1, cmp), jt, next(jt));
    }
}

void merge(vector<Data *> &vec, int l, int m, int r) {
    int len1 = m - l + 1;
    int len2 = r - m;
    vector<Data *> left(vec.begin() + l, vec.begin() + m + 1);
    vector<Data *> right(vec.begin() + m + 1, vec.begin() + r + 1);

    int i = 0;
    int j = 0;
    int k = l;

    while (i < len1 && j < len2) {
        if (left[i]->val1 <= right[j]->val1) {
            vec[k] = left[i];
            i++;
        } else {
            vec[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < len1) {
        vec[k] = left[i];
        k++;
        i++;
    }

    while (j < len2) {
        vec[k] = right[j];
        k++;
        j++;
    }
}

void timSort(list<Data *> &l, int n) {
    vector<Data *> ll;
    ll.resize(l.size());
    auto it = l.begin();
    for (int i = 0; i < l.size(); i++) ll[i] = (*it++);
    for (int i = 0; i < n; i += RUN) insertionSort(ll, i, min((i + RUN - 1), (n - 1)));

    for (int size = RUN; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = min(left + size - 1, n - 1);
            int right = min((left + 2 * size - 1), (n - 1));
            merge(ll, left, mid, right);
        }
    }
    it = l.begin();
    for (auto &i : ll) (*it++) = i;
}

inline bool cmpData(Data *tmp2,  Data *tmp1) {
    return tmp1->val1 > tmp2->val1;
}

void counting_sort(list<Data *> &l, int digit, int radix) {

}

void radix_sort(list<Data *> &l, int base) {
    int max = (*max(l.begin(), l.end()))->;
    int it = 0;
    while (pow(base, it) <= )
}

void sortDataList(list<Data *> &l, int field) {
    switch (field) {
        case 1:
            //l.sort();
            //insertionSort(l);
            timSort(l, l.size());
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        default:
            break;
    }
}

