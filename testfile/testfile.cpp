#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>
#include<string.h>
#define Bmax 10  //最长码长度
#define Smax 20 //数组最大长度
struct Bit
{
	char b[Bmax];
	int last;
};
typedef struct symbol
{
	char c;
	float probability;
	struct Bit bit;
}sbl;
sbl s[Smax];

void sort(int n)//排序
{
	float t;
	char a;
	int i, j;
	for (i = 1; i < n; i++)
		for (j = 0; j < n - i; j++)
			if (s[j].probability < s[j + 1].probability)
			{
				t = s[j].probability;
				a = s[j].c;
				s[j].probability = s[j + 1].probability;
				s[j].c = s[j + 1].c;
				s[j + 1].probability = t;
				s[j + 1].c = a;
			}
}

void code(int low, int mid, int high)//编码
{
	int i;
	for (i = low; i < high; i++)
	{
		if (i < mid)
		{
			s[i].bit.b[s[i].bit.last] = '0';
			s[i].bit.last++;
		}
		else
		{
			s[i].bit.b[s[i].bit.last] = '1';
			s[i].bit.last++;
		}
	}
}

void group1(int low, int mid, int high)//分组
{
	float d, dmin;
	d = 0;
	int i;
	if (high == low + 1)
		return;
	for (i = low; i < mid; i++)
		d += s[i].probability;
	dmin = d - 2 * s[low].probability;
	for (i = low + 1; i < high; i++)
	{
		d = fabs(dmin - 2 * s[i].probability);
		if (d < dmin)
			dmin = d;
		else
			break;
	}
	mid = i;
	code(low, mid, high);
	group1(low, mid, mid);
	group1(mid, high, high);
}

void group(int n)
{
	int i, pmid, plow, phigh;
	pmid = phigh = n;
	plow = 0;
	for (i = 0; i < n; i++)
		s[i].bit.last = 0;
	group1(plow, pmid, phigh);
}

void input(int n)
{
	int i;
	char c;
	printf("请输入符号及符号概率\n");
	c = getchar();
	for (i = 0; i < n; i++)
	{
		scanf("%c", &s[i].c);
		scanf("%f", &s[i].probability);
		c = getchar();
	}
}

void output(int n)//输出编码
{
	int i, j;
	printf("请输出符号,符号概率及编码\n");
	for (i = 0; i < n; i++)
	{
		printf("%c\t%f\t", s[i].c, s[i].probability);
		for (j = 0; j < s[i].bit.last; j++)
			printf("%c", s[i].bit.b[j]);
		printf("\n");
	}
}

void qita(int n)
{
	int i, j;
	float sum, average, effiency;
	sum = average = 0;
	for (i = 0; i < n; i++)
	{
		sum -= s[i].probability * log10(s[i].probability) / log10(2);//信源熵
		average += s[i].probability * s[i].bit.last;//平均码长
	}
	effiency = sum / average;//编码效率
	printf("信源熵:%f\n平均码长:%f\n编码效率:%f\n", sum, average, effiency);
}


void decode(int n, char a[100])//译码
{
	int i = 0, j;
	char s2[100];
	s2[0] = '\0';
	while (i < strlen(a))
	{
		char temp[2];
		temp[0] = a[i];
		temp[1] = '\0';
		strcat(s2, temp);
		for (j = 0; j < n; j++)
		{
			if (strcmp(s2, s[j].bit.b) == 0)
			{
				printf("%c", s[j].c);
				s2[0] = '\0';
				break;
			}
		}
		i++;
	}
	printf("\n");
}


void main()
{
	int n;
	char a[100];
	printf("请注意当显示器再次输出“请输入符号个数时”说明输入的n值有误!\n");
	do {
		printf("请输入符号个数0<n<=20\n");
		scanf("%d", &n);
	} while (n > Smax || n <= 0);
	input(n);
	sort(n);
	group(n);
	output(n);
	qita(n);
	printf("请输入要译的二进制代码\n");
	scanf("%s", a);
	printf("输出译码结果\n");
	decode(n, a);
}
