/**
 * @file    core/manager/category_manager.cpp
 *
 * @brief   Qta::Core::CategoryManager class implementation
 *
 * @author  ymoch
 */

#include <algorithm>
#include "category_manager.h"

using std::string;

namespace Qta
{
namespace Core
{

/*==============================================================================
 * Defenitions of local classes
 *============================================================================*/

/**
 * @brief Category comparator
 */
class CategoryLessName
{
public:
    bool operator ()(const Category& c1, const Category& c2) const
    {
        const int label_comp = c1.GetLabelConstRef().compare(c2.GetLabelConstRef());
        if (label_comp != 0) {
            return label_comp < 0;
        }
        const int name_comp = c1.GetNameConstRef().compare(c2.GetNameConstRef());
        if (name_comp != 0) {
            return name_comp < 0;
        }
        return c1.GetId() < c2.GetId();
    }
};

/**
 * @brief Category comparator
 */
class CategoryIdEqual
{
public:
    CategoryIdEqual(const IdType id) : id_(id) {}
    bool operator ()(const Category& c) const { return c.GetId() == id_; }
private:
    IdType id_;
};

/*==============================================================================
 * Defenitions of member functions
 *============================================================================*/

CategoryManager::CategoryManager()
{
    Clear();
}

void CategoryManager::Clear()
{
    categories_.clear();
    id_maker_.Clear();
}

void CategoryManager::AddCategory(const string& label, const string& name)
{
    const IdType id = static_cast<IdType>(id_maker_.Create());
    categories_.emplace_back(id, label, name);
    Sort();
}

void CategoryManager::EditCategoryByIndex(const CategoriesSizeType idx, const std::string& label, const std::string& name)
{
    categories_[idx].SetLabel(label);
    categories_[idx].SetName(name);
    Sort();
}

ReturnCode CategoryManager::EditCategoryById(const IdType id, const std::string& label, const std::string& name)
{
    auto it = FindById(id);
    if (it == categories_.end()) {
        return kReturnCodeIdNotFound;
    }
    it->SetLabel(label);
    it->SetName(name);
    Sort();
    return kReturnCodeOK;
}

void CategoryManager::Sort()
{
    std::sort(categories_.begin(), categories_.end(), CategoryLessName());
}

CategoryManager::CategoriesType::iterator CategoryManager::FindById(const IdType id)
{
    return std::find_if(categories_.begin(), categories_.end(), CategoryIdEqual(id));
}

/* End of namespace Qta::Core */
}
/* End of namespace Qta */
}

/*==============================================================================
 * Defenitions of serialization
 *============================================================================*/

template <> void Serialization::IArchive::Load(Qta::Core::CategoryManager& group)
{
    *this >> group.categories_ >> group.id_maker_;
}

template <> void Serialization::OArchive::Save(const Qta::Core::CategoryManager& group)
{
    *this << group.categories_ << group.id_maker_;
}

