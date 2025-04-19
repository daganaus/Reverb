cmake_minimum_required(VERSION 3.22)

# ------------ Configuration utilisateur -------------
get_filename_component(TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set(USER_NAME faure)
set(COMPANY_NAME Fred)
project(${TARGET_NAME} VERSION 1.0.4)

# ------------ Options de build configurables -------------
option(BUILD_STANDALONE "Build standalone application" ON)
option(BUILD_VST3 "Build VST3 plugin" ON)
option(BUILD_AU "Build AU plugin (mac only)" ON)
option(ENABLE_PACKAGING "Enable packaging with CPack" ON)

# ------------ Architecture Mac multi-plateforme -------------
if(APPLE)
    set(CMAKE_OSX_ARCHITECTURES x86_64;arm64)
endif()

# ------------ Niveau d'avertissements compilateur -------------
if(MSVC)
    add_compile_options(/W2)
else()
    add_compile_options(-Wall)
endif()

# ------------ Détection JUCE -------------
if(NOT EXISTS "${JUCE_DIR}/CMakeLists.txt")
    message(FATAL_ERROR "JUCE_DIR n'est pas valide : ${JUCE_DIR}")
endif()
add_subdirectory(${JUCE_DIR} JUCE_build)

# ------------ Correctif Xcode 15 pour LTO -------------
if(APPLE AND
    CMAKE_C_COMPILER_VERSION VERSION_GREATER_EQUAL 15.0 AND
    CMAKE_C_COMPILER_VERSION VERSION_LESS 15.1)
    add_link_options(-Wl,-ld_classic)
    add_compile_definitions(JUCE_SILENCE_XCODE_15_LINKER_WARNING)
endif()

# ------------ Définition spécifique Linux -------------
if(CMAKE_SYSTEM MATCHES Linux)
    add_compile_definitions(_GNU_SOURCE)
endif()

# ------------ Construction de la liste des formats ------------
set(PLUGIN_FORMATS "")
if(BUILD_STANDALONE)
    list(APPEND PLUGIN_FORMATS Standalone)
endif()
if(BUILD_VST3)
    list(APPEND PLUGIN_FORMATS VST3)
endif()
if(APPLE AND BUILD_AU)
    list(APPEND PLUGIN_FORMATS AU)
endif()

# ------------ Déclaration du plugin ------------
juce_add_plugin(${TARGET_NAME}
    COMPANY_NAME "${COMPANY_NAME}"
    PLUGIN_NAME "${TARGET_NAME}"
    PRODUCT_NAME "${COMPANY_NAME}_${TARGET_NAME}"
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    PLUGIN_MANUFACTURER_CODE Frdf
    PLUGIN_CODE Tmpl
    COPY_PLUGIN_AFTER_BUILD TRUE
    FORMATS ${PLUGIN_FORMATS}
)

# ------------ Fichiers source ------------
target_sources(${TARGET_NAME}
  PRIVATE
    Source/processor/PluginProcessor.cc
    Source/editor/PluginEditor.cc
    Source/editor/manager.cc
    Source/com.cc
)

target_include_directories(${TARGET_NAME} PRIVATE ".")

# ------------ Définis des macros C++ ------------
target_compile_definitions(${TARGET_NAME}
    PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
    SYNTH_NO_DYNAMIC REV_NO_UI
    SYNTH_MIDICTL
)

# ------------ Liens aux modules JUCE ------------
target_link_libraries(${TARGET_NAME}
    PRIVATE
    juce::juce_audio_utils
    PUBLIC
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags
)

# ------------ Installation et packaging conditionnel ------------
if(ENABLE_PACKAGING)
    if(APPLE)
        set(CMAKE_INSTALL_PREFIX /)
        set(CPACK_PACKAGING_INSTALL_PREFIX /)

        install(TARGETS ${TARGET_NAME}_AU
            LIBRARY DESTINATION Library/Audio/Plug-Ins/Components
            COMPONENT AU)
        install(TARGETS ${TARGET_NAME}_VST3
            LIBRARY DESTINATION Library/Audio/Plug-Ins/VST3
            COMPONENT VST3)
        install(TARGETS ${TARGET_NAME}_Standalone
            BUNDLE DESTINATION "Applications"
            COMPONENT Standalone)

        set(CPACK_GENERATOR productbuild)
        set(CPACK_PACKAGE_VENDOR ${COMPANY_NAME})
        include(CPack)

    elseif(UNIX)
        install(TARGETS ${TARGET_NAME}_VST3 
            LIBRARY DESTINATION "lib/vst3"
            COMPONENT VST3)
        install(TARGETS ${TARGET_NAME}_Standalone
            RUNTIME DESTINATION bin)

        set(CPACK_GENERATOR "TGZ;DEB")
        set(CPACK_PACKAGE_NAME "${TARGET_NAME}")
        set(CPACK_PACKAGE_VENDOR "${COMPANY_NAME}")
        set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
        set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${TARGET_NAME} plugin for audio processing")
        set(CPACK_DEBIAN_PACKAGE_MAINTAINER "${USER_NAME}")
        include(CPack)

    elseif(WIN32)
        set(CMAKE_INSTALL_PREFIX "C:/Users/${USER_NAME}")

        install(TARGETS ${TARGET_NAME}
            LIBRARY DESTINATION "VST3"
            COMPONENT VST3)
        install(TARGETS ${TARGET_NAME}_Standalone
            RUNTIME DESTINATION "${TARGET_NAME}"
            COMPONENT Standalone)

        set(CPACK_GENERATOR "NSIS")
        set(CPACK_PACKAGE_NAME "${TARGET_NAME}")
        set(CPACK_PACKAGE_VENDOR "${COMPANY_NAME}")
        set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
        set(CPACK_PACKAGE_DESCRIPTION "${TARGET_NAME} plugin for audio processing")
        set(CPACK_NSIS_INSTALL_ROOT "C:/Users/${USER_NAME}")
        set(CPACK_NSIS_DISPLAY_NAME "${TARGET_NAME} Audio Plugins")
        include(CPack)
    endif()
endif()
