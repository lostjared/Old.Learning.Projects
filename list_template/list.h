/* List Template example
   writen by Jared Bruni
   www.LostSideDead.com

  "Open Source, Open Mind"
*/

const int size = 100;

template<class type>
class List
{
public:
	List();
	void add(type t);
	type get(int number);
	int  length();
private:
	type list[size];
	int  pos;
};

template<class type>
List<type>::List()
{
	pos = 0;
}

template<class type>
void List<type>::add(type t)
{
	if(pos < size)
	{
		list[pos] = t;
		pos++;
	}
}

template<class type>
type List<type>::get(int number)
{
	if(number > pos) { return 0; }

	return list[number];
}

template<class type>
int List<type>::length()
{
	return pos;
}