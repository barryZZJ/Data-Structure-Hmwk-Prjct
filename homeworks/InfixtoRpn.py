#计算rpn:
# 在计算机中，我们通常这样实现： 
# 从左向右遍历，遇到数就入栈，遇到运算符就从栈顶弹出两个元素，
# 将后弹出的与先弹出的进行运算（运算顺序从左到右），再将运算结果入栈，
# 直到栈中只有一个元素（或遍历完整个后缀表达式）

#生成rpn：
# 从左向右遍历中缀表达式，遇到数字就直接写入后缀表达式；
# 遇到运算符，若它比栈顶的运算符的优先级高，则直接入栈，
# 若它比栈顶的运算符的优先级低或等，出栈直到它比栈顶的运算符的优先级高，
# 将出栈的运算符按出栈顺序放入后缀表达式并将当前运算符入栈；
# 遇到左括号直接入栈；
# 遇到右括号，出栈直到左括号，将出栈的运算符按出栈顺序放入后缀表达式。
# 剩下的全部出栈

# -*- coding=utf-8 -*-

from stack import Stack
def trans(x:str):
    s = Stack()
    # x = input("inFix here:\n")

    for i in range(len(x)):
        if x[i] == "(" :
            s.push(x[i])
            
        elif x[i] == "*" or x[i] == "/":
            s.push(x[i])
            
        elif x[i] =="+" or x[i] == "-":
            while not s.isEmpty() and s.peek() != "(":
                print(s.pop() ,end="")
            s.push(x[i])
            
        elif x[i] == ")":
            while not s.isEmpty() and s.peek() != "(":
                print(s.pop() ,end="")
            if s.peek() == "(":
                s.pop()
                
        else:
            print(x[i] ,end="")
    while not s.isEmpty():
        print(s.pop(),end="")
    

if __name__ == '__main__':
    x = "3+(9-8/3)*(3-(6+7)/(6+5))"
    print(f"before:\n{x}")
    print("after:")
    trans(x)
    print()
    x = "7+6-5*6+7/4-3*3+2"
    print(f"before:\n{x}")
    print("after:")
    trans(x)
    print()
    
    


        