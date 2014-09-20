/**
 * @file    externals/id_maker/id_maker.h
 *
 * @brief   IdMaker::IdMaker class header
 *
 * @author  ymoch
 */

#ifndef ID_MAKER_ID_MAKER_H
#define ID_MAKER_ID_MAKER_H

#include "../serialization/archive.h"

namespace IdMaker
{

/*==============================================================================
 * Defenitions of classes
 *============================================================================*/

class IdMaker
{
    SERIALIZE_ARCHIVE_FRIEND

public:
    /**
     * @brief ID yype
     */
    typedef unsigned long IdType;

    /**
     * @brief Invalid ID
     */
    static const IdType kInvalidId;

    /**
     * @brief IdMaker
     */
    IdMaker();

    /**
     * @brief Create an ID
     */
    IdType Create();

    /**
     * @brief Clear
     */
    void Clear();

private:
    IdType last_id_;
};

/* End of namespace IdMaker */
}

/*==============================================================================
 * Declarations of types
 *============================================================================*/

template <> void Serialization::IArchive::Load(IdMaker::IdMaker& id_maker);
template <> void Serialization::OArchive::Save(const IdMaker::IdMaker& id_maker);

#endif // ID_MAKER_ID_MAKER_H
