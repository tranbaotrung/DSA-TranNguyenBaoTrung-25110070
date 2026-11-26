#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

struct Bid {
    string bidderId;
    double amount;
    long long timestamp;
    int auctionId;
};

void printBids(const vector<Bid>& v, size_t limit = 10) {
    for (size_t i = 0; i < min(v.size(), limit); ++i)
        cout << "[" << v[i].bidderId << "] $" << v[i].amount<< " @ " << v[i].timestamp << "\n";
    if (v.size() > limit) cout << "... (" << v.size() << " total)\n";
}

bool loadBids(const string& path, vector<Bid>& out) {
    ifstream f(path);
    if (!f) return false;
    Bid b;
    while (f >> b.bidderId >> b.amount >> b.timestamp >> b.auctionId)
        out.push_back(b);
    return true;
}

bool sosanhBids(const Bid& a, const Bid& b) {
    if (a.amount==b.amount) {
        return a.timestamp<b.timestamp;
    }
    return a.amount<b.amount;
}

void insertionSort(vector<Bid>& v) {
    for (int i=1; i<v.size(); ++i) {
        Bid k=v[i];
        int j=i-1;
        while (j>=0 && sosanhBids(k, v[j])) {
            v[j+1]=v[j];
            j=j-1;
        }
        v[j+1]=k;
    }
}

void selectionSort(vector<Bid>& v) {
    for (int i = 0; i<v.size(); ++i) {
        int max=i;
        for (int j=i+1; j<v.size(); ++j) {
            if (v[j].amount>v[max].amount) {
                max=j;
            }
        }
        swap(v[i],v[max]);
    }
    for (int i = 0; i<min(v.size(), (size_t)3); ++i) {
        cout << v[i].bidderId <<" "<< v[i].amount << "\n";
    }
}
void interchangeSort(vector<Bid>& v) {
    int Count=0;
    for (int i=0; i<v.size(); ++i) {
        for (int j=i+1; j<v.size(); ++j) {
            if (v[i].amount>v[j].amount) {
                swap(v[i],v[j]);
                Count++;
            }
        }
    }
    cout << "Swaps: " << Count << "\n";
}
bool bubbleSort(vector<Bid>& v) {
    bool stop = true;
    for (int i = 0; i < v.size(); ++i) {
        bool swapped = false;
        for (int j = 0; j < v.size() - i - 1; ++j) {
            if (v[j].amount > v[j + 1].amount) {
                swap(v[j], v[j + 1]);
                swapped = true;
                if (i == 0) stop = false;
            }
        }
        if (!swapped) break;
    }
    
    if (stop) {
        cout << "STABLE\n";
        return true;
    } else {
        cout << "UNSTABLE\n";
        return false;
    }
}

// Hàm sinh dữ liệu ngẫu nhiên (dùng LLM để làm hàm này ạ)
void generateLargeTestFile(const string& filename, int num_records) {
    ofstream out(filename);
    if (!out) {
        cout << "Loi: Khong the tao file " << filename << "\n";
        return;
    }
    mt19937 gen(12345);
    uniform_real_distribution<double> dis_amount(10.0, 5000.0);
    uniform_int_distribution<long long> dis_time(1600000000, 1700000000);
    uniform_int_distribution<int> dis_auction(1, 50);
    for (int i = 0; i < num_records; ++i) {
        out << "bidder_" << i << " " 
            << dis_amount(gen) << " " 
            << dis_time(gen) << " " 
            << dis_auction(gen) << "\n";
    }
    out.close();
    cout << ">> Da tao thanh cong file: " << filename << " voi " << num_records << " records!\n";
}

void quickSort(vector<Bid>& v, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    if (sosanhBids(v[mid], v[left])) swap(v[left], v[mid]);
    if (sosanhBids(v[right], v[left])) swap(v[left], v[right]);
    if (sosanhBids(v[right], v[mid])) swap(v[mid], v[right]);
    swap(v[mid], v[right]); 
    Bid pivot = v[right];
    int i = left;
    for (int j = left; j < right; j++) {
        if (sosanhBids(v[j], pivot)) {
            swap(v[i], v[j]);
            i++;
        }
    }
    swap(v[i], v[right]);
    quickSort(v, left, i - 1);
    quickSort(v, i + 1, right);
}

void quickSortWrapper(vector<Bid>& v) {
    if (v.empty()) return;
    auto start = chrono::high_resolution_clock::now();
    quickSort(v, 0, v.size() - 1);
    auto end = chrono::high_resolution_clock::now();
    auto time_taken = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Runtime: " << time_taken << " ms\n";
}

int main() {
    generateLargeTestFile("test_data/large.txt", 100000);
    vector<Bid> bids;
    string filepath = "test_data/large.txt";
    loadBids(filepath, bids);
    quickSortWrapper(bids);
    cout << "--- Ket qua sau khi sap xep ---\n";
    printBids(bids, 5);
    return 0;
}
