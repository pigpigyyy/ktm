#ifndef _BUFFER_H_
#define _BUFFER_H_

#include "Chtholly.h"

namespace xxd
{
class CHTHOLLY_API VertexBuffer
{
public:
    virtual ~VertexBuffer() { };
    virtual void Bind() = 0;
    virtual void UnBind() = 0;

    static VertexBuffer* Create(float* vertices, uint32_t size);
};   

class CHTHOLLY_API IndexBuffer
{
public:
    virtual ~IndexBuffer() { };
    virtual void Bind() = 0;
    virtual void UnBind() = 0;

    static IndexBuffer* Create(uint32_t* indices, uint32_t size);
};
}

#endif