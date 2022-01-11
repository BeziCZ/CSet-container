#ifndef __CENTITY_CDOUBLE_H__
#define __CENTITY_CDOUBLE_H__
/*
* File: CEntity_CDouble.h
* Brief: CEntity_CDouble class header
* Details: File contain CEntity_CDouble::CEntity definition.
* Author: Martin Bezecny
*/

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <typeinfo>
#include <utility>		// Due to: std::declval<CEntityBase>

#include "ClassInfo.h"
#include "CEntityBase.h"
#include "check.h"

 /*
 * Namespace for encapsulating of  CDouble variant of CEntity class
 * Details: For selecting this variant of CEntity class uncomment  using  namespace section in the CEntity.h
 */
namespace CEntity_CDouble
{
	/*
	* Method: CDouble class.
	*Details: Definition of CDouble class.
	*/
	class CDouble {
		double iVal; ///< Encapsulated  double value.
	public:
		
		/*
		* Method: Implicit c'tor
		* Details: Value attribute is set to  0.
		*/
		CDouble() :iVal(0) {}
		/*
		* Method: Conversion c'tor
		* Details: Value is set.
		* Parameters:	aVal	New encapsulated  double Value
		*/
		CDouble(double aVal) :iVal(aVal) {}
		/*
		* Method: Copy c'tor
		* Details: Create new instance by copying only \p iVal parameter.
		* Parameters:	aVal	Original instance for copying
		*/
		CDouble(const CDouble& aVal) :iVal(aVal.iVal) {}
		
		/*
		* Method: Assigment operator
		* Return: CDouble instance iVal
		*/
		CDouble& operator=(const CDouble& aVal)
		{
			iVal = aVal.iVal;
			return *this;
		}
		/*
		* Method: Inverse operator
		* Return: CDouble instance with inversed iVal value
		*/
		CDouble operator-() const
		{
			if (iVal == 0) return CDouble();
			return CDouble(-iVal);
		}
		/*
		* Method: Comparing by Value operator
		* Return: Return  bool result of comparation iVal values
		*/
		bool operator==(const CDouble& aValue) const
		{
			return iVal == aValue.iVal;
		}
		/*
		* Method: Threeway comparison by Value operator
		* Return: Return  std::partial_ordering result of comparation
		*/
		std::partial_ordering operator<=>(const CDouble& aValue) const
		{
			return iVal <=> aValue.iVal;
		}
		/*
		* Method: Output to the stream operator. (\em serialization)
		* Parameters:	aOStream	Output stream
		* Parameters:	aValue		Serialized instantions of CDouble
		* Return: Return  std::ostream with serialized CDouble
		*/
		friend std::ostream& operator<<(std::ostream& aOStream, const CDouble& aValue)
		{

			aOStream << aValue.iVal;

			return aOStream;
		}
		/*
		* Method: Input from the stream operator. (\em deserialization)
		* Parameters:	aIStream	Input stream
		* Return: Return rest of  std::istream
		*/
		friend std::istream& operator>>(std::istream& aIStream, CDouble& aValue)
		{

			aIStream >> aValue.iVal;

			return aIStream;
		}
	};


	/*
	* Method: CEntity class ( CDouble variant)
	* Details: Definition of CEntity class ( CDouble variant). There are defined all common methods and attributes.
	*/
	class CEntity : public CEntityBase
	{
		ClassInfo<CEntity> iInstanceInfo;	///< Instance of the class info for usage statistics
		CDouble iValue; ///< Encapsulated  CDouble value

	public:
		// c'tors
		/*
		* Method: Implicit c'tor
		* Details: Value attribute is set to  0.
	    */
		CEntity() : CEntityBase(), iValue(0)
		{
		}

		/*
		* Method: Conversion c'tor
		* Details: Value is set. Pointer attributes are initialised by given values or implicitly to the  this value (CEntityBase definition).
		* Parameters:	aValue	New encapsulated  CDouble Value
		* Parameters:	aNext	Connection with next node (when needed)
		* Parameters:	aExtraInt	Special value used for some container types
		*/
		explicit CEntity(const CDouble aValue, CEntity* aNext = nullptr, int aExtraInt = 0) :
			CEntityBase(aNext, aExtraInt), iValue(aValue)
		{
		}

		/*
		* Method: Copy c'tor
		* Details: Create new instance by copying only \p iValue parameter. Pointer attributes are initialised to the  this value (CEntityBase definition).
		* Parameters:	aValue	Original instance for copying
		*/
		CEntity(const CEntity& aValue) : CEntityBase(), iValue(aValue.Value())
		{
		}

		/*
		* Method: Conversion c'tor from plain C string (striped string)
		* Details: Create new instance from Value in the string. Pointer attributes are initialised by given values or implicitly to the  this value (CEntityBase definition).
		* Parameters:	aStr	Plain C string with positive/negative decimal number or with 0.
		* Parameters:	aNext	Connection with next node (when needed)
		* Parameters:	aExtraInt	Special value used for some container types
		*/
		explicit CEntity(const char* aStr, CEntity* aNext = nullptr, int aExtraInt = 0) :
			CEntityBase(aNext, aExtraInt), iValue(false)
		{
			std::istringstream iss(aStr, std::istringstream::in);
			iss >> iValue;
		}

		/*
		* Method: Conversion c'tor from std::string
		* Details: Create new instance from Value in the string. Pointer attributes are initialised by given values or implicitly to the  this value (CEntityBase definition).
		* Parameters:	aString	std::string with positive/negative decimal number or with 0.
		* Parameters:	aNext	Connection with next node (when needed)
		* Parameters:	aExtraInt	Special value used for some container types
		*/
		explicit CEntity(const std::string& aString, CEntity* aNext = nullptr, int aExtraInt = 0) :
			CEntity(aString.c_str(), aNext, aExtraInt)
		{
		}

		// d'tor
		/*
		* Method: Virtual d'tor
		*/
		virtual ~CEntity() noexcept(noexcept(std::declval<CEntityBase>().~CEntityBase()))	// noexcept(KCEntityDtorNoException)
		{
			iValue = 0;
		}

		// InstanceInfo getters
		/*
		* Method: ID getter
		* Return: Unique instance ID
		*/
		size_t ID() const
		{
			return iInstanceInfo.ID();
		}

		// setter/getter
		/*
		* Method: Value setter
		* Parameters:	aValue	New Value
		*/
		void SetValue(const CDouble& aValue)
		{
			iValue = aValue;
		}

		/*
		* Method: Value getter
		* Return: Actual  CDouble \p Value
		*/
		CDouble Value() const
		{
			return iValue;
		}

		// operators
		/*
		* Method: Complement operator
		* Return: CEntity instance with complemented attribute Value.
		*/
		CEntity operator-() const
		{
			return CEntity(-iValue);
		}

		/*
		* Method: Assigment operator
		* Return: CEntity instance with copied attribute Value.
		*/
		CEntity& operator=(const CEntity& aValue)
		{
			SetValue(aValue.Value());
			return *this;
		}

		/*
		* Method: Comparing by Value operator
		* Return: Return  bool result of comparation
		*/
		bool operator==(const CEntity& aValue) const
		{
			return iValue == aValue.Value();
		}

#ifdef CENTITY_THREE_WAY_COMPARISON
		/*
		* Method: Threeway comparison by Value operator
		* Return: Return  std::partial_ordering result of comparation
		*/
		std::partial_ordering operator<=>(const CEntity& aValue) const
		{
			return iValue <=> aValue.Value();
		}

#else
		/*
		* Method: Comparing by Value operator
		* Return: Return  CDouble result of comparation
		*/
		CDouble operator!=(const CEntity& aValue) const
		{
			return iValue != aValue.Value();
		}

		/*
		* Method: Comparing by Value operator
		* Return: Return  CDouble result of comparation
		*/
		CDouble operator<(const CEntity& aValue) const
		{
			return iValue < aValue.Value();
		}

		/*
		* Method: Comparing by Value operator
		* Return: Return  CDouble result of comparation
		*/
		CDouble operator>(const CEntity& aValue) const
		{
			return iValue > aValue.Value();
		}

#endif /* CENTITY_THREE_WAY_COMPARISON */

		/** Method: Output to the stream operator. (\em serialization)
		 * Parameters:	aOStream	Output stream
		 * Parameters:	aValue	Serialized instantion of CEntity
		 * Return: Return  std::ostream with serialized Value
		 */
		friend std::ostream& operator<<(std::ostream& aOStream, const CEntity& aValue)
		{
			std::ios_base::fmtflags fmtflags = aOStream.setf(std::ios_base::boolalpha); // Save the state of the CDoublealpha flag & set it
			aOStream << ' ' << aValue.Value();
			aOStream.flags(fmtflags); 	// restore previous flags
			return aOStream;
		}

		/** Method: Input from the stream operator. (\em deserialization)
		 * Parameters:	aIStream	Input stream
		 *  \param[out]	aValue	Place for deserialized instantion of CEntity
		 * Return: Return rest of  std::istream
		 */
		friend std::istream& operator>>(std::istream& aIStream, CEntity& aValue)
		{

			std::ios_base::fmtflags fmtflags = aIStream.setf(std::ios_base::boolalpha); // Save the state of the CDoublealpha flag & set it
			aIStream >> aValue.iValue;

			aIStream.flags(fmtflags); 	// restore previous flags
			return aIStream;
		}

#ifdef CENTITY_TEST_API
		// constants for testing CEntity functionality

			/** Method: First test value
			 * Return: Return  CDouble value ( 0)
			 *  \note Useful for automated testing of CEntity functionality
			 */
		static CDouble TestValue0()
		{
			return CDouble(0);
		}

		/** Method: First test string value
		 * Return: Return string with  CDouble value ( 0)
		 *  \note Useful for automated testing of CEntity functionality
		 */
		static std::string TestStringValue0()
		{
			return std::string("0");
		}

		/** Method: Second test value
		 * Return: Return  CDouble value ( 1)
		 *  \note Useful for automated testing of CEntity functionality
		 */
		static CDouble TestValue1()
		{
			return CDouble(1);
		}

		/** Method: Second test string value
		 * Return: Return string with  CDouble value ( 1)
		 *  \note Useful for automated testing of CEntity functionality
		 */
		static std::string TestStringValue1()
		{
			return std::string("1");
		}

		/** Method: Random test value
		 * Return: Return random  CDouble value
		 *  \note Useful for automated testing of CEntity functionality
		 */
		static CDouble TestValueRandom()
		{
			return CDouble(std::rand()%100);
		}

		/** Method: Random test string value
		 * Return: Return string with random  CDouble value
		 *  \note Useful for automated testing of CEntity functionality
		 */
		static std::string TestStringValueRandom()
		{
			return std::to_string(std::rand() % 100);
		}

		static std::string TestStringSet0() {
			return "[0],[0.3],[0.4],[0.5],[0.6],[0.3]";
		}

		static std::string TestStringSet1() {
			return "[1],[7.4],[9.6],[13.4],[15.6],[7.4]";
		}
#endif /* CENTITY_TEST_API */

	}; /* class CEntity */
} /* namespace CEntity_CDouble */
#endif /* __CENTITY_CDOUBLE_H__ */

