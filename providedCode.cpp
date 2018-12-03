// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, FALL 2018

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
    cin >> filename;
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

void insertionSortArr(list<Data *> &l);

void countSortInt(list<Data *> &l);

void countSortInt2(list<Data *> &l);


void countSort(list<Data *> &l);

void hybridRadixSort(list<Data *> &l);

void hybridRadixSort2(list<Data *> &l);

void sortDataList(list<Data *> &l, int field) {
    switch (field) {
        case 1:
            //l.sort();
            insertionSortArr(l);
            //timSort(l);
            //lsbRadixInt1(l);
            break;
        case 2:
            //lsbRadixInt(l);
            countSortInt(l);
            //countSortInt2(l);
            break;
        case 3:
            countSort(l);
            break;
        case 4:
            hybridRadixSort2(l);
            break;
        default:
            break;
    }
}


#include <cstring>

void pprint(list<Data *> &l, list<Data *>::iterator stop) {
    for (auto it = l.begin(); it != stop; it++) {
        cout << (*it)->val1 << " ";
    }
    cout << endl;
}

inline bool cmp(unsigned int target, Data *tmp1) {
    return tmp1->val1 > target;
}

inline bool cmpData(Data *tmp1, Data *tmp2) {
    return tmp1->val2 < tmp2->val2;
}

inline bool cmpData1(Data *tmp1, Data *tmp2) {
    return tmp1->val1 < tmp2->val1;
}

inline bool cmpData4(string tmp, Data *tmp2) {
    return tmp < tmp2->val4;
}

//const int RUN = 32;
const unsigned int radix = 65535;
//vector<Data *> ll(1000001);
Data *lll[1048576];
//vector<Data *> bucket(1000001);
//Data *bucket[1000100];
//vector<int> countRadix(radix, 0);
//vector<vector<Data *>> countBucket(94, vector<Data *>(1000001));
Data *countBucket[128][32768];
Data *countBucket1[65536][64];
Data *countBucket2[2097153][32];
int countRadix[65536] = {0};
int countRadix1[2097153] = {0};
int countArr[128] = {0};
//vector<int> countRadixString(127, 0);
// not completed
//void insertionSortList(list<Data *> &l) {
//    for (auto it = next(l.begin()); it != l.end(); it++) {
//        auto t = prev(it);
//        bool changed = false;
//
//        while ((t != l.begin() && (*t)->val1 > (*it)->val1)) {
//            t--;
//        }
//        cout << (*t)->val1 << " " << (*it)->val1 << endl;
//        if (t == l.begin() && (*t)->val1 > (*it)->val1) {
//            l.begin()._M_node->_M_hook(it._M_node);
//            it._M_node->_M_unhook();
//            changed = true;
//            it = l.begin();
//        } else if (t == prev(it) && (*t)->val1 > (*it)->val1){
//            t._M_node->_M_hook(it._M_node);
//            it._M_node->_M_unhook();
//            changed = true;
//            it = t;
//        }
//
//        if (t != prev(it) && !changed){
//            next(t)._M_node->_M_hook(it._M_node);
//            it._M_node->_M_unhook();
//            it = next(t);
//        }
//        for (auto jt = l.begin(); jt != next(l.begin(), 10); jt++) {
//            cout << (*jt)->val1 << " ";
//        }
//        cout << endl;
//    }
//}

//void insertionSort(list<Data *> &l) {
//    auto a = l.begin();
//    auto b = l.end();
//    for (auto it = a; it != b; ++it) {
//        rotate(upper_bound(a, it, (*it)->val1, cmp), it, next(it));
//    }
//}

// stl vector
//void insertionSortVec(list<Data *> &l) {
//    int size = l.size();
//    auto it = l.begin();
//    for (int i = 0; i < size; i++) { ll[i] = (*it++); }
//
//    for (int i = 1; i < size; i++) {
//        auto tmp = ll[i];
//        int j = i - 1;
//        while (j >= 0 && ll[j]->val1 > tmp->val1) {
//            ll[j + 1] = ll[j];
//            j--;
//        }
//        ll[j + 1] = tmp;
//    }
//
//    it = l.begin();
//    for (auto jt = ll.begin(); jt != ll.begin() + size; ++jt) { (*it++) = *jt; }
//}

// array
void insertionSortArr(list<Data *> &l) {
    int size = l.size();
    lll[0] = *l.begin();

    auto it = next(l.begin());
    for (int i = 1; i < size; ++i) {
        lll[i] = (*it++);
        auto tmp = lll[i];
        int j = i - 1;
        while (j >= 0 && lll[j]->val1 > tmp->val1) {
            lll[j + 1] = lll[j];
            --j;
        }
        lll[j + 1] = tmp;
    }

    it = l.begin();
    for (int i = 0; i < size; i++) (*it++) = lll[i];
}

//void insertionSort(vector<Data *> &vec, int left, int right) {
//    for (auto jt = vec.begin() + left; jt != vec.begin() + right + 1; ++jt) {
//        rotate(upper_bound(vec.begin() + left, jt, (*jt)->val1, cmp), jt, next(jt));
//    }
//}
//
//void merge(vector<Data *> &vec, int l, int m, int r) {
//    int len1 = m - l + 1;
//    int len2 = r - m;
//    vector<Data *> left(vec.begin() + l, vec.begin() + m + 1);
//    vector<Data *> right(vec.begin() + m + 1, vec.begin() + r + 1);
//
//    int i = 0;
//    int j = 0;
//    int k = l;
//
//    while (i < len1 && j < len2) {
//        if (left[i]->val1 <= right[j]->val1) {
//            vec[k] = left[i];
//            i++;
//        } else {
//            vec[k] = right[j];
//            j++;
//        }
//        k++;
//    }
//
//    while (i < len1) {
//        vec[k] = left[i];
//        k++;
//        i++;
//    }
//
//    while (j < len2) {
//        vec[k] = right[j];
//        k++;
//        j++;
//    }
//}
//
//
//void timSort(list<Data *> &l) {
//    int n = l.size();
//    auto it = l.begin();
//    for (int i = 0; i < l.size(); i++) ll[i] = (*it++);
//    for (int i = 0; i < n; i += RUN) insertionSort(ll, i, min((i + RUN - 1), (n - 1)));
//
//    for (int size = RUN; size < n; size = 2 * size) {
//        for (int left = 0; left < n; left += 2 * size) {
//            int mid = min(left + size - 1, n - 1);
//            int right = min((left + 2 * size - 1), (n - 1));
//            merge(ll, left, mid, right);
//        }
//    }
//    it = l.begin();
//    for (auto &i : ll) (*it++) = i;
//}

//void lsbRadixInt1(list<Data *> &l) {
//    auto it = l.begin();
//    const int size = l.size();
//    for (int i = 0; i < size; i++) ll[i] = (*it++);
//    long long maximum = (*max_element(ll.begin(), ll.begin() + size, cmpData1))->val1;
//    int digit = 0;
//    while ((maximum >> (digit << 4)) > 0) {
//        fill(countRadix.begin(), countRadix.end(), 0);
//        for (int i = 0; i < size; i++) {
//            countRadix[(ll[i]->val1 >> (digit << 4)) % radix]++;
//        }
//        for (int i = 1; i < radix; i++) {
//            countRadix[i] += countRadix[i - 1];
//        }
//        for (int i = size - 1; i >= 0; i--) {
//            bucket[--countRadix[(ll[i]->val1 >> (digit << 4)) % radix]] = ll[i];
//        }
//        for (int i = 0; i < size; i++) {
//            ll[i] = bucket[i];
//        }
//        digit++;
//    }
//    it = l.begin();
//    for (int i = 0; i < size; i++) (*it++) = ll[i];
//}

//void lsbRadixInt(list<Data *> &l) {
//    const int size = l.size();
//    auto it = l.begin();
//    for (int i = 0; i < size; i++) lll[i] = (*it++);
//
//    int digit = 0;
//    while (digit < 2) {
//        int tmp = digit << 4;
//        memset(countRadix, 0, sizeof(countRadix));
//        for (int i = 0; i < size; i++) {
//            countRadix[((lll[i]->val2 >> tmp) & radix)]++;
//        }
//        for (int i = 1; i < radix + 1; i++) {
//            countRadix[i] += countRadix[i - 1];
//        }
//        for (int i = size - 1; i >= 0; i--) {
//            bucket[--countRadix[((lll[i]->val2 >> tmp) & radix)]] = lll[i];
//        }
//        for (int i = 0; i < size; i++) {
//            lll[i] = bucket[i];
//        }
//        digit++;
//    }
//
//    it = l.begin();
//    for (int i = 0; i < size; i++) (*it++) = lll[i];
//}

void countSort(list<Data *> &l) {
    for (auto &d : l) {
        countBucket[d->val3][countArr[d->val3]++] = d;
    }
    auto it = l.begin();
    for (int j = 33; j < 127; j++) {
        for (int i = 0; i < countArr[j]; i++) {
            (*it++) = countBucket[j][i];
        }
    }
}

void hybridRadixSort(list<Data *> &l) {
    auto it = l.begin();
    const int size = l.size();
//    for (int i = 0; i < size; i++) lll[i] = *(it++);
    int digit = 2;
    while (digit >= 0) {
        memset(countArr, 0, sizeof(countArr));

        if (digit == 2) {
            for (int i = 0; i < size; i++) {
                auto d = (*it++);
                int tmp = d->val4[digit];
                countBucket[tmp][countArr[tmp]++] = d;
            }
        } else {
            for (int i = 0; i < size; i++) {
                auto d = lll[i];
                int tmp = d->val4[digit];
                countBucket[tmp][countArr[tmp]++] = d;
            }
        }

        int idx = 0;
        for (int j = 33; j < 127; j++) {
            for (int i = 0; i < countArr[j]; i++) {
                lll[idx++] = countBucket[j][i];
            }
        }
        digit--;
    }

    for (int i = 1; i < size; i++) {
        auto tmp = lll[i];
        int j = i - 1;
        while (j >= 0 && lll[j]->val4 > tmp->val4) {
            lll[j + 1] = lll[j];
            j--;
        }
        lll[j + 1] = tmp;
    }

    it = l.begin();
    for (int i = 0; i < size; i++) *(it++) = lll[i];
}

void countSortInt(list<Data *> &l) {
    const int size = l.size();
    auto it = l.begin();

    int digit = 0;
    while (digit < 2) {
        int tmp = digit << 4;
        memset(countRadix, 0, sizeof(countRadix));
        // count frequencies
        if (digit == 0) {
            for (int i = 0; i < size; i++) {
                auto d = (*it++);
                int t = (d->val2 >> (tmp)) & radix;
                countBucket1[t][countRadix[t]++] = d;
            }
        } else {
            for (int i = 0; i < size; i++) {
                int t = (lll[i]->val2 >> (tmp)) & radix;
                countBucket1[t][countRadix[t]++] = lll[i];
            }
        }
        int idx = 0;
        for (int j = 0; j < 65536; j++) {
            for (int i = 0; i < countRadix[j]; i++) {
                lll[idx++] = countBucket1[j][i];
            }
        }
        digit++;
    }

    it = l.begin();
    for (int i = 0; i < size; i++) (*it++) = lll[i];
}

void hybridRadixSort2(list<Data *> &l) {
    auto it = l.begin();
    const int size = l.size();

    for (int i = 0; i < size; i++) {
        auto d = (*it++);
        unsigned int tmp = (d->val4[0] << 14) + (d->val4[1] << 7) + ((d->val4[2]));
        countBucket2[tmp][countRadix1[tmp]++] = d;
    }

    int idx = 0;
    for (int j = 0; j < 2097152; j++) {
        for (int i = 0; i < countRadix1[j]; i++) {
            lll[idx++] = countBucket2[j][i];
        }
    }

    for (int i = 1; i < size; i++) {
        auto tmp = lll[i];
        int j = i - 1;
        while (j >= 0 && lll[j]->val4 > tmp->val4) {
            lll[j + 1] = lll[j];
            j--;
        }
        lll[j + 1] = tmp;
    }

    it = l.begin();
    for (int i = 0; i < size; i++) *(it++) = lll[i];
}

void countSortInt2(list<Data *> &l) {
    const int size = l.size();
    auto it = l.begin();

    for (int i = 0; i < size; i++) {
        auto d = (*it++);
        unsigned int t = d->val2 >> 11;
        countBucket2[t][countRadix1[t]++] = d;
    }

    int idx = 0;
    for (int j = 0; j < 2097153; j++) {
        for (int i = 0; i < countRadix1[j]; i++) {
            lll[idx++] = countBucket2[j][i];
        }
    }

    for (int i = 1; i < size; i++) {
        auto tmp = lll[i];
        int j = i - 1;
        while (j >= 0 && lll[j]->val2 > tmp->val2) {
            lll[j + 1] = lll[j];
            j--;
        }
        lll[j + 1] = tmp;
    }

    it = l.begin();
    for (int i = 0; i < size; i++) (*it++) = lll[i];
}