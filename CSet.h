#ifndef __CSet_H__
#define __CSet_H__
/*
*  File: CSet.h
*  Brief: CSet class header
*  Details: File contain CSet class container definition.
*  Authors: Martin Bezecný
*/

#include "CEntity.h"
#include "check.h"


/*
 * CSet class
 * Definition of CSet class. There are defined all common methods and attributes.
 */
class CSet
	{

    ClassInfo <CSet> iInstanceInfo; ///< Instance of the class info for usage statistics
    CEntity* iFirst = nullptr; ///< Location of first node
    size_t iSize = 0; ///< Number of elements in CSet

    void Copy(const CSet& aVal);//Function for copying sets


    void Destroy(); //function for deallocating sets

public:
        /* 
        * Method: Implicit c'tor
        * Details: iFirst is set to nullptr, iSize is set to 0
        */
        CSet() : iInstanceInfo(), iFirst(nullptr), iSize(0) {}; //implicit constructor

        /*
        * Method: Copy c'tor
        * Details:Create new instance by copying iFirst and iSize Parameters:
        * Parameters: aVal	Original instance for copying
        */
        CSet(const CSet& aVal) : iFirst(nullptr), iSize(0) { Copy(aVal); }; // copy constructor

		/*
        * Method: Conversion c'tor from CEntity
		* Details:creating CSet with one element aVal, iFirst is set to aVal, iSize is set to 1
		* Parameters: aVal  is  CEntity Value
		*/
		CSet(CEntity& aVal) : iFirst(new CEntity(aVal)), iSize(1) { iFirst->SetNextItem(nullptr); } // constructor, creating CSet with one element aVal
		
        /*
        * Method: Conversion c'tor from string
		* Details: creating CSet from string
	    * Parameters: aStr  is char string of CEntity values in [ ] and they are separated by ,
		*/
		CSet(const char* aStr);//constructor from C string

        /*
        * Method: Conversion c'tor from size_t
        * Details: creating random instances of CEntity and creating CSet of aSize instances
        * Parameters:	aSize that is number of elements in Set
        */
        CSet(size_t aSize);// constructor size_t, generating random instances of CEntity and creating CSet of aSize instances

        /*
        * Method: Conversion c'tor from array of CEntity values and number of elements of CSet
        * Details: creates a set, which is consecutively filled with elements from the array aVal, their number is given by aSize and elements are selected, so that there are no repetetive ones in set.
        * If the array aVal does not contain sufficient number of elements, to the required amount aSize the set is completed with random unique values.
        * Parameters:	aVal is CEntity value, aSize is the number of elements to be added to the set
        */
        CSet(CEntity* aVal, size_t aSize);

        /*
        * Method: Virtual D'tors
        * Details: the set destructor will be implemented with the active element countdown mechanism using the ClassInfo class variable.
        * It removes dynamic member elements and gradually sets the pointers of the elements in the linear list hidden under the set to nullptr.
        */

        ~CSet() { Destroy(); } //d'tor

        /*
        * Method: Assigment operator
        * Details: operator creating a copy of the values (except for the iID, which will keep the original).
        * Parameters:: aVal is constant reference CSet
        * Return: Overwrite the original values in the resulting variable, dynamical deallocate
        */
        CSet& operator=(const CSet& aVal);

        /*
        * Method: Comparing by Value operator
        * Details: compares card powers of Sets
        * Parameters: aVal is constant reference CSet
        * Return: Return  bool result of comparation of card powers, if they match, it returns true, otherwise it returns false
        */
        bool operator == (const CSet& aVal) const { return iSize == aVal.iSize; };

        /*
        * Method: Inequality operator
        * Details: compares card powers of Sets.
        * Parameters: aVal is constant reference CSet
        * Return: Return  bool result of comparation of card powers, if they match, it returns false, otherwise it returns true
        */
        bool operator != (const CSet& aVal) const { return Compare(aVal) != 0; };
        /*
        * Method: friend input operator
        * Details: serves as input into CSet.
        * Parameters: aIStream is input stream and aValue is a CSet
        * Return: Returns  stream without the elements loaded into the CSet
        */
        friend std::istream& operator >>(std::istream& aIStream, CSet& aValue);

        /*
        * Method: friend output operator
        * Details: serves as output from CSet.
        * Parameters: aOStream is output stream, aValue is given set
        * Return: Return  output stream with formatted elements from CSet
        */
        friend std::ostream& operator <<(std::ostream& aOStream, const CSet& aValue);

		/*
        * Method: Unary operator minus
		* Details: makes the inversion of container
	    * Return:  same set, but with inversed element values
		*/
		CSet& operator-();

		/* 
        * Method: Relational operator Larger equal
		* Details: Compares if the first set has more or the same amount of elements
        * Parameters: aVal is constant reference CSet
		* Return: true when the number of elements in the set is larger or same, otherwise returns false
		*/
		bool operator >= (const CSet& aVal) const { return (Compare(aVal) == 1 || Compare(aVal) == 0); }
		/*
        * Method: Relational operator Larger
		* Details: Compares if the first set has bigger amount of elements
        * Parameters: aVal is constant reference CSet
		* Return: true when the number of elements in the set is larger, otherwise returns false
		*/
		bool operator > (const CSet& aVal) const { return Compare(aVal) == 1; }
        
        /*
        * Method: Binary operator minus
        * Details: makes the inversion of container makes the difference of containers
        * Parameters: aVal is constant reference CSet
        *  Return: new set with all elements of the first set that were not included in the second 
        */
        CSet operator - (const CSet& aVal) const;

        /*
        * Method: Binary operator plus equal
        * Details: it makes union of two sets, stores it in first set
        * Parameters: aVal is constant reference CSet
        * Return:  first set with all unique elements of both sets
        */
        CSet& operator += (const CSet& aVal);

        /*
        * Method: Relational operator smaller
        * Details: Compares if the first set has smaller amount of elements
        * Parameters: aVal is constant reference CSet
        * Return: true when the number of elements in the set is smaller, otherwise returns false
        */
        bool operator < (const CSet& aVal) const { return (Compare(aVal) == -1); }

        /*
        * Method: Operator size_t
        * Details: converts set to size_t
        * Return: number of elements in set
        */
        operator size_t() const { return iSize; }

        /*
        * Method: Binary operator plus
        * Details: it makes union of two sets, stores it in new set
        * Parameters: aVal is constant reference CSet
        * Return:  new set with all unique elements of both sets
        */
        CSet operator + (const CSet& aVal) const;

        /*
        * Method: Relational operator smaller equal
        * Details: Compares if the first set has less or the same amount of elements
        * Parameters: aVal is constant reference CSet
        * Return: true when the number of elements in the set is smaller or same, otherwise returns false
        */
        bool operator <= (const CSet& aVal) const { return (Compare(aVal) == -1 || Compare(aVal) == 0); }
        
        /*
        * Method: Non-member operator plus
        * Details: it makes sum of CEntity value and set
        * Parameters: aVal is constant reference CEntity
        * Return:  new set with one added element of CEntity, if the elemnt was not already included in the set
        */
        friend CSet operator + (const CSet& aSet, const CEntity& aVal);
 
        /*
        * Method: is subset of
        * Details: it checks if the set is subset of the set in the parameter
        * Parameters:	aVal  is  CSet Value
        * Return:  bool value according to whether the set is subset or not
        */
        bool is_subset_of(const CSet& aVal) const;

        /*
        * Method: intersection
        * Details: it makes intersection of calling set and the set in parameter
        * Parameters:	aVal  is  CSet Value
        * Return: set of elements which are common for both sets
        */
        CSet intersection(const CSet& aVal) const;

        /*
        * Method: is subset of
        * Details: checks if the containers are exactly same element wise
        * Parameters:	aVal  is  CSet Value
        * Return:  bool value according to whether sets are same or not
        */
        bool are_same(const CSet& aVal) const;

        /*
        * Method: ID
        * Details: returns unique ID of given set
        * Return:  size_t value of ID of the given instance 
        */
        size_t ID() const
        {
            return iInstanceInfo.ID();
        }

		 /*
         * Method: Number of elements of the set
		 * Details:  It has no Parameters:
		 * Return:   Number of active elements of the set
		 */
		size_t num_of_elements() const { return iSize; }

		/*
        * Method: Complement of the set
		* Parameters:	aVal  is  CSet Value
		* Return:  new set with all elements of the first set that were not included in the second
		*/
		CSet complement(const CSet& aVal) const;

		/*
        * Method: Section of the set - smaller
		* Parameters:	aVal  is  CEntity Value
		* Return:  new set with all elements that have smaller values then given CEntity value
		*/
		CSet section_smaller(const CEntity& aVal) const;

		/*
        * Method: Section of the set - larger
		* Parameters:	aVal  is  CEntity Value
		* Return:  new set with all elements that have larger values then given CEntity value
		*/
		CSet section_larger(const CEntity& aVal) const;

        /*
        * Method: Addition of element
        * Parameters:	aVal  is  CEntity Value
        */
        void add(const CEntity& aVal);

        /*
        * Method: Erasing of element
        * Parameters:	aVal  is  CEntity Value
        */
        
        void erase(const CEntity& aVal);
        /*
        * Method: Usage of memory info
        * Return:  a double value [in percent] representing memory usage efficiency
        */
        double usage() const;

        /*
        * Method: Reverse 1
        * Return:  set based on reversed linear list
        */
        CSet& Reverse();

        /*
        * Method: Is empty
        * Details: returns true if set is empty, otherwise returns false
        * Return:  bool value according to whether the set is empty or not
        */
        bool is_empty() const { return (iSize == 0); }

        /*
        * Method: Is element of
        * Details: checks if the given elemenet of CEntity is inluded in the set
        * Return:  bool value according to whether the set contains the given element
        */
        bool is_element_of(const CEntity& aVal) const;

        /*
        * Method: First element
        * Details: gets you pointer on first instance of CEntity in set
        * Return:  CEntity pointer of first element
        */
        CEntity* first_elem() const;

private:

        /*
        * Method: Comparing by number of elements and also by CEntity values
        * Return: Return true if the containers are same length and if they have exactly same elements
        */
        bool DeepCompare(const CSet& aVal) const;

        
        /*
        * Method: Comparing by number of elements
        * Return: Return -1 or 0 or 1
        */
        int Compare(const CSet& aVal) const;
	}; /* class CSet */

/*
* Method: Reverse 2
* Parameters:	aVal  is  CSet Value
* Return:  new set based on reversed linear list of given CSet parameter
*/
CSet Reverse(const CSet& aVal);


#endif /* __CSet_H__ */
