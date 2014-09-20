/**
 * @file    externals/serialization/archive.h
 *
 * @brief   Serializer master header
 *
 * @author  ymoch
 */

#ifndef SERIALIZARION_ARCHIVE_H
#define SERIALIZARION_ARCHIVE_H

#include "iarchive.h"
#include "oarchive.h"

#define SERIALIZE_ARCHIVE_FRIEND \
    SERIALIZE_IARCHIVE_FRIEND SERIALIZE_OARCHIVE_FRIEND

#endif // SERIALIZARION_ARCHIVE_H
