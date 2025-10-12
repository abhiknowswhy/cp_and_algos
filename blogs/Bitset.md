# 🧾 **C++ Bitset Cheat Sheet**

Bitset operation is a fast and memory efficient operation for storing a boolean vector
The difference between bitset and boolean vector is bitset must be of fixed size at compile time, i.e. we cannot declare a variable sized bitset

### **Declaration**

```cpp
#include <bitset>
bitset<8> b1;                   // 00000000
bitset<8> b2(5);                 // 00000101
bitset<8> b3("101");             // 00000101 (string, right aligned)
```

---

### **Core APIs**

| **Category**      | **API**           | **Description / Example**            |
| ----------------- | ----------------- | ------------------------------------ |
| **Access**        | `b[i]`            | Access bit at index `i` (0 = LSB).   |
| **Set**           | `b.set()`         | Set all bits to `1`.                 |
|                   | `b.set(pos)`      | Set bit at `pos` to `1`.             |
|                   | `b.set(pos, val)` | Set bit at `pos` to `val` (`0`/`1`). |
| **Reset**         | `b.reset()`       | Reset all bits to `0`.               |
|                   | `b.reset(pos)`    | Reset bit at `pos` to `0`.           |
| **Flip**          | `b.flip()`        | Flip all bits.                       |
|                   | `b.flip(pos)`     | Flip bit at `pos`.                   |
| **Test**          | `b.test(pos)`     | Returns true if bit at `pos` is `1`. |
| **Count / Check** | `b.count()`       | Number of `1`s in bitset.            |
|                   | `b.any()`         | True if any bit is `1`.              |
|                   | `b.none()`        | True if all bits are `0`.            |
|                   | `b.all()`         | True if all bits are `1`.            |
| **Size**          | `b.size()`        | Returns size of bitset (fixed).      |
| **Conversion**    | `b.to_ulong()`    | Convert to `unsigned long`.          |
|                   | `b.to_ullong()`   | Convert to `unsigned long long`.     |
|                   | `b.to_string()`   | Convert to string `"0101..."`.       |
| **Bitwise Ops**   | `a & b`           | AND                                  |
|                   | `a \|\| b`        | OR                                   |
|                   | `a ^ b`           | XOR                                  |
|                   | `~a`              | NOT                                  |
|                   | `a << k`          | Left shift by `k`.                   |
|                   | `a >> k`          | Right shift by `k`.                  |
| **Compare**       | `a == b`          | Equality check.                      |
|                   | `a != b`          | Inequality check.                    |

---

### **Quick Examples**

```cpp
bitset<8> b("10110010");

cout << b.count();     // 4
cout << b.any();       // 1 (true)
cout << b.none();      // 0 (false)
cout << b.all();       // 0
cout << b.test(2);     // 1

b.set(1);              // 10110011
b.reset(3);            // 10100011
b.flip(0);             // 10100010

cout << b.to_ulong();  // 162
cout << (b << 2);      // 10001000
```

---

✅ `std::bitset` is **fixed-size**, so if you need **dynamic-sized bit arrays**, you’d use **`vector<bool>`** or external libraries like **Boost Dynamic Bitset**.

---
