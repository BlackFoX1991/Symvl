#include "Table.h"
#include <math.h>

namespace
{
    inline bool IsInt(double d)
    {
        return floor(d) == d;
    }
} // namespace

namespace symvl
{
    Table::Table()
    {
    }

    void Table::Accept(GCObjectVisitor *v)
    {
        if (v->Visit(this))
        {
            // Visit all array members
            if (array_)
            {
                for (const auto &value : *array_)
                    value.Accept(v);
            }

            // Visit all keys and values in hash table.
            if (hash_)
            {
                for (auto it = hash_->begin(); it != hash_->end(); ++it)
                {
                    it->first.Accept(v);
                    it->second.Accept(v);
                }
            }
        }
    }

    bool Table::SetArrayValue(std::size_t index, const Value &value)
    {
        if (index < 1)
            return false;

        std::size_t array_size = ArraySize();
        if (index > array_size + 1)
            return false;

        if (index == array_size + 1)
            AppendAndMergeFromHashToArray(value);
        else
            (*array_)[index - 1] = value;

        return true;
    }

    bool Table::InsertArrayValue(std::size_t index, const Value &value)
    {
        if (index < 1)
            return false;

        std::size_t array_size = ArraySize();
        if (index > array_size + 1)
            return false;

        if (index == array_size + 1)
            AppendAndMergeFromHashToArray(value);
        else
        {
            // Insert value
            auto it = array_->begin();
            std::advance(it, index - 1);
            array_->insert(it, value);
            // Try to merge from hash to array
            MergeFromHashToArray();
        }

        return true;
    }

    bool Table::EraseArrayValue(std::size_t index)
    {
        if (index < 1 || index > ArraySize())
            return false;

        auto it = array_->begin();
        std::advance(it, index - 1);
        array_->erase(it);
        return true;
    }

    void Table::SetValue(const Value &key, const Value &value)
    {
        // Try array part
        if (key.type_ == ValueT_Number && IsInt(key.num_))
        {
            if (SetArrayValue(static_cast<std::size_t>(key.num_), value))
                return ;
        }

        // Hash part
        if (!hash_)
        {
            // If value is nil and hash part is not existed, then do nothing
            if (value.IsNil())
                return ;
            hash_.reset(new Hash);
        }

        auto it = hash_->find(key);
        if (it != hash_->end())
        {
            // If value is nil, then just erase the element
            if (value.IsNil())
                hash_->erase(it);
            else
                it->second = value;
        }
        else
        {
            // If key is not existed and value is not nil, then insert it
            if (!value.IsNil())
                hash_->insert(std::make_pair(key, value));
        }
    }

    Value Table::GetValue(const Value &key) const
    {
        // Get from array first
        if (key.type_ == ValueT_Number && IsInt(key.num_))
        {
            std::size_t index = static_cast<std::size_t>(key.num_);
            if (index >= 1 && index <= ArraySize())
                return (*array_)[index - 1];
        }

        // Get from hash table
        if (hash_)
        {
            auto it = hash_->find(key);
            if (it != hash_->end())
                return it->second;
        }

        // key not exist
        return Value();
    }

    bool Table::FirstKeyValue(Value &key, Value &value)
    {
        // array part
        if (ArraySize() > 0)
        {
            key.num_ = 1;           // first element index
            key.type_ = ValueT_Number;
            value = (*array_)[0];
            return true;
        }

        // hash part
        if (hash_ && !hash_->empty())
        {
            auto first = hash_->begin();
            key = first->first;
            value = first->second;
            return true;
        }

        return false;
    }

    bool Table::NextKeyValue(const Value &key, Value &next_key, Value &next_value)
    {
        // array part
        if (key.type_ == ValueT_Number && IsInt(key.num_))
        {
            std::size_t index = static_cast<std::size_t>(key.num_) + 1;
            if (index >= 1 && index <= ArraySize())
            {
                next_key.num_ = index;
                next_key.type_ = ValueT_Number;
                next_value = (*array_)[index - 1];
                return true;
            }
        }

        // hash part
        if (hash_)
        {
            auto it = hash_->find(key);
            if (it == hash_->end() && !hash_->empty())
            {
                it = hash_->begin();
                next_key = it->first;
                next_value = it->second;
                return true;
            }

            if (it != hash_->end() && ++it != hash_->end())
            {
                next_key = it->first;
                next_value = it->second;
                return true;
            }
        }

        return false;
    }

    std::size_t Table::ArraySize() const
    {
        return array_ ? array_->size() : 0;
    }

    void Table::AppendAndMergeFromHashToArray(const Value &value)
    {
        AppendToArray(value);
        MergeFromHashToArray();
    }

    void Table::AppendToArray(const Value &value)
    {
        if (!array_)
            array_.reset(new Array);
        array_->push_back(value);
    }

    void Table::MergeFromHashToArray()
    {
        auto index = ArraySize();
        Value key;
        key.num_ = ++index;
        key.type_ = ValueT_Number;

        while (MoveHashToArray(key))
            key.num_ = ++index;
    }

    bool Table::MoveHashToArray(const Value &key)
    {
        if (!hash_)
            return false;

        auto it = hash_->find(key);
        if (it == hash_->end())
            return false;

        AppendToArray(it->second);
        hash_->erase(it);
        return true;
    }
} // namespace symvl
