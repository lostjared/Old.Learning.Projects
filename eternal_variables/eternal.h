#include<fstream>

using namespace std;


template<class type>
class eternal {
	
	struct Data
	{
		type t;
		bool on;

		inline Data()
		{
			on = false;
		}
	};

	Data dat;

public:

	eternal(type t, char *filename);
	~eternal();
	type get();
	void save();
	void load();
	void operator=(type t);


	char *str;


};

template<class type>
eternal<type>::eternal(type init, char *filename)
{
	str = filename;
	load();
	if(dat.on == false)
	{
		dat.on = true;
		dat.t = init;
	}
}

template<class type>
eternal<type>::~eternal()
{
	save();
}

template<class type>
void eternal<type>::save()
{
	ofstream fout(str,ios::binary);
	fout.write((char*)&dat,sizeof(dat));
	fout.close();

}

template<class type>
void eternal<type>::load()
{
	ifstream fin(str,ios::binary);
	fin.read((char*)&dat,sizeof(dat));
	fin.close();
} 

template<class type>
type eternal<type>::get()
{
	return dat.t;
}

template<class type>
void eternal<type>::operator=(type x)
{
	dat.t = x;
}