
// Primary Include
#include "Core/SystemStorage.h"

namespace Fluent
{

    void SystemStorage::SetWindowData(const WindowData& windowData)
    {
        mWindowData = windowData;
    }

    void SystemStorage::SetWindowMessage(const WindowMsg& windowMsg)
    {
        mWindowMsg = windowMsg;

        switch (windowMsg.MsgType)
        {
        case EWindowMsgType::DisplayChange:
            mWindowData.MonitorHeight = static_cast<u32>((windowMsg.LParam >> 16) & 0xffff);
            mWindowData.MonitorWidth = static_cast<u32>(windowMsg.LParam & 0xffff);
            break;
        case EWindowMsgType::Size:
            mWindowData.ScreenHeight = static_cast<u32>((windowMsg.LParam >> 16) & 0xffff);
            mWindowData.ScreenWidth = static_cast<u32>(windowMsg.LParam & 0xffff);
            break;
        default:
            break;
        }
    }

}
