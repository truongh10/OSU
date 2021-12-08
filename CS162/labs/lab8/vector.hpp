#include <stdlib.h>
#include <stdexcept>
template <class T>


class vector {
private:
	T *v;
	int s;
public:
	vector(){
		s=0;
		v=NULL;
	}

	// Copy Constructor
	vector(vector<T> &other) {
		s = other.s;
		v = new T[s];
		for (int i = 0; i < s; i++) {
			v[i] = other.v[i];
		}
	} 
	  
	void operator=(vector<T> &other) {
		if (this != &other) {
			delete [] v;
			s = other.s;
			
			v = new T[s];
			for (int i = 0; i < s; i++) {
				v[i] = other.v[i];
			}
		}
		return *this;
	}

	~vector(){
		delete [] v;
	}
	  
	int size() {
		return s;
	}
	  
	void push_back(T ele) {
		T *temp;
		temp = new T[++s];
		for(int i=0; i<s-1; i++)
	        	temp[i]=v[i];

	     	delete [] v;
	     	v=temp;
	     	v[s-1]=ele;
      	}

	T operator[] (int idx) {
		return v[idx];
	}

	T at(int idx) {
		if (idx >= s) {
			throw std::out_of_range("out of my vector bounds");
		}
		return v[idx];
	}






};
