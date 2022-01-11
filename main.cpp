/*
* File: main.cpp
* Brief description: Main source
* Details: Simple CContainer example of usage
* Authors: Petyovsky 2021, modified Richter and Bezecny 2021
*/

#include <ctime>
#include <iostream>
#include <stdexcept>
#include <typeinfo>
#include <type_traits>		// Due to: std::is_same_v<>

#include "demagle.h"
#include "CEntity.h"
#include "CSet.h"
#include "check.h"

using std::endl;
using std::cout;
using std::cin;
using std::cerr;

int main(int argc, char *argv[])
	{
#ifdef NDEBUG
	std::srand(unsigned(std::time(nullptr)));	// Initialize random generator by actual time
#else
	std::srand(unsigned(42));					// Initialize random generator by fixed value useful for debugging
#endif

	cout << "Number of parameters: " << argc << endl;
	for(int i = 0; i < argc; i++)
		cout << "Parametr #" << i << ": " << argv[i] << endl;
	
	cout << endl << "Now exists " << ClassInfo<CEntity>::Living() << " class instances: " << DM(typeid(CEntity).name()) << endl;
	cout << "Size of one instance " << DM(typeid(CEntity).name()) << " is: " << sizeof(CEntity) << " bytes." << endl;

	try
		{
		cout << "Now exists " << ClassInfo<CEntity>::Living() << " instances of class: " << DM(typeid(CEntity).name()) << endl;

		{
			cout << "------------------Autor1 Tests------------------" << endl;
			// Implicit c'tor
			CSet SetA;
			//  Copy C'tor
			CSet SetB(SetA);
			// != and == operator tests
			cout << "Sets aren't same length " << (SetA != SetB) << endl;
			cout << "Are sets same length? " << (SetA == SetB) << endl;
			// << and = operator test
			SetA = CSet(CEntity::TestStringSet1().c_str());
			cout << "Elements of set A are: " << SetA << endl;
			// >> operator test
			std::istringstream aStre(CEntity::TestStringSet0(), std::istringstream::in);
			try {
				aStre >> SetB;
				cout << "Elements of set B are: " << SetB << endl;
			}
			catch (std::runtime_error & e)
			{
				cerr << "std::runtime error" << &e << endl;
			}
			// are_same method test
			SetB = CSet(CEntity::TestStringSet1().c_str());
			cout << "Are sets same? " << (bool)(SetA.are_same(SetB)) << endl;
			// is_subset_of method test
			SetA.erase(CEntity(CEntity::TestValue1()));
			cout << "Set A: " << SetA << endl;
			cout << "Set B: " << SetB << endl;
			cout << "Is A subset of B? " << (bool)SetB.is_subset_of(SetA) << endl;
			// intersection method test
			SetA.add(CEntity(CEntity::TestValue0()));
			cout << "Set A: " << SetA << endl;
			cout << "Set B: " << SetB << endl;
			cout << "Intersection of A and B: " << SetA.intersection(SetB) << endl;
			cout << "Intersection of B and A: " << SetB.intersection(SetA) << endl;
		}
		
		{
			cout << "------------------Autor2 Tests------------------" << endl;
			//C'tor from CEntity
			CEntity Val = CEntity(CEntity::TestValue1());
			CSet Set1 = CSet(Val);
			//C'tor from string
			CSet Set2 = CSet(CEntity::TestStringSet1().c_str());
			// unary minus test
			cout << "Set 2 before inversion: " << Set2 << endl;
			CSet Set3 = Set2;
			cout << "Set 2 after inversion" << -Set3 << endl;
			// >= and > operators test
			cout << "Set 1 is longer or has same length as set 2: " << (Set1 >= Set2) << endl;
			cout << "Set 1 is longer than set 2 " << (Set1 > Set2) << endl;
			//num_of_elements method test
			cout << "Set 1 has " << Set1.num_of_elements() << " elements." << endl;
			//complement method test
			cout << "Set 1: " << Set1 << endl;
			cout << "Set 2:" << Set2 << endl;
			cout << "Complement of set 2 and set 1: " << Set2.complement(Set1) << endl;
			//section_smaller and section_larger
			cout << "Set 2:" << Set2 << endl;
			cout << "Section smaller than " << CEntity::TestValue1() << ": " << Set2.section_smaller(CEntity(CEntity::TestValue1())) << endl;
			cout << "Section larger than " << CEntity::TestValue1() << ": " << Set2.section_larger(CEntity(CEntity::TestValue1())) << endl;
		}

		
		{
			cout << "------------------Autor3------------------" << endl;
			//c'tor from size_t
			CSet SetA(5);
			// add and erase method test
			CEntity elem = CEntity(CEntity::TestValue1());
			cout << "Set A: " << SetA << endl;
			SetA.add(elem);
			cout << "Set A after addition: " << SetA << endl;
			SetA.erase(elem);
			cout << "Set A after erasion: " << SetA << endl;
			// usage method
			cout << "Percentage of efficiency: " << SetA.usage() << endl;
			// Reverse method and function
			cout << "SetB = Reverse(SetA) test" << endl;
			cout << "Set A:" << SetA << endl;
			CSet SetB = Reverse(SetA);
			cout << "Set B after reversion: " << SetB << endl;
			cout << "Set A after reversion: " << SetA << endl;
			cout << "SetB = SetA.Reverse() test" << endl;
			cout << "Set A:" << SetA << endl;
			SetB = SetA.Reverse();
			cout << "Set B after reversion: " << SetB << endl;
			cout << "Set A after reversion: " << SetA << endl;
			// binary - operator
			SetA = CSet(elem);
			SetA.add(CEntity(CEntity::TestValue0()));
			SetA = CSet(elem);
			cout << "Set A: " << SetA << endl;
			cout << "Set B: " << SetB << endl;
			cout << "Set A - B: " << (SetA - SetB) << endl;
			// += operator 
			CSet SetC;
			cout << "Set A: " << SetA << endl;
			cout << "Set C: " << SetC << endl;
			cout << "SetC += SetA: " << (SetC += SetA) << endl;
			// < operator
			cout << "Set A: " << SetA << endl;
			cout << "Set B: " << SetB << endl;
			cout << "Set A is smaller than Set B: " << (SetA < SetB) << endl;
			//size_t operator test
			size_t aSize = size_t(SetB); // size_t operator
			cout << "Number of elements of Set B: " << aSize << endl;
		}

		{
			cout << "------------------Autor4------------------" << endl;
			//CEntity array c'tor
			CEntity* EntityArray = new CEntity[3]();
			EntityArray[0] = CEntity(CEntity::TestValue0());
			EntityArray[1] = CEntity(CEntity::TestValue1());
			size_t size = 2;
			CSet Set1 = CSet(EntityArray, size), Set2 = CSet();
			delete[] EntityArray;
			cout << "Set 1 elements: " << Set1 << endl;
			//is_element_of method test
			CEntity elem(CEntity::TestStringValue1());
			bool is_el = Set1.is_element_of(elem);
			cout << "Is " << elem << " member of Set 1? " << is_el << endl;
			//is_empty method test
			bool empty = Set2.is_empty();
			cout << "Is set 2 empty? " << empty << endl;
			// first_elem method test
			CSet fSet = CSet(CEntity::TestStringSet1().c_str());
			CEntity* aVal = fSet.first_elem();
			cout << "Set 1 first value: " << aVal->Value() << endl;
			//binary plus operator test
			Set1 = CSet(CEntity::TestStringSet0().c_str());
			Set2 = CSet(elem);
			cout << "Set 1: " << Set1 << endl;
			cout << "Set 2: " << Set2 << endl;
			CSet Set3 = Set1 + Set2;
			cout << "Set3 = Set1 + Set2:" << Set3 << endl;
			//<= operator
			cout << "Is set 3 smaller or same length as set 1? " << (Set3 <= Set1) << endl;
			// + operator with CEntity
			cout << "CEntity elem: " << elem.Value() << endl;
			cout << "Set1:" << Set1 << endl;
			Set2 = Set1 + elem;
			cout << "Set1 + elem: " << Set2 << endl;
		}
		cout << "Done." << endl;
		} /* try */

	catch(std::invalid_argument &e)
		{
		cerr << "std::invalid_argument: " << e.what() << ".\n\a" << endl;
		}
	catch(std::length_error &e)
		{
		cerr << "std::length_error: " << e.what() << ".\n\a" << endl;
		}
	catch(std::out_of_range &e)
		{
		cerr << "std::out_of_range: " << e.what() << ".\n\a" << endl;
		}
	catch(std::range_error &e)
		{
		cerr << "std::range_error: " << e.what() << ".\n\a" << endl;
		}
	catch(std::runtime_error &e)
		{
		cerr << "std::runtime_error: " << e.what() << ".\n\a" << endl;
		}

	cout << endl << "Now exists " << ClassInfo<CEntity>::Living() << " instances of class: " << DM(typeid(CEntity).name()) << endl;
	cout << "In the running of the program existed: " << ClassInfo<CEntity>::Total() << " instances of class: " << DM(typeid(CEntity).name()) << endl;
	
	return(0);
	}
