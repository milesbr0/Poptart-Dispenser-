#include <vector> //only to be used to contain dispenser states and nothing else
#include <iostream>
#include <string>

using namespace std;

//state index enumerations
enum state { Out_Of_Poptarts, No_Credit, Has_Credit, Dispenses_Poptart };

//state parameter index enumerations
enum stateParameter { No_Of_Poptarts, Credit, Cost_Of_Poptart };

//Forward class declaration so the State class is able to use it.
class StateContext; 

//Abstract 'State' superclass
class State{
protected:
	StateContext* CurrentContext;
public:
	State(StateContext* Context) { CurrentContext = Context; } //sets the current context for handling states
	virtual ~State(void) {	}
};

//Abstract 'StateContext' superclass
class StateContext {
protected:
	State* CurrentState = nullptr; //pointer to manage the current state
	int stateIndex = 0;
	vector<State*> availableStates;
	vector<int> stateParameters;
public:
	//The destructor deletes the pointers and clears the vectors.
	virtual ~StateContext() {
		for (int index = 0; index < this->availableStates.size(); index++) delete this->availableStates[index];
		this->availableStates.clear();
		this->stateParameters.clear();
	}
	
	//if transition returns true CurrentState will change
	virtual void setState(state newState) { 
		this->CurrentState = availableStates[newState]; 
		this->stateIndex = newState; 
	}
	
	virtual int getStateIndex(void) { return this->stateIndex; } //returns current state's index 
	virtual void setStateParam(stateParameter SP, int value) { this->stateParameters[SP] = value; } //overwrites stateparameter with value
	virtual int getStateParam(stateParameter SP) { return this->stateParameters[SP]; } //returns stateparameter's value
};

//Transition interface with default error messages
class Transition{
public:
	virtual bool insertMoney(int) { cout << "Error!" << endl; return false; }
	virtual bool makeSelection(int) { cout << "Error!" << endl; return false; }
	virtual bool moneyRejected(void) { cout << "Error!" << endl; return false; }
	virtual bool addPoptart(int) { cout << "Error!" << endl; return false; }
	virtual bool dispense(void) { cout << "Error!" << endl; return false; }
};

#pragma region PoptartState Classes
//Abstract 'PopTartState' class
class PoptartState : public State, public Transition {
public:
	PoptartState(StateContext* CurrentContext) : State(CurrentContext) {}
};
class OutOfPoptarts : public PoptartState{
public:
	OutOfPoptarts(StateContext* CurrentContext) : PoptartState(CurrentContext) {}
	bool insertMoney(int);
	bool makeSelection(int);
	bool moneyRejected(void);
	bool addPoptart(int);
	bool dispense(void);
};
class NoCredit : public PoptartState{
public:
	NoCredit(StateContext* CurrentContext) : PoptartState(CurrentContext) {}
	bool insertMoney(int);
	bool makeSelection(int);
	bool moneyRejected(void);
	bool addPoptart(int);
	bool dispense(void);
};
class HasCredit : public PoptartState{
public:
	HasCredit(StateContext* CurrentContext) : PoptartState(CurrentContext) {}
	bool insertMoney(int);
	bool makeSelection(int);
	bool moneyRejected(void);
	bool addPoptart(int);
	bool dispense(void);
};
class DispensesPoptart : public PoptartState{
public:
	DispensesPoptart(StateContext* CurrentContext) : PoptartState(CurrentContext) {}
	bool insertMoney(int);
	bool makeSelection(int);
	bool moneyRejected(void);
	bool addPoptart(int);
	bool dispense(void);
};
#pragma endregion

#pragma region Product Classes
//Product interface
class Product{
protected:
	string product_description = "";
	int itemCost = 0;
public:
	//delete Product after 'consuming'
	virtual void consume(void){
		cout << "Consuming..." << endl;
		delete this;
	}
	virtual int cost(void) { return this->itemCost; }
	virtual string description(void) { return this->product_description; }
	virtual Product* ReturnHighestCostItem(void) { return nullptr; }
};
class Base : public Product
{ 
};

//Different flavoured bases
//Assign default values in constructors:
class Plain : public Base{
public:
	Plain(void){
		this->product_description = "Plain base";
		this->itemCost = 100;
	}
};
class Spicy : public Base{
public:
	Spicy(void){
		this->product_description = "Spicy base";
		this->itemCost = 150;
	}
};
class Chocolate : public Base{
public:
	Chocolate(void){
		this->product_description = "Chocolate base";
		this->itemCost = 150;
	}
};
class Coconut : public Base{
public:
	Coconut(void){
		this->product_description = "Coconut base";
		this->itemCost = 200;
	}
};
class Fruity : public Base{
public:
	Fruity(void){
		this->product_description = "Fruity base";
		this->itemCost = 200;
	}
};

//Filling interface
class Filling : public Product{
protected:
	Product* product; //pointer to existing product
public:
	virtual void fillProduct(Product* NewBase); //assigning existing product
	virtual int cost(void);
	virtual string description(void);
	Product* ReturnHighestCostItem(void) 
	{ 
		//Termination_Criteria

		//Do_something

		//Call Recursive_algorithm(next_item)
		return nullptr; 
	}
	~Filling(void);
};
void Filling::fillProduct(Product *NewBase) { product = NewBase; }
int Filling::cost(void) { return this->itemCost; }

//returns existing product(s)' description + added filling's description
string Filling::description(void) { return product->description() + " + " + this->product_description; }

Filling::~Filling() { delete product; } // deletes pointer to Product

//Different flavoured fillings
//Assign default values in constructors:
class Chocolate_filling : public Filling {
public:
	Chocolate_filling(){
		itemCost = 20;
		product_description = "Chocolate Filling";
	}
};
class Banana : public Filling {
public:
	Banana() {
		itemCost = 50;
		product_description = "Banana Filling";
	}
};
class Strawberry : public Filling {
public:
	Strawberry() {
		itemCost = 50;
		product_description = "Strawberry Filling";
	}
};
class Raspberry : public Filling {
public:
	Raspberry() {
		itemCost = 50;
		product_description = "Raspberry Filling";
	}
};
class Apple : public Filling {
public:
	Apple() {
		itemCost = 50;
		product_description = "Apple Filling";
	}
};
class Blackberry : public Filling {
public:
	Blackberry() {
		itemCost = 50;
		product_description = "BlackBerry Filling";
	}
};
class Maple : public Filling {
public:
	Maple() {
		itemCost = 100;
		product_description = "Maple Filling";
	}
};
class Marshmallow : public Filling {
public:
	Marshmallow() {
		itemCost = 20;
		product_description = "Marshmallow Filling";
	}
};
class Cheese : public Filling {
public:
	Cheese() {
		itemCost = 70;
		product_description = "Cheese Filling";
	}
};
class Cheese_and_ham : public Filling {
public:
	Cheese_and_ham() {
		itemCost = 100;
		product_description = "Cheese and ham Filling";
	}
};
class Caramel : public Filling {
public:
	Caramel() {
		itemCost = 20;
		product_description = "Caramel Filling";
	}
};
class Vanilla : public Filling {
public:
	Vanilla() {
		itemCost = 50;
		product_description = "Vanilla Filling";
	}
};
#pragma endregion

#pragma region Poptart_Dispenser
class Poptart_Dispenser : public StateContext, public Transition{
	//friend classes so DispensesPoptart and HasCredit states 
	//can access the protected DispensedItem Product pointer and itemDispensed boolean
	friend class DispensesPoptart; 
	friend class HasCredit;
protected:
	PoptartState* currentPoptartState = nullptr; //pointer to current poptart state
	Product* DispensedItem = nullptr; //pointer to the dispensed poptart
	Filling* filling = nullptr; //pointer to the filling
	bool itemDispensed = false; //boolean to determine whether the prouct has been dispensed and ready to be retrieved
	bool itemRetrieved = false; //boolean to determine whether the product has been retrieved
public:
	Poptart_Dispenser(int inventory_count);
	~Poptart_Dispenser(void);
	bool insertMoney(int money);
	bool makeSelection(int option);
	bool moneyRejected(void);
	bool addPoptart(int number);
	bool dispense(void);
	Product* getProduct(void);
	virtual void setStateParam(stateParameter SP, int value);
	virtual int getStateParam(stateParameter SP);
};
Poptart_Dispenser::Poptart_Dispenser(int inventory_count) {

	//fill avilableStates vector with sensible data
	this->availableStates.push_back(new OutOfPoptarts(this));
	this->availableStates.push_back(new NoCredit(this));
	this->availableStates.push_back(new HasCredit(this));
	this->availableStates.push_back(new DispensesPoptart(this));

	//fill setParameters vector with sensible data
	this->stateParameters.push_back(0); //Number of Chocolates
	this->stateParameters.push_back(0); //Available Credit
	this->stateParameters.push_back(0); //Cost of poptart
	
	this->setState(Out_Of_Poptarts); //set starting state as defined in the state diagram

	//if passed in argument value is greater than 0, it adds that many poptarts to the vending machine
	if (inventory_count > 0) this->addPoptart(inventory_count); 
}
Poptart_Dispenser::~Poptart_Dispenser(void){

	//deletes product pointer
	if (!this->itemRetrieved) delete this->DispensedItem;

	//clears up vectors
	for (int index = 0; index < this->availableStates.size(); index++) delete this->availableStates[index];
	this->availableStates.clear();
	this->stateParameters.clear();
}

//Member functions that call transition methods in the given context
bool Poptart_Dispenser::insertMoney(int money){
	currentPoptartState = (PoptartState*)this->CurrentState;
	currentPoptartState->insertMoney(money);
	return true;
}
bool Poptart_Dispenser::moneyRejected(void){
	currentPoptartState = (PoptartState*)this->CurrentState;
	currentPoptartState->moneyRejected();
	return true;
}
bool Poptart_Dispenser::makeSelection(int option){
	currentPoptartState = (PoptartState*)this->CurrentState;
	currentPoptartState->makeSelection(option);
	return true;
}
bool Poptart_Dispenser::addPoptart(int number){
	currentPoptartState = (PoptartState*)this->CurrentState;
	currentPoptartState->addPoptart(number);
	return true;
}
bool Poptart_Dispenser::dispense(void) {
	currentPoptartState = (PoptartState*)this->CurrentState;
	currentPoptartState->dispense();
	return true;
}
Product* Poptart_Dispenser::getProduct(void) {
	//when item is ready to be retrieved (is dispensed)
	if (this->itemDispensed){
		this->itemDispensed = false; //reset boolean so other poptarts can be dispensed
		this->itemRetrieved = true; //retrieve product
		return this->DispensedItem; //return product
	}
	return nullptr; //else return null pointer
}
void Poptart_Dispenser::setStateParam(stateParameter SP, int value) {
	//doesn't let poptart dispenser to change the cost of poptart since it is determined by the poptart and the filling(s)
	if (SP == Cost_Of_Poptart) return; 
	//else sets stateparameter to value
	else this->stateParameters[SP] = value; 
}
int Poptart_Dispenser::getStateParam(stateParameter SP) {
	if (SP == Cost_Of_Poptart){ //need to make different behaviour when makeselection tries to access the cost of the product 
		if (DispensedItem == nullptr) return 0; //when there is no product dispensed it returns 0;
		return DispensedItem->cost();
	}
	return this->stateParameters[SP];
}
#pragma endregion

#pragma region PoptartStateMembersFunctions
bool OutOfPoptarts::moneyRejected(void) {
	cout << "Money rejected!" << endl;
	this->CurrentContext->setStateParam(Credit, 0); //explicit transition not really needed, but included to improve clarity
	this->CurrentContext->setState(Out_Of_Poptarts); //set state based on state diagram
	return true;
}
bool OutOfPoptarts::addPoptart(int poptart) {
	cout << "Adding " << poptart << " poptart..." << endl;
	this->CurrentContext->setStateParam(No_Of_Poptarts, poptart); //set No_Of_Poptarts to passed in value
	this->CurrentContext->setState(No_Credit); //set state based on state diagram
	return true;
}
bool OutOfPoptarts::dispense(void) {
	cout << "Error: Out of Poptarts... Can't dispense." << endl;
	return false;
}
bool OutOfPoptarts::makeSelection(int) {
	cout << "Error! No Poptarts Left! No Selection Made!" << endl;
	return false;
}
bool OutOfPoptarts::insertMoney(int) {
	cout << "Error: Out of Poptarts... Can't insert money." << endl;
	return false;
}

bool NoCredit::insertMoney(int money) {
	cout << "Insterting " << money << " money..." << endl;
	this->CurrentContext->setStateParam(Credit, this->CurrentContext->getStateParam(Credit) + money);//increment Credit by passed in value 
	this->CurrentContext->setState(Has_Credit);//set state based on state diagram
	return true;
}
bool NoCredit::makeSelection(int option) {
	cout << "Error: No Credit... Can't make selection." << endl;
	return false;
}
bool NoCredit::moneyRejected(void) {
	cout << "Error: No Credit... Can't make selection." << endl;
	return false;
}
bool NoCredit::addPoptart(int) {
	cout << "Error: No Credit... Can't add poptart." << endl;
	return false;
}
bool NoCredit::dispense(void) {
	cout << "Error: No Credit... Can't dispense." << endl;
	return false;
}

bool HasCredit::insertMoney(int money)
{
	cout << "Insterting " << money << " money..." << endl;
	this->CurrentContext->setStateParam(Credit, this->CurrentContext->getStateParam(Credit) + money); //increment money by passed in value
	this->CurrentContext->setState(Has_Credit); //set state to has_credit as user has inserted credit
	return true;
}
bool HasCredit::moneyRejected(void)
{
	cout << "Money rejected..." << endl;
	this->CurrentContext->setStateParam(Credit, 0);
	this->CurrentContext->setState(No_Credit);
	return true;
}
bool HasCredit::makeSelection(int selection) {
	//if there was no product dispensed so far you can select one base
	if (!((Poptart_Dispenser*)(this->CurrentContext))->itemDispensed){
		switch (selection){
		default:
			return false;
		case 1:{
			((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem = new Plain();
			break;
		}
		case 2: {
			((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem = new Spicy();
			break;
		}
		case 4: {
			((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem = new Chocolate();
			break;
		}
		case 8: {
			((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem = new Coconut();
			break;
		}
		case 16: {
			((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem = new Fruity();
			break;
		}
		}
	}

	//if there was a product dispensed already you can add multiple fillings
	else if (((Poptart_Dispenser*)(this->CurrentContext))->itemDispensed) {
		switch (selection) {
		default:
			return false;
		case 32:{
			((Poptart_Dispenser*)(this->CurrentContext))->filling = new Chocolate_filling();
			((Poptart_Dispenser*)(this->CurrentContext))->filling->fillProduct(((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem);
			((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem = ((Poptart_Dispenser*)(this->CurrentContext))->filling;
			break;
		}
		case 64:{
			((Poptart_Dispenser*)(this->CurrentContext))->filling = new Banana();
			((Poptart_Dispenser*)(this->CurrentContext))->filling->fillProduct(((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem);
			((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem = ((Poptart_Dispenser*)(this->CurrentContext))->filling;
			break;
		}
		case 128:{
			((Poptart_Dispenser*)(this->CurrentContext))->filling = new Strawberry();
			((Poptart_Dispenser*)(this->CurrentContext))->filling->fillProduct(((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem);
			((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem = ((Poptart_Dispenser*)(this->CurrentContext))->filling;
			break;
		}
		case 256:{
			((Poptart_Dispenser*)(this->CurrentContext))->filling = new Raspberry();
			((Poptart_Dispenser*)(this->CurrentContext))->filling->fillProduct(((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem);
			((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem = ((Poptart_Dispenser*)(this->CurrentContext))->filling;
			break;
		}
		case 512:{
			((Poptart_Dispenser*)(this->CurrentContext))->filling = new Apple();
			((Poptart_Dispenser*)(this->CurrentContext))->filling->fillProduct(((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem);
			((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem = ((Poptart_Dispenser*)(this->CurrentContext))->filling;
			break;
		}
		case 1024: {
			((Poptart_Dispenser*)(this->CurrentContext))->filling = new Blackberry();
			((Poptart_Dispenser*)(this->CurrentContext))->filling->fillProduct(((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem);
			((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem = ((Poptart_Dispenser*)(this->CurrentContext))->filling;
			break;
		}
		case 2048: {
			((Poptart_Dispenser*)(this->CurrentContext))->filling = new Maple();
			((Poptart_Dispenser*)(this->CurrentContext))->filling->fillProduct(((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem);
			((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem = ((Poptart_Dispenser*)(this->CurrentContext))->filling;
			break;
		}
		case 4096: {
			((Poptart_Dispenser*)(this->CurrentContext))->filling = new Marshmallow();
			((Poptart_Dispenser*)(this->CurrentContext))->filling->fillProduct(((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem);
			((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem = ((Poptart_Dispenser*)(this->CurrentContext))->filling;
			break;
		}
		case 8192: {
			((Poptart_Dispenser*)(this->CurrentContext))->filling = new Cheese();
			((Poptart_Dispenser*)(this->CurrentContext))->filling->fillProduct(((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem);
			((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem = ((Poptart_Dispenser*)(this->CurrentContext))->filling;
			break;
		}
		case 16384: {
			((Poptart_Dispenser*)(this->CurrentContext))->filling = new Cheese_and_ham();
			((Poptart_Dispenser*)(this->CurrentContext))->filling->fillProduct(((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem);
			((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem = ((Poptart_Dispenser*)(this->CurrentContext))->filling;
			break;
		}
		case 32768: {
			((Poptart_Dispenser*)(this->CurrentContext))->filling = new Caramel();
			((Poptart_Dispenser*)(this->CurrentContext))->filling->fillProduct(((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem);
			((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem = ((Poptart_Dispenser*)(this->CurrentContext))->filling;
			break;
		}
		case 65536: {
			((Poptart_Dispenser*)(this->CurrentContext))->filling = new Vanilla();
			((Poptart_Dispenser*)(this->CurrentContext))->filling->fillProduct(((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem);
			((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem = ((Poptart_Dispenser*)(this->CurrentContext))->filling;
			break;
		}
		}
	}
	
	cout << "You have selected " << selection << endl;

	//set the Cost of Poptart to current item cost
	this->CurrentContext->setStateParam(Cost_Of_Poptart, ((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem->cost());

	//if item is out of budget return false
	if (this->CurrentContext->getStateParam(Credit) - this->CurrentContext->getStateParam(Cost_Of_Poptart) < 0)
		return false;

	//take away the poptart cost from available credit
	this->CurrentContext->setStateParam(Credit, this->CurrentContext->getStateParam(Credit) - this->CurrentContext->getStateParam(Cost_Of_Poptart));

	cout << "You have : " << this->CurrentContext->getStateParam(Credit) << " left." << endl;

	//set state to dispenses_poptart as the user is finished with selection
	this->CurrentContext->setState(Dispenses_Poptart);

	this->CurrentContext->setStateParam(No_Of_Poptarts, this->CurrentContext->getStateParam(No_Of_Poptarts) - 1); //decrement inventory count
	return true;
}
bool HasCredit::addPoptart(int) {
	cout << "Error: Can't add poptart now." << endl;
	return false;
}
bool HasCredit::dispense(void) {
	cout << "Error: Can't dispense poptart now." << endl;
	return false;
}

bool DispensesPoptart::dispense(void) {
	cout << "Dispensing " << ((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem->description() << endl;
	if (this->CurrentContext->getStateParam(No_Of_Poptarts) == 0) {
		cout << "Out of poptarts..." << endl;
		this->CurrentContext->setState(Out_Of_Poptarts);
	}
	else if (this->CurrentContext->getStateParam(No_Of_Poptarts) > 0 && this->CurrentContext->getStateParam(Credit) > 0) {
		cout << "You still have credit left, you can make another selection: " << endl;
		this->CurrentContext->setState(Has_Credit);
	}
	else if (this->CurrentContext->getStateParam(No_Of_Poptarts) > 0 && this->CurrentContext->getStateParam(Credit) == 0) {
		cout << "Dispensing poptart..." << endl;
		this->CurrentContext->setState(No_Credit);
		((Poptart_Dispenser*)(this->CurrentContext))->DispensedItem->consume();
	}


	//Tells the dispenser that the product has been dispensed so that GetProduct can function correctly
	((Poptart_Dispenser*)(this->CurrentContext))->itemDispensed = true;

	return true;
}
bool DispensesPoptart::addPoptart(int) {
	cout << "Error: Can't add poptart now." << endl;
	return false;
}
bool DispensesPoptart::makeSelection(int) {
	cout << "Error: Can't make selection now." << endl;
	return false;
}
bool DispensesPoptart::insertMoney(int) {
	cout << "Error: Can't insert money now." << endl;
	return false;
}
bool DispensesPoptart::moneyRejected(void) {
	cout << "Error: Can't reject money now." << endl;
	return false;
}

#pragma endregion