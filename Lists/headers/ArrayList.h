#pragma once
#include "List.h"

class ArrayList : public List {
    public:
        virtual void show(void) override;
        virtual size_t get_size(void) const override;
        virtual int get_element(size_t index) const override;

        virtual void append(int value) override;
        virtual void prepend(int value) override;
        virtual void insert(int value, size_t index) override;

        virtual int pop_front(void) override;
        virtual int pop_back(void) override;
        virtual int remove(size_t index) override;

        virtual bool search(int value) override;
        
        ArrayList();
        ArrayList(size_t init_capacity);
        ~ArrayList();

    private:
        size_t size;
        size_t capacity;
        int* array;
        void resize(size_t new_capacity);
};