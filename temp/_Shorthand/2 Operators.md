# C++ Operator Overloading Quick Reference

## What is Operator Overloading?
Operator overloading allows you to define custom behavior for operators when used with user-defined types (classes/structs). Essential for creating clean, intuitive DSA implementations.

## Syntax Forms
- **Member function**: `ReturnType operator@(parameters)`
- **Friend function**: `friend ReturnType operator@(parameters)`
- **Global function**: `ReturnType operator@(parameters)`

## Overloadable Operators
- **Arithmetic**: `+` `-` `*` `/` `%` `++` `--`
- **Comparison**: `==` `!=` `<` `>` `<=` `>=` `<=>`
- **Assignment**: `=` `+=` `-=` `*=` `/=` `%=`
- **Subscript**: `[]`
- **Function call**: `()`
- **Stream**: `<<` `>>`
- **Others**: `->` `*` `&` `,`

## Non-Overloadable Operators
`::` `.` `.*` `?:` `sizeof` `typeid`

## Basic Point Class with Arithmetic Operators

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

class Point {
public:
    int x, y;
    
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    
    // 1. Addition (member function)
    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }
    
    // 2. Subtraction (member function)
    Point operator-(const Point& other) const {
        return Point(x - other.x, y - other.y);
    }
    
    // 3. Scalar multiplication (member function)
    Point operator*(int scalar) const {
        return Point(x * scalar, y * scalar);
    }
    
    // 4. Compound assignment
    Point& operator+=(const Point& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    
    // 5. Pre-increment
    Point& operator++() {
        ++x; ++y;
        return *this;
    }
    
    // 6. Post-increment
    Point operator++(int) {
        Point temp = *this;
        ++x; ++y;
        return temp;
    }
    
    // 7. Stream output (friend function needed for left operand)
    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }
};

// 8. Scalar multiplication (global function for int * Point)
Point operator*(int scalar, const Point& p) {
    return p * scalar;
}

int main() {
    Point p1(3, 4);
    Point p2(1, 2);
    
    Point sum = p1 + p2;        // (4, 6)
    Point diff = p1 - p2;       // (2, 2)
    Point scaled = p1 * 2;      // (6, 8)
    Point scaled2 = 3 * p1;     // (9, 12)
    
    std::cout << "p1: " << p1 << "\n";
    std::cout << "p2: " << p2 << "\n";
    std::cout << "sum: " << sum << "\n";
    std::cout << "diff: " << diff << "\n";
    std::cout << "scaled: " << scaled << "\n";
    
    p1 += p2;  // p1 becomes (4, 6)
    std::cout << "p1 after +=: " << p1 << "\n";
    
    return 0;
}
```

## Comparison Operators for Sorting

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

struct Student {
    std::string name;
    int grade;
    
    Student(std::string n, int g) : name(n), grade(g) {}
    
    // 1. Equality operator
    bool operator==(const Student& other) const {
        return name == other.name && grade == other.grade;
    }
    
    // 2. Inequality operator
    bool operator!=(const Student& other) const {
        return !(*this == other);
    }
    
    // 3. Less than (for sorting)
    bool operator<(const Student& other) const {
        if (grade != other.grade) return grade > other.grade; // Higher grade first
        return name < other.name; // Then alphabetical
    }
    
    // 4. Other comparison operators
    bool operator>(const Student& other) const { return other < *this; }
    bool operator<=(const Student& other) const { return !(other < *this); }
    bool operator>=(const Student& other) const { return !(*this < other); }
    
    // 5. Three-way comparison (C++20)
    auto operator<=>(const Student& other) const {
        if (auto cmp = grade <=> other.grade; cmp != 0) return cmp;
        return name <=> other.name;
    }
    
    // Stream output
    friend std::ostream& operator<<(std::ostream& os, const Student& s) {
        return os << s.name << "(" << s.grade << ")";
    }
};

int main() {
    std::vector<Student> students = {
        {"Alice", 85}, {"Bob", 92}, {"Charlie", 85}, {"Diana", 78}
    };
    
    // Sort using overloaded < operator
    std::sort(students.begin(), students.end());
    
    std::cout << "Sorted students:\n";
    for (const auto& s : students) {
        std::cout << s << " ";
    }
    std::cout << "\n";
    
    // Use in set (requires < operator)
    std::set<Student> studentSet(students.begin(), students.end());
    std::cout << "Unique students: " << studentSet.size() << "\n";
    
    // Comparison usage
    if (students[0] == students[1]) {
        std::cout << "First two students are equal\n";
    }
    
    return 0;
}
```

## Custom Container with Subscript Operator

```cpp
#include <iostream>
#include <vector>
#include <stdexcept>

template<typename T>
class SafeVector {
private:
    std::vector<T> data;
    
public:
    SafeVector(std::initializer_list<T> init) : data(init) {}
    
    // 1. Subscript operator (non-const version)
    T& operator[](size_t index) {
        if (index >= data.size()) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }
    
    // 2. Subscript operator (const version)
    const T& operator[](size_t index) const {
        if (index >= data.size()) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }
    
    // 3. Function call operator (for 2D access)
    T& operator()(size_t row, size_t col) {
        return data[row * 3 + col]; // Assuming 3 columns for demo
    }
    
    // 4. Assignment operator
    SafeVector& operator=(const SafeVector& other) {
        if (this != &other) {
            data = other.data;
        }
        return *this;
    }
    
    // 5. Stream insertion
    friend std::ostream& operator<<(std::ostream& os, const SafeVector& sv) {
        os << "[";
        for (size_t i = 0; i < sv.data.size(); ++i) {
            os << sv.data[i];
            if (i < sv.data.size() - 1) os << ", ";
        }
        os << "]";
        return os;
    }
    
    size_t size() const { return data.size(); }
    void push_back(const T& value) { data.push_back(value); }
};

int main() {
    SafeVector<int> sv = {1, 2, 3, 4, 5};
    
    // Using subscript operator
    std::cout << "sv[2] = " << sv[2] << "\n"; // 3
    sv[2] = 10;
    std::cout << "After sv[2] = 10: " << sv << "\n";
    
    // Using function call operator (simulating 2D array)
    SafeVector<int> matrix = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << "matrix(1,2) = " << matrix(1, 2) << "\n"; // Element at row 1, col 2
    
    // Assignment
    SafeVector<int> sv2 = {10, 20, 30};
    sv = sv2;
    std::cout << "After assignment: " << sv << "\n";
    
    return 0;
}
```

## Smart Pointer and Advanced Operators

```cpp
#include <iostream>
#include <memory>

// Custom smart pointer demonstration
template<typename T>
class SimplePtr {
private:
    T* ptr;
    
public:
    explicit SimplePtr(T* p = nullptr) : ptr(p) {}
    ~SimplePtr() { delete ptr; }
    
    // 1. Dereference operator
    T& operator*() {
        return *ptr;
    }
    
    // 2. Arrow operator
    T* operator->() {
        return ptr;
    }
    
    // 3. Boolean conversion
    explicit operator bool() const {
        return ptr != nullptr;
    }
    
    // 4. Copy constructor and assignment (Rule of 3)
    SimplePtr(const SimplePtr&) = delete;
    SimplePtr& operator=(const SimplePtr&) = delete;
    
    // 5. Move constructor and assignment (Rule of 5)
    SimplePtr(SimplePtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }
    
    SimplePtr& operator=(SimplePtr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }
};

// Custom class for demonstration
class Node {
public:
    int value;
    Node* next;
    
    Node(int v) : value(v), next(nullptr) {}
    
    void print() const {
        std::cout << "Node value: " << value << "\n";
    }
};

// Fraction class with comprehensive operators
class Fraction {
private:
    int num, den;
    
    int gcd(int a, int b) const {
        return b == 0 ? a : gcd(b, a % b);
    }
    
    void reduce() {
        int g = gcd(abs(num), abs(den));
        num /= g;
        den /= g;
        if (den < 0) { num = -num; den = -den; }
    }
    
public:
    Fraction(int n = 0, int d = 1) : num(n), den(d) {
        if (den == 0) throw std::invalid_argument("Denominator cannot be zero");
        reduce();
    }
    
    // Arithmetic operators
    Fraction operator+(const Fraction& other) const {
        return Fraction(num * other.den + other.num * den, den * other.den);
    }
    
    Fraction operator-(const Fraction& other) const {
        return Fraction(num * other.den - other.num * den, den * other.den);
    }
    
    Fraction operator*(const Fraction& other) const {
        return Fraction(num * other.num, den * other.den);
    }
    
    Fraction operator/(const Fraction& other) const {
        return Fraction(num * other.den, den * other.num);
    }
    
    // Comparison operators
    bool operator<(const Fraction& other) const {
        return num * other.den < other.num * den;
    }
    
    bool operator==(const Fraction& other) const {
        return num == other.num && den == other.den;
    }
    
    // Stream operators
    friend std::ostream& operator<<(std::ostream& os, const Fraction& f) {
        if (f.den == 1) return os << f.num;
        return os << f.num << "/" << f.den;
    }
    
    friend std::istream& operator>>(std::istream& is, Fraction& f) {
        char slash;
        is >> f.num >> slash >> f.den;
        f.reduce();
        return is;
    }
};

int main() {
    // Smart pointer usage
    SimplePtr<Node> nodePtr(new Node(42));
    if (nodePtr) {
        nodePtr->print();         // Using arrow operator
        (*nodePtr).value = 100;   // Using dereference operator
        nodePtr->print();
    }
    
    // Fraction operations
    Fraction f1(3, 4);
    Fraction f2(1, 2);
    
    std::cout << "f1 = " << f1 << "\n";
    std::cout << "f2 = " << f2 << "\n";
    std::cout << "f1 + f2 = " << (f1 + f2) << "\n";
    std::cout << "f1 * f2 = " << (f1 * f2) << "\n";
    std::cout << "f1 < f2: " << (f1 < f2) << "\n";
    
    return 0;
}
```

## Design Guidelines

### When to Use Member vs Friend vs Global Functions

**Member Functions** (most common):
- Use for most operators where left operand is your class
- Examples: `+`, `-`, `*`, `/`, `+=`, `==`, `<`, `[]`, `()`

**Friend Functions**:
- Use when you need access to private members but left operand isn't your class
- Examples: `<<` (stream output), `>>` (stream input)

**Global Functions**:
- Use when you don't need access to private members
- Examples: `int * Point` (when Point already has `Point * int`)

### Common Patterns

```cpp
class MyClass {
public:
    // 1. If you define ==, also define !=
    bool operator==(const MyClass& other) const { /* ... */ }
    bool operator!=(const MyClass& other) const { return !(*this == other); }
    
    // 2. If you define <, you can derive other comparisons
    bool operator<(const MyClass& other) const { /* ... */ }
    bool operator>(const MyClass& other) const { return other < *this; }
    bool operator<=(const MyClass& other) const { return !(other < *this); }
    bool operator>=(const MyClass& other) const { return !(*this < other); }
    
    // 3. Compound assignment, then define binary operator
    MyClass& operator+=(const MyClass& other) { /* modify this */ return *this; }
    MyClass operator+(const MyClass& other) const {
        MyClass result = *this;
        result += other;
        return result;
    }
    
    // 4. Pre/post increment pattern
    MyClass& operator++() {        // Pre-increment
        /* increment logic */
        return *this;
    }
    
    MyClass operator++(int) {      // Post-increment
        MyClass temp = *this;
        ++(*this);
        return temp;
    }
};
```

## DSA Applications

```cpp
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

// Custom hash function for pairs (useful in unordered_map/set)
struct PairHash {
    size_t operator()(const std::pair<int, int>& p) const {
        return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
    }
};

// Graph edge with weight comparison
struct Edge {
    int from, to, weight;
    
    Edge(int f, int t, int w) : from(f), to(t), weight(w) {}
    
    // For Kruskal's algorithm - sort by weight
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Edge& e) {
        return os << "(" << e.from << "->" << e.to << ":" << e.weight << ")";
    }
};

// Interval for scheduling problems
struct Interval {
    int start, end;
    
    Interval(int s, int e) : start(s), end(e) {}
    
    // Sort by end time for greedy scheduling
    bool operator<(const Interval& other) const {
        return end < other.end;
    }
    
    // Check for overlap
    bool operator&&(const Interval& other) const {
        return !(end <= other.start || other.end <= start);
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Interval& i) {
        return os << "[" << i.start << ", " << i.end << "]";
    }
};

int main() {
    // Edge sorting for Kruskal's algorithm
    std::vector<Edge> edges = {
        {1, 2, 4}, {1, 3, 2}, {2, 3, 1}, {2, 4, 5}, {3, 4, 3}
    };
    
    std::sort(edges.begin(), edges.end());
    std::cout << "Edges sorted by weight:\n";
    for (const auto& e : edges) {
        std::cout << e << " ";
    }
    std::cout << "\n";
    
    // Interval scheduling
    std::vector<Interval> intervals = {
        {1, 3}, {2, 4}, {3, 5}, {0, 2}, {4, 6}
    };
    
    std::sort(intervals.begin(), intervals.end());
    std::cout << "Intervals sorted by end time:\n";
    for (const auto& i : intervals) {
        std::cout << i << " ";
    }
    std::cout << "\n";
    
    // Check overlap between first two intervals
    if (intervals[0] && intervals[1]) {
        std::cout << "First two intervals overlap\n";
    }
    
    return 0;
}
```