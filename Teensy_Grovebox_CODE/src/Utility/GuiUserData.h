#include "Audio/AudioSynth.h"

// * Template class for user data storage in Pages
// This make the data object responsible for applying the changes to the system.
template <class T>
class GuiUserData
{
public:
    GuiUserData(T data, int8_t id = 0, void (*onValueChangedFunc) (T data, int8_t id) = NULL)
    {
        this->data = data;
        this->id = id;
        this->setOnValueChanged(onValueChangedFunc);
    }
    T get()
    {
        return data;
    }
    void set(T data)
    {
        this->data = data;
        if (onValueChangedFunc != NULL)
        {
            onValueChangedFunc(data, id);
        }
    }
    void setOnValueChanged(void (*onValueChangedFunc) (T data, int8_t id))
    {
        this->onValueChangedFunc = onValueChangedFunc;
    }
private:
    T data;
    int8_t id;
    void (*onValueChangedFunc) (T data, int8_t id);
};

