#--- SCRIPT DE COMPILATION AVEC CMAKE POUR WINDOWS

# Créer le dossier de build s'il n'existe pas
$buildPath = "C:\Users\$env:USERNAME\TP\juce_template-main\build"
if (-Not (Test-Path -Path $buildPath)) {
    New-Item -ItemType Directory -Path $buildPath
}

# Se déplacer dans ce nouveau repertoire
Set-Location $buildPath


# Définir la variable d'environnement pour JUCE_DIR
$env:JUCE_DIR="C:\Users\$env:USERNAME\TP\JUCE-master\build\JUCE"

# Générer les fichiers make avec cmake
cmake ..

# Compiler avec CMake 
cmake --build . --config Release


# Se déplacer 
Set-Location "C:\Users\$env:USERNAME\TP"

