cmake_minimum_required(VERSION 3.22)

project(Template VERSION 1.0.4)

# build for Intel (x86_64) and M1 (arm64) architectures
set(CMAKE_OSX_ARCHITECTURES x86_64;arm64)


# set compiler warning level to "basic" warnings only
if(MSVC)
	add_compile_options(/W2)
else()
	add_compile_options(-Wall)
endif()


# build for Intel (x86_64) and M1 (arm64) architectures
set(CMAKE_OSX_ARCHITECTURES x86_64;arm64)



#
# For the details, see
#
# https://github.com/juce-framework/JUCE/blob/master/docs/CMake%20API.md
#
find_package(JUCE CONFIG REQUIRED)


# On macOS, JUCE emits the warning below. We do what they recommend:
#
#	If you are using Link Time Optimisation (LTO), the new linker
#	introduced in Xcode 15 may produce a broken binary. As a
#	workaround, add either '-Wl,-weak_reference_mismatches,weak'
#	or '-Wl,-ld_classic' to your linker flags. Once you've
#	selected a workaround, you can add
#	JUCE_SILENCE_XCODE_15_LINKER_WARNING to your preprocessor
#	definitions to silence this warning.
#
if(APPLE AND
	CMAKE_C_COMPILER_VERSION VERSION_GREATER_EQUAL 15.0 AND
	CMAKE_C_COMPILER_VERSION VERSION_LESS 15.1)
	add_link_options(-Wl,-ld_classic)
	add_compile_definitions(JUCE_SILENCE_XCODE_15_LINKER_WARNING)
endif()

# Linux needs _GNU_SOURCE for certain functions we use, like dladdr()
if(CMAKE_SYSTEM MATCHES Linux)
	add_compile_definitions(_GNU_SOURCE)
endif()








juce_add_plugin(Template
    # VERSION ...				# Set this if the plugin version is different to the project version
    # ICON_BIG ...				# ICON_* arguments specify a path to an image file to use as an icon for the Standalone
    # ICON_SMALL ...
    COMPANY_NAME "Fred"				# Specify the name of the plugin's author
    PLUGIN_NAME "Template"			# The name of the plugin as displayed by the DAW
    PRODUCT_NAME "Fred_Template"			# The name of the final executable
    IS_SYNTH TRUE				# Is this a synth or an effect?
    NEEDS_MIDI_INPUT TRUE			# Does the plugin need midi input?
    #NEEDS_MIDI_OUTPUT TRUE			# Does the plugin need midi output?
    #IS_MIDI_EFFECT TRUE				# Is this plugin a MIDI effect?
    # EDITOR_WANTS_KEYBOARD_FOCUS TRUE/FALSE	# Does the editor need keyboard focus?
    # PLUGIN_MANUFACTURER_CODE Frdf		# A four-character manufacturer id with at least one upper-case character
    # PLUGIN_CODE Tzma				# A unique four-character plugin id with exactly one upper-case character
    COPY_PLUGIN_AFTER_BUILD TRUE
    FORMATS Standalone AU VST3)

  






  
target_sources(Template
  PRIVATE
  	Source/processor/PluginProcessor.cc
	Source/editor/PluginEditor.cc
	Source/editor/manager.cc
	Source/com.cc)


  
target_include_directories(Template PRIVATE ".")

# `target_compile_definitions` adds some preprocessor definitions to our target. In a Projucer
# project, these might be passed in the 'Preprocessor Definitions' field. JUCE modules also make use
# of compile definitions to switch certain features on/off, so if there's a particular feature you
# need that's not on by default, check the module header for the correct flag to set here. These
# definitions will be visible both to your code, and also the JUCE module code, so for new
# definitions, pick unique names that are unlikely to collide! This is a standard CMake command.

target_compile_definitions(Template
    PUBLIC
	JUCE_WEB_BROWSER=0
	JUCE_USE_CURL=0
	JUCE_VST3_CAN_REPLACE_VST2=0
	SYNTH_NO_DYNAMIC REV_NO_UI	# Disable GUI and license management
	SYNTH_MIDICTL)			# Allow MIDI control of parameters

# `target_link_libraries` links libraries and JUCE modules to other libraries or executables. Here,
# we're linking our executable target to the `juce::juce_audio_utils` module. Inter-module
# dependencies are resolved automatically, so `juce_core`, `juce_events` and so on will also be
# linked automatically.

target_link_libraries(Template
    PRIVATE
	juce::juce_audio_utils
    PUBLIC
	juce::juce_recommended_config_flags
	juce::juce_recommended_lto_flags
	juce::juce_recommended_warning_flags)

if(APPLE)
	set(CMAKE_INSTALL_PREFIX /)
	set(CPACK_PACKAGING_INSTALL_PREFIX /)

	install(TARGETS Template_AU
		LIBRARY DESTINATION Library/Audio/Plug-Ins/Components
		COMPONENT AU)
	install(TARGETS Template_VST3
		LIBRARY DESTINATION Library/Audio/Plug-Ins/VST3
		COMPONENT VST3)



	install(TARGETS Template_Standalone
		BUNDLE DESTINATION "Applications"
		COMPONENT Standalone)


	# most CPACK_xxx vars are guessed from project properties
	set(CPACK_GENERATOR productbuild)
	set(CPACK_PACKAGE_VENDOR Fred)
	include(CPack)



elseif(UNIX)

	install(TARGETS Template_VST3 
		LIBRARY DESTINATION "lib/vst3"
		COMPONENT VST3)



	install(TARGETS Template_Standalone
        RUNTIME DESTINATION bin)


elseif(WIN32)
    set(CMAKE_INSTALL_PREFIX "C:/Users/faure")  # Modifiez ce chemin si nécessaire

    install(TARGETS Template
        LIBRARY DESTINATION "VST3"
        COMPONENT VST3)
		
    install(TARGETS Template_Standalone
        RUNTIME DESTINATION "Template"
        COMPONENT Standalone)

    # Configure CPack for Windows packaging
    set(CPACK_GENERATOR "NSIS")  # NSIS est un générateur pour créer des installateurs Windows
    set(CPACK_PACKAGE_NAME "Template")
    set(CPACK_PACKAGE_VENDOR "Fred")
    set(CPACK_PACKAGE_VERSION ${VERSION_CONTENT})  # Utilise la version définie précédemment
    set(CPACK_PACKAGE_DESCRIPTION "Template plugin for audio processing")
    set(CPACK_NSIS_INSTALL_ROOT "C:/Users/faure")
    set(CPACK_NSIS_DISPLAY_NAME "Template Audio Plugins")
    include(CPack)
endif()

