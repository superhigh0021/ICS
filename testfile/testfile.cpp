#include<iostream>
#include<string>
#include<iomanip>
#include<cmath>
using namespace std;

//静态三叉链表节点
struct HNode {
	int weight;//权重
	int parent;//双亲指针
	int LChild;//左孩子指针
	int RChild;//右孩子指针
};

///编码表节点
struct HCode {
	char data;
	string code;
	float p;
};

//最小和次小选取
void Select(HNode*& HTree, int n, int& min1, int& min2) {
	struct TempNode {
		int tweight;//储存权重
		int p;//储存位置
	};
	TempNode* tempTree = new TempNode[n];
	int j = 0;
	for (int i = 0; i < n; i++) {
		if (HTree[i].parent == -1 && HTree->weight != 0) {
			tempTree[j].tweight = HTree[i].weight;
			tempTree[j].p = i;
			j++;
		}
	}//将HTree中无双亲的节点存储到tempTree中
	int m1 = 0, m2 = 0;
	for (int i = 0; i < j; i++) {
		if (tempTree[i].tweight < tempTree[m1].tweight)//不取等号，权值相等时m1取前面的
			m1 = i;
	}
	for (int i = 0; i < j; i++) {
		if (m1 == m2)
			m2++;//m1在位置1时，m2后移一位
		if (tempTree[i].tweight <= tempTree[m2].tweight)//取等号，权值相等时m2取后面的
			m2 = i;
	}
	min1 = tempTree[m1].p;
	min2 = tempTree[m2].p;
}

//建立哈夫曼树
void CreateHTree(HNode*& HTree, int weight[], int n) {
	HTree = new HNode[2 * n - 1];
	for (int i = 0; i < n; i++) {//根据权重初始化Huffman树
		HTree[i].weight = weight[i];
		HTree[i].LChild = -1;
		HTree[i].RChild = -1;
		HTree[i].parent = -1;
	}
	if (n <= 1)//错误处理
		throw"数据不足无法建立哈夫曼树";

	int min1, min2;
	for (int i = n; i < 2 * n - 1; i++) {
		Select(HTree, i, min1, min2);
		HTree[min1].parent = HTree[min2].parent = i;
		HTree[i].weight = HTree[min1].weight + HTree[min2].weight;
		HTree[i].LChild = min1;
		HTree[i].RChild = min2;
		HTree[i].parent = -1;
	}
}
//逆置编码函数
void Reverse(string& s) {
	int length = s.size();
	char temp;
	for (int i = 0; i < length / 2; i++) {
		temp = s[i];
		s[i] = s[length - i - 1];
		s[length - i - 1] = temp;
	}
}
//哈夫曼编码表
void CreateCodeTable(HNode*& HTree, HCode*& HCodeTable, string b, int n) {
	HCodeTable = new HCode[n];//生成编码表
	cout << "code table is : " << endl;
	for (int i = 0; i < n; i++) {
		HCodeTable[i].data = b[i];
		int child = i;
		int parent = HTree[i].parent;
		int k = 0;
		while (parent != -1) {
			if (child == HTree[parent].LChild)
				HCodeTable[i].code += '0';
			else
				HCodeTable[i].code += '1';
			child = parent;
			parent = HTree[child].parent;
		}
		Reverse(HCodeTable[i].code);//逆置
									//输出编码表
		cout << setiosflags(ios::left) << ' ' << setw(5) << HCodeTable[i].data << ' ' << setw(5) << HCodeTable[i].code << endl;//打印编码表
	}
	cout << endl << endl;
}
//编码
string Encode(HCode*& HCodeTable, string s, int n) {
	string encodedString;//编码串
	int length = s.size();
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < n; j++) {
			if (s[i] == HCodeTable[j].data)
				encodedString += HCodeTable[j].code;
		}
	}
	return encodedString;
}
//解码
string Decode(HNode*& HTree, HCode*& HCodeTable, string s, int n) {
	string decodedString;
	int length = s.size();
	for (int i = 0; i < length; i++) {
		int parent = 2 * n - 1 - 1;//根节点在哈夫曼树中的下标
		int j = 0;
		while (HTree[parent].LChild != -1) {
			if (s[i + j] == '0')
				parent = HTree[parent].LChild;
			else
				parent = HTree[parent].RChild;
			j++;
		}
		i += j - 1;
		decodedString += HCodeTable[parent].data;
	}
	return decodedString;
}
//计算编码效率
float Code_efficiency(HCode*& HCodeTable, int n) {
	float a = 0;
	float b = 0;
	float c;
	for (int i = 0; i < n; i++) {
		a = -(HCodeTable[i].p * (log(HCodeTable[i].p) / log(2))) + a;
	}//信息熵=-概率*log概率之和
	for (int i = 0; i < n; i++) {
		b = HCodeTable[i].p * HCodeTable[i].code.size() + b;
	}//平均码长=概率*码长之和
	c = a / b;//编码效率=信息熵/平均码长
	return c;
}
//释放指针
void Delete(HNode*& HTree, HCode*& HCodeTable) {

	delete[]HTree;
	//cout << "哈夫曼树已删除" << endl;
	delete[]HCodeTable;
	//cout << "哈夫曼表已删除" << endl;
}

int main() {
	cout << "please input:" << endl;
	char a[100];
	cin.get(a, 100);
	char d[50] = { '\0' };//字符
	int w[50] = { 0 };//字符权值
	for (int i = 0; a[i] != '\0'; i++) {//统计输入字符
		for (int j = 0; j <= 50; j++) {
			if (j == 50) {//若d中不存在此字符，新存入
				int h = -1;
				while (w[++h] != 0);//寻找存入位置
				d[h] = a[i];
				w[h]++;
			}
			if (d[j] == a[i]) {
				w[j]++;
				break;
			}
		}
	}
	HNode* HTree;
	HCode* HCodeTable;
	string data, s;
	int sum = 0;
	s = a;//输入字符串转为string
	int l = s.size();
	int n = 0;//统计编码表中字符个数
	while (d[n] != '\0') {
		data += d[n];
		n++;
	}
	CreateHTree(HTree, w, n);
	CreateCodeTable(HTree, HCodeTable, data, n);
	//求各符号概率
	for (int j = 0; j < l; j++) {
		sum = sum + 1;
	}
	for (int i = 0; i < n; i++) {
		HCodeTable[i].p = HTree[i].weight / float(sum);
	}
	string encodeString;
	encodeString = Encode(HCodeTable, s, n);
	cout << "after coding:" << encodeString << endl;
	cout << "input string you want to decode:";
	char b[100];
	cin >> b;
	cout << "after decoding:" << Decode(HTree, HCodeTable, b, n) << endl;
	cout << "efficiency is:" << Code_efficiency(HCodeTable, n) << endl;
	Delete(HTree, HCodeTable);//释放指针
	return 0;
}
