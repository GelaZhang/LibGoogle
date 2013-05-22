// sample.cpp : Defines the entry point for the console application.
//

#include <sparsehash/internal/sparseconfig.h>
#include <sparsehash/sparsetable>
#include <sparsehash/dense_hash_map>
#include <sparsehash/sparse_hash_map>
#include <tchar.h>
#include <iostream>
#include <string>
using namespace std;
//dense_hash_map  ע��ʱ��Ч�ʵ�map
//dense_hash_set ע��ʱ��Ч�ʵ�set
//sparse_hash_map ע�ؿռ�Ч�ʵ�map �ʺ��ڴ������ݣ����ṩ���л�
//sparse_hash_set ע�ؿռ�Ч�ʵ�set �ʺ��ڴ������ݣ����ṩ���л�
//sparsetable ע�ؿռ�Ч�ʵ�vector ���ṩ���л�

void sparsetable()
{
#define DENSE 0 
#if DENSE
	google::dense_hash_map<string, int> months;
#else
	google::sparse_hash_map<string, int> months;
#endif
#if DENSE
	months.set_empty_key(""); //�������κε���ǰ����
#endif
	months["january"] = 31;
	months["february"] = 28;
	months["march"] = 31;
	months["april"] = 30;
	months["may"] = 31;
	months["june"] = 30;
	months["july"] = 31;
	months["august"] = 31;
	months["september"] = 30;
	months["october"] = 31;
	months["november"] = 30;
	months["december"] = 31;
	cout<<endl;
	cout << "september -> " << months["september"] << endl;
	cout << "april     -> " << months["april"] << endl;
	cout << "june      -> " << months["june"] << endl;
	cout << "november  -> " << months["november"] << endl;
	cout<<endl<<"size: "<<months.size()<<"max_size:"<<months.max_size();
	months.set_deleted_key("iam delete"); //�����ڵ���erase֮ǰ����
	months["december"] = 40;
	cout<<"december count:"<<months.count("december");
	cout<<"del:"<<months.erase("december");
}

int _tmain(int argc, _TCHAR* argv[])
{
	google::sparsetable<string> x(7);
	cout<< x.size();
	x[0] = "test0";
	x.set(2, "test2");
	for (google::sparsetable<string>::iterator i = x.begin(); x.end() != i; ++i )
	{
		if ( x.test(i) )
			cout<<static_cast<string>(*i)<<" x ";
	}
	sparsetable();
	return 0;
}

