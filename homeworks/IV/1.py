#栈的容量为2，依次入栈abcde，给出所有合理出栈顺序
class Stack:
    def __init__(self, size = 2):
        self.s = []
        self.size = size

    def push(self, val):
        assert not self.isFull() , "Stack is full!"
        self.s.append(val)

    def pop(self):
        return self.s.pop()

    def peek(self):
        assert self.s.__len__(), "Stack is empty!"
        return self.s[-1]
    
    def length(self):
        return self.s.__len__();
    
    def isFull(self):
        if self.s.__len__() == self.size :
            return True
        return False

    def isEmpty(self):
        return not bool(self.s.__len__())


a = Stack();

l = ['a','b','c','d','e']

res = []

count = 1

def dfs(atmp, i, res:list):
    global count
    
    if atmp.isEmpty():
        if i>=l.__len__():
            print(count, ":", res)
            print()
            count += 1
            return
        atmp.push(l[i])
        dfs(atmp, i+1, res.copy())
    elif atmp.isFull():
        res.append(atmp.pop())
        dfs(atmp, i, res.copy())
    else:
        tmp = atmp.pop()
        res.append(tmp)
        dfs(atmp, i, res.copy())

        if i>=l.__len__():
            return
        res.pop()
        atmp.push(tmp)
        atmp.push(l[i])
        dfs(atmp, i+1, res.copy())
    
    
dfs(a, 0, res.copy())
    
    
    
    
    