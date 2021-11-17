class CQueue {
public:
    stack<int> stk1, stk2;
    CQueue() {
    }
    
    void appendTail(int value) {
        stk1.push(value);
    }
    
    int deleteHead() {
        int res = -1;
        if (stk2.empty()) {
            while(!stk1.empty()) {
                stk2.push(stk1.top());
                stk1.pop();
            }
        }
        if (!stk2.empty()) {
            res = stk2.top();
            stk2.pop(); 
        }
        return res;
    }
};