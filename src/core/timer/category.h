/**
 * @file    core/timer/category.h
 *
 * @brief   Qta::Core::Category class header
 *
 * @author  ymoch
 */

#ifndef QTA_CORE_TIMER_CATEGORY_H
#define QTA_CORE_TIMER_CATEGORY_H

#include <string>
#include "../../externals/serialization/archive.h"
#include "../api/typedef.h"

namespace Qta
{
namespace Core
{

/*==============================================================================
 * Defenitions of classes
 *============================================================================*/

/**
 * @brief Category
 */
class Category
{
    SERIALIZE_ARCHIVE_FRIEND

public:
    /**
     * @brief Default constructor
     */
    Category() : id_(0), label_(), name_() {}

    /**
     * @brief constructor
     *
     * @param id ID
     */
    Category(const IdType id, const std::string& label, const std::string& name)
        : id_(id), label_(label), name_(name) {}

    /**
     * @brief Get the ID
     *
     * @return ID
     */
    IdType GetId() const { return id_; }

    /**
     * @brief Get the reference to the label
     *
     * @return reference to the label
     */
    const std::string& GetLabelConstRef() const { return label_; }

    /**
     * @brief Get the reference to the name
     *
     * @return reference to the name
     */
    const std::string& GetNameConstRef() const { return name_; }

    /**
     * @brief Set the label
     *
     * @param label label
     */
    void SetLabel(const std::string& label) { label_ = label; }

    /**
     * @brief Set the name
     *
     * @param name name
     */
    void SetName(const std::string& name) { name_ = name; }

private:
    IdType id_;         /**< ID */
    std::string label_; /**< Label */
    std::string name_;  /**< Name */
};

/* End of namespace Qta::Core */
}
/* End of namespace Qta */
}

/*==============================================================================
 * Declarations of types
 *============================================================================*/

namespace Serialization
{
template <> void IArchive::Load(Qta::Core::Category&);
template <> void OArchive::Save(const Qta::Core::Category&);
}

#endif // QTA_CORE_TIMER_CATEGORY_H
