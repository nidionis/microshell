# BigInt Assignment - Complete Guide

## Overview
The bigint assignment requires you to create a class that handles arbitrarily large unsigned integers by storing them as strings. This allows you to work with numbers larger than `SIZE_MAX` without precision loss.

---

## Core Concept

### Why BigInt?
- Standard `unsigned int` has a maximum value (typically 4,294,967,295 on 32-bit systems)
- BigInt stores numbers as strings, allowing unlimited size
- Operations are performed digit-by-digit, similar to manual arithmetic

### Key Idea: String Storage
```cpp
class bigint {
private:
    std::string str;  // "12345" represents the number 12345
};
```

---

## Required Operators & Functions

### 1. **Constructors**

#### Default Constructor
```cpp
bigint::bigint() {
    this->str = "0";  // Initialize to zero
}
```

#### Parameterized Constructor
```cpp
bigint::bigint(unsigned int num) {
    std::stringstream ss;
    ss << num;
    this->str = ss.str();  // Convert number to string
}
```

#### Copy Constructor
```cpp
bigint::bigint(const bigint& source) {
    (*this) = source;  // Use assignment operator
}
```

---

### 2. **Assignment Operator**

```cpp
bigint& bigint::operator=(const bigint& source) {
    if(this == &source)  // Self-assignment check
        return(*this);
    this->str = source.str;
    return(*this);
}
```

**Purpose**: Allows `bigint b = a;` syntax

---

### 3. **Addition Operators**

#### Strategy: Manual Addition Algorithm
You need to add digit-by-digit from right to left, handling carries.

**Steps:**
1. Reverse both strings (to process from least significant digit)
2. Pad shorter string with zeros
3. Add digit by digit, tracking carry
4. Reverse result back

#### Helper Function: Reverse String
```cpp
std::string reverse(const std::string& str) {
    std::string revStr;
    for(size_t i = str.length(); i > 0; i--) {
        revStr.push_back(str[i - 1]);
    }
    return(revStr);
}
```

#### Addition Logic
```cpp
std::string addition(const bigint& obj1, const bigint& obj2) {
    std::string str1 = reverse(obj1.getStr());
    std::string str2 = reverse(obj2.getStr());
    std::string result;
    
    // Make both strings same length
    size_t len1 = str1.length();
    size_t len2 = str2.length();
    
    if(len1 > len2) {
        for(size_t i = 0; i < len1 - len2; i++)
            str2.push_back('0');
    }
    else if(len2 > len1) {
        for(size_t i = 0; i < len2 - len1; i++)
            str1.push_back('0');
    }
    
    int carry = 0;
    for(size_t i = 0; i < str1.length(); i++) {
        int digit1 = str1[i] - '0';
        int digit2 = str2[i] - '0';
        int sum = digit1 + digit2 + carry;
        
        if(sum > 9) {
            carry = sum / 10;
            result.push_back((sum % 10) + '0');
        }
        else {
            carry = 0;
            result.push_back(sum + '0');
        }
    }
    
    if(carry != 0)
        result.push_back(carry + '0');
    
    return(reverse(result));
}
```

#### Operator+ Implementation
```cpp
bigint bigint::operator+(const bigint& other) const {
    bigint temp;
    temp.str = addition(*this, other);
    return(temp);
}
```

#### Operator+= Implementation
```cpp
bigint& bigint::operator+=(const bigint& other) {
    (*this) = (*this) + other;
    return(*this);
}
```

---

### 4. **Increment Operators**

#### Pre-increment (++x)
```cpp
bigint& bigint::operator++() {
    *this = *this + bigint(1);
    return(*this);
}
```
- Returns reference to modified object
- Used as: `++b`

#### Post-increment (x++)
```cpp
bigint bigint::operator++(int) {
    bigint temp = *this;  // Save current value
    *this = *this + bigint(1);  // Increment
    return(temp);  // Return old value
}
```
- Returns copy of original value
- Used as: `b++`
- The `int` parameter distinguishes it from pre-increment

---

### 5. **Shift Operators (Digit Shift)**

**Concept**: Instead of bit shifting, we shift decimal digits.
- Left shift: Add zeros to the right (`42 << 3 = 42000`)
- Right shift: Remove digits from the right (`1337 >> 2 = 13`)

#### Left Shift with unsigned int
```cpp
bigint bigint::operator<<(unsigned int n) const {
    bigint temp = *this;
    temp.str.insert(temp.str.end(), n, '0');  // Add n zeros to end
    return(temp);
}
```

#### Right Shift with unsigned int
```cpp
bigint bigint::operator>>(unsigned int n) const {
    bigint temp = *this;
    size_t len = temp.str.length();
    
    if(n >= len)
        temp.str = "0";  // Shifted all digits away
    else
        temp.str.erase(temp.str.length() - n, n);  // Remove last n characters
    
    return(temp);
}
```

#### Assignment Shift Operators
```cpp
bigint& bigint::operator<<=(unsigned int n) {
    (*this) = (*this) << n;
    return(*this);
}

bigint& bigint::operator>>=(unsigned int n) {
    (*this) = (*this) >> n;
    return(*this);
}
```

#### Shift with bigint Objects
Need to convert bigint to unsigned int first:

```cpp
unsigned int stringToUINT(std::string str) {
    std::stringstream ss(str);
    unsigned int res;
    ss >> res;
    return (res);
}

bigint bigint::operator<<(const bigint& other) const {
    return (*this) << stringToUINT(other.str);
}

bigint bigint::operator>>(const bigint& other) const {
    return (*this) >> stringToUINT(other.str);
}

bigint& bigint::operator<<=(const bigint& other) {
    (*this) = (*this) << stringToUINT(other.str);
    return(*this);
}

bigint& bigint::operator>>=(const bigint& other) {
    (*this) = (*this) >> stringToUINT(other.str);
    return(*this);
}
```

---

### 6. **Comparison Operators**

#### Equality (==)
```cpp
bool bigint::operator==(const bigint& other) const {
    return (this->str == other.str);
}
```

#### Inequality (!=)
```cpp
bool bigint::operator!=(const bigint& other) const {
    return !((*this) == other);
}
```

#### Less Than (<)
```cpp
bool bigint::operator<(const bigint& other) const {
    std::string str1 = this->str;
    std::string str2 = other.str;
    size_t len1 = str1.length();
    size_t len2 = str2.length();
    
    // If different lengths, shorter is smaller
    if(len1 != len2)
        return(len1 < len2);
    
    // Same length: lexicographic comparison works
    return(str1 < str2);
}
```

**Why this works:**
- Fewer digits = smaller number (42 < 1337)
- Same digits: lexicographic comparison is correct ("042" < "100")

#### Greater Than (>)
```cpp
bool bigint::operator>(const bigint& other) const {
    return !((*this) < other || (*this) == other);
}
```

#### Less Than or Equal (<=)
```cpp
bool bigint::operator<=(const bigint& other) const {
    return ((*this) < other || (*this) == other);
}
```

#### Greater Than or Equal (>=)
```cpp
bool bigint::operator>=(const bigint& other) const {
    return ((*this) > other || (*this) == other);
}
```

---

### 7. **Output Stream Operator**

```cpp
std::ostream& operator<<(std::ostream& output, const bigint& obj) {
    output << obj.getStr();
    return(output);
}
```

**Must be non-member function** because:
- Left operand is `std::ostream`, not `bigint`
- Allows syntax: `std::cout << bigint_obj`

---

## Implementation Strategy

### Step-by-Step Approach

1. **Start with basic structure:**
   - Private string member
   - Constructors
   - Getter function

2. **Implement addition first:**
   - Helper functions (reverse, addition)
   - operator+
   - operator+=

3. **Add increment operators:**
   - Pre-increment
   - Post-increment

4. **Implement shift operators:**
   - Start with unsigned int versions
   - Add bigint versions using conversion

5. **Complete comparison operators:**
   - Implement < carefully
   - Derive others from < and ==

6. **Add output operator:**
   - Must be non-member function

---

## Common Pitfalls & Tips

### ⚠️ Pitfalls

1. **Forgetting to reverse back after addition**
   - You reverse for processing, must reverse result

2. **Not handling carries correctly**
   - Carry can propagate through multiple digits

3. **Comparison operator logic errors**
   - `>` is NOT simply `!(<)` (must also check !=)
   - Correct: `!(< || ==)` or `(> || ==)`

4. **Self-assignment in operator=**
   - Always check `if(this == &source)`

5. **Post-increment return type**
   - Must return by value, not reference
   - Must return ORIGINAL value before increment

6. **Output operator as member function**
   - Must be non-member to work with `cout <<`

### ✅ Tips

1. **Test incrementally**
   - Test each operator separately before moving on

2. **Use provided main.cpp**
   - It shows expected behavior for all operations

3. **Watch for edge cases:**
   - Adding to zero
   - Shifting by more than number length
   - Comparing numbers of different lengths

4. **String operations to remember:**
   - `str.insert(str.end(), n, '0')` - Add n zeros
   - `str.erase(pos, len)` - Remove len chars from pos
   - `str.push_back(char)` - Add character to end

---

## Testing Examples

### Addition Test
```cpp
bigint a(42);
bigint b(21);
std::cout << a + b;  // Should output: 63
```

### Shift Test
```cpp
bigint x(42);
std::cout << (x << 3);  // Should output: 42000
std::cout << (x >> 1);  // Should output: 4
```

### Comparison Test
```cpp
bigint a(42);
bigint b(1337);
std::cout << (a < b);   // Should output: 1 (true)
std::cout << (a > b);   // Should output: 0 (false)
```

### Increment Test
```cpp
bigint x(5);
std::cout << ++x;  // Should output: 6, x is now 6
std::cout << x++;  // Should output: 6, x is now 7
std::cout << x;    // Should output: 7
```

---

## Expected Output from main.cpp

```
a = 42
b = 21
c = 0
d = 1337
e = 1337
a + b = 63
a + c = 42
(c += a) = 42
b = 21
++b = 22
b++ = 22
(b << 10) + 42 = 23000000042
(d <<= 4) = 13370000, d: 13370000
(d >>= 2) = 133700, d: 133700
a = 42
d = 133700
(d < a) = 0
(d > a) = 1
(d == d) = 1
(d != a) = 1
(d <= a) = 0
(d >= a) = 1
(x << y) = 1234567800000, x: 12345678, y: 5
(x >>= y) = 123, x: 123, y: 5
(x >= y) = 1, x: 123, y: 5
x= 3936, y= 20480
(x >= y) = 0, x: 3936, y: 20480
```

---

## Exam Tips

1. **Time Management:**
   - Allocate 60-90 minutes for this assignment
   - Implement in the order suggested above

2. **Debugging:**
   - Use std::cout to verify intermediate results
   - Test each operator before moving to next

3. **Memory:**
   - Know the manual addition algorithm
   - Remember comparison logic (length first, then lexicographic)
   - Remember pre vs post increment difference

4. **Common Mistakes to Avoid:**
   - Forgetting `const` on read-only methods
   - Wrong return types (reference vs value)
   - Off-by-one errors in string manipulation

5. **Quick Reference:**
   - String to int: `std::stringstream`
   - Int to string: `std::stringstream` or `std::to_string()`
   - Add to string end: `str.push_back()` or `str.insert(str.end())`
   - Remove from end: `str.erase(pos, len)`

---

## Summary Checklist

Before submitting, verify you have implemented:

- [ ] Default constructor (initializes to 0)
- [ ] Parameterized constructor (unsigned int)
- [ ] Copy constructor
- [ ] Assignment operator (=)
- [ ] Addition operator (+)
- [ ] Addition assignment operator (+=)
- [ ] Pre-increment operator (++x)
- [ ] Post-increment operator (x++)
- [ ] Left shift with unsigned int (<<)
- [ ] Right shift with unsigned int (>>)
- [ ] Left shift assignment with unsigned int (<<=)
- [ ] Right shift assignment with unsigned int (>>=)
- [ ] Left shift with bigint object (<<)
- [ ] Right shift with bigint object (>>)
- [ ] Left shift assignment with bigint object (<<=)
- [ ] Right shift assignment with bigint object (>>=)
- [ ] Equality operator (==)
- [ ] Inequality operator (!=)
- [ ] Less than operator (<)
- [ ] Greater than operator (>)
- [ ] Less than or equal operator (<=)
- [ ] Greater than or equal operator (>=)
- [ ] Output stream operator (<<)
- [ ] Getter function (getStr)

Good luck with your exam! 🚀
