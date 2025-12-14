#include "bigint_essai01122025.hpp"

		bigint::bigint(){
			str = "0";
		}

		bigint::bigint(unsigned int num){
			std::stringstream ss;
			ss << num;
			str = ss.str();
		}

		bigint::bigint(const bigint& other){
			*this = other;			
		}
		bigint& bigint::operator=(const bigint& other){
			if(this == &other)
				return *this;
			this->str = other.str;
			return *this;
		}
		bigint::~bigint(){}

		std::string bigint::getStr()const{
			return(this->str);
		}

		///////////////////////////////////////////////////
		std::string reverse(const std::string& str){
			std::string reversedStr;
			for(size_t i = str.length(); i>0; i--)
				reversedStr.push_back(str[i-1]);
			return reversedStr;
		}
		std::string addition(const bigint& obj1, const bigint& obj2){
			std::string str1 = reverse(obj1.getStr());
			std::string str2 = reverse(obj2.getStr());
			std::string res;

			size_t len1 = str1.length();
			size_t len2 = str2.length();

			if(len1>len2){
				for(size_t i = 0; i < len1 - len2; i++)
					str2.push_back('0');
			}
			else if(len1<len2){
				for(size_t i = 0; i < len2 - len1; i++)
					str1.push_back('0');
			}
			int carry = 0;

			for(size_t i = 0; i < str1.length(); i++)
			{
				int digit1 = str1[i] - '0';
				int digit2 = str2[i] - '0';
				int sum = digit1 + digit2 + carry;

				if(sum > 9){
					carry = sum / 10;
					res.push_back((sum% 10 ) + '0');
				}
				else{
					carry = 0;
					res.push_back((sum% 10 ) + '0');
				}
			}
			if(carry != 0)
				res.push_back(carry +0);
			return(reverse(res));
		}
		//////////////////////////////////////////////////
		bigint bigint::operator+(const bigint& other) const{
			bigint temp;
			temp.str = addition(*this, other);
			return temp;
		}
		bigint& bigint::operator+=(const bigint& other){
			(*this) = (*this) + other;
			return (*this);
		}

		bigint& bigint::operator++(){
			*this = *this + bigint(1);
			return *this;
		}
		
		bigint bigint::operator++(int){
			bigint temp = *this;
			*this = *this + bigint(1);
			return temp;
		}

		bigint bigint::operator<<(unsigned int n)const{
			bigint temp = *this;
			temp.str.insert(temp.str.end(), n, 0);
			return temp;
		}

		bigint bigint::operator>>(unsigned int n)const{
			bigint temp = *this;
			size_t len = temp.str.length();

			if (n>= len)
				temp.str = "0";
			else
				temp.str.erase(temp.str.length() - n, n);
			return temp;
		}

		bigint& bigint::operator<<=(unsigned int n){
			*this = *this << n;
			return *this;
		}

		bigint& bigint::operator>>=(unsigned int n){
			*this = *this >> n;
			return *this;
		}

		/////////////////////////////////////////////
		unsigned int stringToUINT(std::string str){
			std::stringstream ss(str);
			unsigned int res;
			ss >> res;
			return res;
		}
		////////////////////////////////////////////

		bigint bigint::operator<<(const bigint& other)const{
			return *this << stringToUINT(other.str);

		}
		bigint bigint::operator>>(const bigint& other)const{
			return *this >> stringToUINT(other.str);
		}

		bigint& bigint::operator<<=(const bigint& other){
			*this = *this << stringToUINT(other.str);
			return *this;
		}
		bigint& bigint::operator>>=(const bigint& other){
			*this = *this >> stringToUINT(other.str);
			return *this;
		}

		bool bigint::operator==(const bigint& other)const{
			return (this->str == other.str);
		}
		bool bigint::operator!=(const bigint& other)const{
			return (this->str == other.str);
		}
		bool bigint::operator>=(const bigint& other)const{
			return(*this > other || *this == other);
		}
		bool bigint::operator<=(const bigint& other)const{
			return(*this < other || *this == other);
		}
		bool bigint::operator>(const bigint& other)const{
			return !((*this) < other || (*this) == other);
		}
		bool bigint::operator<(const bigint& other)const{
			std::string str1 = this->str;
			std::string str2 = other.str;
			size_t len1 = str1.length();
			size_t len2 = str2.length();

			if(len1 != len2)
				return (len1 < len2);
			return(str1 < str2);
		}

std::ostream& operator<<(std::ostream& output, const bigint& obj){
	output << obj.getStr();
	return output;
}
