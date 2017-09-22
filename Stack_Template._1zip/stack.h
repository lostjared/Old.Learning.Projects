/* stack template example 
   written by Jared Bruni
   www.LostSideDead.com
   "Open Source, Open Mind"
*/

const int max = 100;

template <class type>
class Stack
{
public:
	Stack()
	{
		off_set = 0;
	}

	void push(type t)
	{
		if(off_set < max)
		{

		array[off_set] = t;
		off_set++;

		}

	}
	type pop()
	{
		type temp;
		off_set--;
		if(off_set >= 0)
		{

		temp = array[off_set];

		}
		return temp;
	}
private:
	type array[max];
	int off_set;
};


