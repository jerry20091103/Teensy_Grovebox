

template <class T, int i>
class SimpleStack
{
public:
    SimpleStack()
    {
        topInd = 0;
    };
    ~SimpleStack(){};
    void push(T x)
    {
        if (topInd < i)
        {
            data[topInd] = x;
            topInd++;
        }
    };
    
    T pop()
    {
        if (topInd > 0)
        {
            topInd--;
            return data[topInd];
        }
        else
        {
            return 0;
        }
    };
    T top()
    {
        if (topInd > 0)
        {
            return data[topInd - 1];
        }
        else
        {
            return 0;
        }
    };
    int size()
    {
        return topInd;
    };

private:
    T data[i];
    int topInd;
};
