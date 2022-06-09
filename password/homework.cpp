#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

void exgcd(int a, int b, int& d, int& x, int& y) {
    if (!b) {
        d = a;
        x = 1;
        y = 0;
    } else {
        exgcd(b, a % b, d, y, x);
        y -= x * (a / b);
    }
}
//求逆元
int inv(int a, int p) {
    int d, x, y;
    exgcd(a, p, d, x, y);
    return d == 1 ? (x + p) % p : -1;
}

//求逆矩阵
void nijuzhen(vector<int>& vec) {
    int temp = vec[0] * vec[3] - vec[1] * vec[2];
    int ans = inv(temp, 26);
    temp = vec[0];
    vec[0] = vec[3] * ans;
    vec[1] = (-vec[1]) * ans;
    vec[2] = (-vec[2]) * ans;
    vec[3] = temp * ans;
    for (auto& i : vec)
        while (i < 0)
            i += 26;
}

//求密钥
void getKey(const string& s1, const string& s2) {
    unordered_map<char, int> wordToInt;
    for (int i = 0; i < 26; ++i)
        wordToInt['A' + i] = i;
    vector<int> ans;

    vector<int> m{wordToInt['T'], wordToInt['S'], wordToInt['H'], wordToInt['T']};
    vector<int> c{wordToInt[s1[0]], wordToInt[s2[0]], wordToInt[s1[1]], wordToInt[s2[1]]};
    for (auto i : m)
        cout << i << ' ';
    cout << endl;
    for (auto i : c)
        cout << i << ' ';
    cout << endl
         << endl;

    nijuzhen(m);
    vector<int> temp{c};
    c[0] = (temp[0] * m[0] + temp[1] * m[2]) % 26;
    c[1] = (temp[0] * m[1] + temp[1] * m[3]) % 26;
    c[2] = (temp[2] * m[0] * temp[3] * m[2]) % 26;
    c[3] = (temp[2] * m[1] + temp[3] * m[3]) % 26;

    cout << "Key is:" << endl
         << "       " << c[0] << ' ' << c[1] << endl
         << "       " << c[2] << ' ' << c[3] << endl;
}

int main(void) {
    string str = "LMQETXYEAGTXCTUIEWNCTXLZEWAISPZYVAPEWLMGQWYAXFTCJMSQCADAGTXLMDXNXSNPJQSYVAPRIQSMHNOCVAXFV";
    unordered_map<string, int> mp;
    int maxFrequencyCnt = 0;
    string maxFrequencyStr;
    for (int i = 0; i < str.size(); i += 2) {
        string SubStr = str.substr(i, 2);
        ++mp[SubStr];
        if (mp[SubStr] > maxFrequencyCnt)
            maxFrequencyCnt = mp[SubStr], maxFrequencyStr = SubStr;
    }
    vector<pair<string, int>> vec;
    for (auto i : mp)
        vec.push_back(i);
    sort(vec.begin(), vec.end(), [](const pair<string, int>& p1, const pair<string, int>& p2) { return p1.second > p2.second; });

    cout << vec[0].first << " occurs " << vec[0].second << " times." << endl;
    cout << vec[1].first << " occurs " << vec[1].second << " times." << endl;
    cout << endl;

    getKey(vec[0].first, vec[1].first);

    return 0;
}