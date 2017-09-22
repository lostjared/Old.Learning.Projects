/* Vector Template
   written by Jared Bruni
   www.LostSideDead.com

  "Open Source, Open Mind"
*/


template <class type>
class Vector
{
public:
	Vector();
	Vector(int size);
	~Vector();
	type operator[](int pos);
	void Resize(int size);
	void Add(type t);
	void Asn(int pos, type t);
 	type Get(int pos);
	unsigned long Length();
private:
	type* array;
	unsigned long size;
	int i;
};

template<class type>
Vector<type>::Vector()
{
	array = 0;
	size = 0;
}

template <class type>
Vector<type>::Vector(int sizex)
{
	size = sizex;
	array = new type[ size ];
}

template <class type>
Vector<type>::~Vector()
{
	if( array != 0 )
	{
		delete [] array;
		array = 0;
	}
}

template <class type>
type Vector<type>::operator [](int pos)
{
	if( pos > size || pos < 0 && array != 0 ) { return 0; }
	return array[pos];
}

template <class type>
void Vector<type>::Resize(int sizex)
{
	type* temp = new type[ size ];
	for(i = 0; i < size; i++)
	{
		temp[i] = array[i];
	}
	
	if(array != 0)
	{

	delete [] array;

	array = 0;

	}

	array = new type [ sizex ];
	for(i = 0; i < size; i++)
	{
		if(i < sizex) 
		{
		array[i] = temp[i];
		}
	}

	delete [] temp;
	temp = 0;
	size = sizex;
}

template <class type>
void Vector<type>::Add(type t)
{
	int size2;
	size2 = size + 1;
	Resize(size2);
	array[size2-1] = t;
}

template<class type>
unsigned long Vector<type>::Length()
{
	return size;
}

template<class type>
void Vector<type>::Asn(int pos, type t)
{
	if(pos < size && pos >= 0) 
	{
		array[pos] = t;
	}
}

template<class type>
type Vector<type>::Get(int pos)
{
	return this[pos];
}


