# ================================================
# Script PowerShell pour compiler un projet JUCE
# Compatible PowerShell Windows
# Options : --release / --fast
# ================================================

param(
    [string]$mode = ""
)

# Déduit le chemin du répertoire JUCE_PROJ et du projet
$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$JUCE_PROJ = Split-Path $ScriptDir -Parent
$PROJECT = Split-Path $ScriptDir -Leaf
$JUCE_DIR = Join-Path $JUCE_PROJ "JUCE-master"
$BUILD_DIR = Join-Path $ScriptDir "build"

# Options par défaut
$BUILD_TYPE = "Debug"
$FULL_REBUILD = $true

# Lecture des options
switch ($mode) {
    "--release" { $BUILD_TYPE = "Release" }
    "--fast"    { $FULL_REBUILD = $false }
}

Write-Host "🚀 Compilation de $PROJECT [$BUILD_TYPE]"

# Vérification JUCE_DIR
if (-not (Test-Path (Join-Path $JUCE_DIR "CMakeLists.txt"))) {
    Write-Host "❌ Erreur : JUCE_DIR invalide ($JUCE_DIR)"
    exit 1
}

# Nettoyage build si nécessaire
if ($FULL_REBUILD) {
    Write-Host "🧹 Nettoyage du dossier build..."
    if (Test-Path $BUILD_DIR) { Remove-Item -Recurse -Force $BUILD_DIR }
    New-Item -ItemType Directory -Path $BUILD_DIR | Out-Null
}

Set-Location $BUILD_DIR

# Configuration CMake
if ($FULL_REBUILD -or -not (Test-Path "CMakeCache.txt")) {
    Write-Host "⚙️ Configuration CMake..."
    cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DJUCE_DIR=$JUCE_DIR ..
}

# Compilation
Write-Host "🛠️ Compilation en cours..."
cmake --build . --config $BUILD_TYPE

# Packaging (optionnel)
if ($FULL_REBUILD) {
    Write-Host "📦 Packaging avec cpack..."
    try {
        cpack .
    } catch {
        Write-Host "⚠️ Aucun package généré (facultatif)"
    }
}

# Message final
Write-Host "✅ Compilation réussie."
Write-Host "▶️ Étape suivante : .\\3_exec.ps1"
