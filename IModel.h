#ifndef __i_model_h__
#define __i_model_h__

class IModel
{
public:
    virtual ~IModel() {}
    virtual void transform() = 0;
    virtual void draw() = 0;
};

#endif
