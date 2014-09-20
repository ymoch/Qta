/**
 * @file    externals/serialize/iarchive.h
 *
 * @brief   Serialization::IArchive class header
 *
 * @author  ymoch
 */

#ifndef SERIALICATION_IARCHIVE_H
#define SERIALICATION_IARCHIVE_H

#include <istream>
#include <string>
#include <memory>
#include <vector>
#include <deque>
#include <map>
#include <unordered_map>
#include "typedef.h"

#define SERIALIZE_IARCHIVE_FRIEND \
    template <typename T> friend void Serialization::IArchive::Load(T&);

namespace Serialization
{

/*==============================================================================
 * Defenitions of classes
 *============================================================================*/

class IArchive
{
public:
    /**
     * @brief Constructor
     *
     * @param is input stream
     */
    IArchive(std::istream& is);

    /**
     * @brief Get the serial version
     *
     * @return version
     */
    unsigned long GetVersion() const { return version_; }

    /* Stream operators */
    template <typename Key, typename T, typename Comp, typename Allocator>
    IArchive& operator>>(std::map<Key, T, Comp, Allocator>& values);

    template <typename Key, typename T, typename Comp, typename Allocator>
    IArchive& operator>>(std::multimap<Key, T, Comp, Allocator>& values);

    template <typename Key, typename T, typename Hash, typename Pred, typename Allocator>
    IArchive& operator>>(std::unordered_map<Key, T, Hash, Pred, Allocator>& values);

    template <typename T, typename Allocator> IArchive& operator>>(std::vector<T, Allocator>& values);
    template <typename T, typename Allocator> IArchive& operator>>(std::deque<T, Allocator>& values);
    template <typename T> IArchive& operator>>(T& value);

    /* Load functions */
    template <typename Key, typename T, typename Comp, typename Allocator>
    void Load(std::map<Key, T, Comp, Allocator>& values);

    template <typename Key, typename T, typename Comp, typename Allocator>
    void Load(std::multimap<Key, T, Comp, Allocator>& values);

    template <typename Key, typename T, typename Hash, typename Pred, typename Allocator>
    void Load(std::unordered_map<Key, T, Hash, Pred, Allocator>& values);

    template <typename T, typename Allocator> void Load(std::vector<T>& values);
    template <typename T, typename Allocator> void Load(std::deque<T>& values);
    template <typename T> void Load(T& value);

private:
    std::istream& is_;          /**< Input stream */
    SerialVersionType version_; /**< Serial version */

    template <typename T, typename Allocator, template <typename U1, typename U2> class Container>
    void LoadSizedContainer(Container<T, Allocator>& container);

    template <typename Key, typename T, typename Comp, typename Allocator, template <typename U1, typename U2, typename U3, typename U4> class Container>
    void LoadMapContainer(Container<Key, T, Comp, Allocator>& container);
};

/*==============================================================================
 * Defenitions of member functions
 *============================================================================*/

inline IArchive::IArchive(std::istream& is)
    : is_(is)
{
    Load<SerialVersionType>(version_);
}

template <typename Key, typename T, typename Comp, typename Allocator>
inline IArchive& IArchive::operator>>(std::map<Key, T, Comp, Allocator>& values)
{
    Load<Key, T, Comp, Allocator>(values);
    return *this;
}

template <typename Key, typename T, typename Comp, typename Allocator>
inline IArchive& IArchive::operator>>(std::multimap<Key, T, Comp, Allocator>& values)
{
    Load<Key, T, Comp, Allocator>(values);
    return *this;
}

template <typename Key, typename T, typename Hash, typename Pred, typename Allocator>
inline IArchive& IArchive::operator>>(std::unordered_map<Key, T, Hash, Pred, Allocator>& values)
{
    Load<Key, T, Hash, Pred, Allocator>(values);
    return *this;
}

template <typename T, typename Allocator>
inline IArchive& IArchive::operator>>(std::vector<T, Allocator>& values)
{
    Load<T, Allocator>(values);
    return *this;
}

template <typename T, typename Allocator>
inline IArchive& IArchive::operator>>(std::deque<T, Allocator>& values)
{
    Load<T, Allocator>(values);
    return *this;
}

template <typename T>
inline IArchive& IArchive::operator>>(T& value)
{
    Load<T>(value);
    return *this;
}

template <typename Key, typename T, typename Comp, typename Allocator>
void IArchive::Load(std::map<Key, T, Comp, Allocator>& values)
{
    LoadMapContainer(values);
}

template <typename Key, typename T, typename Comp, typename Allocator>
void IArchive::Load(std::multimap<Key, T, Comp, Allocator>& values)
{
    LoadMapContainer(values);
}

template <typename Key, typename T, typename Hash, typename Pred, typename Allocator>
void IArchive::Load(std::unordered_map<Key, T, Hash, Pred, Allocator>& values)
{
    typedef typename std::unordered_map<Key, T, Hash, Pred, Allocator>::size_type SizeType;

    SizeType size;
    Load(size);
    for (SizeType i = 0; i < size; ++i) {
        Key key;
        Load(key);
        Load(values[key]);
    }
}

template <typename T, typename Allocator>
inline void IArchive::Load(std::vector<T>& values)
{
    LoadSizedContainer(values);
}

template <typename T, typename Allocator>
inline void IArchive::Load(std::deque<T>& values)
{
    LoadSizedContainer(values);
}

template <typename T>
inline void IArchive::Load(T& value)
{
    is_.read(reinterpret_cast<char*>(&value), sizeof(T));
}

template <> void
inline IArchive::Load(std::string& value)
{
    std::string::size_type size;
    Load(size);

    std::unique_ptr<char[]> buffer(new char[size]);
    is_.read(buffer.get(), sizeof(char) * size);
    value = std::string(buffer.get(), size);
}

template <typename T, typename Allocator, template <typename U1, typename U2> class Container>
inline void IArchive::LoadSizedContainer(Container<T, Allocator>& container)
{
    typename Container<T, Allocator>::size_type size;
    Load(size);

    container.resize(size);
    for (auto it = container.begin(); it != container.end(); ++it) {
        Load(*it);
    }
}

template <typename Key, typename T, typename Comp, typename Allocator, template <typename U1, typename U2, typename U3, typename U4> class Container>
void IArchive::LoadMapContainer(Container<Key, T, Comp, Allocator>& values)
{
    typedef std::multimap<Key, T, Comp, Allocator> Type;
    typedef typename Type::size_type SizeType;

    SizeType size;
    Load(size);

    for (SizeType i = 0; i < size; ++i) {
        Key key;
        T value;

        Load(key);
        Load(value);
        values.insert(Type::value_type(key, value));
    }
}

/* End of namespace Serialization */
}

#endif // SERIALICATION_IARCHIVE_H
