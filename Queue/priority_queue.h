#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__

#include <vector>

namespace msh
{

    template <typename _Tp>
    class maxHeap
    {
    private:
        std::vector<_Tp> __v;
        size_t __size;

    public:
        bool empty();
        size_t size();
        _Tp top();
        void push();
        void pop();

    private:
        void maxHeapify();
    };

    template <typename _Tp>
    class minHeap
    {
    private:
        std::vector<_Tp> __v;
        size_t __size;

    public:
        bool empty();
        size_t size();
        _Tp top();
        void push();
        void pop();
        
    private:
        void minHeapify();
    };

} //namespace msh

#endif //__PRIORITY_QUEUE_H__