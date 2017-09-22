#ifndef GARBAGE_H__
#define GARBAGE_H__

class Garbage_Collector {

public:
	~Garbage_Collector() {
		for(size_t i = 0; i < size; i++) {
			/*char data[256];
			std::sprintf(data,"Freed data: %s\n", mem_ptr[i]);
			OutputDebugString(data);*/
			free(mem_ptr[i]);
		}
	}

	Garbage_Collector() {
		mem_ptr = 0;
		size = 0;
	}

	void *alloc(size_t pos) {
		void *ptr = malloc(pos);
		mem_ptr = (void**)realloc(mem_ptr, sizeof(void**) * (++size));
		void **temp_ptr  = mem_ptr;
		temp_ptr  += (size-1);
		*temp_ptr = ptr;
		return ptr;
	}

	void *operator[](size_t pos) { return mem_ptr[pos]; }

private:
	void **mem_ptr;
	size_t size;


};


static Garbage_Collector mem;

#endif

