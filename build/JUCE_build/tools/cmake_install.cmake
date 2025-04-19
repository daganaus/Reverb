# Install script for directory: /home/faure/c++/musique/JUCE_fred/JUCE-master

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/bin/objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/faure/c++/musique/JUCE_fred/Template/build/JUCE_build/tools/modules/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/faure/c++/musique/JUCE_fred/Template/build/JUCE_build/tools/extras/Build/cmake_install.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/JUCE-8.0.1" TYPE FILE FILES
    "/home/faure/c++/musique/JUCE_fred/Template/build/JUCE_build/tools/JUCEConfigVersion.cmake"
    "/home/faure/c++/musique/JUCE_fred/Template/build/JUCE_build/tools/JUCEConfig.cmake"
    "/home/faure/c++/musique/JUCE_fred/JUCE-master/extras/Build/CMake/JUCECheckAtomic.cmake"
    "/home/faure/c++/musique/JUCE_fred/JUCE-master/extras/Build/CMake/JUCEHelperTargets.cmake"
    "/home/faure/c++/musique/JUCE_fred/JUCE-master/extras/Build/CMake/JUCEModuleSupport.cmake"
    "/home/faure/c++/musique/JUCE_fred/JUCE-master/extras/Build/CMake/JUCEUtils.cmake"
    "/home/faure/c++/musique/JUCE_fred/JUCE-master/extras/Build/CMake/JuceLV2Defines.h.in"
    "/home/faure/c++/musique/JUCE_fred/JUCE-master/extras/Build/CMake/LaunchScreen.storyboard"
    "/home/faure/c++/musique/JUCE_fred/JUCE-master/extras/Build/CMake/PIPAudioProcessor.cpp.in"
    "/home/faure/c++/musique/JUCE_fred/JUCE-master/extras/Build/CMake/PIPAudioProcessorWithARA.cpp.in"
    "/home/faure/c++/musique/JUCE_fred/JUCE-master/extras/Build/CMake/PIPComponent.cpp.in"
    "/home/faure/c++/musique/JUCE_fred/JUCE-master/extras/Build/CMake/PIPConsole.cpp.in"
    "/home/faure/c++/musique/JUCE_fred/JUCE-master/extras/Build/CMake/RecentFilesMenuTemplate.nib"
    "/home/faure/c++/musique/JUCE_fred/JUCE-master/extras/Build/CMake/UnityPluginGUIScript.cs.in"
    "/home/faure/c++/musique/JUCE_fred/JUCE-master/extras/Build/CMake/checkBundleSigning.cmake"
    "/home/faure/c++/musique/JUCE_fred/JUCE-master/extras/Build/CMake/copyDir.cmake"
    "/home/faure/c++/musique/JUCE_fred/JUCE-master/extras/Build/CMake/juce_runtime_arch_detection.cpp"
    "/home/faure/c++/musique/JUCE_fred/JUCE-master/extras/Build/CMake/juce_LinuxSubprocessHelper.cpp"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/faure/c++/musique/JUCE_fred/Template/build/JUCE_build/tools/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
