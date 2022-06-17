#ifndef DIAG_ERROR_DOMAIN_H
#define DIAG_ERROR_DOMAIN_H

#include <exception>
#include "../core/error_domain.h"
#include "../core/error_code.h"

namespace ara
{
    namespace diag
    {
        /// @class Diagnostic Management interal error type
        enum class DiagErrc : ara::core::ErrorDomain::CodeType
        {
            kAlreadyOffered = 101,                      ///!< Already offered service
            kConfigurationMismatch = 102,               ///!< Configuration misalignment with DEXT
            kDebouncingConfigurationInconsistent = 103, ///!< Invalid monitor debouncing configuration
            kReportIgnored = 104,                       ///!< Disabled control DTC setting
            kInvalidArgument = 105,                     ///!< Invalid passed argument from caller
            kNotOffered = 106,                          ///!< Request from a not offered service
            kGenericError = 107,                        ///!< General error occurrance
            kNoSuchDTC = 108,                           ///!< Invalid DTC number
            kBusy = 109,                                ///!< Busy interface call
            kFailed = 110,                              ///!< Failed process
            kMemoryError = 111,                         ///!< Memory error occurrance
            kWrongDtc = 112,                            ///!< Incorrect passed DTC number
            kRejected = 113,                            ///!< Request rejection
            kResetTypeNotSupported = 114,               ///!< Unsupported reset type by the Diagnostic Address instance
            kRequestFailed = 115                        ///!< Failed diagnostic request process
        };

        /// @class Diagnostic Management error domain
        /// @note The class is not fully aligned with ARA standard.
        class DiagErrorDomain final : public ara::core::ErrorDomain
        {
        public:
            constexpr DiagErrorDomain() noexcept;
            const char *Name() const noexcept override;
            const char *Message(ara::core::ErrorDomain::CodeType errorCode) const noexcept override;

            /// @brief Get the global diagnostic error domain
            /// @returns Reference to the singleton diagnostic error domain
            constexpr const ara::core::ErrorDomain &GetDiagDomain() noexcept;

            /// @brief Make an error code based on the given giagnostic error type
            /// @param code Diagnostic error code input
            /// @returns Created error code
            /// @note Vendor specific data is not supported.
            constexpr ara::core::ErrorCode MakeErrorCode(DiagErrc code) noexcept;
        };
    }
}

#endif