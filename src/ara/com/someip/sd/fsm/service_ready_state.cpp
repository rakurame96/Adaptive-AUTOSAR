#include "./service_ready_state.h"

namespace ara
{
    namespace com
    {
        namespace someip
        {
            namespace sd
            {
                namespace fsm
                {
                    ServiceReadyState::ServiceReadyState(
                        helper::TtlTimer *ttlTimer,
                        std::condition_variable *conditionVariable) noexcept : helper::MachineState<helper::SdClientState>(helper::SdClientState::ServiceReady),
                                                                               ClientServiceState(ttlTimer),
                                                                               mConditionVariable{conditionVariable},
                                                                               mActivated{false},
                                                                               mClientRequested{true}
                    {
                    }

                    void ServiceReadyState::onTimerExpired()
                    {
                        Transit(helper::SdClientState::InitialWaitPhase);
                    }

                    void ServiceReadyState::Activate(helper::SdClientState previousState)
                    {
                        mActivated = true;

                        if (!mClientRequested)
                        {
                            Transit(helper::SdClientState::ServiceSeen);
                        }

                        // Notify the condition variable that the service has been offered
                        mConditionVariable->notify_one();

                        auto _callback =
                            std::bind(&ServiceReadyState::onTimerExpired, this);
                        Timer->SetExpirationCallback(_callback);
                    }

                    void ServiceReadyState::ServiceNotRequested()
                    {
                        if (mActivated)
                        {
                            Transit(helper::SdClientState::ServiceSeen);
                        }
                        else
                        {
                            // Reset the client requested flag
                            mClientRequested = false;
                        }
                    }

                    void ServiceReadyState::ServiceOffered(uint32_t ttl)
                    {
                        Timer->Reset(ttl);
                    }

                    void ServiceReadyState::ServiceStopped()
                    {
                        Timer->Cancel();
                        Transit(helper::SdClientState::Stopped);
                    }

                    void ServiceReadyState::Deactivate(helper::SdClientState nextState)
                    {
                        Timer->ResetExpirationCallback();
                        
                        // Set the client requested flag to default
                        mClientRequested = true;
                        mActivated = false;
                    }

                    ServiceReadyState::~ServiceReadyState()
                    {
                        Timer->ResetExpirationCallback();
                    }
                }
            }
        }
    }
}