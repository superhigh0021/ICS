#include <bitset>
#include <cmath>
#include <cstring>
#include <iostream>
#include <unordered_map>
#include <vector>

#define M 5 //能表示出出现的字符的最小二进制位数
#define N 6 //能表示出出现最多次数的最小二进制位数

class RunLength {
private:
    std::string sourceString;                         //源字符串
    std::string encodeText;                           //编码后
    std::string decodeText;                           //译码后
    std::unordered_map<char, std::string> dict;       //各字符对应的二进制串
    std::unordered_map<std::string, char> decodeDict; //译码时需要的 二进制串对应的字符
    std::unordered_map<char, int> mp{};               //统计各字符出险次数

public:
    RunLength() {}

    RunLength(std::string&& _str)
        : sourceString(std::move(_str)) {
        computeRule();
    }

    void computeRule();

    void Encode();

    void Decode();
};

void RunLength::computeRule() {
    for (auto i : this->sourceString)
        ++this->mp[i];
    int size = mp.size();
    int index = 0;
    for (auto i : mp) {
        auto temp = std::bitset<M>(index++);
        dict[i.first] = temp.to_string();
    }
    for (auto i : dict)
        this->decodeDict[i.second] = i.first;

    // for test
    for (auto i : dict)
        std::cout << "i.first = " << i.first << "i.second = " << i.second << std::endl;
    //  for (auto i : decodeDict)
    //      std::cout << "i.first = " << i.first << "i.second = " << i.second << std::endl;
}

void RunLength::Encode() {
    for (int i = 0; i < this->sourceString.size();) {
        auto str = this->sourceString[i];

        this->encodeText += this->dict[str];
        auto temp = std::bitset<N>(this->mp[str]);
        this->encodeText += temp.to_string();
        i += this->mp[str];
    }
    std::cout << "the encodeText = " << this->encodeText << std::endl;
}

void RunLength::Decode() {
    for (int i = 0; i < this->encodeText.size();) {
        std::string str_to_char{};  //用于表示对应的字符
        std::string str_to_times{}; //用于表示对应字符出现的次数
        int j = i;
        for (; j < i + M; ++j)
            str_to_char += this->encodeText[j];
        for (; j < i + M + N; ++j)
            str_to_times += this->encodeText[j];

        char ch = this->decodeDict[str_to_char];
        int round = this->mp[ch];
        std::cout << "ch = " << ch << " times = " << round << std::endl;
        while (round-- > 0)
            this->decodeText += ch;

        i += M + N;
    }
    std::cout << "decodeText = " << this->decodeText << std::endl;
}

void unitTest() {
    RunLength rl("this");
    rl.Encode();
    rl.Decode();
}

int main() {
    unitTest();
}