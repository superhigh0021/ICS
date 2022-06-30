#include <algorithm>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>

struct FanoNode {
    char ch;
    double pro; //出现频率
    std::string encode;

    FanoNode() {}

    FanoNode(const FanoNode& f1)
        : ch(f1.ch), encode(f1.encode), pro(f1.pro) {}

    FanoNode(char _ch, double _pro, std::string _str = "")
        : ch(_ch), encode(_str), pro(_pro) {}
};

class Fano {
private:
    std::string sourceString;
    std::vector<FanoNode> vec;
    std::unordered_map<char, std::pair<int, double>> mp; //统计各字符出现次数和频率
    std::unordered_map<char, std::string> dict;          //记录每个字符对应编码的字典
    std::string EncodeText;
    std::string DecodeText;
    double Effeciency;

public:
    Fano() {}

    Fano(std::string&& _str)
        : sourceString(std::move(_str)) {
        buildFano();
    }

    void buildFano();

    void group();

    void group(int lo, int hi);

    void showEncodeTable(); //各字符对应的编码

    void Encode(); //对输入字符串进行编码

    void Decode(); //对编码序列进行解码

    void calculateEfficiency(); //计算编码效率
};

void Fano::buildFano() {
    for (auto i : sourceString)
        ++mp[i].first;
    for (auto i = mp.begin(); i != mp.end(); ++i) {
        i->second.second = i->second.first / static_cast<double>(sourceString.size());
        this->vec.emplace_back(i->first, i->second.second);
    }

    auto sortFunc = [](const FanoNode& f1, const FanoNode& f2) { return f1.pro > f2.pro; };
    sort(this->vec.begin(), this->vec.end(), sortFunc);

    // for test
    //  for (auto i : vec) {
    //      std::cout << "ch = " << i.ch << " pro = " << i.pro << std::endl;
    //  }
    this->group();

    // for test
    // for (auto i = mp.begin(); i != mp.end(); ++i) {
    //     std::cout << "ch = " << i->first << " time = " << i->second.first
    //               << " pro = " << i->second.second << std::endl;
    // }
}

void Fano::group() {
    this->group(0, vec.size() - 1);
}

void Fano::group(int lo, int hi) {
    if (hi == lo) return;
    int pivot = 0;      //分界点
    double cmpFlag = 1; //因为任意频率都不可能大于1，所以初值设为1
    for (int i = lo; i <= hi; ++i) {
        //前半部分和后半部分的概率和
        double frontSum = 0, backSum = 0;
        for (int a = lo; a <= i; ++a)
            frontSum += this->vec[a].pro;
        for (int b = i + 1; b <= hi; ++b)
            backSum += this->vec[b].pro;
        if (abs(frontSum - backSum) < cmpFlag) {
            cmpFlag = abs(frontSum - backSum);
            pivot = i;
        }
    }
    //对两个部分分别进行追加编码
    for (int i = lo; i <= pivot; ++i)
        this->vec[i].encode += '0';
    for (int i = pivot + 1; i <= hi; ++i)
        this->vec[i].encode += '1';

    this->group(lo, pivot);
    this->group(pivot + 1, hi);

    // for test
    // for (auto i : this->vec) {
    //     std::cout << "i.ch = " << i.ch << "i.pro = " << i.pro
    //               << "i.encode = " << i.encode << std::endl;
    // }
}

void Fano::showEncodeTable() {
    for (auto i : this->vec) {
        this->dict[i.ch] = i.encode;
        std::cout << "i.ch = " << i.ch << " i.pro = " << i.pro
                  << " i.encode = " << i.encode << std::endl;
    }
}

void Fano::Encode() {
    for (auto i : sourceString)
        EncodeText += dict[i];
    std::cout << "the source string encode to:" << EncodeText << std::endl;
}

void Fano::Decode() {
    std::string tmp{};
    for (int i = 0; i < EncodeText.size(); ++i) {
        tmp += this->EncodeText[i];
        for (auto p : this->vec) {
            if (p.encode == tmp) {
                this->DecodeText += p.ch;
                tmp = "";
                break;
            }
        }
    }
    std::cout << "DecodeText = " << this->DecodeText << std::endl;
}

void Fano::calculateEfficiency() {
    double entropy, aver;
    for (auto i : this->vec) {
        entropy -= i.pro * log2(i.pro);
        aver += i.pro * i.encode.size();
    }
    this->Effeciency = entropy / aver;
    std::cout << "the code efficiency is:" << this->Effeciency << std::endl;
}

void unitTest() {
    Fano f("asfafagd");
    f.showEncodeTable();
    f.Encode();
    f.Decode();
    f.calculateEfficiency();
}

int main(void) {
    unitTest();

    return 0;
}