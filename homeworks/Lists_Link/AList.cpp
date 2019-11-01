#include "List.cpp"
template <typename E>
class AList: public List<E>{
private:
    
    int maxSize; // Maximum size of list
    int listSize; // Number of list items now
    int curr; // Position of current element
    E* listArray; //Array holding list elements

public:
    Alist(int size = defaultSize){
        maxSize = size;
        listSize = curr = 0;
        listArray = new E[maxSize];
    }

    ~AList() { delete [] listArray; }

    void clear(){
        //delete [] listArray;
        listSize = curr = 0;
        //listArray = new E[maxSize];
    }

    // Insert "it" at current position
    void insert(const E& it){
        // Assert(listSize < maxSize, "List capacity exceeded");
        assert(listSize < maxSize);
        for (int i = listSize; i > curr; i--){
            listArray[i] = listArray[i-1];
        }
        listArray[curr] = it;
        listSize++;
    }

    void append(const E& it){
        // Assert(listSize < maxSize, "List capacity exceeded");
        assert(listSize < maxSize);
        listArray[listSize++] = it;
    }

    // Remove and return the current element.
    E remove(){
        // Assert( (curr>=0) && (curr < listSize), "No element");
        assert( (curr>=0) && (curr < listSize));
        E it = listArray[curr];
        for (int i = curr; i < listSize-1; i++)
        {
            listArray[i] = listArray[i+1];
        }
        listSize--;
        return it;
    }

    void moveToStart() { curr =0; }
    void moveToEnd() {curr = listSize;}
    void prev() { if (curr !=0) curr--; }
    void next() { if (curr < listSize) curr++; }
    
    int length() const { return listSize; }

    int currPost() const {return curr;}

    void moveToPos(int pos){
        // Assert((pos>=0)&&(pos<=listSize), "Pos out of range");
        assert((pos>=0)&&(pos<=listSize) );
        curr = pos;
    }

    const E& getValue() const{
        // Assert((curr>=0)&&(curr<listSize), "No current element");
        assert((curr>=0)&&(curr<listSize) );
        return listArray[curr];
    }

};