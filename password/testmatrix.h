#include <cmath>
#include <iostream>
#include <vector>
#define N 10
using namespace std;
class Mat {
public:
    int m = 1, n = 1;       //行数和列数
    double mat[N][N] = {0}; //矩阵开始的元素

    Mat() {}
    Mat(int mm, int nn) {
        m = mm;
        n = nn;
    }
    void create(const vector<int>& v); //创建矩阵
    void Print();                      //打印矩阵

    void augmat(Mat a, Mat b); //求矩阵 a 和向量 b 的增广矩阵
    bool solve(Mat a, Mat b);  //求线性方程组的解
};

void Mat::create(const vector<int>& v) {
    if (v.size() == 4) {
        mat[1][1] = v[0];
        mat[1][2] = v[1];
        mat[2][1] = v[2];
        mat[2][2] = v[3];
    } else if (v.size() == 2) {
        mat[1][1] = v[0];
        mat[2][1] = v[1];
    }
}
void Mat::Print() {
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            cout << mat[i][j] << "\t";
        }
        cout << endl;
    }
}
void Mat::augmat(Mat a, Mat b) //求矩阵 a 和向量 b 的增广矩阵
{
    m = a.m;
    n = a.n + 1;
    for (int i = 1; i <= a.m; i++) {
        for (int j = 1; j <= a.n; j++) {
            mat[i][j] = a.mat[i][j];
        }
        mat[i][n] = b.mat[i][1];
    }
}

bool Mat::solve(Mat a, Mat b) // a 为方阵 ，b 为列向量
//求线性方程组的解(ax=b ,求 x)，矩阵 a 为方阵并且方程组有唯一解时返回 true
{
    if (a.n != a.m) //只求解是方阵时的情形
    {
        cout << "系数矩阵不是方阵" << endl;
        return false; //返回false
    }
    m = a.n;
    n = 1; //解向量中必定有 a.n（ a.m ）个分量,是 a.n * 1 的列向量
    Mat aa;
    aa.augmat(a, b); //求增广矩阵

    //下面代码将增广矩阵化为上三角矩阵，并判断增广矩阵秩是否为 n
    for (int i = 1; i <= aa.m; i++) {
        //寻找第 i 列不为零的元素
        int k;
        for (k = i; k <= aa.m; k++) {
            if (fabs(aa.mat[k][i]) > 1e-10) //满足这个条件时，认为这个元素不为0
                break;
        }
        if (k <= aa.m) //说明第 i 列有不为0的元素
        {
            //交换第 i 行和第 k 行所有元素
            for (int j = i; j <= aa.n; j++) //从第 i 个元素交换即可，因为前面的元素都为0
            {                               //使用aa.mat[0][j]作为中间变量交换元素
                aa.mat[0][j] = aa.mat[i][j];
                aa.mat[i][j] = aa.mat[k][j];
                aa.mat[k][j] = aa.mat[0][j];
            }
            double c; //倍数
            for (int j = i + 1; j <= aa.m; j++) {
                c = -aa.mat[j][i] / aa.mat[i][i];
                for (k = i; k <= aa.n; k++) {
                    aa.mat[j][k] += c * aa.mat[i][k]; //第 i 行 a 倍加到第 j 行
                }
            }
        } else //没有找到则说明系数矩阵秩不为 n ，说明方程组中有效方程的个数小于 n
        {
            cout << "系数矩阵奇异，线性方程组无解或有无数解" << endl;
            return false;
        }
    }
    //自下而上求解
    for (int i = a.m; i >= 1; i--) {
        mat[i][1] = aa.mat[i][aa.n];
        for (int j = a.m; j > i; j--) {
            mat[i][1] -= mat[j][1] * aa.mat[i][j];
        }
        mat[i][1] /= aa.mat[i][i];
    }
    return true;
}

// int main()
// {
// 	Mat a(2,2), b(2, 1);
// 	cout << "input " << a.m << "*" << a.n << " matrix" << endl;
// 	a.create();
// 	cout << "input " << b.m << "*" << b.n << " clomn" << endl;
// 	b.create();

// 	Mat x;
// 	if (x.solve(a, b))//求线性方程组的解向量
// 	{
// 		cout << "ans:" << endl << endl;
// 		x.Print();
// 	}
// 	return 0;
// }