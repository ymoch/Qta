/**
 * @file    externals/id_maker/id_maker.cpp
 *
 * @brief   IdMaker::IdMaker class implementation
 *
 * @author  ymoch
 */

#include "id_maker.h"

namespace IdMaker
{

/*==============================================================================
 * Defenitions of static member variables
 *============================================================================*/

const IdMaker::IdType IdMaker::kInvalidId = 0;

/*==============================================================================
 * Defenitions of member functions
 *============================================================================*/

IdMaker::IdMaker()
    : last_id_(kInvalidId)
{}

IdMaker::IdType IdMaker::Create()
{
    ++last_id_;
    return last_id_;
}

void IdMaker::Clear()
{
    last_id_ = kInvalidId;
}

/* End of namespace IdMaker */
}

/*==============================================================================
 * Defenitions of serialization
 *============================================================================*/

template <> void Serialization::IArchive::Load(IdMaker::IdMaker& id_maker)
{
    *this >> id_maker.last_id_;
}

template <> void Serialization::OArchive::Save(const IdMaker::IdMaker& id_maker)
{
    *this << id_maker.last_id_;
}

