/**
 * @file    externals/serialize/oarchive.h
 *
 * @brief   Serialization::OArchive class header
 *
 * @author  ymoch
 */

#ifndef SERIALIZATION_OARCHIVE_H
#define SERIALIZATION_OARCHIVE_H

#include <ostream>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include <unordered_map>
#include "typedef.h"

#define SERIALIZE_OARCHIVE_FRIEND \
    template <typename T> friend void Serialization::OArchive::Save(const T&);

namespace Serialization
{

/*==============================================================================
 * Defenitions of classes
 *============================================================================*/

class OArchive
{
public:
    /**
     * @brief Constructor
     *
     * @param os output stream
     */
    OArchive(std::ostream& os, const unsigned long version);

    /* Stream operators */
    template <typename Key, typename T, typename Comp, typename Allocator>
    OArchive& operator<<(const std::map<Key, T, Comp, Allocator> values);

    template <typename Key, typename T, typename Hash, typename Pred, typename Allocator>
    OArchive& operator<<(const std::unordered_map<Key, T, Hash, Pred, Allocator> values);

    template <typename T> OArchive& operator<<(const T& value);
    template <typename T, typename Allocator> OArchive& operator<<(const std::vector<T, Allocator>& values);
    template <typename T, typename Allocator> OArchive& operator<<(const std::deque<T, Allocator>& values);

    /* Save functions */
    template <typename Key, typename T, typename Comp, typename Allocator>
    void Save(const std::map<Key, T, Comp, Allocator> values);

    template <typename Key, typename T, typename Hash, typename Pred, typename Allocator>
    void Save(const std::unordered_map<Key, T, Hash, Pred, Allocator> values);

    template <typename T> void Save(const T& value);
    template <typename T, typename Allocator> void Save(const std::vector<T, Allocator>& values);
    template <typename T, typename Allocator> void Save(const std::deque<T, Allocator>& values);

private:
    std::ostream& os_;          /**< Output stream */
    SerialVersionType version_; /**< Serial version */

    template <typename T, typename Allocator, template <typename T1, typename T2> class Container>
    void SaveSizedContainer(const Container<T, Allocator>& a);

    template <typename Key, typename T, typename Comp, typename Allocator, template <typename U1, typename U2, typename U3, typename U4> class Container>
    void SaveMapContainer(const Container<Key, T, Comp, Allocator>& a);
};

/*==============================================================================
 * Defenitions of member functions
 *============================================================================*/

inline OArchive::OArchive(std::ostream& os, const unsigned long version)
: os_(os), version_(version)
{
    Save<SerialVersionType>(version_);
}

template <typename Key, typename T, typename Comp, typename Allocator>
inline OArchive& OArchive::operator<<(const std::map<Key, T, Comp, Allocator> values)
{
    Save<Key, T, Comp, Allocator>(values);
    return *this;
}

template <typename Key, typename T, typename Hash, typename Pred, typename Allocator>
inline OArchive& OArchive::operator<<(const std::unordered_map<Key, T, Hash, Pred, Allocator> values)
{
    Save<Key, T, Hash, Pred, Allocator>(values);
    return *this;
}

template <typename T, typename Allocator>
inline OArchive& OArchive::operator<<(const std::deque<T, Allocator>& values)
{
    Save<T, Allocator>(values);
    return *this;
}

template <typename T, typename Allocator>
inline OArchive& OArchive::operator<<(const std::vector<T, Allocator>& values)
{
    Save<T, Allocator>(values);
    return *this;
}

template <typename T>
inline OArchive& OArchive::operator<<(const T& value)
{
    Save<T>(value);
    return *this;
}

template <typename Key, typename T, typename Comp, typename Allocator>
inline void OArchive::Save(const std::map<Key, T, Comp, Allocator> values)
{
    SaveMapContainer(values);
}

template <typename Key, typename T, typename Hash, typename Pred, typename Allocator>
inline void OArchive::Save(const std::unordered_map<Key, T, Hash, Pred, Allocator> values)
{
    SaveMapContainer(values);
}

template <typename T, typename Allocator>
inline void OArchive::Save(const std::deque<T, Allocator>& values)
{
    return SaveSizedContainer(values);
}

template <typename T, typename Allocator>
inline void OArchive::Save(const std::vector<T, Allocator>& values)
{
    return SaveSizedContainer(values);
}

template <typename T>
inline void OArchive::Save(const T& value)
{
    os_.write(reinterpret_cast<const char*>(&value), sizeof(T));
}

template <>
inline void OArchive::Save(const std::string& value)
{
    const std::string::size_type size = value.size();
    Save(size);
    os_.write(value.c_str(), sizeof(const char) * size);
}

template <typename T, typename Allocator, template <typename T1, typename T2> class Container>
inline void OArchive::SaveSizedContainer(const Container<T, Allocator>& container)
{
    Save(container.size());
    for (auto it = container.cbegin(); it != container.cend(); ++it) {
        Save(*it);
    }
}

template <typename Key, typename T, typename Comp, typename Allocator, template <typename U1, typename U2, typename U3, typename U4> class Container>
inline void OArchive::SaveMapContainer(const Container<Key, T, Comp, Allocator>& values)
{
    Save(values.size());
    for (auto it = values.cbegin(); it != values.cend(); ++it) {
        Save(it->first);
        Save(it->second);
    }
}


/* End of namespace Qta::Serialization */
}

#endif // SERIALIZATION_OARCHIVE_H
