#include <cmath>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Algorithm {
private:
    std::string sourceString;
    //用于存储不重复的字符及其频率
    std::vector<std::pair<char, long double>> vec;

    std::string EncodeTextStr;

    long double EncodeTextDbl;

    std::string DecodeText;

public:
    Algorithm() {}

    Algorithm(std::string&& _str) : sourceString(std::move(_str)) {
        init();
    }

    void init();

    void Encode();

    void Decode();

    void calculateEfficiency();
};

void Algorithm::init() {
    std::cout.setf(std::ios::fixed); //规定了小数部分位数为三位
    std::cout.setf(std::ios::showpoint);
    std::cout.precision(3);

    int sumSize = this->sourceString.size();
    std::vector<std::pair<char, int>> temp_vec;
    temp_vec.emplace_back(this->sourceString[0], 1);

    for (int i = 1; i < this->sourceString.size(); ++i) {
        bool flag = false;
        for (int j = 0; j < temp_vec.size(); ++j) {
            if (temp_vec[j].first == this->sourceString[i]) {
                ++temp_vec[j].second;
                flag = true;
                break;
            } else
                continue;
        }
        if (!flag) temp_vec.emplace_back(this->sourceString[i], 1);
    }

    for (auto i : temp_vec)
        this->vec.emplace_back(i.first, static_cast<long double>(i.second) / sumSize);

    // for test
    // for (auto i : this->vec)
    //     std::cout << i.first << " " << i.second << std::endl;
}

void Algorithm::Encode() {
    long double High = 0.0, Low = 0.0;
    long double highTemp, lowTemp, range;

    //第一个字符的工作
    range = this->vec[0].second;
    High = Low + range;
    // for test
    // std::cout << "Low = " << Low << " High = " << High << std::endl;

    for (int i = 1; i < this->sourceString.size(); ++i) {
        for (int j = 0; j < this->vec.size(); ++j) {
            //寻找该字符在不重复vector中的位置
            if (this->vec[j].first == this->sourceString[i]) {
                if (j == 0) {
                    //和第一个字符一样
                    range *= this->vec[j].second;
                    //等比例缩放区间大小，取之
                    High = Low + this->vec[j].second * range;
                } else {
                    //和第一个字符不一样
                    long double needed_pro{};
                    for (int k = 0; k < j; ++k)
                        needed_pro += this->vec[k].second;
                    lowTemp = Low + range * needed_pro;
                    High = Low + range * (needed_pro + this->vec[j].second);
                    Low = lowTemp;
                    range *= this->vec[j].second;
                }
            }
        }
    }
    std::stringstream ss{};
    ss.precision(8);
    std::cout.precision(8);
    ss << Low;
    ss >> this->EncodeTextStr;
    EncodeTextDbl = Low;
    std::cout << "EncodingText = " << this->EncodeTextStr << std::endl;
}

void Algorithm::Decode() {
    //用于每个区间的下限
    std::vector<double> lowerBound{};
    lowerBound.resize(vec.size());
    lowerBound[0] = 0.0;
    for (int i = 1; i < this->vec.size() + 1; ++i) {
        lowerBound[i] = lowerBound[i - 1] + this->vec[i - 1].second;
    }
    long double temp = this->EncodeTextDbl;
    for (int j = 0; j < this->sourceString.size(); ++j) {
        for (int k = 0; k < this->vec.size(); ++k) {
            if (temp > lowerBound[k] && temp < lowerBound[k + 1]) {
                DecodeText += this->sourceString[j];
                //计算下一个被编码字符的下限
                temp = (temp - lowerBound[k]) / (lowerBound[k + 1] - lowerBound[k]);
                break;
            }
        }
    }
    std::cout << "DecodeText = " << this->DecodeText << std::endl;
}

void Algorithm::calculateEfficiency() {
    long double ps = 1, pEntropy = 0;
    for (auto i : vec) {
        ps *= pow(i.second, i.second * this->sourceString.size());
        pEntropy -= i.second * log2(i.second);
    }
    double l = ceil(-log2(ps)) / this->sourceString.size();
    std::cout << "the code efficiency = " << pEntropy / l << std::endl;
}

void unitTest() {
    Algorithm al{"122444488888888"};
    al.Encode();
    al.Decode();
    al.calculateEfficiency();
}

int main(void) {
    unitTest();

    return 0;
}