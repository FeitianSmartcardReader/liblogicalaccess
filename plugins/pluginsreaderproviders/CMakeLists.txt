remove_definitions(-DLIBLOGICALACCESS_EXPORTS_DLL)

if (WIN32)
	remove_definitions(-DVERSION_PRODUCTNAME_VALUE="${VERSION_PRODUCTNAME_VALUE}")
endif()

add_subdirectory(a3mlgm5600)
add_subdirectory(admitto)
add_subdirectory(axesstmc13)
add_subdirectory(axesstmclegic)
add_subdirectory(deister)
add_subdirectory(elatec)
add_subdirectory(gigatms)
add_subdirectory(gunnebo)
add_subdirectory(idondemand)
add_subdirectory(iso7816)
add_subdirectory(ok5553)
add_subdirectory(osdp)
add_subdirectory(pcsc)
add_subdirectory(promag)
add_subdirectory(rpleth)
add_subdirectory(sciel)
add_subdirectory(smartid)
add_subdirectory(stidstr)
add_subdirectory(stidprg)
if(WIN32)
add_subdirectory(keyboard)
add_subdirectory(rfideas)
endif()
