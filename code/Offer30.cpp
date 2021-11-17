class MinStack {
public:
    /** initialize your data structure here. */
    stack<int> stk1, stk2;
    MinStack() { }
    
    void push(int x) {
        if (stk1.empty() || stk2.top() >= x) {
            stk2.push(x);
        } 
        stk1.push(x);
    }
    
    void pop() {
        if (stk1.top() == stk2.top()) stk2.pop();
        stk1.pop();
    }
    
    int top() {
        return stk1.top();
    }
    
    int min() {
        return stk2.top();
    }
};