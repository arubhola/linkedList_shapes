#include <iostream>
#include <iomanip>
#include <string>
#include <typeinfo>
#include <ctime>

using namespace std;

class Shape
{
private:
	string color;
	static int count;
public:
	static double const PI; //Value of PI for later use
public:
	Shape() { color = "None"; count++; }
	Shape(const string& c) { color = c; count++; }
	Shape(const Shape& s) { color = s.getColor(); count++; }

	virtual ~Shape() { count--; }

	string getColor() const { return color; }
	static int getCount() { return count; }

	void setColor(const string& c) { color = c; }

	virtual double getArea() const = 0;
	virtual double getPerimeter() const = 0;
	string getType() const
	{
		string s = typeid(*this).name();	//Now s is "class CLASSNAME"
		return s.substr(6);					//returning CLASSNAME
	}

	virtual void readInfo(istream&) = 0;
	virtual void printInfo(ostream&) const = 0;

	friend istream& operator>>(istream& in, Shape& s)
	{
		s.readInfo(in);
		return in;
	}
	friend ostream& operator<<(ostream& out, const Shape& s)
	{
		out.setf(ios::fixed | ios::left);	//Left aligned fixed decimal places
		s.printInfo(out);
		out.unsetf(ios::fixed | ios::left);	//Removing formatting
		cout.precision(0);					//Resetting the decimal places
		return out;
	}
};
int Shape::count = 0;
double const Shape::PI = 3.14159265359;
typedef Shape* ShapePtr;

class Rectangle : public Shape
{
private:
	double length, width;
public:
	Rectangle();
	Rectangle(const double&, const double&, const string&);

	double getLength() const;
	double getWidth() const;

	virtual void setLength(const double&);
	virtual void setWidth(const double&);

	virtual double getArea() const;
	virtual double getPerimeter() const;

	virtual void readInfo(istream&);
	virtual void printInfo(ostream&) const;
};

Rectangle::Rectangle() : Shape()
{
	length = 0;
	width = 0;
}
Rectangle::Rectangle(const double& len, const double& wid, const string& c) : Shape(c)
{
	length = len;
	width = wid;
}
double Rectangle::getLength() const { return length; }
double Rectangle::getWidth() const { return width; }
void Rectangle::setLength(const double& len) { length = len; }
void Rectangle::setWidth(const double& wid) { width = wid; }
double Rectangle::getArea() const { return length*width; }
double Rectangle::getPerimeter() const { return 2*(length+width); }
void Rectangle::readInfo(istream& in)
{
	cout << "\tEnter length ";
	in >> length;
	cout << "\tEnter width ";
	in >> width;
	string color;
	cout << "\tEnter color ";
	in >> color;
	this->setColor(color);
}
void Rectangle::printInfo(ostream& out) const
{
	out << setw(17) << getType() + " " + getColor();
	out << "Area = " << setw(9) << setprecision(2) << getArea();
	out << "Per. = " << setw(9) << setprecision(2) << getPerimeter();
	out << "Length = " << setw(7) << setprecision(2) << length;
	out << "Width = " << setw(5) << setprecision(2) << width;
}

class Square : public Rectangle
{
public:
	Square();
	Square(const double&, const string&);

	double getSide() const;

	virtual void setLength(const double&);
	virtual void setWidth(const double&);
	void setSide(const double&);

	virtual void readInfo(istream&);
	virtual void printInfo(ostream&) const;
};

Square::Square() : Rectangle() { }
Square::Square(const double& side, const string& c) : Rectangle(side, side, c) { }
double Square::getSide() const
{
	return getLength();
}
void Square::setLength(const double& len)
{
	setSide(len);
}
void Square::setWidth(const double& wid)
{
	setSide(wid);
}
void Square::setSide(const double& side)
{
	this->Rectangle::setLength(side);
	this->Rectangle::setWidth(side);
}
void Square::readInfo(istream& in)
{
	double side;
	cout << "\tEnter side ";
	in >> side;
	this->setSide(side);
	string color;
	cout << "\tEnter color ";
	in >> color;
	this->setColor(color);
}
void Square::printInfo(ostream& out) const
{
	out << setw(17) << getType() + " " + getColor();
	out << "Area = " << setw(9) << setprecision(2) << getArea();
	out << "Per. = " << setw(9) << setprecision(2) << getPerimeter();
	out << "Side = " << setw(9) << setprecision(2) << getLength();
}

class Triangle : public Shape
{
private:
	double base, height;
public:
	Triangle();
	Triangle(const double&, const double&, const string&);

	double getBase() const;
	double getHeight() const;

	void setBase(const double&);
	void setHeight(const double&);

	virtual double getArea() const;
	virtual double getPerimeter() const;

	virtual void readInfo(istream&);
	virtual void printInfo(ostream&) const;
};

Triangle::Triangle() : Shape()
{
	base = 0;
	height = 0;
}
Triangle::Triangle(const double& b, const double& h, const string& c) : Shape(c)
{
	base = b;
	height= h;
}
double Triangle::getBase() const { return base; }
double Triangle::getHeight() const { return height; }
void Triangle::setBase(const double& b) { base = b; }
void Triangle::setHeight(const double& h) { height = h; }
double Triangle::getArea() const
{
	return 0.5*base*height;
}
double Triangle::getPerimeter() const
{
	return base+height+sqrt(base*base + height*height);
}
void Triangle::readInfo(istream& in)
{
	cout << "\tEnter base ";
	in >> base;
	cout << "\tEnter height ";
	in >> height;
	string color;
	cout << "\tEnter color ";
	in >> color;
	this->setColor(color);
}
void Triangle::printInfo(ostream& out) const
{
	out << setw(17) << getType() + " " + getColor();
	out << "Area = " << setw(9) << setprecision(2) << getArea();
	out << "Per. = " << setw(9) << setprecision(2) << getPerimeter();
	out << "Base = " << setw(9) << setprecision(2) << base;
	out << "Height = " << setw(5) << setprecision(2) << height;
}

class Circle : public Shape
{
private:
	double radius;
public:
	Circle();
	Circle(const double&, const string&);

	double getRadius() const;

	void setRadius(const double&);

	virtual double getArea() const;
	virtual double getPerimeter() const;

	virtual void readInfo(istream&);
	virtual void printInfo(ostream&) const;
};
Circle::Circle() : Shape()
{
	radius = 0;
}
Circle::Circle(const double& r, const string& c) : Shape(c)
{
	radius = r;
}
double Circle::getRadius() const
{
	return radius;
}
void Circle::setRadius(const double& r)
{
	radius = r;
}
double Circle::getArea() const
{
	return PI*radius*radius;
}
double Circle::getPerimeter() const
{
	return 2*PI*radius;
}
void Circle::readInfo(istream& in)
{
	cout << "\tEnter radius ";
	in >> radius;
	string color;
	cout << "\tEnter color ";
	in >> color;
	this->setColor(color);
}
void Circle::printInfo(ostream& out) const
{
	out << setw(17) << getType() + " " + getColor();
	out << "Area = " << setw(9) << setprecision(2) << getArea();
	out << "Per. = " << setw(9) << setprecision(2) << getPerimeter();
	out << "Radius = " << setw(7) << setprecision(2) << radius;
}

class Node
{
typedef Node* NodePtr;
private:
	ShapePtr data;
	NodePtr link;
public:
	Node();
	Node(const ShapePtr&);
	Node(const Node&);
	~Node();
	ShapePtr getData() const;
	NodePtr getLink() const;
	void setData(const ShapePtr&);
	void setLink(const NodePtr&);
	friend ostream& operator<< (ostream&, const Node&);
};

typedef Node* NodePtr;

Node::Node() : data(nullptr), link(nullptr) { }
Node::Node(const Node& n) : data(n.data), link(n.link){ }
Node::Node(const ShapePtr& d) : data(d), link(nullptr){ }
Node::~Node() { delete data; }
ShapePtr Node::getData() const { return data; }
NodePtr Node::getLink() const { return link; }
void Node::setData(const ShapePtr& d) { data = d; }
void Node::setLink(const NodePtr& p) { link = p; }
ostream& operator<< (ostream& out, const Node& n)
{
	out << *(n.data);
	return out;
}

class LinkedList
{
private:
	NodePtr head;
public:
	LinkedList();
	LinkedList(const LinkedList&);
	~LinkedList();
	LinkedList& operator= (const LinkedList&);
	int getSize() const;
	void head_insert(const ShapePtr&);
	NodePtr search_node(const ShapePtr&) const;
	void insert_after(const NodePtr&, const ShapePtr&) const;
	void remove_node(const NodePtr&);
	void remove_node(const ShapePtr&);
	void remove_all(const ShapePtr&);
	void tail_insert(const ShapePtr&);
	void insert_before(const NodePtr&, const ShapePtr&);
	void insert_increasing(const ShapePtr&);
	void insert_grouped(const ShapePtr&);
	void insert_grouped_increasing(const ShapePtr&);
	friend ostream& operator<< (ostream&, const LinkedList&); //This is already implemented for you
};

LinkedList::LinkedList()
{
	head = nullptr;
}

LinkedList::LinkedList(const LinkedList& LL)
{
	head = nullptr;
	NodePtr temp = LL.head;
	NodePtr lastNode = nullptr;
	while (temp != nullptr)
	{
		if (lastNode == nullptr)
		{
			this->head_insert(temp->getData());
			lastNode = head;
		}
		else
		{
			this->insert_after(lastNode, temp->getData());
			lastNode = lastNode->getLink();
		}
		temp = temp->getLink();
	}
}

LinkedList::~LinkedList()
{
	NodePtr temp;
	while(head != nullptr)
	{
		temp = head;
		head = head->getLink();
		delete temp;
	}
}

LinkedList& LinkedList:: operator= (const LinkedList& LL)
{
	if (this == &LL)
		return *this;
	else
	{
		this->~LinkedList();
		NodePtr lastNode = nullptr;
		NodePtr temp = LL.head;
		while (temp != nullptr)
		{
			if (lastNode == nullptr)
			{
				this->head_insert(temp->getData());
				lastNode = head;
			}
			else
			{
				this->insert_after(lastNode, temp->getData());
				lastNode = lastNode->getLink();
			}
			temp = temp->getLink();
		}
		return *this;
	}
}

int LinkedList:: getSize() const
{
	int count = 0;
	NodePtr temp = head;
	while(temp!=nullptr)
	{
		count++;
		temp = temp->getLink();
	}
	return count;
}

void LinkedList::head_insert(const ShapePtr& s)
{
	NodePtr temp = new Node(s);
	temp->setLink(this->head);
	head = temp;
}

NodePtr LinkedList::search_node(const ShapePtr& s) const
{
	NodePtr temp = head;
	while(temp!=nullptr)
	{
		if(temp->getData() == s)
			return temp;
		else
			temp = temp->getLink();
	}
	return nullptr;
}

void LinkedList::insert_after(const NodePtr& np, const ShapePtr& s) const
{
	if (np == nullptr)
		return;
	else
	{
		NodePtr temp = new Node(s);
		temp->setLink(np->getLink());
		np->setLink(temp);
	}
}

void LinkedList::remove_node(const NodePtr&np )
{
	if(np == nullptr || head == nullptr)
		return;
	else if(np==head)
	{
		NodePtr temp = head;
		head = head->getLink();
		delete temp;
	}
	else
	{
		NodePtr temp = head;
		while(temp!= nullptr)
		{
			if(temp->getLink()==np)
			{
				NodePtr t2 = temp;
				temp->setLink(np->getLink());
				delete t2;
			}
		}
	}
}

void LinkedList::remove_node(const ShapePtr& s)
{
	NodePtr temp = this->search_node(s);
	this->remove_node(temp);
}

void LinkedList::remove_all(const ShapePtr&s)
{
	NodePtr temp;
	do
	{
		temp = this->search_node(s);
		this->remove_node(temp);
	}while(temp!=nullptr);
}

void LinkedList::tail_insert(const ShapePtr&s)
{
	if(head == nullptr)
	{
		head_insert(s);
		return;
	}
	NodePtr temp = head;
	while(temp->getLink() != nullptr)
		temp = temp->getLink();
	
	insert_after(temp, s);
}

void LinkedList::insert_before(const NodePtr& np, const ShapePtr& s)
{
	if(head == nullptr)
	{
		if(np==nullptr)
			head_insert(s);
		else 
			cout<<"\nInsertion failed."<<endl;
		return;
	}

	if(np == nullptr)
	{
		tail_insert(s);
		return;
	}

	if(np == head)
	{
		head_insert(s);
		return;
	}
	
	NodePtr temp = head;
	while(temp != nullptr)
	{
		if(temp->getLink()==np)
			break;
		temp = temp->getLink();
	}
	if(temp==nullptr)
		cout<<"\nInsertion failed."<<endl;
	else
		insert_after(temp, s);
}

void LinkedList::insert_increasing(const ShapePtr&s)
{
	NodePtr temp = head;
	while(temp != nullptr)
	{
		if(temp->getData()->getArea() >= s->getArea())
			break;
		temp = temp->getLink();
	}
	insert_before(temp, s);
}

void LinkedList::insert_grouped(const ShapePtr&s)
{
	NodePtr temp = head;
	while(temp!=nullptr)
	{
		if((temp->getData())->getType()==s->getType())
			break;
		temp = temp->getLink();
	}
	insert_before(temp, s);
}

void LinkedList::insert_grouped_increasing(const ShapePtr&s)
{
	NodePtr temp = head;
	while(temp!=nullptr)
	{
		if((temp->getData())->getType()==s->getType())
			break;
		temp = temp->getLink();
	}

	while(temp!= nullptr)
	{
		if((temp->getData())->getType()!=s->getType())
			break;
		else if(temp->getData()->getArea() >= s->getArea())
			break;
		else
			temp = temp->getLink();
	}
	insert_before(temp, s);
}


ostream& operator<< (ostream& out, const LinkedList& LL)
{
	NodePtr temp = LL.head;
	while(temp != nullptr)
	{
		out << *temp << endl;
		temp = temp->getLink();
	}
	return out;
}

ShapePtr getRandomShape()
{
	string ColorArray[] = {"Red", "White", "Green", "Yellow", "Black", "Orange", "Brown", "Grey", "Purple", "Blue"};
	int r = rand() % 4;
	switch (r)
	{
		case 0:
			return new Rectangle(rand()%5+1, rand()%5+1, ColorArray[rand()%10]);
		case 1:
			return new Triangle(rand()%5+1, rand()%5+1, ColorArray[rand()%10]);
		case 2:
			return new Circle(rand()%5+1, ColorArray[rand()%10]);
		default:
			return new Square(rand()%5+1, ColorArray[rand()%10]);
	}
}

int main()
{
	//Let us use the same seed in order to generate the same random numbers on all the lab computers
	//that use the same version of MSVC++. This way the output of this program on any of the lab
	//computers will be identical to the output provided below so long as your implementations are
	//correct.
	unsigned int seed = 5;
	srand(seed);
	const int SIZE = 20;

	//Declare a linkedlist container to store pointers to Shape objects
	LinkedList LL;

	//Print the number of objects at the beginning
	cout << "At the beginning there are " << Shape::getCount() << " objects constructed." << endl;
	cout << "And there are " << LL.getSize() << " elements in the linkedlist container." << endl << endl;
	
	///////////////////////////////////// TASK 1 ///////////////////////////////////////////////////////
	//Insert SIZE random objects into the container using head_insert member function
	cout << endl << "Inserting " << SIZE << " objects with insert_increasing member function" << endl;
	cout << "***********************************************************" << endl;
	for (int i = 0; i < SIZE; i++)
	{
		ShapePtr p = getRandomShape();
		cout << "Inserting " << endl << *p << endl;
		LL.insert_increasing(p);
	}
	//Print the number of objects constructed so far and the number of elements of the forward list
	cout << endl << "Now there are " << Shape::getCount() << " objects constructed." << endl;
	cout << "And there are " << LL.getSize() << " elements in the linkedlist container." << endl << endl;

	//Print the elements of the container
	cout << "The elements of the linkedlist container are" << endl;
	cout << LL << endl;

	//Now delete all the elements of the forward_list and also clear the forward list
	cout << endl << "Emptying the linkedlist container." << endl;
	LL.~LinkedList();
	
	//Print the number of objects we still have in our application and the number of elements in the container
	cout << "Now there are " << Shape::getCount() << " objects constructed." << endl;
	cout << "And there are " << LL.getSize() << " elements in the linkedlist container." << endl << endl;
	
	///////////////////////////////////// TASK 2 ///////////////////////////////////////////////////////
	//Insert SIZE random objects into the container using insert_grouped function
	cout << "Inserting " << SIZE << " objects with insert_grouped function" << endl;
	cout << "*************************************************" << endl;
	for (int i = 0; i < SIZE; i++)
	{
		ShapePtr p = getRandomShape();
		cout << "Inserting " << endl << *p << endl;
		LL.insert_grouped(p);
	}

	//Print the number of objects constructed so far and the number of elements of the forward list
	cout << endl << "Now there are " << Shape::getCount() << " objects constructed." << endl;
	cout << "And there are " << LL.getSize() << " elements in the linkedlist container." << endl << endl;

	//Print the elements of the container
	cout << "The elements of the linkedlist container are" << endl;
	cout << LL << endl;

	//Now delete all the elements of the forward_list also clear the forward list
	cout << endl << "Emptying the linkedlist container." << endl;
	LL.~LinkedList();
	
	//Print the number of objects we still have in our application and the number of elements in the container
	cout << "Now there are " << Shape::getCount() << " objects constructed." << endl;
	cout << "And there are " << LL.getSize() << " elements in the linkedlist container." << endl << endl;
	
	///////////////////////////////////// TASK 3 ///////////////////////////////////////////////////////
	//Insert SIZE random objects into the container using insert_grouped_sorted function
	cout << "Inserting " << SIZE << " objects with insert_grouped_increasing function" << endl;
	cout << "************************************************************" << endl;
	for (int i = 0; i < SIZE; i++)
	{
		ShapePtr p = getRandomShape();
		cout << "Inserting " << endl << *p << endl;
		LL.insert_grouped_increasing(p);
	}

	//Print the number of objects constructed so far and the number of elements of the forward list
	cout << endl << "Now there are " << Shape::getCount() << " objects constructed." << endl;
	cout << "And there are " << LL.getSize() << " elements in the linkedlist container." << endl << endl;

	//Print the elements of the container
	cout << "The elements of the linkedlist container are" << endl;
	cout << LL << endl;

	//Now delete all the elements of the forward_list also clear the forward list
	cout << endl << "Emptying the linkedlist container." << endl;
	LL.~LinkedList();
	
	//Print the number of objects we still have in our application and the number of elements in the container
	cout << "Now there are " << Shape::getCount() << " objects constructed." << endl;
	cout << "And there are " << LL.getSize() << " elements in the linkedlist container." << endl << endl;

	system("Pause");
	return 0;
}
