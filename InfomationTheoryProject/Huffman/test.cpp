#include <algorithm>
#include <cstring>
#include <iostream>
#include <math.h>
#include <unordered_map>
#include <vector>

struct HuffNode {

    HuffNode()
        : leftChild(-1), rightChild(-1) {
    }

    HuffNode(const HuffNode& node)
        : ch(node.ch), weight(node.weight), parent(node.parent), leftChild(node.leftChild), rightChild(node.rightChild) {
    }

    HuffNode(char _ch, int _weight, int _parent, int _leftChild, int _rightChild)
        : ch(_ch), weight(_weight), parent(_parent), leftChild(_leftChild), rightChild(_rightChild) {}

    char ch; //表示的字符
    int weight;
    int parent;
    int leftChild;
    int rightChild;
};

class HuffmanTree {
private:
    int Huff_ori_size;
    std::vector<HuffNode> Huff;
    std::string sourceString;
    std::string HuffCodeResult; //编码结果
    std::unordered_map<char, std::string> encodeTable;
    std::unordered_map<char, int> mp; //统计各字符出现次数
    std::string decodeText;

public:
    HuffmanTree(){};

    HuffmanTree(std::string&& _str)
        : sourceString(std::move(_str)), Huff{} {
        buildHuffTree();
    }

    void buildHuffTree();

    std::pair<int, int> Select(); //选择两个最小的节点

    void Encode(); //编码

    std::string getEncodeText() { return HuffCodeResult; }

    void makeEncodeTable(); //构建编码表

    void Decode(); //解码

    double calculateEfficiency(); //计算编码效率

    ~HuffmanTree();
};

void HuffmanTree::buildHuffTree() {
    for (auto& i : sourceString)
        ++mp[i];

    // for test
    // for (auto i = mp.begin(); i != mp.end(); ++i)
    //     std::cout << i->first << ' ' << i->second << std::endl;
    for (auto i = mp.begin(); i != mp.end(); ++i) {
        Huff.emplace_back(i->first, i->second, -1, -1, -1);
        // std::cout << "Huff.back().leftChild = " << Huff.back().leftChild << std::endl;
        // std::cout << "Huff.back().rightChild = " << Huff.back().rightChild << std::endl;
    }

    //按照从大到小的排序，这样构建树的时候只需要 pop_back 即可
    // auto sortFunc = [](const HuffNode& v1, const HuffNode& v2) { return v1.weight > v2.weight; };
    // sort(Huff.begin(), Huff.end(), sortFunc);

    // for test
    //  for(auto i : Huff)
    //      std::cout<<i.ch<<' '<<i.weight<<std::endl;
    this->Huff_ori_size = Huff.size();
    while (Huff.size() < 2 * Huff_ori_size - 1) {
        std::pair<int, int> two_index = Select();
        int left = two_index.first, right = two_index.second;
        // std::cout << left << ' ' << right<<std::endl;
        Huff.emplace_back('\0', Huff[left].weight + Huff[right].weight, -1, left, right);
        // std::cout << "Huff back().leftChild = " << Huff.back().leftChild << " ";
        // std::cout << "Huff back().rightChild = " << Huff.back().rightChild << " ";
        // std::cout << std::endl;

        Huff[left].parent = Huff.size() - 1;
        Huff[right].parent = Huff.size() - 1;
    }

    // for test
    for (auto i : Huff) {
        std::cout << "i.ch = " << i.ch << " i.weight = " << i.weight << " i.parent = "
                  << i.parent << " i.leftChild = " << i.leftChild << " i.rightChild = " << i.rightChild << std::endl;
    }
}

//寻找最小的两个节点(前提：parent 为 0)
std::pair<int, int> HuffmanTree::Select() {
    //可优化为动态规划
    int min1 = INT_MAX, min2 = INT_MAX;
    int min_index1 = 0, min_index2 = 0;
    int i = 0;
    auto vec{this->Huff};

    for (i = 0; i < vec.size(); ++i) {
        if (vec[i].parent == -1 && vec[i].weight < min1) {
            min1 = vec[i].weight;
            min_index1 = i;
        }
    }

    vec[min_index1].weight = INT_MAX;
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i].parent == -1 && vec[i].weight < min2) {
            min2 = vec[i].weight;
            min_index2 = i;
        }
    }

    // for test
    // std::cout << min_index1 << ' ' << min_index2 << std::endl;

    return min1 < min2 ? std::make_pair(min_index1, min_index2) : std::make_pair(min_index2, min_index1);
}

//编码
void HuffmanTree::Encode() {
    makeEncodeTable();
    for (auto i : sourceString)
        this->HuffCodeResult += this->encodeTable[i];
    std::cout << this->HuffCodeResult << std::endl;
}

//构建编码表
void HuffmanTree::makeEncodeTable() {
    int n = this->Huff_ori_size;
    for (int i = 0; i < n; ++i) {
        int curChild = i, curParent = this->Huff[i].parent;
        while (curParent != -1) {
            // for test : print curChild & curParent
            // std::cout << "curChild = " << curChild << " curParent = " << curParent << std::endl;
            //没有到根节点
            if (curChild == this->Huff[curParent].leftChild) { //如果是左孩子
                encodeTable[Huff[i].ch] += '0';
                // std::cout << encodeTable[Huff[i].ch] << std::endl;
            } else {
                encodeTable[Huff[i].ch] += '1';
                // std::cout << encodeTable[Huff[i].ch] << std::endl;
            }
            curChild = curParent;
            curParent = this->Huff[curChild].parent;
        }
    }

    std::cout << "The Encoding Tble is :" << std::endl;
    for (auto i = encodeTable.begin(); i != encodeTable.end(); ++i) {
        i->second = std::string{i->second.rbegin(), i->second.rend()};
        // for test: print the encode table
        std::cout << i->first << " : " << i->second << std::endl;
    }
}

void HuffmanTree::Decode() {
    // for test
    //  for (auto i : Huff)
    //      std::cout << "i.leftChild = " << i.leftChild << " i.rightChild = " << i.rightChild << std::endl;
    int encodeTextSize = this->HuffCodeResult.size();
    for (int i = 0; i < encodeTextSize; ++i) {
        int curParent = this->Huff.size() - 1; //根节点下标

        int j = 0;
        while (Huff[curParent].leftChild != -1 && Huff[curParent].rightChild != -1) {
            std::cout << "curParent = " << curParent << "leftChild = " << Huff[curParent].leftChild
                      << "rightChild = " << Huff[curParent].rightChild << std::endl;

            if (HuffCodeResult[i + j] == '0') {
                std::cout << "left" << std::endl;

                curParent = Huff[curParent].leftChild;
            } else {
                std::cout << "right is " << std::endl;

                curParent = Huff[curParent].rightChild;
            }
            ++j;
        }
        i += j - 1;
        this->decodeText += this->Huff[curParent].ch;
    }
    std::cout << this->decodeText << std::endl;
}

//计算编码效率
double HuffmanTree::calculateEfficiency() {
    int entropy{};
    int size = this->sourceString.size();
    double sum1, sum2;
    std::unordered_map<char, double> probability{};
    //计算熵
    for (auto i = this->mp.begin(); i != mp.end(); ++i) {
        double prob = i->second / static_cast<double>(size);
        // std::cout << prob << std::endl;
        sum1 -= prob * log2(prob);
        probability[i->first] = prob;
        // std::cout << "sum1 = " << prob * log2(prob) << ' ';
    }
    std::cout << std::endl;
    // for (auto i : probability)
    //     std::cout << i << std::endl;

    //计算平均码长
    for (auto i = this->mp.begin(); i != mp.end(); ++i) {
        double partialAns = probability[i->first] * encodeTable[i->first].size();
        // std::cout << "partialAns = " << partialAns << ' ';
        sum2 += partialAns;
    }
    // std::cout << "sum1 = " << sum1 << " sum2 = " << sum2 << std::endl;
    return sum1 / sum2;
}

HuffmanTree::~HuffmanTree() = default;

void unit_test() {
    HuffmanTree h("122444488888888999999999");
    h.Encode();
    h.Decode();
    std::cout << h.calculateEfficiency() << std::endl;
}

int main(void) {
    unit_test();

    return 0;
}