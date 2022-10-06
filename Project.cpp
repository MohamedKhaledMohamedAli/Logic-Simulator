//============================================================================
// Name        : Project.cpp
// Author      : Mohamed Khaled
// Description : Logic Simulator
//============================================================================

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

class Node{

	//Function prototype to overload << operator
	friend ostream& operator<<(ostream& out, const Node& node);

private:
	string name;
	bool data;
public:

	//default constructor
	Node():
		name("\0"),
		data(0){}

	//non-default constructor
	Node(string name,bool data=0):
		name(name),
		data(data){}

	//Getter to return value of private member data
	bool getdata() const{
		return data;
	}

	//Getter to return value of private member name
	string getname() const{
		return name;
	}

	//Setter to set value of private member data
	void setdata(bool value){
		data = value;
	}

	//Setter to set value of private member name
	void setname(string new_name){
		name = new_name;
	}

	//Function for AND operation between two Nodes
	bool AND(const Node& node){
		return data & node.data;
	}

	//Function for OR operation between two Nodes
	bool OR(const Node& node){
		return data | node.data;
	}

	//Function for XOR operation between two Nodes
	bool XOR(const Node& node){
		return data ^ node.data;
	}

	//overload Assignment operator
	Node& operator=(const bool& value){
		data = value;
		return *this;
	}
};

//Function prototype to overload << operator
ostream& operator<<(ostream& out, const Node& node){
	out<<node.name<<": "<<node.data<<endl;
	return out;
}

class Gate{
private:
	Node& input_1;
	Node& input_2;
	Node& output;
public:

	//default constructor
//	Gate(){}

	//default constructor
	Gate(Node& data1, Node& data2, Node& data3):
		input_1(data1),
		input_2(data2),
		output(data3){}

	//Getter to return value of first private member input_1
	Node getinput1(void) const{
		return input_1;
	}

	//Getter to return value of second private member input_2
	Node getinput2(void) const{
		return input_2;
	}

	//Getter to return value of third private member output
	Node getoutput(void) const{
		return output;
	}

	//Setter to set value of first private member input_1
	void setinput1(bool value){
		input_1 = value;
	}

	//Setter to set value of second private member input_2
	void setinput2(bool value){
		input_2 = value;
	}

	//Setter to set value of third private member output
	void setoutput(bool value){
		output = value;
	}

	//function returns the logic value of the gate according to its type
	virtual bool simulateGate(void)=0;

	//virtual destructor
	virtual ~Gate(){}
};

//AND is a Gate type
class AND : public Gate{
public:

	//default constructor
//	AND(){}

	//non-default constructor
	AND(Node& data1, Node& data2, Node& data3) : Gate(data1,data2,data3){}

	//function to perform AND operation on two input Nodes and return result to output Node
	bool simulateGate(void) override {
		setoutput(getinput1().AND(getinput2()));
		return getoutput().getdata();
	}
};

//OR is a Gate type
class OR : public Gate{
public:

	//default constructor
//	OR(){}

	//non-default constructor
	OR(Node& data1, Node& data2, Node& data3) : Gate(data1,data2,data3){}

	//function to perform OR operation on two input Nodes and return result to output Node
	bool simulateGate(void) override{
		setoutput(getinput1().OR(getinput2()));
		return getoutput().getdata();
	}
};

//NAND is a Gate type
class NAND : public Gate{
public:

	//default constructor
//	NAND(){}

	//non-default constructor
	NAND(Node& data1, Node& data2, Node& data3) : Gate(data1,data2,data3){}

	//function to perform NAND operation on two input Nodes and return result to output Node
	bool simulateGate(void) override{
		setoutput(!(getinput1().AND(getinput2())));
		return getoutput().getdata();
	}
};

//NOR is a Gate type
class NOR : public Gate{
public:

	//default constructor
//	NOR(){}

	//non-default constructor
	NOR(Node& data1, Node& data2, Node& data3) : Gate(data1,data2,data3){}

	//function to perform NOR operation on two input Nodes and return result to output Node
	bool simulateGate(void) override{
		setoutput(!(getinput1().OR(getinput2())));
		return getoutput().getdata();
	}
};

//XOR is a Gate type
class XOR : public Gate{
public:

	//default constructor
//	XOR(){}

	//non-default constructor
	XOR(Node& data1, Node& data2, Node& data3) : Gate(data1,data2,data3){}

	//function to perform XOR operation on two input Nodes and return result to output Node
	bool simulateGate(void) override{
		setoutput(getinput1().XOR(getinput2()));
		return getoutput().getdata();
	}
};

//XNOR is a Gate type
class XNOR : public Gate{
public:

	//default constructor
//	XNOR(){}

	//non-default constructor
	XNOR(Node& data1, Node& data2, Node& data3) : Gate(data1,data2,data3){}

	//function to perform XNOR operation on two input Nodes and return result to output Node
	bool simulateGate(void) override{
		setoutput(!(getinput1().XOR(getinput2())));
		return getoutput().getdata();
	}
};

//NOT is a Gate type
class NOT : public Gate{

	Node x;

public:

	//default constructor
//	NOT(){}

	//non-default constructor
	NOT(Node& data1, Node& data2) : Gate(data1,x,data2){}

	//function to perform NOT operation on input Node and return result to output Node
	bool simulateGate(void) override{
		setoutput(!(getinput1().getdata()));
		return getoutput().getdata();
	}
};

class Simulator{
private:

	//Array of pointer to Node
	vector<Node*> NodeContainer;

	//Array of pointer to Gate
	vector<Gate*> GateContainer;

	//default constructor
	// = delete since i removed the constructor so no one can call constructor outside class
	Simulator(){
	}

	//default copy constructor
	// = delete since i removed the copy constructor so no one can call copy constructor
	//outside class
	Simulator(const Simulator& other)=delete;

public:

	//Static function
	//by this method only one object can be created from class
	//by calling this function at first time i will create the one and only object of this class
	static Simulator& create_object(){
		static Simulator object;
		return object;
	}

	//Function accepts a pointer to a created Gate to insert it into the array
	void postGate(Gate* ptr){
		GateContainer.push_back(ptr); //add element to vector array
	}

	//Function accepts a pointer to a created node to insert it into the array
	void postNode(Node* ptr){
		NodeContainer.push_back(ptr); //add element to vector array
	}

	//Function accepts a string node's name to find it in the container and return its address
	Node* FindNode(const string& name){
		for (Node* i : NodeContainer) {
			if(name == i->getname())
			{
				return i;
			}
		}
		return NULL;
	}

	//Function start the simulation for each gate by looping over the gates container
	void startSimulate(){
		for (Gate* i : GateContainer) {
			i->simulateGate();
		}
	}

	//Function to print All
	void printALL(void){
		for (Node* i : NodeContainer) {
			cout<<(*(i));
		}
		for (Node* i : NodeContainer) {
			free(i);
		}
		NodeContainer.clear();
	}
};

Simulator& object = Simulator::create_object();

class GateGenerator{
public:

	//Function reads the inputs and parses each keyword ("SIM"/"OUT",..) to the appropriate logic
	void parseInput(void){
		string operand_1,operand_2,operand_3;
		string operation;
		Node*ptr_Node[3];
		bool TRUE=1;
		bool value;
		while(TRUE){
			cin>>operation;
			if(operation=="AND"){
				cin>>operand_1>>operand_2>>operand_3;
				ptr_Node[0]=object.FindNode(operand_1);
				ptr_Node[1]=object.FindNode(operand_2);
				ptr_Node[2]=object.FindNode(operand_3);
				if(ptr_Node[0]==NULL){
					ptr_Node[0]=createNode(operand_1);
					object.postNode(ptr_Node[0]);
				}
				if(ptr_Node[1]==NULL){
					ptr_Node[1]=createNode(operand_2);
					object.postNode(ptr_Node[1]);
				}
				if(ptr_Node[2]==NULL){
					ptr_Node[2]=createNode(operand_3);
					object.postNode(ptr_Node[2]);
				}
				object.postGate(createGate(operation, *ptr_Node[0], *ptr_Node[1], *ptr_Node[2]));
			}
			else if(operation=="OR"){
				cin>>operand_1>>operand_2>>operand_3;
				ptr_Node[0]=object.FindNode(operand_1);
				ptr_Node[1]=object.FindNode(operand_2);
				ptr_Node[2]=object.FindNode(operand_3);
				if(ptr_Node[0]==NULL){
					ptr_Node[0]=createNode(operand_1);
					object.postNode(ptr_Node[0]);
				}
				if(ptr_Node[1]==NULL){
					ptr_Node[1]=createNode(operand_2);
					object.postNode(ptr_Node[1]);
				}
				if(ptr_Node[2]==NULL){
					ptr_Node[2]=createNode(operand_3);
					object.postNode(ptr_Node[2]);
				}
				object.postGate(createGate(operation, *ptr_Node[0], *ptr_Node[1], *ptr_Node[2]));
			}
			else if(operation=="NAND"){
				cin>>operand_1>>operand_2>>operand_3;
				ptr_Node[0]=object.FindNode(operand_1);
				ptr_Node[1]=object.FindNode(operand_2);
				ptr_Node[2]=object.FindNode(operand_3);
				if(ptr_Node[0]==NULL){
					ptr_Node[0]=createNode(operand_1);
					object.postNode(ptr_Node[0]);
				}
				if(ptr_Node[1]==NULL){
					ptr_Node[1]=createNode(operand_2);
					object.postNode(ptr_Node[1]);
				}
				if(ptr_Node[2]==NULL){
					ptr_Node[2]=createNode(operand_3);
					object.postNode(ptr_Node[2]);
				}
				object.postGate(createGate(operation, *ptr_Node[0], *ptr_Node[1], *ptr_Node[2]));
			}
			else if(operation=="NOR"){
				cin>>operand_1>>operand_2>>operand_3;
				ptr_Node[0]=object.FindNode(operand_1);
				ptr_Node[1]=object.FindNode(operand_2);
				ptr_Node[2]=object.FindNode(operand_3);
				if(ptr_Node[0]==NULL){
					ptr_Node[0]=createNode(operand_1);
					object.postNode(ptr_Node[0]);
				}
				if(ptr_Node[1]==NULL){
					ptr_Node[1]=createNode(operand_2);
					object.postNode(ptr_Node[1]);
				}
				if(ptr_Node[2]==NULL){
					ptr_Node[2]=createNode(operand_3);
					object.postNode(ptr_Node[2]);
				}
				object.postGate(createGate(operation, *ptr_Node[0], *ptr_Node[1], *ptr_Node[2]));
			}
			else if(operation=="XOR"){
				cin>>operand_1>>operand_2>>operand_3;
				ptr_Node[0]=object.FindNode(operand_1);
				ptr_Node[1]=object.FindNode(operand_2);
				ptr_Node[2]=object.FindNode(operand_3);
				if(ptr_Node[0]==NULL){
					ptr_Node[0]=createNode(operand_1);
					object.postNode(ptr_Node[0]);
				}
				if(ptr_Node[1]==NULL){
					ptr_Node[1]=createNode(operand_2);
					object.postNode(ptr_Node[1]);
				}
				if(ptr_Node[2]==NULL){
					ptr_Node[2]=createNode(operand_3);
					object.postNode(ptr_Node[2]);
				}
				object.postGate(createGate(operation, *ptr_Node[0], *ptr_Node[1], *ptr_Node[2]));
			}
			else if(operation=="XNOR"){
				cin>>operand_1>>operand_2>>operand_3;
				ptr_Node[0]=object.FindNode(operand_1);
				ptr_Node[1]=object.FindNode(operand_2);
				ptr_Node[2]=object.FindNode(operand_3);
				if(ptr_Node[0]==NULL){
					ptr_Node[0]=createNode(operand_1);
					object.postNode(ptr_Node[0]);
				}
				if(ptr_Node[1]==NULL){
					ptr_Node[1]=createNode(operand_2);
					object.postNode(ptr_Node[1]);
				}
				if(ptr_Node[2]==NULL){
					ptr_Node[2]=createNode(operand_3);
					object.postNode(ptr_Node[2]);
				}
				object.postGate(createGate(operation, *ptr_Node[0], *ptr_Node[1], *ptr_Node[2]));
			}
			else if(operation=="NOT"){
				Node x;
				cin>>operand_1>>operand_2;
				ptr_Node[0]=object.FindNode(operand_1);
				ptr_Node[1]=object.FindNode(operand_2);
				ptr_Node[2]=&x;
				if(ptr_Node[0]==NULL){
					ptr_Node[0]=createNode(operand_1);
					object.postNode(ptr_Node[0]);
				}
				if(ptr_Node[1]==NULL){
					ptr_Node[1]=createNode(operand_2);
					object.postNode(ptr_Node[1]);
				}
				object.postGate(createGate(operation, *ptr_Node[0], *ptr_Node[1], *ptr_Node[2]));
			}
			else if(operation=="SET"){
				cin>>operand_1>>value;
				ptr_Node[0]=object.FindNode(operand_1);
				if(ptr_Node[0]==NULL){
					ptr_Node[0]=createNode(operand_1);
					object.postNode(ptr_Node[0]);
				}
				ptr_Node[0]->setdata(value);
			}
			else if(operation=="SIM"){
				object.startSimulate();
			}
			else if(operation=="OUT"){
				cin>>operand_1;
				if(operand_1!="ALL"){
					ptr_Node[0]=object.FindNode(operand_1);
					cout<<(*(ptr_Node[0]));
				}
				else{
					object.printALL();
					TRUE=0;
				}
			}
		}
	}

	//Function creates a node and return its address
	Node* createNode(string name){
		return new Node(name);
	}

	//Function creates a (AND,OR,...) gates according to the input and return its address
	Gate* createGate(string ID,Node& opr1,Node& opr2,Node& opr3){
		Gate * ptr;
		if(ID=="AND")
			ptr = new AND(opr1,opr2,opr3);
		else if(ID=="OR")
			ptr = new OR(opr1,opr2,opr3);
		else if(ID=="NAND")
			ptr = new NAND(opr1,opr2,opr3);
		else if(ID=="NOR")
			ptr = new NOR(opr1,opr2,opr3);
		else if(ID=="XOR")
			ptr = new XOR(opr1,opr2,opr3);
		else if(ID=="XNOR")
			ptr = new XNOR(opr1,opr2,opr3);
		else if(ID=="NOT")
			ptr = new NOT(opr1,opr2);
		return ptr;
	}
};

int main() {
	GateGenerator obj;

	obj.parseInput();

	return 0;
}
