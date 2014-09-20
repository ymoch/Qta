/**
 * @file    core/api/return_code.h
 *
 * @brief   Qta core API return code definition
 *
 * @author  ymoch
 */

#ifndef QTA_CORE_API_RETURN_CODE_H
#define QTA_CORE_API_RETURN_CODE_H

namespace Qta
{
namespace Core
{

/*==============================================================================
 * Defenitions of enumerated types
 *============================================================================*/

/**
 * @brief Return code
 */
enum ReturnCode
{
    kReturnCodeOK               = 0x0000,
    kReturnCodeFileOpenFailed   = 0x0010,
    kReturnCodeFileReadFailed   = 0x0011,
    kReturnCodeFileWriteFailed  = 0x0012,
    kReturnCodeIdNotFound       = 0x0020,
    kReturnCodeOther            = 0xffff,
};


/* End of namespace Qta::Core */
}
/* End of namespace Qta */
}

#endif // QTA_CORE_API_RETURN_CODE_H
