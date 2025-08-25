# Priority queue

## Max heap priority queue

```cpp
priority_queue<int, vector<int>, greater<int>> pq(comp);
```

## Custom operator syntax 1 - internal lambda

```cpp
priority_queue<int, vector<int>, function<bool(int, int)>> pq( [](int a, int b) {
        return a < b; 
    }
);
```

## Custom operator syntax 2 - external lambda

```cpp
auto comp = [](int a, int b) { 
    return a < b; 
};
priority_queue<int, vector<int>,decltype(comp)> pq(comp);
```

### Custom comparator syntax 3 - comparator struct

```cpp
struct comp{
    bool operator()(const int &a, const int &b){
        return a[0] < b[0];
    }
};
priority_queue<int, vector<int>, comp > pq;
```
