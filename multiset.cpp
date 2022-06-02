#include<iostream>
#include<stdexcept>

template<typename T>
class MultiSet
{
public:
	MultiSet();
	MultiSet(const MultiSet&, int new_size = -1);
	MultiSet& operator=(MultiSet);
	const T& operator[](const int index) const;
	T& operator[](const int index);

	T get(int);
	void clear();
	int size() const;
	void add(const T& t);
	T del(int index);
	int get_alloc_size() const;
	int get_actual_size() const;
	T* get_mas() const;
	~MultiSet();
	
private:
	int alloc_size; 
	int actual_size;
	T* mas;
};

template<typename T>
MultiSet<T>::MultiSet() : alloc_size(0), actual_size(0), mas(nullptr){}


template<typename T>
int MultiSet<T>::get_alloc_size() const
{
	return alloc_size;
}

template<typename T>
int MultiSet<T>::get_actual_size() const
{
	return actual_size;
}

template<typename T>
T* MultiSet<T>::get_mas() const
{
	return mas;
}


template<typename T>
MultiSet<T>::MultiSet(const MultiSet<T> & other, int new_size): 
alloc_size(0), actual_size(0), mas(nullptr)
{
	size_t allocated_size;
	if (new_size > other.actual_size)
	{
		allocated_size = new_size;
	}
	else {
		allocated_size = other.alloc_size;
	}

	try
	{
		mas = new T[allocated_size];
		if (!mas) { throw std::runtime_error(""); }
		for (int i = 0; i < other.actual_size; i++)
		{
			mas[i] = other[i];
		}
	}
	catch (std::exception&)
	{
		delete[] mas;
		throw std::runtime_error("");
	}
	alloc_size = allocated_size;
	actual_size = other.actual_size;
}

template<typename T>
MultiSet<T>& MultiSet<T>::operator=(MultiSet<T> other)
{
	
	std::swap(other.mas, mas);

	alloc_size = other.alloc_size;
	actual_size = other.actual_size;
	
	return *this;
}

template<typename T>
const T& MultiSet<T>::operator[](const int index) const
{
	if (index < 0 || index > actual_size)
	{
		throw std::runtime_error("");
	}
	return mas[index];
}

template<typename T>
T& MultiSet<T>::operator[](const int index)
{
	if (index < 0 || index > actual_size)
	{
		throw std::runtime_error("");
	}
	return mas[index];
}

template<typename T>
void MultiSet<T>::clear()
{
	actual_size = 0;
}

template<typename T>
int MultiSet<T>::size() const
{
	return actual_size;
}

template<typename T>
void MultiSet<T>::add(const T& t)
{
	if (actual_size >= alloc_size)
	{
		if (!alloc_size) { alloc_size = 1; }
		//тут может быть исключение, хрен с ним, деструктор вроде стработает и ок 
		MultiSet<T> tmp(*this, alloc_size * 2);
		tmp[tmp.actual_size] = t;
		tmp.actual_size++;
		
		//*this = tmp;	
		actual_size = tmp.actual_size;
		alloc_size = tmp.alloc_size;
		std::swap(mas, tmp.mas);


	}
	else {
		mas[actual_size] = t;
		actual_size++;
	}

}

template<typename T>
T MultiSet<T>::del(int index)
{
	if (index < 0 || index > actual_size)
	{
		throw std::runtime_error("");
	}
	T tmp = mas[index];

	mas[index] = mas[actual_size - 1];
	actual_size--;

	return tmp;
}


template<typename T>
MultiSet<T>::~MultiSet()
{
	delete[] mas;
}


int main()
{

	MultiSet<int> my_set;
	my_set.add(5);
	my_set.add(6);
	my_set.add(7);
	my_set.add(7);
	my_set.add(7);
	my_set.add(7);

	my_set.del(0); 
	MultiSet<int> my_set1 = my_set;
	//my_set.clear();

	for (int i = 0; i < my_set1.size(); i++)
	{
		std::cout << my_set1[i] << std::endl;
	}

	return 0;
}


