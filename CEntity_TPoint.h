#ifndef __CENTITY_TPOINT_H__
#define __CENTITY_TPOINT_H__

/*
* File: CEntity_TPoint.h
* Brief description: CEntity_TPoint class header
* Details File contain CEntity_TPoint::CEntity definition.
* Author: Martin Bezecny
*/

#include <iostream>
#include <sstream>
#include <cmath>
#include <string>
#include <stdexcept>
#include <typeinfo>
#include <utility>		// Due to: std::declval<CEntityBase>

#include "ClassInfo.h"
#include "CEntityBase.h"
#include "check.h"

 /*
 * Description: Namespace for encapsulating of  TPoint variant of CEntity class
 * Details: For selecting this variant of CEntity class uncomment  using  namespace section in the CEntity.h
 */

namespace CEntity_TPoint

{
	/*
	* Basic definition of class TPoint which are representing point coordinates in space.
	*/
	class TPoint
	{
		double iX; ///< Representing X coordinate of point.
		double iY; ///< Representing Y coordinate of point.
		double iZ; ///< Representing Z coordinate of point.
	public:
		/*
		* Method: Implicit c'tor
		* Details: attributes are set:  iX = 0, iY = 0, iZ = 0.
		*/
		TPoint() :iX(0), iY(0), iZ(0) {}
		/*
		* Method: Conversion c'tor
		* Details: values of iX, iY, iZ are set.
		* Parameters:	aX	New encapsulated  TPoint iX Value
		* Parameters:	aY	New encapsulated  TPoint iY Value
		* Parameters:	aZ	New encapsulated  TPoint iZ Value
		*/
		TPoint(double aX, double aY, double aZ) :iX(aX), iY(aY), iZ(aZ) {}
		/*
		* Method: Copy c'tor
		* Details: Create new instance by copying \p iX, iY, iZ parameter.
		*  Parameters:	aPoint	Original instance for copying
		*/
		TPoint(const TPoint& aPoint) :iX(aPoint.iX), iY(aPoint.iY), iZ(aPoint.iZ) {}
		/*
		* Method: Assigment operator
		* Return: TPoint instance with copied iX, iY, iZ values.
		*/
		TPoint& operator=(const TPoint& aVal)
		{
			iX = aVal.iX;
			iY = aVal.iY;
			iZ = aVal.iZ;
			return *this;
		}
		/*
		* Method: Inverse operator
		* Return: TPoint instance with inversed iX, iY, iZ values.
		*/
		TPoint operator-() const
		{
			return TPoint(-iX, -iY, -iZ);
		}
		/*
		* Method: Comparing by Value operator
		* Return: Return  bool result of comparation iX, iY, iZ values
		*/
		bool operator==(const TPoint& aValue) const
		{
			return (iX == aValue.iX) && (iY == aValue.iY) && (iZ == aValue.iZ);
		}
		/*
		* Method: Threeway comparison by Value operator
		* Details: Comparison based on the distance of points from the origin
		* Return: Return  std::partial_ordering result of comparation
		*/
		std::partial_ordering operator<=>(const TPoint& aValue) const
		{

			double iDistance = sqrt(pow(iX, 2) + pow(iY, 2) + pow(iZ, 2));
			double aDistance = sqrt(pow(aValue.iX, 2) + pow(aValue.iY, 2) + pow(aValue.iZ, 2));
			return iDistance <=> aDistance;
		}

		/*
		* Method: Output to the stream operator. (\em serialization)
		* Parameters:	aOStream	Output stream
		* Parameters:	aValue		Serialized instantions of TPoint
		* Return: Return  std::ostream with serialized aWeekDay
		*/
		friend std::ostream& operator<<(std::ostream& aOStream, const TPoint& aValue)
		{

			aOStream << aValue.iX << ' ' << aValue.iY << ' ' << aValue.iZ;

			return aOStream;
		}
		/*
		* Method: Input from the stream operator. (\em deserialization)
		* Parameters:	aIStream Input stream
		* Parameters:	aValue a TPoint instance
		* Return: Return rest of  std::istream
		*/
		friend std::istream& operator>>(std::istream& aIStream, TPoint& aValue)
		{

			aIStream >> aValue.iX >> aValue.iY >> aValue.iZ;

			return aIStream;
		}
	};
	class CEntity : public CEntityBase
	{
		ClassInfo<CEntity> iInstanceInfo;	///< Instance of the class info for usage statistics
		TPoint iValue; ///< Encapsulated  TPoint value

	public:
		// c'tors
		/*
		* Method: Implicit c'tor
		*  Details: Value attribute is set to  0 0 0
		*/
		CEntity() : CEntityBase(), iValue()
		{
		}

		/*
		* Method: Conversion c'tor
		*  Details: Value is set. Podoubleer attributes are initialised by given values or implicitly to the  this value (CEntityBase definition).
		*  Parameters:	aValue	New encapsulated  TPoint Value
		*  Parameters:	aNext	Connection with next node (when needed)
		*  Parameters:	aExtradouble	Special value used for some container types
		*/
		explicit CEntity(const TPoint& aValue, CEntity* aNext = nullptr, int aExtraInt = 0) :
			CEntityBase(aNext, aExtraInt), iValue(aValue)
		{
		}

		/*
		* Method: Copy c'tor
		* Details: Create new instance by copying only \p iValue parameter. Podoubleer attributes are initialised to the  this value (CEntityBase definition).
		* Parameters:	aValue	Original instance for copying
		*/
		CEntity(const CEntity& aValue) : CEntityBase(), iValue(aValue.Value())
		{
		}

		/*
		* Method: Conversion c'tor from plain C string (striped string)
		* Details: Create new instance from Value in the string. Podoubleer attributes are initialised by given values or implicitly to the  this value (CEntityBase definition).
		* Parameters:	aStr	Plain C string with 3 point coordinates in [ ]
		* Parameters:	aNext	Connection with next node (when needed)
		* Parameters:	aExtradouble	Special value used for some container types
		*/
		explicit CEntity(const char* aStr, CEntity* aNext = nullptr, int aExtraInt = 0) :
			CEntityBase(aNext, aExtraInt), iValue()
		{
			std::istringstream iss(aStr, std::istringstream::in);
			iss >> iValue;
		}

		/*
		* Method: Conversion c'tor from std::string
		* Details: Create new instance from Value in the string. Podoubleer attributes are initialised by given values or implicitly to the  this value (CEntityBase definition).
		* Parameters:	aString	std::string with 3 point coordinates in [ ]
		* Parameters:	aNext	Connection with next node (when needed)
		* Parameters:	aExtradouble	Special value used for some container types
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
			iValue = TPoint(0, 0, 0);
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
		void SetValue(const TPoint& aValue)
		{
			iValue = aValue;
		}

		/*
		* Method: Value getter
		* Return: Actual  TPoint \p Value
		*/
		TPoint Value() const
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
		* Return: Return  TPoint result of comparation
		*/
		Cdouble operator!=(const CEntity& aValue) const
		{
			return iValue != aValue.Value();
		}

		/*
		* Method: Comparing by Value operator
		* Return: Return  TPoint result of comparation
		*/
		Cdouble operator<(const CEntity& aValue) const
		{
			return iValue < aValue.Value();
		}

		/*
		* Method: Comparing by Value operator
		* Return: Return  TPoint result of comparation
		*/
		Cdouble operator>(const CEntity& aValue) const
		{
			return iValue > aValue.Value();
		}
#endif /* CENTITY_THREE_WAY_COMPARISON */

		/*
		* Method: Output to the stream operator. (\em serialization)
		*  Parameters:	aOStream	Output stream
		*  Parameters:	aValue	Serialized instantion of CEntity
		*  Return: Return  std::ostream with serialized Value
		*/
		friend std::ostream& operator<<(std::ostream& aOStream, const CEntity& aValue)
		{
			aOStream << aValue.Value();
			return aOStream;
		}

		/*
		* Method: Input from the stream operator. (\em deserialization)
		*  Parameters:	aIStream	Input stream
		*  Return: Return rest of  std::istream
		*/
		friend std::istream& operator>>(std::istream& aIStream, CEntity& aValue)
		{

			aIStream >> aValue.iValue;
			return aIStream;
		}

#ifdef CENTITY_TEST_API
		// constants for testing CEntity functionality

		/*
		* Method: First test value
		* Return: Return  TPoint value (__0 0 0__)
		* Note: Useful for automated testing of CEntity functionality
		*/
		static TPoint TestValue0()
		{
			return TPoint(0, 0, 0);
		}

		/*
		* Method: First test string value
		* Return: Return string with  TPoint value (__0 0 0__)
		* v Useful for automated testing of CEntity functionality
		*/
		static std::string TestStringValue0()
		{
			return std::string("0 0 0");
		}

		/*
		* Method: Second test value
		* Return: Return  TPoint value (__17 3 5__)
		* Note: Useful for automated testing of CEntity functionality
		*/
		static TPoint TestValue1()
		{
			return TPoint(17, 3, 5);
		}

		/*
		* Method: Second test string value
		* Return: Return string with  TPoint value (__17 3 5__)
		* Note: Useful for automated testing of CEntity functionality
		*/
		static std::string TestStringValue1()
		{
			return std::string("17 3 5");
		}

		/*
		* Method: Random test value
		* Return: Return random  TPoint value
		* Note: Useful for automated testing of CEntity functionality
		*/
		static TPoint TestValueRandom()
		{
			return TPoint(std::rand() % 100, std::rand() % 100, std::rand() % 100);
		}

		/*
		* Method: Random test string value
		* Return: Return string with random  TPoint value
		* Note: Useful for automated testing of CEntity functionality
		*/
		static std::string TestStringValueRandom()
		{
			std::string aStr = std::to_string(std::rand() % 100) + " " + std::to_string(std::rand() % 100) + " " + std::to_string(std::rand() % 100);
			return aStr;
		}

		static std::string TestStringSet0() {
			return "[0;0;0],[0;1;1],[0;2;2],[0;3;3],[0;4;4],[0;1;1]";
		}

		static std::string TestStringSet1() {
			return "[17;3;5],[3;2;4],[3;3;6],[3;4;8],[3;5;10],[3;2;4]";
		}
#endif /* CENTITY_TEST_API */

	}; /* class CEntity */
} /* namespace CEntity_TPoint */

#endif

