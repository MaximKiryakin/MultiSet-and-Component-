
#include<iostream>
#include"z1.cpp"

class Component
{
public:
	Component();
	Component(const Component&) = delete;
	Component& operator= (const Component&) = delete;
	virtual ~Component();
	int count() const;
	Component& subcomponent(int);
	const Component& subcomponent(int) const;
	void add(Component&);
	friend std::ostream& operator<<(std::ostream& out, const Component& other);

protected:
	virtual const std::string& name() const = 0;
	MultiSet<Component*> my_set;

};


std::ostream& operator<<(std::ostream& out, const Component& other)
{
	out << other.name() << '(';
	for (int i = 0; i < other.my_set.size(); i++)
	{
		out << other.subcomponent(i);
		if (i != other.my_set.size() - 1)
		{
			out << ',' << ' ';
		}
	}
	out << ')';
	return out;
}


Component& Component::subcomponent(int index)
{
	return *my_set[index];
}

void Component::add(Component& t)
{
	my_set.add(&t);
}


const Component& Component::subcomponent(int index) const
{
	return *my_set[index];
}

int Component::count() const
{
	return my_set.size();
}

Component::Component() :my_set() {}
Component:: ~Component() {}


class Box : public Component
{
public:
	Box(std::string);
	Box(const Box&);
	Box& operator=(const Box&);

	

private:
	const std::string& name() const;
	std::string my_string;
	std::string box = "Box";

};

class comm: public Component{

};

Box::Box(const Box& other) : my_string(other.my_string) {}
Box::Box(std::string s) : my_string(s) {}

Box& Box::operator=(const Box& other)
{

	if (&other == this) { return *this; }
	my_string = other.my_string;
	my_set.clear();
	return *this;
}

const std::string& Box::name() const
{
	return box;
}


int main()
{
	
	MultiSet<Component*> mmm;
	Box a = Box("Bohhhhx1");
	Box b = Box("Bohhhhx2");
	Box c = Box("Bohhhhx3");
	a.add(b);
	std::cout<< a;
	return 0;
}
