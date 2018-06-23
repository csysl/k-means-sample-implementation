/*
实现k-means算法：
需提供聚类簇数k，初始簇心随机获取
需提供聚类对象的维度d
终止条件：前后两次阈值差小于0.1，阈值为对象平均误差的总和

数据以txt输入输出
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h> 
#include<algorithm>  //random_shuffle()
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

int k, d;//k簇，d维

struct Tuple {
	vector<float> T;
};
//距离函数采用两对象之间的欧几里得距离
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
//计算当前对象属于哪个簇
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
//计算平均误差
float Arrerror(vector<Tuple>cluster[], vector<Tuple> center, int k,int d) {
	float sum = 0;
	for (int i = 0; i < k; i++) {
		vector<Tuple> tmp = cluster[i];
		for (int j = 0; j <tmp.size(); j++) {
			sum += Distance(tmp[j], center[i],d);
		}
	}
	//cout << "平均误差和" << sum << endl;
	return sum;
}
//获得当前簇的聚类中心
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
	vector<Tuple> cluster[100];//k簇，最多支持分为100簇
	vector<Tuple> tupleslist;//用于存放误差最小聚类时的对象顺序
	vector<Tuple> center;//簇心
	Tuple tuple;
	int num = tuples.size();

	int label[100];//标记属于哪个簇
	int labelist[10][100];//迭代100次，记录每次的标记
	float tag_a = INFINITY; //放置最小误差
	int tag_b = -1;   //放置误差最小时的迭代次数
	float a, b;//a:误差，b:前一次的误差

	//计算十次，取误差最小的输出
	for (int t = 0; t < 10; t++) {
		//获取k个初始簇心
		random_shuffle(tuples.begin(), tuples.end());//打乱tuples顺序，取前k个为初始簇心，达到随机取得簇心的目的
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
		//计算属于哪个簇,添加到簇
		for (int i = 0; i<num; i++) {
			label[i] = Cluster(center, tuples[i], k,d);
			cluster[label[i]].push_back(tuples[i]);
			//cout << "label:"<<label[i] << endl;
		}
		//cout << "debug3" << endl;
		a = Arrerror(cluster, center, k,d);
		//cout << a;
		//迭代，前后两次误差小于0.1跳出
		for (int i = 0;; i++) {
			//获得簇心
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
			//清空原簇
			for (int j = 0; j < k; j++) {
				cluster[j].clear();
			}
			//计算得到新簇
			for (int j = 0; j<num; j++) {
				label[j] = Cluster(center, tuples[j], k,d);
				labelist[t][j] = label[j];
				cluster[label[j]].push_back(tuples[j]);
				//cout << label[j] << "  ";
			}
			//cout << endl;
			if (abs(a - b) <= 0.1)break;
		}
		//清空簇
		for (int j = 0; j < k; j++) {
			cluster[j].clear();
		}
		//cout << "debug6" << endl;
		//取得误差值最小的聚类
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
	//输出结果
	cout << "结果" << endl;
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < d; j++) {
			cout << tupleslist[i].T[j] << "  ";
		}
		cout << "cluster:" << labelist[tag_b][i] << endl;
	}
	//保存结果到out.txt
	ofstream mycout("out.txt");
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < d; j++) {
			mycout << tupleslist[i].T[j] << "  ";
		}
		mycout << labelist[tag_b][i] << endl;
	}
}

int main() {
    cout << "输入数据维度:" << endl;
	cin >> d;
	Tuple tuple;
	for (int i = 0; i < d; i++) {
		tuple.T.push_back(i);
		//cout << tuple.T[i] << " ";
	}

	ifstream refile;
	refile.open("data2.txt", ios::in);
	if(!refile)
		cout<< "找不到输入文件" << endl;
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
		cout << "输入聚类的簇数：" << endl;
		cin >> k;
		if (tab < k * d) {
			cout << "对象数目超过了簇数,请重新输入：" << endl;
			goto begin;
		}
		else if (k < 1) {
			cout << "聚类数目不能小于1，请重新输入：" << endl;
			goto begin;
		}
		//计算k均值
		Kmeans(tuples, k,d);
	}
	
	system("pause");
	return 0;
}