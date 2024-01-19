template <class T, uint8_t i>
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
    void print()
    {
        for (int ind = 0; ind < i; ind++)
        {
            Serial.print(data[ind]);
            Serial.print(" ");
        }
        Serial.println(" ");
        Serial.print("top: ");
        Serial.println(topInd);
    }

private:
    T data[i+1];
    int topInd;
};
