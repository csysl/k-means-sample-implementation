/*
ʵ��k-means�㷨��
���ṩ�������k����ʼ���������ȡ
���ṩ��������ά��d
��ֹ������ǰ��������ֵ��С��0.1����ֵΪ����ƽ�������ܺ�

������txt�������
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h> 
#include<algorithm>  //random_shuffle()
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

int k, d;//k�أ�dά

struct Tuple {
	vector<float> T;
};
//���뺯������������֮���ŷ����þ���
float Distance(Tuple A, Tuple B,int d) {
	float result=0, tmp;
	for (int i = 0; i < d; i++) {
		tmp = (A.T[i] - B.T[i])*(A.T[i] - B.T[i]);
		result += tmp;
	}
	result = sqrt( result);
	//cout << "  " << result;
	return result;
}
//���㵱ǰ���������ĸ���
int Cluster(vector<Tuple> center, Tuple tuple, int k,int d) {
	float dis = Distance(center[0], tuple,d);
	float tmp;
	int label = 0;
	for (int i = 0; i < k; i++) {
		tmp = Distance(center[i], tuple,d);
		//cout << " tmp " << tmp;
		if (tmp < dis) {
			dis = tmp;
			label = i;
		}
	}
	return label;
}
//����ƽ�����
float Arrerror(vector<Tuple>cluster[], vector<Tuple> center, int k,int d) {
	float sum = 0;
	for (int i = 0; i < k; i++) {
		vector<Tuple> tmp = cluster[i];
		for (int j = 0; j <tmp.size(); j++) {
			sum += Distance(tmp[j], center[i],d);
		}
	}
	//cout << "ƽ������" << sum << endl;
	return sum;
}
//��õ�ǰ�صľ�������
Tuple getcenter(vector<Tuple> tuples,int d) {
	Tuple center;
	int num = tuples.size();
	//cout << "num" << num;
	vector<float> x;
	float y=0;
	for (int i = 0; i < d; i++) {
		for (int j = 0; j < num; j++) {
			y += tuples[j].T[i];
		}
		x.push_back(y);
		y = 0;
		//cout << x[i] << " ";
	}
	for (int j = 0; j < d; j++) {
		center.T.push_back( x[j] / num);
	}
	x.clear();
	return center;
}

void Kmeans(vector<Tuple>tuples, int k, int d) {
	vector<Tuple> cluster[100];//k�أ����֧�ַ�Ϊ100��
	vector<Tuple> tupleslist;//���ڴ�������С����ʱ�Ķ���˳��
	vector<Tuple> center;//����
	Tuple tuple;
	int num = tuples.size();

	int label[100];//��������ĸ���
	int labelist[10][100];//����100�Σ���¼ÿ�εı��
	float tag_a = INFINITY; //������С���
	int tag_b = -1;   //���������Сʱ�ĵ�������
	float a, b;//a:��b:ǰһ�ε����

	//����ʮ�Σ�ȡ�����С�����
	for (int t = 0; t < 10; t++) {
		//��ȡk����ʼ����
		random_shuffle(tuples.begin(), tuples.end());//����tuples˳��ȡǰk��Ϊ��ʼ���ģ��ﵽ���ȡ�ô��ĵ�Ŀ��
		//cout << "debug1"<<endl;
		center.clear();
		for (int i = 0; i < k; i++) {
			for (int j = 0; j < d; j++) {
				//cout <<"tup  "<< tuples[i].T[j] << "  ";
				tuple.T.push_back(tuples[i].T[j]);
				//cout << tuple.T[j] << "  ";
			}
			center.push_back(tuple);
			tuple.T.clear();
			//cout <<"cen"<<i<<" "<< center[i].T[0]<<"  ";
		}
		//cout << "debug2"<<endl;
		//���������ĸ���,��ӵ���
		for (int i = 0; i<num; i++) {
			label[i] = Cluster(center, tuples[i], k,d);
			cluster[label[i]].push_back(tuples[i]);
			//cout << "label:"<<label[i] << endl;
		}
		//cout << "debug3" << endl;
		a = Arrerror(cluster, center, k,d);
		//cout << a;
		//������ǰ���������С��0.1����
		for (int i = 0;; i++) {
			//��ô���
			tuple.T.clear();
			center.clear();
			for (int j = 0; j < k; j++) {
				//cout << "debug4";
				center.push_back(getcenter(cluster[j], d));
				/*cout << "center  ";
				for (int m = 0; m < d; m++) {
					cout << center[j].T[m] << " ";
				}*/
			}
			//cout << "debug5" << endl;
			b = a;
			a = Arrerror(cluster, center, k,d);
			//cout << a << endl;
			//���ԭ��
			for (int j = 0; j < k; j++) {
				cluster[j].clear();
			}
			//����õ��´�
			for (int j = 0; j<num; j++) {
				label[j] = Cluster(center, tuples[j], k,d);
				labelist[t][j] = label[j];
				cluster[label[j]].push_back(tuples[j]);
				//cout << label[j] << "  ";
			}
			//cout << endl;
			if (abs(a - b) <= 0.1)break;
		}
		//��մ�
		for (int j = 0; j < k; j++) {
			cluster[j].clear();
		}
		//cout << "debug6" << endl;
		//ȡ�����ֵ��С�ľ���
		tuple.T.clear();
		if (a <= tag_a) {
			tag_a = a;
			tag_b = t;
			tupleslist.clear();
			for (int i = 0; i < num; i++) {
				for (int j = 0; j < d; j++) {
					tuple.T.push_back(tuples[i].T[j]);
				}
				tupleslist.push_back(tuple);
				tuple.T.clear();
			}
		}
		//cout << "debug7" << endl;

	}
	//������
	cout << "���" << endl;
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < d; j++) {
			cout << tupleslist[i].T[j] << "  ";
		}
		cout << "cluster:" << labelist[tag_b][i] << endl;
	}
	//��������out.txt
	ofstream mycout("out.txt");
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < d; j++) {
			mycout << tupleslist[i].T[j] << "  ";
		}
		mycout << labelist[tag_b][i] << endl;
	}
}

int main() {
    cout << "��������ά��:" << endl;
	cin >> d;
	Tuple tuple;
	for (int i = 0; i < d; i++) {
		tuple.T.push_back(i);
		//cout << tuple.T[i] << " ";
	}

	ifstream refile;
	refile.open("data2.txt", ios::in);
	if(!refile)
		cout<< "�Ҳ��������ļ�" << endl;
	vector<Tuple> tuples;
	int count = 0, tab=0;
	while (!refile.eof()) {
		refile >> tuple.T[count];
		//cout << tuple.T[count] <<" "<<count<< endl;
		count++;
		tab++;
		if (count%d==0) {
			tuples.push_back(tuple);
			count = 0;
		}
	}
begin:
	while (1) {
		cout << "�������Ĵ�����" << endl;
		cin >> k;
		if (tab < k * d) {
			cout << "������Ŀ�����˴���,���������룺" << endl;
			goto begin;
		}
		else if (k < 1) {
			cout << "������Ŀ����С��1�����������룺" << endl;
			goto begin;
		}
		//����k��ֵ
		Kmeans(tuples, k,d);
	}
	
	system("pause");
	return 0;
}