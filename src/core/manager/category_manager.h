/**
 * @file    core/manager/category_manager.h
 *
 * @brief   Qta::Core::CategoryManager class header
 *
 * @author  ymoch
 */

#ifndef QTA_CORE_MANAGER_CATEGORY_MANAGER_H
#define QTA_CORE_MANAGER_CATEGORY_MANAGER_H

#include <string>
#include <vector>
#include "../../externals/id_maker/id_maker.h"
#include "../api/return_code.h"
#include "../timer/category.h"

namespace Qta
{
namespace Core
{

/*==============================================================================
 * Defenitions of classes
 *============================================================================*/

/**
 * @brief Category manager
 */
class CategoryManager
{
    SERIALIZE_ARCHIVE_FRIEND

public:
    /**
     * @brief   Categories type
     */
    typedef std::vector<Category> CategoriesType;

    /**
     * @brief   Categories size type
     */
    typedef CategoriesType::size_type CategoriesSizeType;

    /**
     * @brief   Name map type
     */
    typedef std::multimap<std::string, Category*> NameMapType;

    /**
     * @brief   ID map type
     */
    typedef std::unordered_map<IdType, Category*> IdMapType;

    /**
     * @brief   Default constructor
     */
    CategoryManager();

    /**
     * @brief Clear
     */
    void Clear();

    /**
     * @brief   Get the size of the categories
     *
     * @return  size of categories
     */
    const CategoriesSizeType GetSize() const { return categories_.size(); }

    /**
     * @brief   Add a category
     *
     * @param   info category information
     */
    void AddCategory(const std::string& label, const std::string& name);

    /**
     * @brief   Edit a category specified by its index
     *
     * @param   info category information
     */
    void EditCategoryByIndex(const CategoriesSizeType idx, const std::string& label, const std::string& name);

    /**
     * @brief   Edit a category specified by its id
     *
     * @param   info category information
     */
    ReturnCode EditCategoryById(const IdType id, const std::string& label, const std::string& name);

    /**
     * @brief Get the ID
     *
     * @param idx index of the category
     * @return  ID
     */
    IdType GetId(const CategoriesSizeType idx) const { return categories_[idx].GetId(); }

    /**
     * @brief   Get the reference to the category
     *
     * @param   idx index of the category
     * @return  name of the category
     */
    const std::string& GetLabelConstRefByIndex(const CategoriesSizeType idx) { return categories_[idx].GetLabelConstRef(); }

    /**
     * @brief   Get the reference to the category
     *
     * @param   idx index of the category
     * @return  name of the category
     */
    const std::string& GetNameConstRefByIndex(const CategoriesSizeType idx) { return categories_[idx].GetNameConstRef(); }

private:
    CategoriesType categories_; /**< Categories */
    IdMaker::IdMaker id_maker_; /**< ID maker */

    /**
     * @brief Sort categories
     */
    void Sort();

    /**
     * @brief Find category by its id
     *
     * @param id category ID
     * @return iterator of categories
     */
    CategoriesType::iterator FindById(const IdType id);
};

/* End of namespace Qta::Core */
}
/* End of namespace Qta */
}

/*==============================================================================
 * Declarations of types
 *============================================================================*/

template <> void Serialization::IArchive::Load(Qta::Core::CategoryManager&);
template <> void Serialization::OArchive::Save(const Qta::Core::CategoryManager&);

#endif // QTA_CORE_MANAGER_CATEGORY_MANAGER_H
