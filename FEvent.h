#pragma once

#include "TEvent.h"
#include "FWizardSettings.h"

namespace t3d
{
    //

    struct FEvent
    {
         FEvent () = delete;
        ~FEvent () = delete;

        static T3D_INLINE TEvent<FWizardSettings::Settings_T> SettingsSaved;
        static T3D_INLINE TEvent<FWizardSettings::Settings_T> SettingsLoaded;
    };
}
