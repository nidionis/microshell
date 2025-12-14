#ifndef AF362267_6362_483A_AF07_185743BE0F6E
#define AF362267_6362_483A_AF07_185743BE0F6E
#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>
#include <string>

class vect2 {
    private:
        int _x;
        int _y;

    public:
    vect2(int x = 0, int y = 0);
    vect2(const vect2& other);
    vect2& operator=(const vect2& rhs);
    ~vect2();

    
    int& operator[](int i);
    int operator[](int i) const;

    // Binary arithmetic operators (must be const!)
    vect2 operator+(int i) const;
    vect2 operator-(int i) const;
    vect2 operator*(int i) const;
    vect2 operator+(const vect2& vec) const;
    vect2 operator-(const vect2& vec) const;
    vect2 operator*(const vect2& vec) const;

    // Unary operators
    vect2 operator-() const;  // Negation: -v2
    vect2 operator++(int);    // Post-increment: v++
    vect2& operator++();      // Pre-increment: ++v
    vect2 operator--(int);    // Post-decrement: v--
    vect2& operator--();      // Pre-decrement: --v

    // Comparison operators (must be const!)
    bool operator==(const vect2& vec) const;
    bool operator!=(const vect2& vec) const;

    // Compound assignment operators
    vect2& operator+=(int i);
    vect2& operator-=(int i);
    vect2& operator*=(int i);
    vect2& operator+=(const vect2& vec);
    vect2& operator-=(const vect2& vec);

    void print(std::ostream& os) const;
    
    // Friend functions for reverse operations
    friend vect2 operator+(int i, const vect2& vect);
    friend vect2 operator-(int i, const vect2& vect);
    friend vect2 operator*(int i, const vect2& vect);
    friend std::ostream& operator<<(std::ostream& os, const vect2& obj);
};



#endif


#endif /* AF362267_6362_483A_AF07_185743BE0F6E */
