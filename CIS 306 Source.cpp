/*
*Author: Ethan Puschell
*Creation Date: 4-17-20
*Modification Date: 4-18-20
*Purpose: Program solves the water jug lemma, with 2 jugs of differing volumes, if you can create a volume z that is different than both of their volumes and is less than the larger jug.
*/
#include<iostream>
using namespace std;

class Jug											//Jug Abstract Data Type that will be implemented as a class.
{
private:
	int volume;										//The volume and capacity of Jug are declared as private data members.
	int capacity;
public:
	Jug(int c) : capacity(c), volume(0)				//Constructor for Jug that allows the capacity to be declared along with the Jug. Volume is set to 0.
	{
		//cout << "\n\tConstructor called\n";
	}
	const int getVolume() { return volume; }			//Getter functions for volume and capacity that return the private data class members.
	const int getCapacity() { return capacity; }

	/*
	Precondition: The measurement to increase the Jug volume with.
	Postcondition: The Jug's volume is increased by the fill or up to its capacity.
	Description: Function fills the Jug's capacity up to the integer fill or up to its capacity.
	*/
	void setVolume(int& fill)
	{
		if (fill + volume >= capacity)		//If the fill and the current volume of the jug exceeds the capacity of the Jug.
			volume = capacity;				//The volume is set equal to the Jug's capacity.
		else
			volume += fill;					//Else, the volume is set equal to the volume plus the fill.
	}

	/*
	Precondition: The amount to be decreased from volume.
	Postcondition: The Jug volume is decreased by the spill integer, or the volume is set to 0.
	Description: Function pours out the volume of Jug, down to 0.
	*/
	void pourOut(int& spill)
	{
		if (spill >= volume)		//If the amount to be spilled is greater than or equal to the Jug's volume
			volume = 0;				//Then the volume is set equal to 0.
		else
			volume -= spill;		//Else, the volume is updated to the volume minus spill.
	}

	/*
	Precondition: The integer capacity for Jug.
	Postcondition: The Jug's capacity data member is set.
	Description: Setter function for capacity.
	*/
	void setCapacity(int& newCapacity)
	{
		newCapacity = capacity;		//The capacity is set to newCapacity.
	}

	/*
	Precondition: None.
	Postcondition: Jug volume equal to capacity.
	Description: Fills the jug up to its capacity.
	*/
	void fillJug()
	{
		volume = capacity;
	}

	/*
	Precondition: None.
	Postcondition: Volume equal to 0.
	Description: Pours out jugs volume.
	*/
	void emptyJug()
	{
		volume = 0;
	}

	/*
	Precondition: None.
	Postcondition: None.
	Description: Checks if the Jug is completely full.
	*/
	bool isFull()
	{
		if (capacity == volume)		//If the Jug capacity equals the volume.
			return true;			//Function returns true.
		else
			return false;			//Function returns false if Jug capacity does not equal the volume.
	}

	/*
	Precondition: None.
	Postcondition : None.
	Description : Checks if the Jug is empty.
	*/
	bool isEmpty()
	{
		if (volume == 0)		//If the jug's volume is equal to zero.
			return true;		//Function returns true.
		else
			return false;		//Function returns false if Jug volume is not equal to zero.
	}

	~Jug()		//Destructor for Jug.
	{
		//cout << "\n\tDestructor called for " << capacity << " capacity Jug.\n";
	}
};

/*
Precondition: 2 integers a and b.
Postcondition: The greatest common divisor of a and b
Description: Function computes the greatest common divisor of a and b.
*/
int gcd(int a, int b)
{
	while (a != b)		//While loop that will iterate until a and b are the same integer.
	{
		if (a > b)		//If a is greater than b
			a -= b;		//Then a is set equal to a minus b.
		else
			b -= a;		//Else, if a is less than b, then b is set equal to b minus a.
	}
	return a;			//After the while loop is done iterating, the integer a (which will be the greatest common divisor) is returned.
}

/*
Precondition: 2 jugs of a specified capacity and a target integer.
Postcondition: None.
Description: Function validates if the 2 jugs and target provided can be used to solve the water jug problem.
*/
bool validateJugs(Jug x, Jug y, int target)
{
	if (target <= 0)
	{
		cerr << "Error: target cannot be less than or equal to 0." << endl;					//If the target is less than or equal to zero, the function returns false.
		return false;
	}
	if (x.getCapacity() <= 0 || y.getCapacity() <= 0)										//If the capacity of jugs x or y are less than or equal to 0, the function returns false.
	{
		cerr << "Error: jugs cannot have a capacity less than or equal to 0." << endl;
		return false;
	}
	if (x.getCapacity() == y.getCapacity())													//If the capacity of both jugs are the same, the function returns false.
	{
		cerr << "Error: jugs cannot have equal capacities." << endl;
		return false;
	}

	int xCap = x.getCapacity(), yCap = y.getCapacity();										//Integer representations for the capacities of the 2 jugs.
	if (target % gcd(xCap, yCap) == 0)														//If the greatest common divisor of x and y's capacities is a divisor for the target, then the water jug problem can be solved.
		return true;
	else
	{																						//Otherwise, the function returns false.
		cerr << "Water jug problem impossible to solve with given jug capacities " << x.getCapacity() << " and " << y.getCapacity() << "." << endl;
		return false;
	}
}

/*
Precondition: 2 Jugs and the target.
Postcondition: Returns the number of steps taken from the water jug problem.
Description: Function performs the water jug problem.
*/
int lemma(Jug&x, Jug&y, int target)
{
	if (!validateJugs(x, y, target))		//First checks if the water jug problem is possible to compute given the jug capacities and target volume.
	{
		return 0;							//If not, function returns 0, it never performed a single step.
	}
	int count = 0, xVol, drainage;									//Else, integer count, xVol, and drainage are declared outside of the while loop to save on space complexity.
	while (x.getVolume() != target || y.getVolume() != target)		//While the volume of x does not equal the target or if the volume of y does not equal the target.
	{
		if (x.isEmpty())											//If Jug x is empty.
		{
			x.fillJug();											//Fill Jug x up to its capacity.
			count++;												//This is a step, so increment the count.
		}
		xVol = x.getVolume();										//The volume of x is set as an integer so that it can be taken in by the setVolume function.
		drainage = y.getCapacity() - y.getVolume();					//The drainage is set equal to the difference of Jug y capacity and Jug y volume.
		y.setVolume(xVol);											//Jug x is poured into Jug y.
		x.pourOut(drainage);										//Pour out from Jug x what was poured into Jug y.
		count++;													//This was a step, so increment the count.
		if (x.getVolume() == target || y.getVolume() == target)		//If either Jug x or Jug y is equal to the target.
			break;													//Exit while loop.
		if (y.isFull())												//If Jug y is full, then pour it out.
		{
			y.emptyJug();
			count++;												//This was a step, so increment the count.
		}
	}
	x.emptyJug();													//After the while loop finishes, pour out Jug x and Jug y.
	y.emptyJug();													//This is so that the Jugs are not returned still containing water.
	return count;													//Count is returned to the bestMethod function.
}

/*
Precondition: 2 jugs and target volume.
Postcondition: Printed output of the steps taken.
Description: Function outputs the volumes of Jug x and Jug y during the computation of the Water Jug problem.
*/
void printLemma(Jug&x, Jug&y, int target)
{																	//This function acts the exact same way as lemma, with the only difference is instead of incrementing the count
	int xVol, drainage;												//It prints out the volumes of Jug x and y at each step taken.
	cout << "(" << x.getVolume() << "," << y.getVolume() << ")";
	while (x.getVolume() != target || y.getVolume() != target)
	{
		cout << "->";
		if (x.isEmpty())
		{
			x.fillJug();
			cout << "(" << x.getVolume() << "," << y.getVolume() << ")->";
		}
		xVol = x.getVolume();
		drainage = y.getCapacity() - y.getVolume();
		y.setVolume(xVol);
		x.pourOut(drainage);
		cout << "(" << x.getVolume() << "," << y.getVolume() << ")";
		if (x.getVolume() == target || y.getVolume() == target)
			break;
		if (y.isFull())
		{
			y.emptyJug();
			cout << "->(" << x.getVolume() << "," << y.getVolume() << ")";
		}
	}
	cout << endl << endl;
}

/*
Precondition: 2 Jugs and target volume.
Postcondition: None.
Description: Function compares 2 water jug problems and shows the user which one is most efficient.
*/
void bestMethod(Jug& x, Jug& y, int target)
{
	if (validateJugs(x, y, target) == 0)								//Function checks if the water jug problem is solvable given the capacities and target volume.
		return;															//If it is not solvable, function simply exits.
	int method1 = lemma(x, y, target), method2 = lemma(y, x, target);	//2 integers are declared that represent the number of steps taken for each version of the water jug problem that are 
																		//computed. One that uses Jug x to fill and pour into y, and the other that uses Jug y to fill and pour into x.
	if (method1 < method2)												//If the first method was more efficient than the second method
	{																	//Computer lets user know which water jug problem was most efficient with how many steps.
		cout << "Water jug problem was solved in a minimum of " << method1 << " steps. (" << x.getCapacity() << " jug, " << y.getCapacity() << " jug)" << endl;
		printLemma(x, y, target);										//Function call to print out the steps for the x into y jug problem.
	}
	else if (method1 > method2)											//If the second method was more efficient than the first method.
	{																	//Computer lets user know which water jug problem was most efficient with how many steps.
		cout << "Water jug problem was solved in a minimum of " << method2 << " steps. (" << y.getCapacity() << " jug, " << x.getCapacity() << " jug)" << endl;
		printLemma(y, x, target);										//Function call to print out the steps for the y into x jug problem.
	}
	else if (method1 == method2)										//If both methods are equally efficient, then function tells user that the water jug problem can be solved in 2 different ways
	{																	//Prints out both methods and steps.
		cout << "Water jug problem was solved in a minimum of " << method1 << "steps and can be solved in 2 different ways: " << endl;
		cout << "Method 1: (" << x.getCapacity() << " jug, " << y.getCapacity() << " jug)" << endl;
		printLemma(x, y, target);
		cout << "Method 2: (" << y.getCapacity() << " jug, " << x.getCapacity() << " jug)" << endl;
		printLemma(y, x, target);
	}
	else
		cerr << "Error" << endl;
}

int main()
{
	Jug A(3), B(5);			
	bestMethod(A, B, 4);	//TEST CASE 1: A 3-Jug and 5-Jug to find a Volume 4. Test should pass.

	Jug C(21), D(26);		
	bestMethod(C, D, 2);	//TEST CASE 2: A 21-Jug and 26-Jug to find Volume 2. Test should pass.

	Jug E(899), F(1147);	
	bestMethod(E, F, 2);	//TEST CASE 3: A 899-Jug and 1147-Jug to find Volume 2. Test should fail.

	Jug G(3), H(6);			
	bestMethod(G, H, 4);	//TEST CASE 4: A 3-Jug and 6-Jug to find Volume 4. Test shoudl fail.

	Jug I(0), J(-1);
	bestMethod(I, J, 4);	//TEST CASE 5: A 0-Jug and -1-Jug to find Volume 4. Test should fail.
	bestMethod(A, I, 2);	//TEST CASE 6: A 3-Jug and 0-Jug to find Volume 2. Test should fail.
	bestMethod(A, B, 0);	//TEST CASE 7: A 3-Jug and 5-Jug to find Volume 0. Test should fail.
	bestMethod(A, B, -1);	//TEST CASE 8: A 3-Jug and 5-Jug to find Volume -1. Test should fail.
	bestMethod(A, A, 2);	//TEST CASE 9: A 3-Jug and 3-Jug to find Volume 2. Test should fail.

	system("pause");
	return 0;
}