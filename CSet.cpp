/*
* File: CSet.cpp
* Brief description: CSet class implementation
* Details: File contain CSet class container implementation.
* Author: Martin Bezecny
*/

#include "CSet.h"

// Internal functions

void CSet::Copy(const CSet& aVal) { //Function for copying sets
    CEntity* temp1 = aVal.iFirst;
    if (aVal.iFirst) {
        iFirst = new CEntity(*aVal.iFirst);
        temp1 = dynamic_cast<CEntity*>(aVal.iFirst->NextItem());
    }
    CEntity* temp2 = iFirst;
    while (temp1) {
        temp2->SetNextItem(new CEntity(*temp1));
        temp2 = dynamic_cast<CEntity*>(temp2->NextItem());
        temp1 = dynamic_cast<CEntity*>(temp1->NextItem());
    }
    iSize = aVal.iSize;
}

void CSet::Destroy() { //function for deallocating sets
    CEntity* temp = iFirst, * next;
    iFirst = nullptr;
    while (temp) {
        next = dynamic_cast<CEntity*>(temp->NextItem());
        temp->SetNextItem(nullptr);
        delete temp;
        temp = next;
        --iSize;
    }
}

//C'tors
CSet::CSet(const char* aStr) : iFirst(nullptr), iSize(0) {
    std::istringstream iss(aStr, std::istringstream::in);
    iss >> *this;
}

CSet::CSet(size_t aSize) : iFirst(nullptr), iSize(0) {
    for (size_t i = 0; i < aSize; ++i) {
        this->add(CEntity(CEntity::TestValueRandom()));
        ++iSize;
    }
}

CSet::CSet(CEntity* aVal, size_t aSize) : iFirst(nullptr), iSize(0) {
    size_t i = 0;
    size_t living = ClassInfo<CEntity>::Living();
    while (i < aSize - 1) {
        if (aVal->ID() > ClassInfo<CEntity>::Total()) throw std::runtime_error("Given size is larger than array size!");
        this->add(aVal[i]);
        ++i;
    }
}

//Operators
CSet& CSet::operator=(const CSet& aVal) {
    if (this->DeepCompare(aVal)) return *this;
    Destroy();
    Copy(aVal);
    return *this;
}

CSet& CSet::operator-() {
    CEntity* temp = iFirst;
    while (temp) {
        CEntity inv_val = CEntity(-*temp);
        temp->SetValue(inv_val.Value());
        temp = dynamic_cast<CEntity*>(temp->NextItem());
    }
    return *this;
}

CSet CSet::operator -(const CSet& aVal) const {
    if (this->iFirst == nullptr || aVal.iFirst == nullptr) return *this;
    CSet difference = CSet(*this);
    CEntity* temp = aVal.iFirst;
    while (temp) {
        if (difference.is_element_of(*temp)) difference.erase(*temp);
        temp = dynamic_cast<CEntity*>(temp->NextItem());
    }
    return difference;
}

CSet& CSet::operator +=(const CSet& aVal) {
    if (aVal.iFirst == nullptr) return *this;
    CEntity* temp = aVal.iFirst;
    while (temp) {
        if (!this->is_element_of(*temp)) this->add(*temp);
        temp = dynamic_cast<CEntity*>(temp->NextItem());
    }
    return *this;
}

CSet CSet::operator+(const CSet& aVal) const {
    if (aVal.iFirst == nullptr) return *this;
    if (this->iFirst == nullptr) return aVal;
    CSet sum = CSet(*this);
    CEntity* temp = aVal.iFirst;
    while (temp) {
        if (!sum.is_element_of(*temp)) sum.add(*temp);
        temp = dynamic_cast<CEntity*>(temp->NextItem());
    }
    return sum;
}

CSet operator + (const CSet& aSet, const CEntity& aVal) {
    CSet emp = CSet(aSet);
    emp.add(aVal);
    return emp;
}

std::istream& operator >>(std::istream& aIStream, CSet& aValue) {
    char ch = '\0';
    std::string temp_str;
    CEntity temp_ent;
    if (!aIStream.good())
        throw std::runtime_error("Input stream data integrity error!");
    while (!aIStream.eof()) {
        aIStream >> std::noskipws >> ch;
        if (ch == '[' && ch != ',') {
            aIStream >> ch;
            while (ch != ']') {
                if (ch != ';') {
                    temp_str.push_back(ch);
                }
                else {
                    temp_str.push_back(' ');
                }
                aIStream >> ch;
            }
            temp_ent = CEntity(temp_str);
            if (aValue.iFirst == nullptr) aValue = CSet(temp_ent);
            else aValue.add(temp_ent);
        }
        temp_str = "";
    }
    return aIStream;
}

std::ostream& operator <<(std::ostream& aOStream, const CSet& aValue) {
    if (aValue.iFirst == nullptr) {
        aOStream << "";
        return aOStream;
    }
    CEntity* temp = aValue.iFirst;
    while (temp) {
        aOStream << '[' << temp->Value() << ']';
        if (temp->NextItem()) aOStream << ',';
        temp = dynamic_cast<CEntity*>(temp->NextItem());
    }
    return aOStream;
}

//Methods
bool CSet::is_subset_of(const CSet& aVal) const {
    if (iSize < aVal.iSize) return false;
    if (iSize == aVal.iSize) {
        if (this->DeepCompare(aVal)) return true;
        return false;
    }
    CEntity* sub_current = aVal.iFirst;
    while (sub_current) {
        CEntity* this_current = iFirst;
        bool is_member = false;
        while (this_current) {
            if (sub_current->Value() == this_current->Value()) {
                is_member = true;
                break;
            }
            this_current = dynamic_cast<CEntity*>(this_current->NextItem());
        }
        if (!is_member) return false;
        sub_current = dynamic_cast<CEntity*>(sub_current->NextItem());
    }
    return true;
}

CSet CSet::intersection(const CSet& aVal) const {
    if (this->iFirst == nullptr) return *this;
    if (aVal.iFirst == nullptr) return aVal;
    if (this->DeepCompare(aVal)) return *this;
    CSet intersect = CSet();
    CEntity* this_curr = iFirst;
    while (this_curr) {
        CEntity* aVal_curr = aVal.iFirst;
        while (aVal_curr) {
            if (this_curr->Value() == aVal_curr->Value()) {
                intersect.add(*aVal_curr);
                break;
            }
            aVal_curr = dynamic_cast<CEntity*>(aVal_curr->NextItem());
        }
        this_curr = dynamic_cast<CEntity*>(this_curr->NextItem());
    }
    return intersect;
}

bool CSet::are_same(const CSet& aVal) const {
    return this->DeepCompare(aVal);
}

bool CSet::DeepCompare(const CSet& aVal) const {
    if (aVal.iSize != this->iSize) return false;
    CEntity* aVal_curr = aVal.iFirst;
    while (aVal_curr) {
        if (!this->is_element_of(*aVal_curr)) return false;
        aVal_curr = dynamic_cast<CEntity*>(aVal_curr->NextItem());
    }
    return true;
}

CSet CSet::complement(const CSet& aVal) const {
	if (aVal.is_empty()) return *this;
	CSet comp = CSet(*this - aVal);
	return comp;
}

CSet CSet::section_smaller(const CEntity& aVal) const {
	if (iSize == 0) return *this;
	CSet smaller;
	CEntity* temp = iFirst;
	while (temp) {
		if (aVal.Value() > temp->Value()) smaller.add(*temp);
		temp = dynamic_cast<CEntity*>(temp->NextItem());
	}
	return smaller;
}

CSet CSet::section_larger(const CEntity& aVal) const {
	if (iSize == 0) return *this;
	CSet larger;
	CEntity* temp = iFirst;
	while (temp) {
		if (aVal.Value() < temp->Value()) larger.add(*temp);
		temp = dynamic_cast<CEntity*>(temp->NextItem());
	}
	return larger;
}

void CSet::add(const CEntity& aVal) {
    if (!this->is_element_of(aVal)) {
        CEntity* temp_node = new CEntity(aVal);
        if (iFirst == nullptr) {
            iFirst = temp_node;
        }
        else {
            CEntity* temp_first = iFirst;
            while (temp_first->NextItem()) temp_first = dynamic_cast<CEntity*>(temp_first->NextItem());
            temp_first->SetNextItem(temp_node);
            temp_first = dynamic_cast<CEntity*>(temp_first->NextItem());
        }
        iSize++;
    }
}

void CSet::erase(const CEntity& aVal) {
    if (this->is_element_of(aVal)) {
        CEntity* temp = iFirst;
        CEntity* prev = temp;
        while (temp->Value() != aVal.Value()) {
            prev = temp;
            temp = dynamic_cast<CEntity*>(temp->NextItem());
        }
        if (temp == iFirst) {
            iFirst = dynamic_cast<CEntity*>(iFirst->NextItem());
        }
        else {
            prev->SetNextItem(temp->NextItem());
        }
        temp->SetNextItem(nullptr);
        delete(temp);
        iSize--;
    }
}

CSet& CSet::Reverse() {
    CEntity* curr = iFirst;
    CEntity* prev = nullptr, * next = nullptr;
    while (curr != nullptr) {
        next = dynamic_cast<CEntity*>(curr->NextItem());
        curr->SetNextItem(prev);
        prev = curr;
        curr = next;
    }
    iFirst = prev;
    return *this;
}

double CSet::usage() const {
    size_t set_size = sizeof(*this);
    size_t num = this->num_of_elements();
    CEntity* list = new CEntity[num];
    size_t list_size = sizeof(*list);
    delete[] list;
    double efect = ((double)set_size / (double)list_size) * 100;
    return efect;
}

CSet Reverse(const CSet& aVal) {
    CSet reversed = CSet(aVal);
    return reversed.Reverse();
}

bool CSet::is_element_of(const CEntity& aVal) const {
    CEntity* temp = iFirst;
    while (temp) {
        if (temp->Value() == aVal.Value()) return true;
        temp = dynamic_cast<CEntity*>(temp->NextItem());
    }
    return false;
}

int CSet::Compare(const CSet& aVal) const {
    if (iSize == aVal.iSize) return 0;
    if (iSize < aVal.iSize) return -1;
    return 1;
}

CEntity* CSet::first_elem() const {
    return iFirst;
}