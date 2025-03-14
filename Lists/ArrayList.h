#pragma once
#include "List.h"
#include <cstdint>
#include <string>

class ArrayList : public List {
    public:
        virtual void load_from_file(std::string source_path) override;
        virtual void show(void) override;

        virtual void append(int32_t value) override;
        virtual void prepend(int32_t value) override;
        virtual void insert(int32_t value, size_t index) override;

        virtual int32_t pop_front(void) override;
        virtual int32_t pop_back(void) override;
        virtual int32_t remove(size_t index) override;

        virtual bool search(int32_t value) override;

        virtual size_t get_size(void) const override;
        
        ArrayList();
        ArrayList(size_t new_capacity);
        ~ArrayList();

    private:
        size_t capacity;
        int32_t* array;
        void resize(size_t new_capacity);
};