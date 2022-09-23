#ifndef UDS_SERVICE_ROUTER_H
#define UDS_SERVICE_ROUTER_H

#include "./routable_uds_service.h"

namespace ara
{
    namespace diag
    {
        namespace routing
        {
            /// @brief A class to route an UDS request to the proper service for handling
            class UdsServiceRouter
            {
            private:
                const uint8_t cNegativeResponseSid{0x7f};
                const uint8_t cServiceNotSupportedNrc{0x11};

                std::map<uint8_t, RoutableUdsService *> mServices;
                const ara::core::InstanceSpecifier &mSpecifier;

            public:
                /// @brief Constructor
                /// @param specifier Owner instance specifier
                explicit UdsServiceRouter(const ara::core::InstanceSpecifier &specifier);

                /// @brief Route an UDS request message to a service
                /// @param sid UDS service ID
                /// @param requestData Request message byte array
                /// @param metaInfo Request message metainfo
                /// @param cancellationHandler Callack to be invoked when the current conversation is cancelled
                /// @returns Response byte array
                std::future<OperationOutput> Route(
                    std::uint8_t sid,
                    const std::vector<std::uint8_t> &requestData,
                    MetaInfo &metaInfo,
                    CancellationHandler &&cancellationHandler);

                ~UdsServiceRouter() = default;
            };
        }
    }
}

#endif