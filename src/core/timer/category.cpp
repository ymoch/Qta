/**
 * @file    core/timer/category.cpp
 *
 * @brief   Qta::Core::Category class implementation
 *
 * @author  ymoch
 */

#include "category.h"

/*==============================================================================
 * Defenitions of serialization
 *============================================================================*/

template <> void Serialization::IArchive::Load(Qta::Core::Category& category)
{
    *this >> category.id_ >> category.label_ >> category.name_;
}

template <> void Serialization::OArchive::Save(const Qta::Core::Category& category)
{
    *this << category.id_ << category.label_ << category.name_;
}
