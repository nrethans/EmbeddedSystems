#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/ti/simplelink_msp432e4_sdk_4_20_00_12/source;C:/ti/simplelink_msp432e4_sdk_4_20_00_12/kernel/tirtos/packages;C:/Users/NickRethans/Desktop/EmbeddedSystems/Homework4/tirtos_builds_MSP_EXP432E401Y_release_ccs/.config
override XDCROOT = C:/ti/ccs1280/xdctools_3_62_01_16_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/ti/simplelink_msp432e4_sdk_4_20_00_12/source;C:/ti/simplelink_msp432e4_sdk_4_20_00_12/kernel/tirtos/packages;C:/Users/NickRethans/Desktop/EmbeddedSystems/Homework4/tirtos_builds_MSP_EXP432E401Y_release_ccs/.config;C:/ti/ccs1280/xdctools_3_62_01_16_core/packages;..
HOSTOS = Windows
endif
